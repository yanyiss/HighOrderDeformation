#include <iostream>
#include <algorithm>
#include <cmath>

#include <qapplication.h>

#include <OpenMesh/Core/Utils/vector_cast.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>

#include "MeshViewerWidget.h"
#include "../Common/CommonDefinitions.h"
#include "BezierCurve.h"

#include "SamplingOptimization.h"
#include "Deformation.h"
 
using namespace Qt;

MeshViewerWidget::MeshViewerWidget(QWidget* parent)
	: QGLViewerWidget(parent)
{
	mesh.request_vertex_status();
	mesh.request_edge_status();
	mesh.request_face_status();

	mesh.request_face_normals();
	mesh.request_vertex_normals();

	rendermesh.request_vertex_texcoords2D(); 
	samplemesh.request_vertex_texcoords2D(); 

	mesh_vector.clear(); mesh_vector_index = -1;

	draw_BBox_OK = false;
	draw_mesh_boundary_ok = false;
	first_init = true;

	is_cal_curve_box_finished = false; 
	V_N = 0;
	sur_V_num = 0;
	sur_Ver_num = 0;
	tri_F_num = 0;
}

MeshViewerWidget::MeshViewerWidget(QGLFormat& _fmt, QWidget* _parent)
	: QGLViewerWidget(_fmt, _parent)
{
	mesh.request_vertex_status();
	mesh.request_edge_status();
	mesh.request_face_status();

	mesh.request_face_normals();
	mesh.request_vertex_normals();

	rendermesh.request_vertex_texcoords2D(); 
	samplemesh.request_vertex_texcoords2D(); 

	mesh_vector.clear(); mesh_vector_index = -1;

	draw_BBox_OK = false;
	draw_mesh_boundary_ok = false;
	first_init = true;

	is_cal_curve_box_finished = false; 
	V_N = 0;
	sur_V_num = 0;
	sur_Ver_num = 0;
	tri_F_num = 0;
}

MeshViewerWidget::~MeshViewerWidget()
{
}

void MeshViewerWidget::updateMeshCenter()
{
	typedef Mesh::Point Point;
	Mesh::VertexIter vIt = mesh.vertices_begin();
	Mesh::VertexIter vEnd = mesh.vertices_end();
	bbMin = bbMax = OpenMesh::vector_cast<OpenMesh::Vec3d>(mesh.point(vIt));

	size_t count = 0;
	for (; vIt != vEnd; ++vIt, ++count)
	{
		bbMin.minimize(OpenMesh::vector_cast<OpenMesh::Vec3d>(mesh.point(vIt)));
		bbMax.maximize(OpenMesh::vector_cast<OpenMesh::Vec3d>(mesh.point(vIt)));
	}

	Mesh::EdgeIter e_it = mesh.edges_begin();
	Mesh::EdgeIter e_end = mesh.edges_end();
	double aveLen = 0.0; double maxLen = 0.0; double minLen = mesh.calc_edge_length(e_it);
	double e_len = 0.0;
	for (; e_it != e_end; ++e_it)
	{
		double e_len = mesh.calc_edge_length(e_it);
		if (e_len > maxLen)
		{
			maxLen = e_len;
		}
		else if (e_len < minLen)
		{
			minLen = e_len;
		}
		aveLen += e_len;
	}

	// set center and radius and box's radius.
	/*OpenMesh::Vec3d c = (bbMin + bbMax)*0.5;
	for (vIt = mesh.vertices_begin(); vIt != vEnd; ++vIt, ++count)
	{
		OpenMesh::Vec3d p = mesh.point(vIt) - c;
		mesh.set_point(vIt, p);
	}*/

	if (first_init)
	{
		set_scene_pos((bbMin + bbMax) * 0.5, (bbMin - bbMax).norm() * 0.5);
		first_init = false;
	}
	else
	{
		set_scene_pos((bbMin + bbMax) * 0.5, (bbMin - bbMax).norm() * 0.5);
	}

	OpenMesh::Vec3d center = (bbMin + bbMax) * 0.5;

	printf("BoundingBox:\nX : [ %f , %f ]\n", bbMin[0], bbMax[0]);
	printf("Y : [ %f , %f ]\n", bbMin[1], bbMax[1]);
	printf("Z : [ %f , %f ]\n", bbMin[2], bbMax[2]);
	printf("BoundingBox center: [%.8f ,%.8f,%.8f]\n", center[0], center[1], center[2]);
	printf("Diag length of BBox : %f\n", (bbMax - bbMin).norm());
	printf("Edge Length : Max : %f; Min : %f; AVG : %f\n", maxLen, minLen, aveLen / mesh.n_edges());
}

void MeshViewerWidget::updateMeshNormals()
{
	mesh.update_face_normals();
	mesh.update_vertex_normals();
}
 

bool MeshViewerWidget::openMesh(const char* filename)
{
	clearAllMesh();
	bool read_OK = OpenMesh::IO::read_mesh(mesh, filename);

	printf("%s\n", filename);
	if (read_OK)
	{
		initMesh();
		/*Mesh::EdgeHandle eh0 = mesh.edge_handle(960);
		flip_openmesh(eh0, mesh);
		Mesh::EdgeHandle eh1 = mesh.edge_handle(85);
		flip_openmesh(eh1, mesh);*/
		/*FILE* f_de = fopen("b.de", "w");
		for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
		{
			if (mesh.is_boundary(v_it))
			{
				OpenMesh::Vec3d& p = mesh.point(v_it);
				fprintf(f_de, "%d %15.14f %15.14f\n", v_it.handle().idx(), p[0], p[1]);
			}
		}
		fclose(f_de);*/
		// loading done
		mesh_vector.push_back(mesh); mesh_vector_index = 0;
		return true;
	}
	return false;
}

void MeshViewerWidget::initMesh()
{
	mesh.request_vertex_status();
	mesh.request_edge_status();
	mesh.request_face_status();

	mesh.request_face_normals();
	mesh.request_vertex_normals();
	printBasicMeshInfo();
	updateMesh();
}

void MeshViewerWidget::printBasicMeshInfo()
{
	if (mesh.n_vertices() == 0)
		printf("No Mesh\n");

	checkMeshMode();

	QString meshType;
	switch (meshMode())
	{
	case TRIANGLE:
		printf("Triangle Mesh.\n");
		break;
	case QUAD:
		printf("Quadrilateral Mesh.\n");
		break;
	default:
		printf("General Mesh.\n");
		break;
	}

	printf("Information of the input mesh:\nVertex : %d;\nFace : %d;\nEdge : %d, HalfEdge : %d\n",
		mesh.n_vertices(), mesh.n_faces(), mesh.n_edges(), mesh.n_halfedges());;

	//
	/*for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		OpenMesh::Vec3d& p = mesh.point(v_it);
		p[2] = 0.0;
	}*/

	//save tet mesh
	/*int nf = mesh.n_faces(); int nv = mesh.n_vertices(); int ne = mesh.n_edges();
	std::vector<OpenMesh::Vec3d> face_n(nf);
	std::vector<double> edge_len(ne);
	for (Mesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		std::vector<OpenMesh::Vec3d> one_face;
		for (Mesh::FaceVertexIter fv_it = mesh.fv_iter(f_it); fv_it; ++fv_it)
		{
			one_face.push_back(mesh.point(fv_it));
		}
		OpenMesh::Vec3d n = OpenMesh::cross(one_face[1] - one_face[0], one_face[2] - one_face[0]);
		face_n[f_it->idx()] = n.normalize();
	}
	for (Mesh::EdgeIter e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it)
	{
		edge_len[e_it->idx()] = mesh.calc_edge_length(e_it);
	}
	std::vector<OpenMesh::Vec3d> v_v(nv);
	for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		double ave_edge_len = 0.0; OpenMesh::Vec3d vn(0, 0, 0); int edge_count = 0;
		for (Mesh::VertexOHalfedgeIter voh_it = mesh.voh_iter(v_it); voh_it; ++voh_it)
		{
			ave_edge_len += edge_len[mesh.edge_handle(voh_it).idx()]; edge_count += 1;
			Mesh::FaceHandle fh = mesh.face_handle(voh_it);
			if (fh != Mesh::InvalidFaceHandle)
			{
				vn += face_n[fh.idx()];
			}
		}
		vn.normalize();
		v_v[v_it->idx()] = mesh.point(v_it) - vn*ave_edge_len / edge_count;
	}
	std::vector<std::vector<int>> all_tets(nf*6);
	for (Mesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		std::vector<int> one_face;
		for (Mesh::FaceVertexIter fv_it = mesh.fv_iter(f_it); fv_it; ++fv_it)
		{
			one_face.push_back( fv_it->idx() );
		}
		int f_id = f_it->idx();
		std::vector<int> one_tet(4);
		one_tet[0] = one_face[0]; one_tet[1] = one_face[2]; one_tet[2] = one_face[1]; one_tet[3] = one_face[0] + nv;
		all_tets[6 * f_id + 0] = one_tet;
		one_tet[0] = one_face[0]; one_tet[1] = one_face[2]; one_tet[2] = one_face[1]; one_tet[3] = one_face[1] + nv;
		all_tets[6 * f_id + 1] = one_tet;
		one_tet[0] = one_face[0]; one_tet[1] = one_face[2]; one_tet[2] = one_face[1]; one_tet[3] = one_face[2] + nv;
		all_tets[6 * f_id + 2] = one_tet;
		one_tet[0] = one_face[0] + nv; one_tet[1] = one_face[1] + nv; one_tet[2] = one_face[2] + nv; one_tet[3] = one_face[0];
		all_tets[6 * f_id + 3] = one_tet;
		one_tet[0] = one_face[0] + nv; one_tet[1] = one_face[1] + nv; one_tet[2] = one_face[2] + nv; one_tet[3] = one_face[1];
		all_tets[6 * f_id + 4] = one_tet;
		one_tet[0] = one_face[0] + nv; one_tet[1] = one_face[1] + nv; one_tet[2] = one_face[2] + nv; one_tet[3] = one_face[2];
		all_tets[6 * f_id + 5] = one_tet;
	}

	FILE* f_tet = fopen("tet.tet", "w");
	fprintf(f_tet, "Vertices %d", nv+nv);
	for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		OpenMesh::Vec3d p = mesh.point(v_it);
		fprintf(f_tet, "\n%.19f %.19f %.19f", p[0], p[1], p[2]);
	}
	for (int i = 0; i < nv;++i)
	{
		fprintf(f_tet, "\n%.19f %.19f %.19f", v_v[i][0], v_v[i][1], v_v[i][2]);
	}
	fprintf(f_tet, "\nTetrahedra %d", nf*6);
	for (int i = 0; i < all_tets.size(); ++i)
	{
		fprintf(f_tet, "\n%d %d %d %d", all_tets[i][0] + 1, all_tets[i][1] + 1, all_tets[i][2] + 1, all_tets[i][3] + 1);
	}
	fclose(f_tet);*/
}


