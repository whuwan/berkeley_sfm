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
// This class defines the FundamentalMatrixRansacModel class, which
// is derived from the abstract base class RansacModel.
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <Eigen/Core>
#include <gflags/gflags.h>
#include <vector>

#include "ransac_problem.h"
#include "fundamental_matrix_ransac_problem.h"
#include "../math/random_generator.h"
#include "../geometry/eight_point_algorithm_solver.h"
#include "../geometry/fundamental_matrix_solver_options.h"

DEFINE_int64(subsample_size, 8,
             "Number of points required for each minimal sampling in RANSAC.");

namespace bsfm {

// ------------ FundamentalMatrixRansacModel methods ------------ //

// Default constructor.
FundamentalMatrixRansacModel::FundamentalMatrixRansacModel()
    : F_(Eigen::Matrix3d::Identity()), error_(0.0) {}

FundamentalMatrixRansacModel::FundamentalMatrixRansacModel(
    const Eigen::Matrix3d& F)
    : F_(F), error_(0.0) {}

// Destructor.
FundamentalMatrixRansacModel::~FundamentalMatrixRansacModel() {}

// Return model error.
double FundamentalMatrixRansacModel::Error() const {
  return error_;
}

// Evaluate model on a single data element and update error.
bool FundamentalMatrixRansacModel::IsGoodFit(
    const FeatureMatch& data_point,
    double error_tolerance) {
  // Construct vectors for 2D keypoints in match.
  Eigen::Vector3d kp1, kp2;
  kp1 << data_point.feature1_.u_, data_point.feature1_.v_, 1;
  kp2 << data_point.feature2_.u_, data_point.feature2_.v_, 1;

  // Compute error and record its square.
  const double epipolar_condition = kp1.transpose() * F_ * kp2;
  error_ = epipolar_condition * epipolar_condition;

  // Test against the provided tolerance.
  if (error_ < error_tolerance) return true;
  return false;
}

// ------------ FundamentalMatrixRansacProblem methods ------------ //

// RansacProblem constructor.
FundamentalMatrixRansacProblem::FundamentalMatrixRansacProblem() {}

// RansacProblem destructor.
FundamentalMatrixRansacProblem::~FundamentalMatrixRansacProblem() {}

// Subsample the data.
std::vector<FeatureMatch> FundamentalMatrixRansacProblem::SampleData() {
  // Randomly shuffle the entire dataset and take the first 8 elements.
  std::random_shuffle(data_.begin(), data_.end());

  // Make sure we don't over step.
  const size_t max_num_samples =
      std::min<size_t>(data_.size(), FLAGS_subsample_size);
  CHECK(max_num_samples >= 0);

  // Get samples.
  std::vector<FeatureMatch> samples(
      data_.begin(), data_.begin() + max_num_samples);

  return samples;
}

// Return all data that was not sampled.
std::vector<FeatureMatch> FundamentalMatrixRansacProblem::RemainingData()
    const {
  // In Sample(), the data was shuffled and we took the first
  // FLAGS_subsample_size - 1 elements. Here, take the remaining elements.
  if (static_cast<size_t>(FLAGS_subsample_size) >= data_.size()) {
    return std::vector<FeatureMatch>();
  }
  CHECK(FLAGS_subsample_size >= 0);

  return std::vector<FeatureMatch>(
      data_.begin() + FLAGS_subsample_size, data_.end());
}

// Fit a model to the provided data using the 8-point algorithm.
FundamentalMatrixRansacModel FundamentalMatrixRansacProblem::FitModel(
    const std::vector<FeatureMatch>& input_data) const {
  // Create an empty fundamental matrix.
  Eigen::Matrix3d F;

  // Run the 8-point algorithm with default options.
  EightPointAlgorithmSolver solver;
  solver.SetOptions(FundamentalMatrixSolverOptions());

  // Convert data to an input that is useable by the solver.
  std::vector<FeatureMatch> solver_input_data;
  for (const auto& data_point : input_data) {
    solver_input_data.push_back(data_point);
  }

  if (solver.ComputeFundamentalMatrix(solver_input_data, F)) {
    return FundamentalMatrixRansacModel(F);
  }
  return FundamentalMatrixRansacModel(Eigen::Matrix3d::Identity());
}

}  //\namespace bsfm