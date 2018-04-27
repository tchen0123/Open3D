// ----------------------------------------------------------------------------
// -                        Open3D: www.open-3d.org                            -
// ----------------------------------------------------------------------------
// Imported on Apr 11th, 2018 from the Open3D project
// Copyright (c) 2018 www.open3d.org
// released under MIT licence
//
// A fork of their project is avilable at legacy-code.open-3d.org
// Refer to http://legacy-code.open-3d.org/blob/master/LICENSE
// for their full licence
// Check http://legacy-code.open-3d.org/graphs/contributors
// to get the list of their contributors and their contributions
//
// The rights of any later updates or modifications are reserved
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018, Hamdi Sahloul - www.open-3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <vector>
#include <tuple>
#include <Eigen/Core>
#include <Open3D/Core/Utility/IJsonConvertible.h>
#include <Open3D/Visualization/Visualizer/ViewParameters.h>

namespace open3d {

class ViewTrajectory : public IJsonConvertible
{
public:
    static const int32_t INTERVAL_MAX;
    static const int32_t INTERVAL_MIN;
    static const int32_t INTERVAL_STEP;
    static const int32_t INTERVAL_DEFAULT;

public:
    ViewTrajectory() {}
    ~ViewTrajectory() override {}

public:
    /// Function to compute a Cubic Spline Interpolation
    /// See this paper for details:
    /// Bartels, R. H.; Beatty, J. C.; and Barsky, B. A. "Hermite and Cubic
    /// Spline Interpolation." Ch. 3 in An Introduction to Splines for Use in
    /// Computer Graphics and Geometric Modelling. San Francisco, CA: Morgan
    /// Kaufmann, pp. 9-17, 1998.
    /// Also see explanation on this page:
    /// http://mathworld.wolfram.com/CubicSpline.html
    void ComputeInterpolationCoefficients();

    void ChangeInterval(int32_t change) {
        int32_t new_interval = interval_ + change * INTERVAL_STEP;
        if (new_interval >= INTERVAL_MIN && new_interval <= INTERVAL_MAX)
        {
            interval_ = new_interval;
        }
    }

    size_t NumOfFrames() const {
        if (view_status_.empty()) {
            return 0;
        } else {
            return is_loop_ ? (interval_ + 1) * view_status_.size() :
                    (interval_ + 1) * (view_status_.size() - 1) + 1;
        }
    }

    void Reset() {
        is_loop_ = false;
        interval_ = INTERVAL_DEFAULT;
        view_status_.clear();
    }

    std::tuple<bool, ViewParameters> GetInterpolatedFrame(uint32_t k);

    bool ConvertToJsonValue(Json::Value &value) const override;
    bool ConvertFromJsonValue(const Json::Value &value) override;

public:
    std::vector<ViewParameters> view_status_;
    bool is_loop_ = false;
    int32_t interval_ = INTERVAL_DEFAULT;
    std::vector<ViewParameters::Matrix17x4d> coeff_;
};

}   // namespace open3d