bool MeshViewerWidget::saveMesh(const char* filename)
{
	return OpenMesh::IO::write_mesh(mesh, filename);
}
bool MeshViewerWidget::saveScreen(const char* filePath)
{
	QImage image = grabFrameBuffer();
	image.save(filePath);
	return true;
}

void MeshViewerWidget::checkMeshMode()
{
	Mesh::FaceIter fIt = mesh.faces_begin();
	Mesh::FaceIter fEnd = mesh.faces_end();
	Mesh::FaceEdgeIter fe_it;
	int count = 1;
	int meshType[3] = { 0 };
	for (fIt; fIt != fEnd; ++fIt)
	{
		fe_it = mesh.fe_iter(fIt);
		while (--fe_it)
		{
			++count;
		}
		if (count == 4)
		{
			meshType[1]++;
		}
		else if (count == 3)
		{
			meshType[0]++;
		}
		else
		{
			meshType[2]++;
		}
		count = 1;
	}
	int faceNum = mesh.n_faces();
	if (meshType[0] == faceNum)//triangle
	{
		setMeshMode(TRIANGLE);
	}
	else if (meshType[1] == faceNum)//no 
	{
		setMeshMode(QUAD);
	}
	else
	{
		setMeshMode(N_MESH_MODES);
	}
}

void MeshViewerWidget::updateIndices()
{
	//Mesh::ConstFaceIter f_it(mesh.faces_sbegin()), 
	//	f_end(mesh.faces_end());
	//Mesh::ConstFaceVertexIter  fv_it;

	////Indices.clear(); VIndices.clear();
	//int PolygonClass = 0 ;
	//switch(meshMode())
	//{
	//case TRIANGLE:
	//	PolygonClass = 3;
	//	break;
	//case QUAD:
	//	PolygonClass = 4;
	//	break;
	//default:
	//	return;
	//}
	//
	//Indices.reserve(mesh.n_faces()*PolygonClass);
	//for (; f_it!=f_end; ++f_it)
	//{
	//	fv_it = mesh.cfv_iter(f_it); 
	//	for( fv_it; fv_it; ++fv_it)
	//	{
	//		Indices.push_back((fv_it).handle().idx());
	//	}
	//}

	//VIndices.resize(mesh.n_vertices());
	//for(int i=0;i<mesh.n_vertices();++i)
	//{
	//	VIndices[i] = i;
	//}
}

void MeshViewerWidget::draw_scene(int drawmode)
{
	QFont Text_Font("Courier", 12);
	glViewport(0, 0, width(), height());
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&ProjectionMatrix[0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&ModelViewMatrix[0]);

	/*double r = (bbMin-bbMax).norm()*0.5;
	OpenMesh::Vec3d c = (bbMin+ bbMax)*0.5;
	OpenMesh::Vec3d x(1.0*r,0,0); OpenMesh::Vec3d y(0,1.0*r,0); OpenMesh::Vec3d z(0,0,1.0*r);
	OpenMesh::Vec3d temp;
	glDisable(GL_LIGHTING);
	glLineWidth(2.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3dv( c.data() );
	temp = (c + x);
	glVertex3dv( temp.data() );
	glEnd();
	renderText(temp[0] + 0.01*r, temp[1], temp[2] , "X", Text_Font );

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3dv( c.data() );
	temp = (c + y);
	glVertex3dv( temp.data() );
	glEnd();
	renderText(temp[0], temp[1] + 0.01*r, temp[2] , "Y", Text_Font );

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3dv( c.data() );
	temp = (c + z);
	glVertex3dv( temp.data() );
	glEnd();
	renderText(temp[0], temp[1], temp[2] + 0.01*r , "Z", Text_Font );*/

	if (draw_BBox_OK)
	{
		OpenMesh::Vec3d temp0 = bbMin;
		OpenMesh::Vec3d temp1;
		glLineWidth(2.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		temp1 = bbMin; temp1[0] = bbMax[0];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());
		temp1 = bbMin; temp1[1] = bbMax[1];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());
		temp1 = bbMin; temp1[2] = bbMax[2];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMin; temp0[0] = bbMax[0];
		temp1 = bbMax; temp1[1] = bbMin[1];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMin; temp0[0] = bbMax[0];
		temp1 = bbMax; temp1[2] = bbMin[2];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMin; temp0[1] = bbMax[1];
		temp1 = bbMax; temp1[2] = bbMin[2];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMin; temp0[1] = bbMax[1];
		temp1 = bbMax; temp1[0] = bbMin[0];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMin; temp0[2] = bbMax[2];
		temp1 = bbMax; temp1[1] = bbMin[1];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMin; temp0[2] = bbMax[2];
		temp1 = bbMax; temp1[0] = bbMin[0];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());

		temp0 = bbMax;
		temp1 = bbMax; temp1[0] = bbMin[0];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());
		temp1 = bbMax; temp1[1] = bbMin[1];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());
		temp1 = bbMax; temp1[2] = bbMin[2];
		glVertex3dv(temp0.data());
		glVertex3dv(temp1.data());
		glEnd();
	}

	if (draw_mesh_boundary_ok)
	{
		glLineWidth(2.0);
		glColor3f(1.0, 0.5, 0.0);
		glBegin(GL_LINES);
		for (Mesh::EdgeIter e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it)
		{
			if (mesh.is_boundary(e_it))
			{
				Mesh::HalfedgeHandle heh0 = mesh.halfedge_handle(e_it, 0);
				glVertex3dv(mesh.point(mesh.to_vertex_handle(heh0)).data());
				glVertex3dv(mesh.point(mesh.from_vertex_handle(heh0)).data());
			}
		}
		glEnd();

		/*FILE* f_bde = fopen("bde.de", "w");
		for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
		{
			if (mesh.is_boundary(v_it))
			{
				OpenMesh::Vec3d& np = mesh.point(v_it);
				fprintf(f_bde, "%d %20.19f %20.19f 0.0\n", v_it.handle().idx(), np[0], np[1]);
			}
		}
		fclose(f_bde);*/
	}

	draw_scene_mesh(drawmode);
}

void MeshViewerWidget::draw_scene_mesh(int drawmode)
{
	if (mesh.n_vertices() == 0) { return; }

	switch (drawmode)
	{
	case WIRE_FRAME:
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		draw_mesh_wireframe();
		//draw_meshpointset();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case HIDDEN_LINES:
		glDisable(GL_LIGHTING);
		draw_mesh_hidden_lines();
		break;
	case SOLID_FLAT:
		glEnable(GL_LIGHTING);
		glShadeModel(GL_FLAT);
		draw_mesh_solidflat();
		//draw_meshpointset();
		glDisable(GL_LIGHTING);
		break;
	case FLAT_POINTS:
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.5f, 2.0f);
		glEnable(GL_LIGHTING);
		glShadeModel(GL_FLAT);
		draw_mesh_solidflat();
		glDisable(GL_POLYGON_OFFSET_FILL);
		//draw_meshpointset();
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		draw_mesh_wireframe();
		//draw_meshpointset();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case SOLID_SMOOTH:
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		draw_mesh_solidsmooth();
		//draw_meshpointset();
		glDisable(GL_LIGHTING);
		break;
	case POINT_SET:
		glDisable(GL_LIGHTING);
		draw_mesh_pointset();
		break;
	case CURVATURE:
		if (!is_using_texture)
		{
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT, GL_LINE);
			draw_curve_edge(); 
			glPolygonMode(GL_BACK, GL_FILL);
			draw_curve_face(); 

		}
		else 
		{
			Draw(); 
			draw_curve_edge(); 


		}
		break;
	default:
		break;
	}
}


void MeshViewerWidget::draw_mesh_wireframe()
{
	glLineWidth(1);
	//glColor3f(0.753, 0.753, 0.753);
	//glColor3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.25);
	//if(meshMode() != TRIANGLE && meshMode() != QUAD)
	{
		Mesh::ConstFaceIter fIt(mesh.faces_begin()),
			fEnd(mesh.faces_end());
		Mesh::ConstFaceVertexIter fvIt;
		for (; fIt != fEnd; ++fIt)
		{
			//GL::glNormal(dualMesh.normal(f_it));
			fvIt = mesh.cfv_iter(fIt);
			glBegin(GL_POLYGON);
			for (fvIt; fvIt; ++fvIt)
			{
				glVertex3dv(mesh.point(fvIt).data());
			}
			glEnd();
		}
	}

	/*OpenMesh::Vec3d pos = mesh.point(mesh.vertex_handle(0));
	GLdouble  winX, winY, winZ;
	GLint     viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluProject(pos[0],pos[1],pos[2],&ModelViewMatrix[0][0],&ProjectionMatrix[0][0],viewport,&winX,&winY,&winZ);
	int x = (long)winX;
	int y = viewport[3]-(long)winY;
	QString str = "fxum";
	render_text(x,y,str);*/
	/*else
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, mesh.points());
		switch(meshMode())
		{
		case TRIANGLE:
			glDrawElements(GL_TRIANGLES,Indices.size(),GL_UNSIGNED_INT,&Indices[0]);
			break;
		case QUAD:
			glDrawElements(GL_QUADS,Indices.size(),GL_UNSIGNED_INT,&Indices[0]);
			break;
		default:
			break;
		}

		glDisableClientState(GL_VERTEX_ARRAY);
	}*/

}


