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
 * Authors: Erik Nelson            ( eanelson@eecs.berkeley.edu )
 *          David Fridovich-Keil   ( dfk@eecs.berkeley.edu )
 */

///////////////////////////////////////////////////////////////////////////////
//
// This file defines distance metrics that can be used to compare feature
// descriptors to one another to e.g. find the closest match between images.
// Each distance metric struct should be a functor, defining three members:
//
// 1) A typedef'd Descriptor type.
// 2) operator(), which operates on two Descriptor types to compute a distance.
// 3) A 'RequiresNormalizedDescriptors' static method.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BSFM_MATCHING_DISTANCE_METRIC_H
#define BSFM_MATCHING_DISTANCE_METRIC_H

#include "descriptor_extractor.h"

#include <Eigen/Core>
#include <glog/logging.h>

namespace bsfm {

// Compute the L2 norm of the difference between two descriptor vectors. If both
// descriptors have unit length, the L2 norm is equal to 2*(1-x.y). Since all
// distances are computed this way, we can drop the leading 2*. The L2 norm
// induces an inner product space over R^{n}, and we can test as such.
struct ScaledL2Distance {
  // Descriptor type that ScaledL2Distance functor operates on.
  typedef Eigen::VectorXf Descriptor;

  // Functor method.
  float operator()(const Descriptor& descriptor1,
                    const Descriptor& descriptor2) {
    CHECK_EQ(descriptor1.size(), descriptor2.size());
    return 1.0f - descriptor1.dot(descriptor2);
  }

  static bool RequiresNormalizedDescriptors() { return true; }
};  //\struct ScaledL2Distance

}  //\namespace bsfm

#endif