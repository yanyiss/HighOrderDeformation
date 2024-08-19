#include "bezier_def.h"

void bezier_triangle_mesh::init()
{
	basis.resize(mesh.n_faces());
	mesh_control_ids.resize(mesh.n_faces());
	control_points.resize(3, mesh.n_vertices() + (order - 1) * mesh.n_edges() + std::max(0, (order - 1) * (order - 2) / 2) * mesh.n_faces());
	//半边的序号被2整除时，id的序号从小到大
	//  if order==6
	//  (0,6)
	//   .
	//   . .
	//   . . .
	//   . . . .
	//   . . . . .
	//   . . . . . .
	//   . . . . . . .
	// (0,0)         (6,0)
	for (auto tf : mesh.faces())
	{
		int fid = tf.idx();
		basis[fid] = mesh.fh_begin(tf);
		auto prev_h = mesh.prev_halfedge_handle(basis[fid]);
		auto next_h = mesh.next_halfedge_handle(basis[fid]);
		auto& control_id = mesh_control_ids[fid];

		control_id.resize(order + 1, order + 1);

		//for all vertices
		control_id(0, 0) = mesh.from_vertex_handle(basis[fid]).idx();
		control_id(order, 0) = mesh.to_vertex_handle(basis[fid]).idx();
		control_id(0, order) = mesh.to_vertex_handle(next_h).idx();

		//for all edges
		int start_id = mesh.n_vertices() + (order - 1) * (basis[fid].idx() / 2);
		if (basis[fid].idx() % 2 == 0)
			for (int i = 1; i < order; ++i)
				control_id(i, 0) = start_id + i - 1;
		else
			for (int i = 1; i < order; ++i)
				control_id(i, 0) = start_id + order - i - 1;
		start_id = mesh.n_vertices() + (order - 1) * (prev_h.idx() / 2);
		if (prev_h.idx() % 2 == 0)
			for (int i = 1; i < order; ++i)
				control_id(i, 0) = start_id + i - 1;
		else
			for (int i = 1; i < order; ++i)
				control_id(i, 0) = start_id + order - i - 1;
		start_id = mesh.n_vertices() + (order - 1) * (next_h.idx() / 2);
		if (next_h.idx() % 2 == 0)
			for (int i = 1; i < order; ++i)
				control_id(order - i, i) = start_id + i - 1;
		else
			for (int i = 1; i < order; ++i)
				control_id(i, order - i) = start_id + order - i - 1;

		//for all faces
		start_id = mesh.n_vertices() + (order - 1) * mesh.n_edges() + std::max(0, (order - 1) * (order - 2) / 2) * fid;
		for (int i = 1; i < order - 1; ++i)
		{
			for (int j = 1; j < order - i; ++j)
			{
				control_id(i, j) = start_id++;
			}
		}

		auto v0 = mesh.point(mesh.from_vertex_handle(basis[fid]));
		auto v1 = mesh.point(mesh.to_vertex_handle(basis[fid]));
		auto v2 = mesh.point(mesh.to_vertex_handle(next_h));
		//init control points position
		OpenMesh::Vec3d pos;
		for (int i = 0; i <= order; ++i)
		{
			for (int j = 0; j <= order - i; ++j)
			{
				pos = v0 + (i * 1.0 / order) * (v1 - v0) + (j * 1.0 / order) * (v2 - v0);
				control_points.col(control_id(i, j)) << pos[0], pos[1], pos[2];
			}
		}
	}
}