void MeshViewerWidget::draw_mesh_hidden_lines() const
{
	Mesh::ConstFaceIter f_it(mesh.faces_begin());
	Mesh::ConstFaceIter f_end(mesh.faces_end());
	Mesh::ConstFaceVertexIter fv_it;
	glLineWidth(2.0);
	glColor3f(0.0, 1.0, 1.0);

	glDrawBuffer(GL_NONE);
	glDepthRange(0.01, 1.0);
	switch (meshMode())
	{
	case TRIANGLE:
		glBegin(GL_TRIANGLES);
		for (; f_it != f_end; ++f_it)
		{
			fv_it = mesh.cfv_iter(f_it);
			for (fv_it; fv_it; ++fv_it)
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}

		}
		glEnd();
		break;
	case QUAD:
		glBegin(GL_QUADS);
		for (; f_it != f_end; ++f_it)
		{
			fv_it = mesh.cfv_iter(f_it);
			for (fv_it; fv_it; ++fv_it)
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}
		}
		glEnd();
		break;
	default:
		for (; f_it != f_end; ++f_it)
		{
			fv_it = mesh.cfv_iter(f_it);
			glBegin(GL_POLYGON);
			for (fv_it; fv_it; ++fv_it)
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}
			glEnd();
		}
		break;
	}

	glDrawBuffer(GL_BACK);
	glDepthRange(0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDepthFunc(GL_LEQUAL);

	switch (meshMode())
	{
	case TRIANGLE:
		glBegin(GL_TRIANGLES);
		for (f_it = mesh.faces_begin(); f_it != f_end; ++f_it)
		{
			fv_it = mesh.cfv_iter(f_it);
			for (fv_it; fv_it; ++fv_it)
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}
		}
		glEnd();
		break;
	case QUAD:
		glBegin(GL_QUADS);
		for (f_it = mesh.faces_begin(); f_it != f_end; ++f_it)
		{
			fv_it = mesh.cfv_iter(f_it);
			for (fv_it; fv_it; ++fv_it)
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}
		}
		glEnd();
		break;
	default:
		for (f_it = mesh.faces_begin(); f_it != f_end; ++f_it)
		{
			fv_it = mesh.cfv_iter(f_it);
			glBegin(GL_POLYGON);
			for (fv_it; fv_it; ++fv_it)
			{
				glVertex3dv(&mesh.point(fv_it)[0]);
			}
			glEnd();
		}
		break;
	}

	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MeshViewerWidget::draw_mesh_solidflat() const
{
	Mesh::ConstFaceIter fIt(mesh.faces_begin()),
		fEnd(mesh.faces_end());
	Mesh::ConstFaceVertexIter fvIt;

	GLfloat mat_a[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_d[] = { 0.88f, 0.84f, 0.76f, 1.0f };
	GLfloat mat_s[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat shine[] = { 120.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	switch (meshMode())
	{
	case TRIANGLE:
		glBegin(GL_TRIANGLES);
		for (fIt; fIt != fEnd; ++fIt)
		{
			glNormal3dv(mesh.normal(fIt).data());
			fvIt = mesh.cfv_iter(fIt.handle());
			for (fvIt; fvIt; ++fvIt)
			{
				glVertex3dv(mesh.point(fvIt).data());
			}
		}
		glEnd();
		break;
	case QUAD:
		glBegin(GL_QUADS);
		for (; fIt != fEnd; ++fIt)
		{
			glNormal3dv(&mesh.normal(fIt)[0]);
			fvIt = mesh.cfv_iter(fIt.handle());
			for (fvIt; fvIt; ++fvIt)
			{
				glVertex3dv(&mesh.point(fvIt)[0]);
			}
		}
		glEnd();
		break;
	default:
		for (; fIt != fEnd; ++fIt)
		{
			glBegin(GL_POLYGON);
			glNormal3dv(&mesh.normal(fIt)[0]);
			fvIt = mesh.cfv_iter(fIt.handle());
			for (fvIt; fvIt; ++fvIt)
			{
				glVertex3dv(&mesh.point(fvIt)[0]);
			}
			glEnd();
		}
		break;
	}
}

void MeshViewerWidget::draw_mesh_solidsmooth() const
{
	bool drawOK = false;
	glLoadName(mesh.n_vertices());

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_DOUBLE, 0, mesh.points());
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glNormalPointer(GL_DOUBLE, 0, mesh.vertex_normals());
	//switch(meshMode())
	//{
	//case TRIANGLE:
	//	glDrawElements(GL_TRIANGLES,Indices.size(),GL_UNSIGNED_INT,&Indices[0]);
	//	drawOK = true;
	//	break;
	//case QUAD:
	//	glDrawElements(GL_QUADS,Indices.size(),GL_UNSIGNED_INT,&Indices[0]);
	//	drawOK = true;
	//	break;
	//default:
	//	break;
	//}
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);

	//if(drawOK) return;

	Mesh::ConstFaceIter fIt(mesh.faces_begin()),
		fEnd(mesh.faces_end());
	Mesh::ConstFaceVertexIter fvIt;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, mesh.points());
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, mesh.vertex_normals());

	for (; fIt != fEnd; ++fIt)
	{
		glBegin(GL_POLYGON);
		fvIt = mesh.cfv_iter(fIt.handle());
		for (fvIt; fvIt; --fvIt)
		{
			glArrayElement(fvIt.handle().idx());
		}
		glEnd();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void MeshViewerWidget::draw_mesh_pointset() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);

	glColor3f(0.0, 1.0, 1.0);
	glPointSize(10);
	Mesh::VertexIter v_it = mesh.vertices_begin();
	glBegin(GL_POINTS);
	for (v_it; v_it != mesh.vertices_end(); ++v_it)
	{
		glVertex3dv(mesh.point(v_it).data());
	}
	glEnd();
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, mesh.points());
	glDrawElements(GL_POINTS,mesh.n_vertices(),GL_UNSIGNED_INT,&VIndices[0]);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
 
 
void  MeshViewerWidget::Render_Only_Use_mydata(std::string source)
{
	std::cout << "===============  Render Only Use mydata Start!!!  ================" << std::endl;
	 
	Bezier3D2d d_;

	read_get_Data_for_Bezier(d_, source); 

	V_N = d_.toal_v_num;
	sur_V_num = d_.sur_v_num;
	sur_Ver_num = d_.sur_ver_num;
	tri_F_num = d_.tri_f_num;

	GenMesh(d_);

	if (is_using_samplemesh)
	{
		GenSampleMesh();
	}
	else
	{
		subvison_num = 1;
		submesh.clear();
		submesh = mesh;
		for (size_t i = 0; i < subvison_num; i++)
		{
			GenSubMesh();
		}
		GenctrMesh();

		Genrendermesh();
	}


	updateCurveMeshCenter(); 

	if (is_using_texture) 
	{
		if (is_using_samplemesh)
		{
			 
			if (is_draw_curve_boundary) {
				 
				sample_P_OnCurveEdge.clear();
				sample_P_OnCurveEdge.resize(mesh.n_edges());
				Get_sample();
			}
		}
		else
		{
			//set_texcoord_rendermesh();
			 
		}

	}
	else
	{
		sample_P_OnCurveEdge.clear();
		sample_P_OnCurveEdge.resize(mesh.n_edges());
		Get_sample();
	}
	setDrawMode(CURVATURE);

	 
	string filenameBase = source.substr(0, source.find_last_of('\_'));
	string str = filenameBase + "\_" + std::to_string(0) + ".png";
	const char* p0 = str.data();
	saveScreen(p0);

	 
	std::string filename_ = "../src/Data/" + base + "/mydata/";

	int total_frame = 100; 
	for (int t = 1; t <= total_frame; t++)
	{
		string target = filename_ + "\_" + std::to_string(t) + ".txt";
		Eigen::MatrixXd  target_V;
		read_get_Data(target_V, target);
		Eigen::VectorXd position_of_mesh;
		position_of_mesh.resize(3 * V_N);
		for (size_t i = 0; i < 3; i++)
		{
			position_of_mesh.block(i * V_N, 0, V_N, 1) = target_V.col(i);
		}

		 
		updataCurveMeshPoints(position_of_mesh); 
		if (!is_using_texture)
		{
			Get_sample(); 
		}
		else
		{
			if (is_using_samplemesh)
			{
				UpdateSampleMesh();
				if (is_draw_curve_boundary) Get_sample(); 

			}
			else
			{
				submesh.clear();
				submesh = mesh;
				for (size_t i = 0; i < subvison_num; i++)
				{
					GenSubMesh();
				}
				GenctrMesh();
				Updata_For_rendermesh();
			}


		}
		setDrawMode(CURVATURE);
		str = filenameBase + "\_" + std::to_string(t) + ".bmp";
		const char* p = str.data();
		std::cout << "==========save==============" << " " << t << " png  =====================" << std::endl;
		saveScreen(p);

	}

	std::cout << "===============  Render Only Use mydata Finished!!!  ================" << std::endl;


}

