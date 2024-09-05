#pragma once
#include "..\src\MeshViewer\MeshDefinition.h"
#include <Eigen/Core>
class bezier_triangle_mesh
{
public:
    bezier_triangle_mesh(int order_):order(order_){}
	~bezier_triangle_mesh(){}

public:
    Mesh mesh;
    const int order;

    Eigen::Matrix3Xd control_points;
    std::vector<OpenMesh::HalfedgeHandle> basis;
    std::vector<Eigen::MatrixXi> mesh_control_ids;

    void init();
};