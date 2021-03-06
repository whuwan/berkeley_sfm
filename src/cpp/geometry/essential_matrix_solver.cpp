/*
 * Copyright (c) 2015, The Regents of the University of California (Regents).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *    3. Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Please contact the author(s) of this library if you have any questions.
 * Authors: David Fridovich-Keil   ( dfk@eecs.berkeley.edu )
 *          Erik Nelson            ( eanelson@eecs.berkeley.edu )
 */

///////////////////////////////////////////////////////////////////////////////
//
// This header defines a set of functions for converting a fundamental matrix
// and a pair of camera intrinsics into an essential matrix, and from an
// essential matrix to and a set of camera extrinsics.
//
///////////////////////////////////////////////////////////////////////////////

#include "essential_matrix_solver.h"

#include <Eigen/Core>
#include <Eigen/LU>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <vector>

#include "point_3d.h"
#include "triangulation.h"
#include "../camera/camera.h"

DEFINE_double(min_points_visible_ratio, 0.3,
              "Fraction of keypoint matches whose triangulation must be "
              "visible from both cameras. This value should be lowered if you "
              "expect lots of noisy matches.");

namespace bsfm {

// Compute the essential matrix from a fundamental matrix and camera intrinsics.
Matrix3d EssentialMatrixSolver::ComputeEssentialMatrix(
    const Matrix3d& F, const CameraIntrinsics& intrinsics1,
    const CameraIntrinsics& intrinsics2) {
  // Extract intrinsics matrices.
  Matrix3d K1(intrinsics1.K());
  Matrix3d K2(intrinsics2.K());

  // Calculate the essential matrix.
  return K2.transpose() * F * K1;
}

// Compute the relative transformation between two cameras from an essential
// matrix and a list of keypoint matches. Note that translation can only be
// computed up to a scale factor.
// NOTE: this implementation is based on Hartley & Zisserman's MVG, pg. 258.
bool EssentialMatrixSolver::ComputeExtrinsics(
    const Matrix3d& E, const FeatureMatchList& matches,
    const CameraIntrinsics& intrinsics1, const CameraIntrinsics& intrinsics2,
    Pose& relative_pose) {
  // Initialize the W matrix.
  Matrix3d W;
  W << 0.0, -1.0, 0.0,
       1.0,  0.0, 0.0,
       0.0,  0.0, 1.0;

  // Perform an SVD on the essential matrix.
  Eigen::JacobiSVD<Matrix3d> svd;
  svd.compute(E, Eigen::ComputeFullU | Eigen::ComputeFullV);
  if (!svd.computeU() || !svd.computeV()) {
    VLOG(1) << "Failed to compute a singular value decomposition of "
            << "the essential matrix.";
    return false;
  }

  // The essential matrix must satisfy E = U * diag(1, 1, 0) * V^T. Use U and V
  // to get a new E, run another SVD, and get the normalized U and V.
  Matrix3d sigma(Matrix3d::Identity());
  sigma(2, 2) = 0;
  Matrix3d E_augmented = svd.matrixU() * sigma * svd.matrixV().transpose();

  svd.compute(E_augmented, Eigen::ComputeFullU | Eigen::ComputeFullV);
  if (!svd.computeU() || !svd.computeV()) {
    VLOG(1) << "Failed to compute a singular value decomposition of "
            << "the essential matrix.";
    return false;
  }

  // Compute two possibilities for rotation.
  Matrix3d R1 = svd.matrixU() * W * svd.matrixV().transpose();
  Matrix3d R2 = svd.matrixU() * W.transpose() * svd.matrixV().transpose();

  // Ensure positive determinants.
  if (R1.determinant() < 0)
    R1 = -R1;
  if (R2.determinant() < 0)
    R2 = -R2;

  // Compute two possibilities for translation
  Vector3d t1, t2;
  t1 = svd.matrixU().col(2);
  t2 = -t1;

  // Build four possible Poses.
  std::vector<Pose> poses;
  poses.push_back(Pose(R1, t1));
  poses.push_back(Pose(R1, t2));
  poses.push_back(Pose(R2, t1));
  poses.push_back(Pose(R2, t2));

  // Set the first camera's position to identity in rotation and translation.
  CameraExtrinsics extrinsics1;
  extrinsics1.SetWorldToCamera(Pose());

  Camera camera1;
  camera1.SetExtrinsics(extrinsics1);
  camera1.SetIntrinsics(intrinsics1);

  // Test how many points are in front of each pose and the identity pose.
  Pose best_pose;
  int best_num_points = -1;

  double u = 0.0, v = 0.0;
  for (int ii = 0; ii < poses.size(); ii++) {
    int num_points = 0;

    CameraExtrinsics extrinsics2;
    extrinsics2.SetWorldToCamera(poses[ii]);

    Camera camera2;
    camera2.SetExtrinsics(extrinsics2);
    camera2.SetIntrinsics(intrinsics2);

    for (int jj = 0; jj < matches.size(); jj++) {
      // Triangulate points and test if the 3D estimate is in front of both
      // cameras.
      Point3D point;
      double unused = 0.0;
      if (!Triangulate(matches[jj], camera1, camera2, point, unused)) {
        continue;
      }

      num_points++;
    }

    // Update best_num_points and best_pose.
    if (num_points > best_num_points) {
      best_num_points = num_points;
      best_pose = poses[ii];
    }
  }

  // Return with false if not enough points found in front of the cameras.
  if (best_num_points < FLAGS_min_points_visible_ratio * matches.size()) {
    VLOG(1) << "Did not find enough points in front of both cameras.";
    return false;
  }

  relative_pose = best_pose;

  return true;
}

}  //\namespace bsfm