void MeshViewerWidget::Perorm_Curve_Morphing_Using_SamplingOptimization(std::string source, std::string target)
{
	string filenameiternum = "../src/Data/" + base + "/iternum_for_each_frame.txt";

	ofstream outiternum(filenameiternum);

	std::cout << "===============  SamplingOptimization : Curve Morphing Start!!!  ================" << std::endl;
	 
	std::string filenameflip = "../src/Data/" + base + "/SamplingOptimizationError.txt";

	std::ofstream outflip(filenameflip);
	Bezier3D2d d_;
	//read_get_Data(d_, source); 
	read_get_Data_for_Bezier(d_, source); 

	V_N = d_.toal_v_num;
	sur_V_num = d_.sur_v_num;
	sur_Ver_num = d_.sur_ver_num;
	tri_F_num = d_.tri_f_num;

	GenMesh(d_);

	if (is_using_samplemesh)
	{
		GenSampleMesh();
		/*std::string file = "shou_samplemeshfordata1.obj";
		OpenMesh::IO::write_mesh(samplemesh, file);
		return;*/

	}
	else
	{

		subvison_num = 1;
		submesh.clear();
		submesh = mesh;
		for (size_t i = 0; i < subvison_num; i++)
		{
			GenSubMesh();
		}
		GenctrMesh();

		Genrendermesh();
		 

	}


	updateCurveMeshCenter(); 

	if (is_using_texture) 
	{
		if (is_using_samplemesh)
		{
			 
			if (is_draw_curve_boundary) {
			 
				sample_P_OnCurveEdge.clear();
				sample_P_OnCurveEdge.resize(mesh.n_edges());
				Get_sample();
			}
		}
		else
		{
			//set_texcoord_rendermesh();
		 
		}

	}
	else
	{
		sample_P_OnCurveEdge.clear();
		sample_P_OnCurveEdge.resize(mesh.n_edges());
		Get_sample();
	}


	Eigen::MatrixXd  target_V;
	read_get_Data(target_V, target);


	setDrawMode(CURVATURE);




	SamplingOptimization Sampling_solver;
	Sampling_solver.d_ = d_;
	Sampling_solver.target_V = target_V;

	Sampling_solver.is_need_self_adaptation_sampling_Parameter_Domain = false; 
	Sampling_solver.is_need_cal_distortion = false; 
	Sampling_solver.init();
	 
	//check source and target mesh  regular  ???
	Sampling_solver.source_and_target_injective_checker();
	if (Sampling_solver.source_Bezier_mesh_injective == false || Sampling_solver.target_Bezier_mesh_injective == false)
	{
		if (Sampling_solver.source_Bezier_mesh_injective)
		{
			std::cout << "$$$$$$$$$$$$$$$$$ target mesh Not regular $$$$$$$$$$$$$$$$$$$$" << std::endl;
			return;
		}
		else
		{
			std::cout << "$$$$$$$$$$$$$$$$$ source mesh Not regular $$$$$$$$$$$$$$$$$$$$" << std::endl;
			return;

		}

	}
	 

	VectorXd position_of_mesh = Sampling_solver.position_of_mesh;
	double morphing_t = 0.0;
	string filenameBase = source.substr(0, source.find_last_of('\_'));
	string str = filenameBase + "\_" + std::to_string(0) + ".png";
	const char* p0 = str.data();
	saveScreen(p0);

	int max_iter_num = 50;
	int total_frame = Sampling_solver.total_frame;
	std::cout << "================  total frame is:  " << total_frame << "  =====================" << std::endl;

 ; 

	for (int t = 1; t <= total_frame; t++)
	{
		Sampling_solver.position_of_mesh = position_of_mesh;
		morphing_t = double(t) / total_frame;
		Sampling_solver.morphing_t = morphing_t;
		 
		 
 

		Sampling_solver.fixed_total_energy = numeric_limits<double>::infinity();
		long time_beg, time_end;
		time_beg = clock();
		for (size_t i = 0; i < max_iter_num; i++)
		{
			std::cout << "=================== iteration num is: " << (i + 1) << " ========================= " << std::endl;
			 
			Sampling_solver.fixed_last_total_energy = Sampling_solver.fixed_total_energy;
			 
			Sampling_solver.Optimization_OMP_with_cut();
			 
			if (Sampling_solver.cur_gradient_norm < 3 * 1e-5)
			{
				time_end = clock();
				double time_consumption = (time_end - time_beg); 
				outiternum << "frame: " << t << " iter nums: " << (i + 1) << "  grad norm" << Sampling_solver.cur_gradient_norm << " time is: " << time_consumption;
				outiternum << " energy is: " << std::setprecision(10) << Sampling_solver.fixed_total_energy << '\n';
				std::cout << "================= frame: " << t << " iter nums: " << (i + 1) << " ===================" << '\n';
				std::cout << "No self adaptation: gradient_norm is very small ,      Stop iteration! " << std::endl;
				std::cout << "No self adaptation: iteration num is:  " << (i + 1) << "  " << "iteration total num is :  " << max_iter_num << std::endl;
				break;
			}

			if (i == (max_iter_num - 1))
			{
				time_end = clock();
				double time_consumption = (time_end - time_beg); 
				outiternum << "frame: " << t << " iter nums: " << max_iter_num << "  grad norm" << Sampling_solver.cur_gradient_norm << " time is: " << time_consumption;
				outiternum << " energy is: " << std::setprecision(10) << Sampling_solver.fixed_total_energy << '\n';
				std::cout << "================= frame: " << t << " iter nums: " << max_iter_num << " gradient_norm: " << Sampling_solver.cur_gradient_norm << " ===================" << '\n';

			}
		}

		std::cout << "======== No self adaptation:  is_search_direction_error: " << Sampling_solver.is_search_direction_error << "  ===========" << std::endl;
		if (Sampling_solver.is_search_direction_error)
		{
			outflip << "No self adaptation :search_direction_error =============frame:  " << t << '\n';

		}
		Sampling_solver.is_search_direction_error = false;

		std::cout << '\n';
		std::cout << "========== No self adaptation:  is_exist_Bezier_triangle_flip :  " << Sampling_solver.is_exist_Bezier_triangle_flip << "  ===================" << std::endl;
		if (Sampling_solver.is_exist_Bezier_triangle_flip)
		{
			outflip << "No self adaptation :Bezier_fliped =============frame:  " << t << '\n';

		}
		Sampling_solver.is_exist_Bezier_triangle_flip = false;

		std::cout << "========== No self adaptation:  is_error_Cal_lamda_Metric :  " << Sampling_solver.is_error_Cal_lamda_Metric << "  ===================" << std::endl;
		if (Sampling_solver.is_error_Cal_lamda_Metric)
		{

			outflip << "No self adaptation :Cal_lamda_Metric error =============frame:  " << t << '\n';
		}
		Sampling_solver.is_error_Cal_lamda_Metric = false;


		std::cout << '\n';
		std::cout << "========== No self adaptation:  is_Eigenvalues_order_error1:  " << Sampling_solver.is_Eigenvalues_order_error1 << "  ===================" << std::endl;
		if (Sampling_solver.is_Eigenvalues_order_error1)
		{

			outflip << "No self adaptation :is_Eigenvalues_order_error1 =============frame:  " << t << '\n';

		}
		Sampling_solver.is_Eigenvalues_order_error1 = false;


		std::cout << '\n';
		std::cout << "========== No self adaptation:  is_Eigenvalues_order_error2:  " << Sampling_solver.is_Eigenvalues_order_error2 << "  ===================" << std::endl;
		if (Sampling_solver.is_Eigenvalues_order_error2)
		{

			outflip << "No self adaptation :is_Eigenvalues_order_error2=============frame:  " << t << '\n';

		}
		Sampling_solver.is_Eigenvalues_order_error2 = false;

		std::cout << '\n';
		std::cout << "========== No self adaptation:  is_Eigenvalues_order_error3:  " << Sampling_solver.is_Eigenvalues_order_error3 << "  ===================" << std::endl;
		if (Sampling_solver.is_Eigenvalues_order_error3)
		{

			outflip << "No self adaptation :is_Eigenvalues_order_error3=============frame:  " << t << '\n';

		}
		Sampling_solver.is_Eigenvalues_order_error3 = false;


		position_of_mesh = Sampling_solver.position_of_mesh;

		if (is_output_normalize_distortion) Sampling_solver.output_normalize_distortion();
		 

		updataCurveMeshPoints(Sampling_solver.position_of_mesh); 
		if (!is_using_texture)
		{
			Get_sample(); 
		}
		else
		{
			if (is_using_samplemesh)
			{
				UpdateSampleMesh();

				if (is_draw_curve_boundary) Get_sample(); 
			}
			else
			{
				submesh.clear();
				submesh = mesh;
				for (size_t i = 0; i < subvison_num; i++)
				{
					GenSubMesh();
				}
				GenctrMesh();
				Updata_For_rendermesh();
			}


		}


		setDrawMode(CURVATURE);
		str = filenameBase + "\_" + std::to_string(t) + ".png";
		const char* p = str.data();
		std::cout << "==========save==============" << " " << t << " png  =====================" << std::endl;
	 
		saveScreen(p);

		if (is_store_data) 
		{
			std::cout << "==========  save  mydata txt ==============" << " " << t << "  zhen ==================" << std::endl;
			VectorXd position_of_mesh_t = Sampling_solver.position_of_mesh;
			string filenameBaset1 = "../src/Data/" + base + "/mydata/"; 
			string filenamet = filenameBaset1 + "\_" + std::to_string(t) + ".txt";
			write_curve_mesh(filenamet, d_, position_of_mesh_t);
			std::cout << '\n';

			std::cout << "==========  save  gmsh lag control points ==============" << " " << t << "  zhen ==================" << std::endl;
			string filenameBaset2 = "../src/Data/" + base + "/gmsh/";
			string Lagmshname = filenameBaset2 + "Lag" + "\_" + std::to_string(t) + ".msh";
			write_3D_msh_Lagrange(Lagmshname, d_, position_of_mesh_t);
			std::cout << '\n';

		}



	}

	outflip << endl;
	outiternum << endl;
	 
	if (is_output_normalize_distortion) {
		string max_normal_iso = "../src/Data/" + base + "/max_normal_iso.txt";
		ofstream out_max_nor_iso(max_normal_iso);
		for (int i = 0; i < Sampling_solver.max_normalize_iso_distortion.size(); i++) {
			out_max_nor_iso << Sampling_solver.max_normalize_iso_distortion[i] << '\n';
		}
		out_max_nor_iso << endl;

		string min_normal_iso = "../src/Data/" + base + "/min_normal_iso.txt";
		ofstream out_min_nor_iso(min_normal_iso);
		for (int i = 0; i < Sampling_solver.min_normalize_iso_distortion.size(); i++) {
			out_min_nor_iso << Sampling_solver.min_normalize_iso_distortion[i] << '\n';
		}
		out_min_nor_iso << endl;

		string avg_normal_iso = "../src/Data/" + base + "/avg_normal_iso.txt";
		ofstream out_avg_nor_iso(avg_normal_iso);
		for (int i = 0; i < Sampling_solver.avg_normalize_iso_distortion.size(); i++) {
			out_avg_nor_iso << Sampling_solver.avg_normalize_iso_distortion[i] << '\n';
		}
		out_avg_nor_iso << endl;

		string globel_iso = "../src/Data/" + base + "/globel_iso.txt";
		ofstream out_globel_iso(globel_iso);
		for (int i = 0; i < Sampling_solver.globel_iso_distortion.size(); i++)
		{
			out_globel_iso << Sampling_solver.globel_iso_distortion[i] << '\n';
		}
	 

		string max_normal_conformal = "../src/Data/" + base + "/max_normal_conformal.txt";
		ofstream out_max_nor_conformal(max_normal_conformal);
		for (int i = 0; i < Sampling_solver.max_normalize_conformal_distortion.size(); i++) {
			out_max_nor_conformal << Sampling_solver.max_normalize_conformal_distortion[i] << '\n';
		}
		out_max_nor_conformal << endl;

		string min_normal_conformal ="../src/Data/" + base + "/min_normal_conformal.txt";
		ofstream out_min_nor_conformal(min_normal_conformal);
		for (int i = 0; i < Sampling_solver.min_normalize_conformal_distortion.size(); i++) {
			out_min_nor_conformal << Sampling_solver.min_normalize_conformal_distortion[i] << '\n';
		}
		out_min_nor_conformal << endl;

		string avg_normal_conformal = "../src/Data/" + base + "/avg_normal_conformal.txt";
		ofstream out_avg_nor_conformal(avg_normal_conformal);
		for (int i = 0; i < Sampling_solver.avg_normalize_conformal_distortion.size(); i++) {
			out_avg_nor_conformal << Sampling_solver.avg_normalize_conformal_distortion[i] << '\n';
		}
		out_avg_nor_conformal << endl;

		string globel_conformal = "../src/Data/" + base + "/globel_conformal.txt";
		ofstream out_globel_conformal(globel_conformal);
		for (int i = 0; i < Sampling_solver.globel_conformal_distortion.size(); i++)
		{
			out_globel_conformal << Sampling_solver.globel_conformal_distortion[i] << '\n';
		}
	 

	}
}


