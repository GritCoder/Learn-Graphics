//
//  Eigen3DUtil.cpp
//  OpenGLESDemo
//
//  Created by jerry on 2020/11/21.
//  Copyright © 2020 tencent. All rights reserved.
//

#include "utils/Eigen3DUtil.h"

using namespace Eigen;

//返回的是相机的 view matrix
Matrix4f Eigen3DUtil::lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up) noexcept {
    Vector3f z_axis((center - eye).normalized());
    Vector3f norm_up(up.normalized());
    if (std::abs(z_axis.dot(norm_up)) > 0.999) {
        // Fix up vector if we're degenerate (looking straight up, basically)
        norm_up = { norm_up.z(), norm_up.x(), norm_up.y()};
    }
    Vector3f x_axis(z_axis.cross(norm_up).normalized());
    Vector3f y_axis(x_axis.cross(z_axis));
    Matrix4f ret;
    ret << x_axis.x(), y_axis.x(), -z_axis.x(), eye.x(),
           x_axis.y(), y_axis.y(), -z_axis.y(), eye.y(),
           x_axis.z(), y_axis.z(), -z_axis.z(), eye.z(),
           0,0,0,1;
    return ret.inverse().eval();
}

Matrix4f Eigen3DUtil::frustum(float left, float right, float bottom, float top, float near, float far) noexcept {
    Matrix4f m = Matrix4f::Identity();
    m(0,0) = (2 * near) / (right - left);
    m(1,1) = (2 * near) / (top - bottom);
    m(0,2) = (right + left) / (right - left);
    m(1,2) = (top + bottom) / (top - bottom);
    m(2,2) = -(far + near) / (far - near);
    m(3,2) = -1;
    m(2,3) = -(2 * far * near) / (far - near);
    m(3,3) = 0;
    return m;
}

Matrix4f Eigen3DUtil::ortho(float left, float right, float bottom, float top, float near, float far) noexcept {
    Matrix4f m = Matrix4f::Identity();
    m(0,0) = 2 / (right - left);
    m(1,1) = 2 / (top - bottom);
    m(2,2) = -2 / (far - near);
    m(0,3) = -(right + left) / (right - left);
    m(1,3) = -(top + bottom) / (top - bottom);
    m(2,3) = -(far + near) / (far - near);
    return m;
}

Eigen::Matrix4f Eigen3DUtil::getProjection(float fov, float aspect, float near, float far, Fov direction) noexcept {
    float w, h;
    float s = std::tan(fov * (3.14159265358979323846264338327950288 / 360.0)) * near;
    if (direction == Fov::VERTICAL) {
        w = s * aspect;
        h = s;
    } else {
        w = s;
        h = s / aspect;
    }
    return getProjection(Projection::PERSPECTIVE, -w, w, -h, h, near, far);
}

Eigen::Matrix4f Eigen3DUtil::getProjection(Projection projection, double left, double right, double bottom, double top, double near, double far) noexcept {
    // we make sure our preconditions are verified, using default values,
        // to avoid inconsistent states in the renderer later.
    if (left == right ||
        bottom == top ||
        (projection == Projection::PERSPECTIVE && (near <= 0 || far <= near)) ||
        (projection == Projection::ORTHO && (near == far))) {
        assert("Camera preconditions not met. Using default projection.");
        left = -0.1;
        right = 0.1;
        bottom = -0.1;
        top = 0.1;
        near = 0.1;
        far = 100.0;
    }
    Matrix4f p = Matrix4f::Zero();
    switch (projection) {
        case Projection::PERSPECTIVE:
            /*
             * The general perspective projection looks like this:
             *
             * P =  2N/r-l    0      r+l/r-l        0
             *       0      2N/t-b   t+b/t-b        0
             *       0        0      F+N/N-F   2*F*N/N-F
             *       0        0        -1           0
             */
            p = frustum(left, right, bottom, top, near, far);
            /*
             * we're using a far plane at infinity
             *
             * P =  2N/r-l      0    r+l/r-l        0
             *       0      2N/t-b   t+b/t-b        0
             *       0       0         -1        -2*N    <-- far at infinity
             *       0       0         -1           0
             */
            p(2,2) = -1;           // lim(far->inf) = -1
            p(2,3) = -2 * near;    // lim(far->inf) = -2*near

            /*
             * e.g.: A symmetrical frustum with far plane at infinity
             *
             * P =  N/r      0       0      0
             *       0      N/t      0      0
             *       0       0      -1    -2*N
             *       0       0      -1      0
             *
             * v(CC) = P*v
             * v(NDC) = v(CC) * (1 / v(CC).w)
             *
             * for v in the frustum, P generates v(CC).xyz in [-1, 1]
             *
             * v(WC).z = v(NDC).z * (f-n)*0.5 + (n+f)*0.5
             *         = v(NDC).z * 0.5 + 0.5
             */
            break;

        case Projection::ORTHO:
            /*
             * The general orthographic projection looks like this:
             *
             * P =  2/r-l    0         0       - r+l/r-l
             *       0      2/t-b      0       - t+b/t-b
             *       0       0       -2/F-N    - F+N/F-N
             *       0       0         0            1
             */
            p = ortho(left, right, bottom, top, near, far);
            break;
    }
    return p;
}
