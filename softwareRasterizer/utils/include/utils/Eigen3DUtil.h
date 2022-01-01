//
//  Eigen3DUtil.hpp
//  OpenGLESDemo
//
//  Created by jerry on 2020/11/21.
//  Copyright © 2020 tencent. All rights reserved.
//

#ifndef Eigen3DUtil_hpp
#define Eigen3DUtil_hpp

#include <stdio.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

class Eigen3DUtil {
public:
    enum class Projection : int {
        PERSPECTIVE,
        ORTHO
    };
    enum class Fov : int {
        VERTICAL,
        HORIZONTAL
    };
    static Eigen::Matrix4f lookAt(const Eigen::Vector3f& eye, const Eigen::Vector3f& center, const Eigen::Vector3f& up = Eigen::Vector3f(0,1,0)) noexcept;
    static Eigen::Matrix4f getProjection(Projection projection, double left, double right, double bottom, double top, double near, double far) noexcept;
    static Eigen::Matrix4f getProjection(float fov, float aspect, float near, float far, Fov direction = Fov::VERTICAL) noexcept;
private:
    static Eigen::Matrix4f frustum(float left, float right, float bottom, float top, float near, float far) noexcept;
    static Eigen::Matrix4f ortho(float left, float right, float bottom, float top, float near, float far) noexcept;
};
#endif /* Eigen3DUtil_hpp */