void MeshViewerWidget::Perorm_Curve_Deformation(std::string source)
{
	/*
	* //The input files required by our algorithm can be obtained in the commented section below.
	std::string input = "../src/Deformation/input.txt";
	std::string output = "../src/Deformation/output.txt";
	convert_to_my_data(input, output);
	return;*/
	 

	std::cout << "Curve Morphing Start!!!" << std::endl;

	source = "../src/Deformation/Bezier3d_08_source_sample1.txt";

	 
	 
	bool is_need_LagtoBez = false;//Whether the input file needs to be converted into coordinates
	 

	Bezier3D2d d_;
	if (is_need_LagtoBez)
	{
		read_get_Data(d_, source); 

	}
	else
	{
		read_get_Data_for_Bezier(d_, source); 
	}

	V_N = d_.toal_v_num;
	sur_V_num = d_.sur_v_num;
	sur_Ver_num = d_.sur_ver_num;
	tri_F_num = d_.tri_f_num;

	GenMesh(d_);


	if (is_using_samplemesh)
	{
		GenSampleMesh();
		/*std::string file = "chair.obj";
		OpenMesh::IO::write_mesh(samplemesh, file);
		return;*/

	}
	else 
	{
		subvison_num = 1; 
		submesh.clear();
		submesh = mesh;
		for (size_t i = 0; i < subvison_num; i++)
		{
			GenSubMesh();
		}
		GenctrMesh();

		Genrendermesh();

	}

	updateCurveMeshCenter(); 

	if (is_using_texture)
	{
		if (is_using_samplemesh)
		{
			 
			if (is_draw_curve_boundary) {
				 
				sample_P_OnCurveEdge.clear();
				sample_P_OnCurveEdge.resize(mesh.n_edges());
				Get_sample();
			}
		}
		else
		{
			//set_texcoord_rendermesh();
		}
	}
	else
	{
		sample_P_OnCurveEdge.clear();
		sample_P_OnCurveEdge.resize(mesh.n_edges());
		Get_sample();
	}



	setDrawMode(CURVATURE);
	 
	 
	read_get_Data_for_Bezier(d_, source); 

	 
	Deformation deformation_slover;
	deformation_slover.d_ = d_;
	deformation_slover.init();

	deformation_slover.check_source_flip();
	VectorXd position_of_mesh = deformation_slover.position_of_mesh;


	 

	if (deformation_slover.source_Bezier_mesh_injective == false)
	{
		std::cout << "$$$$$$$$$$$$$$$$$ source mesh Not regular $$$$$$$$$$$$$$$$$$$$" << std::endl;
		return;

	}
	else
	{
		std::cout << "==================== source mesh regular =========================" << std::endl;

	}
	 

	/*
	Note that you must first set max_iter_num to 0 to get a file with the suffix "_sample1.txt", and then set the source commented at the beginning
	source = "../src/Deformation/Bezier3d_08_source_sample1.txt";
	Change the path to the file(txt).
	*/
	int max_iter_num = 50;
	 
	deformation_slover.fixed_total_energy = numeric_limits<double>::infinity();

	for (size_t i = 0; i < max_iter_num; i++)
	{
		deformation_slover.fixed_last_total_energy = deformation_slover.fixed_total_energy;
		 
		deformation_slover.Optimization_OMP_with_cut();

		 
		if (deformation_slover.cur_gradient_norm < 5 * 1e-5)
		{
			std::cout << "No self adaptation: Energy is very close,      Stop iteration! " << std::endl;
			std::cout << "No self adaptation: iteration num is:  " << (i + 1) << "  " << "iteration total num is :  " << max_iter_num << std::endl;
			break;
		}
	}

	std::cout << '\n';
	std::cout << "======== No self adaptation:  is_search_direction_error: " << deformation_slover.is_search_direction_error << "  ===========" << std::endl;

	std::cout << '\n';
	std::cout << "========== No self adaptation:  is_exist_Bezier_triangle_flip :  " << deformation_slover.is_exist_Bezier_triangle_flip << "  ===================" << std::endl;

	std::cout << '\n';
	std::cout << "========== No self adaptation:  is_Eigenvalues_order_error1:  " << deformation_slover.is_Eigenvalues_order_error1 << "  ===================" << std::endl;

	std::cout << '\n';
	std::cout << "========== No self adaptation:  is_Eigenvalues_order_error2:  " << deformation_slover.is_Eigenvalues_order_error2 << "  ===================" << std::endl;

	std::cout << '\n';
	std::cout << "========== No self adaptation:  is_Eigenvalues_order_error3:  " << deformation_slover.is_Eigenvalues_order_error3 << "  ===================" << std::endl;

 
	updataCurveMeshPoints(deformation_slover.position_of_mesh); 

	if (!is_using_texture)
	{
		Get_sample(); 
	}
	else
	{

		if (is_using_samplemesh)
		{
			UpdateSampleMesh();
			if (is_draw_curve_boundary) Get_sample(); 

		}
		else
		{
			submesh.clear();
			submesh = mesh;
			for (size_t i = 0; i < subvison_num; i++)
			{
				GenSubMesh();
			}
			GenctrMesh();
			Updata_For_rendermesh();

		}
	}

	setDrawMode(CURVATURE);

	 
	 
	string filenameBase = source.substr(0, source.find_last_of('.'));
	string filename = filenameBase + "_sample1.txt";
	string mshname = filenameBase + "_msh1.msh";
	string DefLagmshname = filenameBase + "_DefLag1.msh";
	position_of_mesh = deformation_slover.position_of_mesh;
	write_curve_mesh(filename, d_, position_of_mesh);
	//write_3D_msh(mshname, d_, position_of_mesh);
	write_3D_msh_Lagrange(DefLagmshname, d_, position_of_mesh);
}


void MeshViewerWidget::GenMesh(Bezier3D2d& d_)
{
	clearAllMesh();
	std::cout << "mesh vertices: " << mesh.n_vertices() << std::endl;
	int sur_ver_num = d_.sur_ver_num;
	Mesh::Point ver_P(0., 0., 0.);
	std::vector<Mesh::VertexHandle> VH;
	VH.clear();
	for (int i = 0; i < sur_ver_num; i++)
	{
		ver_P[0] = d_.m_V(i, 0);
		ver_P[1] = d_.m_V(i, 1);
		ver_P[2] = d_.m_V(i, 2);
		VH.push_back(mesh.add_vertex(ver_P));
	}

	int b1 = 0, b4 = 0, b6 = 0;
	int b2 = 0, b3 = 0, b5 = 0;

	for (int i = 0; i < d_.tri_f_num; i++)
	{
		b1 = d_.m_Sur_T(i, 0);
		b4 = d_.m_Sur_T(i, 3);
		b6 = d_.m_Sur_T(i, 5);
		mesh.add_face({ VH[b1], VH[b4], VH[b6] });
	}

	for (int i = 0; i < d_.tri_f_num; i++)
	{
		b1 = d_.m_Sur_T(i, 0);
		b4 = d_.m_Sur_T(i, 3);
		b6 = d_.m_Sur_T(i, 5);
		b2 = d_.m_Sur_T(i, 1);
		b5 = d_.m_Sur_T(i, 4);
		b3 = d_.m_Sur_T(i, 2);
		auto fh = mesh.face_handle(i);

		mesh.data(fh).fv_id_with_m_T = b1; 
		Mesh::HalfedgeHandle hh = mesh.halfedge_handle(fh);
		auto v0 = mesh.from_vertex_handle(hh);
		if (v0.idx() != b1) hh = mesh.next_halfedge_handle(hh);
		v0 = mesh.from_vertex_handle(hh);
		if (v0.idx() != b1) hh = mesh.next_halfedge_handle(hh);
		v0 = mesh.from_vertex_handle(hh);
		auto eh = mesh.edge_handle(hh);
		if (v0.idx() != b1)
		{
			std::cout << "error " << "v0.idx() is" << v0.idx() << " b1 is" << b1 << std::endl;
		}
		else
		{
			ver_P[0] = d_.m_V(b2, 0);
			ver_P[1] = d_.m_V(b2, 1);
			ver_P[2] = d_.m_V(b2, 2);
			mesh.data(eh).ctp = ver_P;
			mesh.data(eh).ctp_id = b2;
			//mesh.data(eh).fv_id = 1;//b2
			//mesh.data(v0).fv_id = 0;//b1
		}


		hh = mesh.next_halfedge_handle(hh);
		v0 = mesh.from_vertex_handle(hh);
		if (v0.idx() != b4)
		{
			std::cout << "error b4" << std::endl;
		}
		eh = mesh.edge_handle(hh);
		ver_P[0] = d_.m_V(b5, 0);
		ver_P[1] = d_.m_V(b5, 1);
		ver_P[2] = d_.m_V(b5, 2);
		mesh.data(eh).ctp = ver_P;
		mesh.data(eh).ctp_id = b5;
		//mesh.data(eh).fv_id = 4;//b5
		//mesh.data(v0).fv_id = 3;//b4

		hh = mesh.next_halfedge_handle(hh);
		v0 = mesh.from_vertex_handle(hh);
		if (v0.idx() != b6)
		{
			std::cout << "error b6" << std::endl;
		}
		eh = mesh.edge_handle(hh);
		ver_P[0] = d_.m_V(b3, 0);
		ver_P[1] = d_.m_V(b3, 1);
		ver_P[2] = d_.m_V(b3, 2);
		mesh.data(eh).ctp = ver_P;
		mesh.data(eh).ctp_id = b3;
		//mesh.data(eh).fv_id = 2;//b3
		//mesh.data(v0).fv_id = 5;//b6

	}

	std::cout << "generate mesh finished!" << std::endl;
	std::cout << "mesh n_v:" << mesh.n_vertices() << "mesh n_f:" << mesh.n_faces() << std::endl;
}


