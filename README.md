# Shape interpolation framework for quadratic tetrahedral meshes in 3D

This program is used to interpolate two regular quadratic Bezier tetrahedral meshes. For the implementation of higher-order Bezier meshes, you can refer to this framework.

## External Libraries

* [Eigen](http://eigen.tuxfamily.org/)
* [OpenMesh](https://www.openmesh.org/), Recommended version: the latest 8.1(at Oct. 2020)
* [Qt](https://www.qt.io/), Recommended version: 5.13.0
* [Mkl]https://software.intel.com/en-us/mkl

## Usage

Edit lines 7-9 of CmakeLists.txt to set the values of **EIGEN_PATH**,**OPENMESH_PATH** and **OPENMESH_LIB_PATH**
```
mkdir build && cd build
cmake -A x64 ..
```

Open **SurfaceFramework.sln**, select **SrufaceFramework** as launch project, and run.

High-order mesh deformation: click the button 'Perform Curve Deformation' on the left;
High-order mesh shape interpolation: Click the button 'Perform Curve Morphing' on the left.

