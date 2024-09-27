#pragma once
#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>
#include <CGAL/Interval_nt.h>
#define USE_PROTECTOR 1
namespace CABT
{
#if USE_PROTECTOR
    typedef CGAL::Interval_nt<false> scalar;
#else
    typedef CGAL::Interval_nt<> scalar;
#endif
    typedef Eigen::Matrix<scalar, -1, -1> MatrixXs;
    typedef Eigen::Matrix<scalar, 3, 10> mat3_10;
    typedef Eigen::Matrix<scalar, 3, 20> mat3_20;
    typedef Eigen::Matrix<scalar, 3, 84> mat3_84;
    typedef Eigen::Matrix<scalar, 3, 1> vec3s;
    typedef Eigen::Matrix<scalar, 4, 1> vec4s;
    typedef Eigen::Matrix<scalar, 20, 1> vec20s;
    typedef Eigen::Matrix<scalar, 84, 1> vec84s;
    typedef Eigen::Matrix<scalar, 20, 4> mat20_4;
    typedef Eigen::Matrix<scalar, 20, 20> mat20_20;
    typedef Eigen::Matrix<scalar, 84, 4> mat84_4;
    typedef Eigen::Matrix<scalar, 84, 84> mat84_84;
    typedef Eigen::Matrix<scalar, 3, 3> mat3_3;
    typedef Eigen::Matrix<scalar, 4, 4> mat4_4;
    typedef Eigen::Tensor<scalar, 3> tensor3s;
    typedef Eigen::Tensor<int, 3> tensor3i;
}