void  MeshViewerWidget::GenSubMesh()
{
	Mesh result_mesh;
	std::vector<Mesh::VertexHandle> VH;
	int submesh_en = submesh.n_edges();
	int submesh_vn = submesh.n_vertices();
	std::vector<int> e_to_SubV_id(submesh_en, -1);

	std::vector<int> SubV_to_e_id(submesh_vn + submesh_en, -1);

	for (auto v_it = submesh.vertices_begin(); v_it != submesh.vertices_end(); ++v_it) 
	{
		VH.push_back(result_mesh.add_vertex(submesh.point(*v_it)));
	}

	Mesh::HalfedgeHandle hh;
	Mesh::VertexHandle v0;
	Mesh::VertexHandle v1;
	int subV_id = submesh_vn;
	for (auto e_it = submesh.edges_begin(); e_it != submesh.edges_end(); ++e_it)
	{
		hh = e_it->halfedge(0);
		v0 = submesh.from_vertex_handle(hh);
		v1 = submesh.to_vertex_handle(hh);
		VH.push_back(result_mesh.add_vertex((submesh.point(v0) + submesh.point(v1) + 2. * submesh.data(*e_it).ctp) / 4));
		e_to_SubV_id[e_it->idx()] = subV_id;
		SubV_to_e_id[subV_id] = e_it->idx();
		subV_id++;

	}

	Mesh::VertexHandle v2;
	Mesh::EdgeHandle e0;
	Mesh::EdgeHandle e1;
	Mesh::EdgeHandle e2;
	for (auto f_it = submesh.faces_begin(); f_it != submesh.faces_end(); ++f_it)
	{
		hh = submesh.halfedge_handle(*f_it);
		e0 = submesh.edge_handle(hh);
		v0 = submesh.from_vertex_handle(hh);

		hh = submesh.next_halfedge_handle(hh); 
		e1 = submesh.edge_handle(hh);
		v1 = submesh.from_vertex_handle(hh);

		hh = submesh.next_halfedge_handle(hh);
		e2 = submesh.edge_handle(hh);
		v2 = submesh.from_vertex_handle(hh);

		//add face
		result_mesh.add_face({ VH[v2.idx()],VH[e_to_SubV_id[e2.idx()]],VH[e_to_SubV_id[e1.idx()]] });

		result_mesh.add_face({ VH[e_to_SubV_id[e2.idx()]],VH[v0.idx()],VH[e_to_SubV_id[e0.idx()]] });

		result_mesh.add_face({ VH[e_to_SubV_id[e2.idx()]],VH[e_to_SubV_id[e0.idx()]],VH[e_to_SubV_id[e1.idx()]] });

		result_mesh.add_face({ VH[e_to_SubV_id[e1.idx()]],VH[e_to_SubV_id[e0.idx()]],VH[v1.idx()] });


	}

	Mesh::Point P1, P2;
	Mesh::Point P3, P4;
	for (auto e_it = result_mesh.edges_begin(); e_it != result_mesh.edges_end(); e_it++)
	{
		hh = result_mesh.halfedge_handle(e_it, 0);
		v0 = result_mesh.from_vertex_handle(hh);

		bool is_inner_edge = true;
		 
		if (v0.idx() >= submesh_vn)
		{
			P1 = submesh.data(submesh.edge_handle(SubV_to_e_id[v0.idx()])).ctp;
		}
		else 
		{
			is_inner_edge = false;
			P1 = submesh.point(submesh.vertex_handle(v0.idx()));
		}
		v1 = result_mesh.to_vertex_handle(hh);

		 
		if (v1.idx() >= submesh_vn) 
		{
			P2 = submesh.data(submesh.edge_handle(SubV_to_e_id[v1.idx()])).ctp;
		}
		else 
		{
			is_inner_edge = false;
			P2 = submesh.point(submesh.vertex_handle(v1.idx()));
		}

		if (is_inner_edge)
		{
			Mesh::HalfedgeHandle op_hh = result_mesh.opposite_halfedge_handle(hh);
			hh = result_mesh.next_halfedge_handle(hh); 
			v1 = result_mesh.to_vertex_handle(hh);

			if (v1.idx() < submesh_vn)
			{
				P3 = submesh.point(submesh.vertex_handle(v1.idx()));
			}
			else
			{
				P3 = submesh.data(submesh.edge_handle(SubV_to_e_id[v1.idx()])).ctp;
			}


			hh = result_mesh.next_halfedge_handle(op_hh);
			v1 = result_mesh.to_vertex_handle(hh);

			if (v1.idx() < submesh_vn)
			{
				P4 = submesh.point(submesh.vertex_handle(v1.idx()));
			}
			else
			{
				P4 = submesh.data(submesh.edge_handle(SubV_to_e_id[v1.idx()])).ctp;
			}



			result_mesh.data(*e_it).ctp = (P1 + P2 + P3 + P4) / 4;

		}
		else
		{
			result_mesh.data(*e_it).ctp = (P1 + P2) / 2;

		}


	}

	submesh.clear();
	submesh = result_mesh;
	std::cout << "generate subvision mesh finished!!!" << std::endl;

}


void MeshViewerWidget::GenctrMesh()
{
	ctrmesh.clear();
	std::vector<CtrMesh::VertexHandle> VH;
	int submesh_en = submesh.n_edges();
	int submesh_vn = submesh.n_vertices();
	for (auto v_it = submesh.vertices_begin(); v_it != submesh.vertices_end(); ++v_it)
	{
		VH.push_back(ctrmesh.add_vertex(submesh.point(*v_it)));
	}
	std::vector<int> e_to_SubV_id(submesh_en, -1);
	int subV_id = submesh_vn;
	for (auto e_it = submesh.edges_begin(); e_it != submesh.edges_end(); ++e_it)
	{
		VH.push_back(ctrmesh.add_vertex(submesh.data(*e_it).ctp));
		e_to_SubV_id[e_it->idx()] = subV_id;
		subV_id++;
	}

	Mesh::HalfedgeHandle hh;
	Mesh::VertexHandle v0;
	Mesh::VertexHandle v1;
	Mesh::VertexHandle v2;
	Mesh::EdgeHandle e0;
	Mesh::EdgeHandle e1;
	Mesh::EdgeHandle e2;
	for (auto f_it = submesh.faces_begin(); f_it != submesh.faces_end(); ++f_it)
	{
		hh = submesh.halfedge_handle(*f_it);
		e0 = submesh.edge_handle(hh);
		v0 = submesh.from_vertex_handle(hh);

		hh = submesh.next_halfedge_handle(hh); 
		e1 = submesh.edge_handle(hh);
		v1 = submesh.from_vertex_handle(hh);

		hh = submesh.next_halfedge_handle(hh);
		e2 = submesh.edge_handle(hh);
		v2 = submesh.from_vertex_handle(hh);

		//add face
		ctrmesh.add_face({ VH[v2.idx()],VH[e_to_SubV_id[e2.idx()]],VH[e_to_SubV_id[e1.idx()]] });
		ctrmesh.add_face({ VH[e_to_SubV_id[e2.idx()]],VH[v0.idx()],VH[e_to_SubV_id[e0.idx()]] });
		ctrmesh.add_face({ VH[e_to_SubV_id[e2.idx()]],VH[e_to_SubV_id[e0.idx()]],VH[e_to_SubV_id[e1.idx()]] });
		ctrmesh.add_face({ VH[e_to_SubV_id[e1.idx()]],VH[e_to_SubV_id[e0.idx()]],VH[v1.idx()] });

	}

	std::cout << "generate control net mesh finished!!!" << std::endl;

}

void MeshViewerWidget::Genrendermesh()
{
	rendermesh.clear();
	std::vector<CtrMesh::VertexHandle> VH;
	std::vector<CtrMesh::VertexHandle> temp;
	for (auto v_it = ctrmesh.vertices_begin(); v_it != ctrmesh.vertices_end(); ++v_it)
	{
		VH.push_back(rendermesh.add_vertex(ctrmesh.point(*v_it)));
	}
	for (auto f_it = ctrmesh.faces_begin(); f_it != ctrmesh.faces_end(); ++f_it)
	{
		temp.clear();
		for (auto fv_it = ctrmesh.fv_begin(*f_it); fv_it != ctrmesh.fv_end(*f_it); fv_it++)
		{
			temp.push_back(VH[fv_it->idx()]);
		}
		rendermesh.add_face(temp);
	}
	std::cout << "generate rendermesh finished!!!" << std::endl;
	std::cout << "rendermesh v_N:  " << rendermesh.n_vertices() << std::endl;
}

void MeshViewerWidget::updateCurveMeshCenter()
{
	if (is_cal_curve_box_finished == false)
	{
		typedef Mesh::Point Point;
		Mesh::VertexIter vIt = mesh.vertices_begin();
		Mesh::VertexIter vEnd = mesh.vertices_end();
		bbMin = bbMax = OpenMesh::vector_cast<OpenMesh::Vec3d>(mesh.point(vIt));

		size_t count = 0;
		for (; vIt != vEnd; ++vIt, ++count)
		{
			bbMin.minimize(OpenMesh::vector_cast<OpenMesh::Vec3d>(mesh.point(vIt)));
			bbMax.maximize(OpenMesh::vector_cast<OpenMesh::Vec3d>(mesh.point(vIt)));
		}
		is_cal_curve_box_finished = true;
	}

	set_scene_pos((bbMin + bbMax) * 0.5, (bbMin - bbMax).norm() * 0.5); 
	hzb_view();//Adjust the angle of view every time
	//set_Texture_path(path);
}

void MeshViewerWidget::Draw()
{
	//updateCurveMeshCenter();
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	DrawTexture();
	glDisable(GL_LIGHTING);

	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	draw_mesh_wireframe_for_rendermesh();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_POLYGON_OFFSET_FILL);*/



}

void MeshViewerWidget::DrawTexture()
{

	glShadeModel(GL_SMOOTH);


	glBindTexture(GL_TEXTURE_2D, glTextureID);

	glEnable(GL_TEXTURE_2D); 

	glBegin(GL_TRIANGLES);

	if (is_using_samplemesh)
	{
		 
		std::string filename = "../src/Texture_test/cuted_mesh_chair_bijective_para.obj"; 
		CtrMesh samplemesh_;
		CtrMesh::Point P{ 0.,0.,0. };
		OpenMesh::IO::read_mesh(samplemesh_, filename);

		double max_x = -100000; double max_y = -100000; double min_x = 100000; double min_y = 100000;
		for (auto v_it = samplemesh_.vertices_begin(); v_it != samplemesh_.vertices_end(); ++v_it)
		{
			Mesh::Point p = samplemesh_.point(v_it);
			if (max_x < p[0])
			{
				max_x = p[0];
			}
			if (min_x > p[0])
			{
				min_x = p[0];
			}
			if (max_y < p[1])
			{
				max_y = p[1];
			}
			if (min_y > p[1])
			{
				min_y = p[1];
			}
		}
		double x_scale = max_x - min_x;
		double y_scale = max_y - min_y;

		string s = "../src//Texture_test/res_chair.txt";
		std::ifstream ifs(s);
		vector<int> res(17887);
		for (int i = 0; i < res.size(); i++) {
			ifs >> res[i];

		}
		//Now traverse the faces on the parameterized open mesh
		for (auto f_it = samplemesh_.faces_begin(); f_it != samplemesh_.faces_end(); f_it++) {
			for (auto fv_it = samplemesh_.fv_begin(*f_it); fv_it != samplemesh_.fv_end(*f_it); fv_it++) {
				int id = res[fv_it->idx()];
				auto P = samplemesh_.point(*fv_it);

				glTexCoord2f((P[0] - min_x) / x_scale, (P[1] - min_y) / y_scale);
				glVertex3dv(samplemesh.point(samplemesh.vertex_handle(id)).data());
			}


		}
		 
	}
	else
	{
		for (auto f_it = rendermesh.faces_begin(); f_it != rendermesh.faces_end(); f_it++)
		{
			for (auto fv_it = rendermesh.fv_begin(*f_it); fv_it != rendermesh.fv_end(*f_it); fv_it++)
			{
				auto uv = rendermesh.texcoord2D(*fv_it);
				float uvScale = 4.f; 
				glTexCoord2f(uv[0] * uvScale, uv[1] * uvScale);
				glVertex3dv(rendermesh.point(*fv_it).data());

			}

		}


	}


	glEnd();
	glDisable(GL_TEXTURE_2D); 
}

