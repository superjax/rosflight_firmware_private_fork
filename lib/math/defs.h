#ifndef ROSFLIGHT_FIRMWARE_MATH_DEFS_H
#define ROSFLIGHT_FIRMWARE_MATH_DEFS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wlogical-op"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#include <Eigen/Core>
#include <Eigen/Geometry>
#pragma GCC diagnostic pop

namespace rosflight_math
{

// Use this to change all quaternion implemention to use float or f_t
#ifdef MATH_USE_DOUBLE
    typedef double f_t;
#else
    typedef float f_t;
#endif
typedef Eigen::Matrix<f_t, 4, 1> Vec4;
typedef Eigen::Matrix<f_t, 3, 1> Vec3;
typedef Eigen::Matrix<f_t, 3, 3> Mat33;

#ifndef DEG2RAD
#define DEG2RAD 0.01745327
#endif
#ifndef RAD2DEG
#define RAD2DEG 57.295827
#endif

} // namespace rosflight_math

#endif // ROSFLIGHT_FIRMWARE_MATH_DEFS_H
