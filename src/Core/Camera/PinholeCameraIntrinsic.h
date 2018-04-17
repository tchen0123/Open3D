// ----------------------------------------------------------------------------
// -                        Open3D: www.open-3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Initial project was copyrighted (c) 2016-2018, www.open3d.org
// A fork of their project is avilable at www.github.com/Sahloul/Open3D-legacy
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

#include <Eigen/Core>
#include <IO/ClassIO/IJsonConvertible.h>

namespace three {

class PinholeCameraIntrinsic : public IJsonConvertible
{
public:
    static const PinholeCameraIntrinsic PrimeSenseDefault;

public:
    PinholeCameraIntrinsic();
    PinholeCameraIntrinsic(int width, int height, double fx, double fy,
            double cx, double cy);
    ~PinholeCameraIntrinsic() override;

public:
    void SetIntrinsics(int width, int height, double fx, double fy, double cx,
            double cy) {
        width_ = width; height_ = height;
        intrinsic_matrix_.setIdentity();
        intrinsic_matrix_(0, 0) = fx; intrinsic_matrix_(1, 1) = fy;
        intrinsic_matrix_(0, 2) = cx; intrinsic_matrix_(1, 2) = cy;
    }

    std::pair<double, double> GetFocalLength() const {
        return std::make_pair(intrinsic_matrix_(0, 0), intrinsic_matrix_(1, 1));
    }

    std::pair<double, double> GetPrincipalPoint() const {
        return std::make_pair(intrinsic_matrix_(0, 2), intrinsic_matrix_(1, 2));
    }

    double GetSkew() const { return intrinsic_matrix_(0, 1); }

    bool IsValid() const { return (width_ > 0 && height_ > 0); }

    bool ConvertToJsonValue(Json::Value &value) const override;
    bool ConvertFromJsonValue(const Json::Value &value) override;

public:
    int width_ = -1;
    int height_ = -1;
    Eigen::Matrix3d intrinsic_matrix_;
};

}   // namespace three