void MeshViewerWidget::draw_curve_edge()
{

	//updateCurveMeshCenter();
	int e_n = sample_P_OnCurveEdge.size();
	int sample_n = sample_P_OnCurveEdge[0].size() - 1;
	glColor3d(0.0, 0.0, 0.0);
	//glColor3d(0.02, 0.88, 0.98);
	//glLineWidth(2.5);
	glLineWidth(1.2);

	for (int i = 0; i < e_n; i++)
	{
		auto Curve_P = sample_P_OnCurveEdge[i];
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= sample_n; j++)
		{
			glVertex3dv(Curve_P[j].data());
		}
		glEnd();
	}

	/*glColor3f(0.0, 1.0, 1.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	Mesh::VertexHandle vh = mesh.vertex_handle(161);

	glVertex3dv(mesh.point(vh).data());

	Mesh::VertexHandle vh1 = mesh.vertex_handle(406);

	glVertex3dv(mesh.point(vh1).data());

	glEnd();*/
}


 
void MeshViewerWidget::draw_curve_face()
{
	updateCurveMeshCenter();
	glColor3d(0.88, 0.88, 0.88);//
	glBegin(GL_TRIANGLES);
	/*for (auto f_it = ctrmesh.faces_begin(); f_it != ctrmesh.faces_end(); f_it++)
	{
		for (auto fv_it = ctrmesh.fv_begin(*f_it); fv_it != ctrmesh.fv_end(*f_it); fv_it++)
		{
			glVertex3dv(ctrmesh.point(*fv_it).data());
		}

	}*/
	for (auto f_it = samplemesh.faces_begin(); f_it != samplemesh.faces_end(); f_it++)
	{
		for (auto fv_it = samplemesh.fv_begin(*f_it); fv_it != samplemesh.fv_end(*f_it); fv_it++)
		{
			glVertex3dv(samplemesh.point(*fv_it).data());
		}

	}
	glEnd();

}


void MeshViewerWidget::Get_sample()
{
	Mesh::HalfedgeHandle hh;
	int deg = 2;
	double tmin = 0.;
	double tmax = 1.;
	std::vector<Point3> controlpoints;
	controlpoints.resize(deg + 1, Point3{ 0.,0.,0. });
	BezierCurve bc = BezierCurve(deg, tmin, tmax, controlpoints);
	int sample_n = 100;
	std::vector<Mesh::Point> temp_P;
	temp_P.resize(sample_n + 1, Mesh::Point{ 0.,0.,0. });
	Mesh::Point P_;
	for (auto e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it)
	{
		hh = e_it->halfedge(0);
		P_ = mesh.point(mesh.from_vertex_handle(hh));
		controlpoints[0] << P_[0], P_[1], P_[2];
		P_ = mesh.data(*e_it).ctp;
		controlpoints[1] << P_[0], P_[1], P_[2];
		P_ = mesh.point(mesh.to_vertex_handle(hh));
		controlpoints[2] << P_[0], P_[1], P_[2];
		bc.SetControlPoints(controlpoints);
		for (int j = 0; j <= sample_n; j++)
		{
			auto P = bc(double(1. * j / sample_n));
			//std::cout << "Sample "<<P << std::endl;
			temp_P[j] = Mesh::Point{ P(0),P(1),P(2) };
		}
		sample_P_OnCurveEdge[e_it->idx()] = temp_P;

	}


	std::cout << "Sample finished!" << std::endl;


}
 
 

void MeshViewerWidget::updataCurveMeshPoints(Eigen::VectorXd& position_of_mesh)
{
	for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		int v_id = v_it->idx();
		mesh.set_point(*v_it, Mesh::Point{ position_of_mesh(v_id),position_of_mesh(v_id + V_N),position_of_mesh(v_id + 2 * V_N) });
	}
	for (auto e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it)
	{
		int ctp_id = mesh.data(*e_it).ctp_id;
		mesh.data(*e_it).ctp = Mesh::Point{ position_of_mesh(ctp_id),position_of_mesh(ctp_id + V_N),position_of_mesh(ctp_id + 2 * V_N) };
	}

}
void MeshViewerWidget::updataCurveMeshPoints(Eigen::MatrixXd& target_V)
{
	for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		int v_id = v_it->idx();
		mesh.set_point(*v_it, Mesh::Point{ target_V(v_id,0),target_V(v_id,1),target_V(v_id,2) });
	}
	for (auto e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it)
	{
		int ctp_id = mesh.data(*e_it).ctp_id;
		mesh.data(*e_it).ctp = Mesh::Point{ target_V(ctp_id,0),target_V(ctp_id,1),target_V(ctp_id,2) };
	}

}

void MeshViewerWidget::Updata_For_rendermesh()
{
	for (auto v_it = rendermesh.vertices_begin(); v_it != rendermesh.vertices_end(); ++v_it)
	{
		rendermesh.set_point(*v_it, ctrmesh.point(ctrmesh.vertex_handle(v_it->idx())));
	}

}

