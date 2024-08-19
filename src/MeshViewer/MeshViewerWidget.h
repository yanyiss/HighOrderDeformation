#ifndef MESHPROCESSING_MESHVIEWERWIDGET_H
#define MESHPROCESSING_MESHVIEWERWIDGET_H

#include <QString>
#include <QMessageBox>
#include <QFileDialog>

#include "QGLViewerWidget.h"
#include "MeshDefinition.h"
#include "Bezier3DData.h"

class MeshViewerWidget : public QGLViewerWidget
{
	Q_OBJECT
public:
	MeshViewerWidget(QWidget* parent = 0);
	MeshViewerWidget(QGLFormat& _fmt, QWidget* _parent);
	~MeshViewerWidget();
public:
	bool openMesh(const char* filename);
	void initMesh();
	bool saveMesh(const char* filename);
	bool saveScreen(const char* filePath);
	Mesh* mesh_ptr() { return &mesh; };
	Mesh& mesh_ref() { return mesh; };
	const Mesh& mesh_cref() const { return mesh; };
	void updateMesh()
	{
		updateMeshNormals();
		updateMeshCenter();
	};
	virtual void clearAllMesh()
	{
		mesh_vector.clear(); mesh_vector_index = -1;
		mesh.clear();
		//index
		//Indices.clear();
		//VIndices.clear();

		//first_init = true;
		updateGL();
	};

	void set_draw_bbox_ok()
	{
		draw_BBox_OK = draw_BBox_OK ? false : true;
		updateGL();
	}
	void set_draw_mesh_boundary_ok()
	{
		draw_mesh_boundary_ok = draw_mesh_boundary_ok ? false : true;
		updateGL();
	}
	void printBasicMeshInfo();

	 
	void Perorm_Curve_Morphing_Using_SamplingOptimization(std::string source, std::string target); 

	void Perorm_Curve_Deformation(std::string source); 

	void  Render_Only_Use_mydata(std::string source);

	 

	void GenSampleMesh();
	void UpdateSampleMesh();


	void GenMesh(Bezier3D2d& d_);
	void GenSubMesh();
	void GenctrMesh();
	void Genrendermesh();
	void updateCurveMeshCenter();
	void Draw();
	void DrawTexture();
	void draw_curve_edge();
	void draw_curve_face();
	void Get_sample();

	 
	void Updata_For_rendermesh();

	void updataCurveMeshPoints(Eigen::MatrixXd& target_V);
	void updataCurveMeshPoints(Eigen::VectorXd& position_of_mesh);

	 
	int ijtoIndex(int i, int j, int n); 

	int IJ_to_index_for_XY_Priority(int i, int  j, int n);

	template <typename T>
	T  decast_2D(int& n, std::vector<T>  b, double& u, double& v); 


signals:
	void loadMeshOK(bool, QString);

protected:
	void updateMeshCenter(); // used by update_mesh().
	void updateMeshNormals(); // used by update_mesh().

protected:
	virtual void draw_scene(int drawmode);
	void draw_scene_mesh(int drawmode);

private:
	void draw_mesh_wireframe();
	void draw_mesh_hidden_lines() const;
	void draw_mesh_solidflat() const;
	void draw_mesh_solidsmooth() const;
	void draw_mesh_pointset() const;

protected:
	bool first_init;
	OpenMesh::Vec3d bbMin;
	OpenMesh::Vec3d bbMax;
	Mesh mesh;
	Mesh submesh;
	CtrMesh ctrmesh;
	CtrMesh rendermesh;
	std::vector<CtrMesh::TexCoord2D> texture_vec;
	size_t subvison_num;//use for rendering
	bool draw_BBox_OK;
	bool draw_mesh_boundary_ok;
	std::vector<Mesh> mesh_vector;
	int mesh_vector_index;

	 
	//int samplemesh_sample_num = 6; 
	int samplemesh_sample_num = 10;//only for bird and chair

	SampleMesh samplemesh;

	bool is_using_samplemesh = true; 

	bool is_using_texture = true; 

	bool is_draw_curve_boundary = true; 

	bool is_store_data = true; 

	bool is_output_normalize_distortion = true; 
private:
	void updateIndices();
public:
	// mesh modes.
	enum { TRIANGLE = 0, QUAD, N_MESH_MODES };
	void setMeshMode(int mm) { mesh_mode_ = mm; }
	int meshMode() const { return mesh_mode_; }
	void checkMeshMode();

	 
	std::string base = "TwiceVolumeData8";
private:
	int mesh_mode_;
	//std::vector<unsigned int> Indices;
	//std::vector<unsigned int> VIndices;

	//by hzb
	std::vector<std::vector<Mesh::Point>>  sample_P_OnCurveEdge;
	bool is_cal_curve_box_finished;
	int V_N; 
	int sur_V_num; 
	int sur_Ver_num; 
	int tri_F_num; 
};

#endif // MESHPROCESSING_MESHVIEWERWIDGET_H