void MeshViewerWidget::GenSampleMesh()
{
	std::cout << "==================== generate Sample mesh Start !!! ==============================" << std::endl;
	samplemesh.clear();

	bool is_z_negtive = false; 
	 
	std::vector<SampleMesh::VertexHandle> VH;
	OpenMesh::Vec3d P;
	for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); v_it++)
	{
		P = mesh.point(*v_it);
		if (is_z_negtive) P[2] *= -1;
		VH.push_back(samplemesh.add_vertex(P));
	}

	 
	int n_e = mesh.n_edges();
	std::vector<bool> edge_samples_generated(n_e, false);
	std::vector<std::vector<int>> edge_vec_IJ_to_sample_id(n_e); 
	std::vector<int> edge_sample_id(samplemesh_sample_num - 1, -1);

	int total_sample_num_on_face = (samplemesh_sample_num + 1) * (samplemesh_sample_num + 2) / 2;
	std::vector<int> tmp_IJ_to_sample_id(total_sample_num_on_face, -1);
	std::cout << "================== total_sample_num_on_face is: " << total_sample_num_on_face << " ===========================" << std::endl;

	Mesh::HalfedgeHandle hh;
	Mesh::VertexHandle v0;
	Mesh::VertexHandle v1;
	Mesh::VertexHandle v2;
	Mesh::EdgeHandle e0;
	Mesh::EdgeHandle e1;
	Mesh::EdgeHandle e2;

	 
	std::vector<OpenMesh::Vec3d> ctp(6, { 0.,0.,0. });
	int idx = 0;
	int n_ = samplemesh_sample_num + 1;
	std::cout << "================== sample num is: " << samplemesh_sample_num << " ===============" << std::endl;
	int samplemesh_idx = mesh.n_vertices(); 
	int degree = 2;

	for (auto f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		int first_vh_id = mesh.data(*f_it).fv_id_with_m_T;
		hh = mesh.halfedge_handle(*f_it);
		v0 = mesh.from_vertex_handle(hh);

		if (v0.idx() != first_vh_id) {
			hh = mesh.next_halfedge_handle(hh);
			v0 = mesh.from_vertex_handle(hh);
		}
		if (v0.idx() != first_vh_id) {
			hh = mesh.next_halfedge_handle(hh);
			v0 = mesh.from_vertex_handle(hh);
		}
		if (v0.idx() != first_vh_id) std::cout << "######################## ???????? ##################" << std::endl;
		 
		e0 = mesh.edge_handle(hh);
		ctp[0] = mesh.point(v0);

		hh = mesh.next_halfedge_handle(hh); 
		e1 = mesh.edge_handle(hh);
		v1 = mesh.from_vertex_handle(hh);
		ctp[2] = mesh.point(v1);

		hh = mesh.next_halfedge_handle(hh);
		e2 = mesh.edge_handle(hh);
		v2 = mesh.from_vertex_handle(hh);
		ctp[5] = mesh.point(v2);

		ctp[1] = mesh.data(e0).ctp;
		ctp[3] = mesh.data(e2).ctp;
		ctp[4] = mesh.data(e1).ctp;

		 
		idx = IJ_to_index_for_XY_Priority(0, 0, n_);
		tmp_IJ_to_sample_id[idx] = v0.idx(); 

		idx = IJ_to_index_for_XY_Priority(samplemesh_sample_num, 0, n_);
		tmp_IJ_to_sample_id[idx] = v1.idx();


		idx = IJ_to_index_for_XY_Priority(0, samplemesh_sample_num, n_);
		tmp_IJ_to_sample_id[idx] = v2.idx();


		 
		if (edge_samples_generated[e0.idx()] == false)
		{
			for (int i = 1; i < samplemesh_sample_num; i++)
			{
			 
				double uu = double(i) / samplemesh_sample_num;
				double vv = 0;
				P = decast_2D(degree, ctp, uu, vv);
				if (is_z_negtive) P[2] *= -1;
				VH.push_back(samplemesh.add_vertex(P));
				idx = IJ_to_index_for_XY_Priority(i, 0, n_);
				tmp_IJ_to_sample_id[idx] = samplemesh_idx;
				edge_sample_id[i - 1] = samplemesh_idx; 
				samplemesh_idx++;


			}
			edge_samples_generated[e0.idx()] = true;
			edge_vec_IJ_to_sample_id[e0.idx()] = edge_sample_id; 

		}
		else 
		{
			auto tmp = edge_vec_IJ_to_sample_id[e0.idx()];
			for (int i = 1; i < samplemesh_sample_num; i++)
			{
				idx = IJ_to_index_for_XY_Priority(i, 0, n_);
				tmp_IJ_to_sample_id[idx] = tmp[samplemesh_sample_num - 1 - i];

			}



		}

		 
		if (edge_samples_generated[e1.idx()] == false)
		{
			for (int i = 1; i < samplemesh_sample_num; i++)
			{
				double uu = double(samplemesh_sample_num - i) / samplemesh_sample_num;
				double vv = double(i) / samplemesh_sample_num;
				P = decast_2D(degree, ctp, uu, vv);
				if (is_z_negtive) P[2] *= -1;
				VH.push_back(samplemesh.add_vertex(P));
				idx = IJ_to_index_for_XY_Priority(samplemesh_sample_num - i, i, n_);
				tmp_IJ_to_sample_id[idx] = samplemesh_idx;
				edge_sample_id[i - 1] = samplemesh_idx; 
				samplemesh_idx++;

			}
			edge_samples_generated[e1.idx()] = true;
			edge_vec_IJ_to_sample_id[e1.idx()] = edge_sample_id; 

		}
		else
		{
			auto tmp = edge_vec_IJ_to_sample_id[e1.idx()];//
			for (int i = 1; i < samplemesh_sample_num; i++)
			{
				idx = IJ_to_index_for_XY_Priority(samplemesh_sample_num - i, i, n_);
				tmp_IJ_to_sample_id[idx] = tmp[samplemesh_sample_num - 1 - i];

			}
		}

		 
		if (edge_samples_generated[e2.idx()] == false)
		{
			for (int i = 1; i < samplemesh_sample_num; i++)
			{
				double uu = 0;
				double vv = double(samplemesh_sample_num - i) / samplemesh_sample_num;
				P = decast_2D(degree, ctp, uu, vv);
				if (is_z_negtive) P[2] *= -1;

				VH.push_back(samplemesh.add_vertex(P));
				idx = IJ_to_index_for_XY_Priority(0, samplemesh_sample_num - i, n_);
				tmp_IJ_to_sample_id[idx] = samplemesh_idx;
				edge_sample_id[i - 1] = samplemesh_idx; 
				samplemesh_idx++;

			}
			edge_samples_generated[e2.idx()] = true;
			edge_vec_IJ_to_sample_id[e2.idx()] = edge_sample_id; 

		}
		else
		{
			auto tmp = edge_vec_IJ_to_sample_id[e2.idx()];//
			for (int i = 1; i < samplemesh_sample_num; i++)
			{
				idx = IJ_to_index_for_XY_Priority(0, samplemesh_sample_num - i, n_);
				tmp_IJ_to_sample_id[idx] = tmp[samplemesh_sample_num - 1 - i];

			}


		}
		 
		for (int i = 1; i < samplemesh_sample_num - 1; i++)
		{
			for (int j = 1; j <= samplemesh_sample_num - 1 - i; j++)
			{
				double uu = double(i) / samplemesh_sample_num;
				double vv = double(j) / samplemesh_sample_num;
				P = decast_2D(degree, ctp, uu, vv);
				if (is_z_negtive) P[2] *= -1;

				VH.push_back(samplemesh.add_vertex(P));
				idx = IJ_to_index_for_XY_Priority(i, j, n_);
				tmp_IJ_to_sample_id[idx] = samplemesh_idx;
				samplemesh_idx++;

				 
			}

		}

		mesh.data(*f_it).IJ_to_sample_id = tmp_IJ_to_sample_id; 
		std::fill(tmp_IJ_to_sample_id.begin(), tmp_IJ_to_sample_id.end(), -1); 
		for (size_t i = 0; i < tmp_IJ_to_sample_id.size(); i++)
		{
			if (tmp_IJ_to_sample_id[i] != -1) std::cout << "###################################" << std::endl;
		}

	}


	 
	int nV_samplemesh = samplemesh.n_vertices();
	std::cout << "================================= samplemesh vn is: " << nV_samplemesh << "  ,VH size is: " << VH.size() << " ===========================" << std::endl;

	int tri_v0_id = 0;
	int tri_v1_id = 0;
	int tri_v2_id = 0;
	int iter_num = 0;

	for (auto f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		tmp_IJ_to_sample_id.clear();
		tmp_IJ_to_sample_id = mesh.data(*f_it).IJ_to_sample_id;

		 
		for (int i = 0; i < samplemesh_sample_num; i++)
		{
			for (int j = 0; j < samplemesh_sample_num - i; j++)
			{
				int d0 = IJ_to_index_for_XY_Priority(i, j, n_);
				int d1 = IJ_to_index_for_XY_Priority(i + 1, j, n_);
				int d2 = IJ_to_index_for_XY_Priority(i, j + 1, n_);
				if (d0 >= 0 && d0 < tmp_IJ_to_sample_id.size())
				{

				}
				else
				{
					std::cout << "1*****************************" << std::endl;
				}
				if (d1 >= 0 && d1 < tmp_IJ_to_sample_id.size())
				{

				}
				else
				{
					std::cout << "1*****************************" << std::endl;
				}
				if (d2 >= 0 && d2 < tmp_IJ_to_sample_id.size())
				{

				}
				else
				{
					std::cout << "1*****************************" << std::endl;
				}
				tri_v0_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i, j, n_)];
				tri_v1_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i + 1, j, n_)];
				tri_v2_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i, j + 1, n_)];
				if (tri_v0_id >= 0 && tri_v0_id < VH.size())
				{

				}
				else
				{

					std::cout << "1===================== tri_v0_id is: " << tri_v0_id << " ====================" << std::endl;
				}
				if (tri_v1_id >= 0 && tri_v1_id < VH.size())
				{

				}
				else
				{

					std::cout << "1===================== tri_v1_id is: " << tri_v1_id << " ====================" << std::endl;
				}
				if (tri_v2_id >= 0 && tri_v2_id < VH.size())
				{

				}
				else
				{

					std::cout << "1===================== tri_v2_id is: " << tri_v2_id << " ====================" << std::endl;
				}
				samplemesh.add_face({ VH[tri_v0_id],VH[tri_v1_id],VH[tri_v2_id] });
			}
		}

		 
		for (int i = 1; i < samplemesh_sample_num; i++)
		{
			for (int j = 1; j <= samplemesh_sample_num - i; j++)
			{
				int d0 = IJ_to_index_for_XY_Priority(i, j, n_);
				int d1 = IJ_to_index_for_XY_Priority(i - 1, j, n_);
				int d2 = IJ_to_index_for_XY_Priority(i, j - 1, n_);
				if (d0 >= 0 && d0 < tmp_IJ_to_sample_id.size())
				{

				}
				else
				{
					std::cout << "2*****************************" << std::endl;
				}
				if (d1 >= 0 && d1 < tmp_IJ_to_sample_id.size())
				{

				}
				else
				{
					std::cout << "2*****************************" << std::endl;
				}
				if (d2 >= 0 && d2 < tmp_IJ_to_sample_id.size())
				{

				}
				else
				{
					std::cout << "2*****************************" << std::endl;
				}
				tri_v0_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i, j, n_)];
				tri_v1_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i - 1, j, n_)];
				tri_v2_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i, j - 1, n_)];
				if (tri_v0_id >= 0 && tri_v0_id < VH.size())
				{

				}
				else
				{

					std::cout << "2===================== tri_v0_id is: " << tri_v0_id << " ====================" << std::endl;
				}
				if (tri_v1_id >= 0 && tri_v1_id < VH.size())
				{

				}
				else
				{

					std::cout << "2===================== tri_v1_id is: " << tri_v1_id << " ====================" << std::endl;
				}
				if (tri_v2_id >= 0 && tri_v2_id < VH.size())
				{

				}
				else
				{

					std::cout << "2===================== tri_v2_id is: " << tri_v2_id << " ====================" << std::endl;
				}
				samplemesh.add_face({ VH[tri_v0_id],VH[tri_v1_id],VH[tri_v2_id] });
			}
		}

		//std::cout << "====================This is iter_num : " << iter_num << " ====================" << std::endl;
		iter_num++;
	}

	std::cout << "==================== generate Sample mesh finished !!! ==============================" << std::endl;

}

 
void MeshViewerWidget::UpdateSampleMesh()
{
	int n_v_samplemesh = samplemesh.n_vertices();
	std::vector<bool> is_updated_for_sample_ver(n_v_samplemesh, false); 
	int n_ = samplemesh_sample_num + 1;
	int degree = 2;

	bool is_z_negtive = false; 

	Mesh::HalfedgeHandle hh;
	Mesh::VertexHandle v0;
	Mesh::VertexHandle v1;
	Mesh::VertexHandle v2;
	Mesh::EdgeHandle e0;
	Mesh::EdgeHandle e1;
	Mesh::EdgeHandle e2;

	 
	std::vector<OpenMesh::Vec3d> ctp(6, { 0.,0.,0. });

	OpenMesh::Vec3d P;

	std::vector<int> tmp_IJ_to_sample_id;
	int samplemesh_v_id = 0;
	for (auto f_it = mesh.faces_begin(); f_it != mesh.faces_end(); f_it++)
	{
		tmp_IJ_to_sample_id = mesh.data(*f_it).IJ_to_sample_id;

		int first_vh_id = mesh.data(*f_it).fv_id_with_m_T;
		hh = mesh.halfedge_handle(*f_it);
		v0 = mesh.from_vertex_handle(hh);

		if (v0.idx() != first_vh_id) {
			hh = mesh.next_halfedge_handle(hh);
			v0 = mesh.from_vertex_handle(hh);
		}
		if (v0.idx() != first_vh_id) {
			hh = mesh.next_halfedge_handle(hh);
			v0 = mesh.from_vertex_handle(hh);
		}
		if (v0.idx() != first_vh_id) std::cout << "######################## ???????? ##################" << std::endl;
		 
		e0 = mesh.edge_handle(hh);
		ctp[0] = mesh.point(v0);


		hh = mesh.next_halfedge_handle(hh); 
		e1 = mesh.edge_handle(hh);
		v1 = mesh.from_vertex_handle(hh);
		ctp[2] = mesh.point(v1);


		hh = mesh.next_halfedge_handle(hh);
		e2 = mesh.edge_handle(hh);
		v2 = mesh.from_vertex_handle(hh);
		ctp[5] = mesh.point(v2);


		ctp[1] = mesh.data(e0).ctp;
		ctp[3] = mesh.data(e2).ctp;
		ctp[4] = mesh.data(e1).ctp;

		 
		for (int i = 0; i < samplemesh_sample_num + 1; i++)
		{
			for (int j = 0; j < samplemesh_sample_num + 1 - i; j++)
			{
				samplemesh_v_id = tmp_IJ_to_sample_id[IJ_to_index_for_XY_Priority(i, j, n_)];
				 
				if (is_updated_for_sample_ver[samplemesh_v_id] == false)
				{
					 
					double uu = double(i) / samplemesh_sample_num;
					double vv = double(j) / samplemesh_sample_num;
					P = decast_2D(degree, ctp, uu, vv);
					if (is_z_negtive) P[2] *= -1;

					samplemesh.set_point(samplemesh.vertex_handle(samplemesh_v_id), P); 
					is_updated_for_sample_ver[samplemesh_v_id] = true; 

				}

			}

		}



	}



}

int MeshViewerWidget::ijtoIndex(int i, int j, int n) 
{
	return i + j * n - j * (j - 1) / 2;
}

 
int MeshViewerWidget::IJ_to_index_for_XY_Priority(int i, int  j, int n)
{
	return i + j * n - j * (j - 1) / 2;

}

template <typename T>
T  MeshViewerWidget::decast_2D(int& n, std::vector<T> b, double& u, double& v) 
{
	double w = 1 - u - v;
	if (b.size() != ((n + 1) * (n + 2) / 2))
	{
		std::cout << "=============== 2D decast Error ==================" << std::endl;
		return T();
	}

	for (int r = 1; r <= n; r++)
	{
		int idx = 0;
		int order = n - r; 
		for (int j = 0; j < order + 1; ++j) {
			for (int i = 0; i < order + 1 - j; ++i) {
				// i+j<=order-1
				//int k=order-i-j;
				T P = u * b[ijtoIndex(i + 1, j, order + 2)] + v * b[ijtoIndex(i, j + 1, order + 2)] + w * b[ijtoIndex(i, j, order + 2)];
				//b[ij2Index(i, j, order + 1)] = P;
				b[idx] = P;
				idx++;

			}
		}


	}

	return b[0];

}


