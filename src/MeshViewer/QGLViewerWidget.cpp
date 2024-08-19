#include <iomanip>
#include <sstream>
#include <algorithm>

#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>

#include "QGLViewerWidget.h"
#include <QOpenGLTexture>

#include "stb_image.h"
 
#include <iostream>

#if !defined(M_PI)
#  define M_PI 3.1415926535897932
#endif

const double TRACKBALL_RADIUS = 0.6;

//using namespace Qt;

QGLViewerWidget::QGLViewerWidget(QWidget* _parent)
	: QGLWidget(_parent)
{
	init();
}

QGLViewerWidget::
QGLViewerWidget(QGLFormat& _fmt, QWidget* _parent)
	: QGLWidget(_fmt, _parent)
{
	init();
}

void QGLViewerWidget::init(void)
{
	// qt stuff
	setAttribute(Qt::WA_NoSystemBackground, true);
	setFocusPolicy(Qt::StrongFocus);
	//setAcceptDrops( true );  
	//setCursor(PointingHandCursor);

	// draw mode
	//draw_mode_ = SOLID_SMOOTH;
	mouse_mode_ = Qt::NoButton;

	//initialize
	ModelViewMatrix.resize(16, 0.0);
	ProjectionMatrix.resize(16, 0.0);

	Center = OpenMesh::Vec3d(0, 0, 0);
	Radius = 0.0;

	//SetGlWindoPosFunc();
	//BuildFont(NULL);
	pro_mode_ = PERSPECTIVE;
	set_pro_mode(PERSPECTIVE);
}

QGLViewerWidget::~QGLViewerWidget()
{
	//KillFont();
}

QSize QGLViewerWidget::minimumSizeHint() const
{
	return QSize(10, 10);
}

QSize QGLViewerWidget::sizeHint() const
{
	QRect rect = QApplication::desktop()->screenGeometry();
	return QSize(int(rect.width() * 0.8), int(rect.height() * 1.0));
}

void QGLViewerWidget::setDefaultMaterial(void)
{
	// material
#if 1
	GLfloat mat_a[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_d[] = { 0.88f, 0.84f, 0.76f, 1.0f };
	GLfloat mat_s[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat shine[] = { 120.0f };

	/*GLfloat mat_a[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
	GLfloat mat_d[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat mat_s[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	GLfloat shine[] = { 51.2f };*/
#else
	GLfloat mat_a[] = { 0.0, 0.5, 0.75, 1.0 };
	GLfloat mat_d[] = { 0.0, 0.5, 1.0, 1.0 };
	GLfloat mat_s[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat emission[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat shine[] = { 120.0 };
#endif

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}

void QGLViewerWidget::setDefaultLight(void)
{
#if 1
	// lighting
	GLfloat pos1[] = { 20.0f, 20.0f, 20.0f, 0.0f };
	GLfloat pos2[] = { 20.0f, 20.0f, 20.0f, 0.0f };
	//GLfloat pos1[] = { 5.0f, 0.0f, 10.0f, 0.0f };
	//GLfloat pos2[] = { 5.0f, 5.0f, 10.0f, 0.0f };
	GLfloat pos3[] = { 0.0f, 0.0f, 10.0f, 0.0f };
	/*GLfloat col1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat col2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat col3[] = { 0.8f, 0.8f, 0.8f, 1.0f };*/
	GLfloat col1[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat col2[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat col3[] = { 0.8f, 0.8f, 0.8f, 1.0f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, col1);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, col2);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, pos3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, col3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, col3);
#else
	// lighting
	GLfloat pos3[] = { 0.0f, 0.0f, 10.0f, 0.0f };
	GLfloat col3[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT2, GL_POSITION, pos3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, col3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, col3);
#endif

}

void QGLViewerWidget::initializeGL()
{
	// OpenGL state
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClearColor(0.196, 0.196, 0.196, 1.0);
	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	// Material
	setDefaultMaterial();
	// Lighting
	glLoadIdentity();
	setDefaultLight();

	// scene pos and size
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glGetDoublev(GL_MODELVIEW_MATRIX, modelview_matrix_);

	//for initialize all the viewports
	glGetDoublev(GL_MODELVIEW_MATRIX, &ModelViewMatrix[0]);

	set_scene_pos(OpenMesh::Vec3d(0.0, 0.0, 0.0), 1.0);
	LoadTexture();//下载纹理
}

void QGLViewerWidget::resizeGL(int _w, int _h)
{
	glViewport(0, 0, _w, _h);
	update_projection_matrix();
	updateGL();
}

void QGLViewerWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_scene(draw_mode_);

	//renderText(1,1,"");
}

void QGLViewerWidget::draw_scene(int drawmode)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&ProjectionMatrix[0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&ModelViewMatrix[0]);
	assert(drawmode < N_DRAW_MODES);
	switch (drawmode)
	{
	case WIRE_FRAME:
		glDisable(GL_LIGHTING);
		//glutWireTeapot(0.5);
		break;
	case SOLID_FLAT:
		glEnable(GL_LIGHTING);
		glShadeModel(GL_FLAT);
		//glutSolidTeapot(0.5);
		break;
	case FLAT_POINTS:
		glEnable(GL_LIGHTING);
		glShadeModel(GL_FLAT);
		//glutSolidTeapot(0.5);
		break;
	case HIDDEN_LINES:
		glDisable(GL_LIGHTING);
		break;
	case SOLID_SMOOTH:
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		//glutSolidTeapot(0.5);
		break;
	default:
		break;
	}
}

void QGLViewerWidget::mousePressEvent(QMouseEvent* _event)
{
	//assert(mouse_mode_ < N_MOUSE_MODES);
	last_point_2D_ = _event->pos();
	last_point_ok_ = map_to_sphere(last_point_2D_, last_point_3D_);
	mouse_mode_ = _event->button();
}

void QGLViewerWidget::mouseMoveEvent(QMouseEvent* _event)
{
	//assert(mouse_mode_ < N_MOUSE_MODES);

	QPoint newPoint2D = _event->pos();

	// enable GL context
	makeCurrent();

	if (last_point_ok_)
	{
		switch (mouse_mode_)
		{
		case Qt::LeftButton:
			rotation(newPoint2D);
			break;
		case Qt::RightButton:
			translation(newPoint2D);
			break;
		default:
			break;
		}
	} // end of if

	// remember this point
	last_point_2D_ = newPoint2D;
	last_point_ok_ = map_to_sphere(last_point_2D_, last_point_3D_);

	//std::cout << "newPoint2D is " << newPoint2D.x() << " " << newPoint2D.y() << std::endl;

	std::cout << ModelViewMatrix[0] << " " << ModelViewMatrix[4] << " " << ModelViewMatrix[8] << " " << ModelViewMatrix[12] << " " <<
		ModelViewMatrix[1] << " " << ModelViewMatrix[5] << " " << ModelViewMatrix[9] << " " << ModelViewMatrix[13] << " " <<
		ModelViewMatrix[2] << " " << ModelViewMatrix[6] << " " << ModelViewMatrix[10] << " " << ModelViewMatrix[14] << std::endl;

	// trigger redraw
	updateGL();
}

void QGLViewerWidget::mouseReleaseEvent(QMouseEvent* /* _event */)
{
	//assert(mouse_mode_ < N_MOUSE_MODES);
	mouse_mode_ = Qt::NoButton;
	last_point_ok_ = false;


}

void QGLViewerWidget::wheelEvent(QWheelEvent* _event)
{
	// Use the mouse wheel to zoom in/out
	float d = -(float)_event->delta() / 120.0 * 0.05 * Radius;
	translate(OpenMesh::Vec3d(0.0, 0.0, d));
	updateGL();
	_event->accept();

	/*std::cout << ModelViewMatrix[0] << " " << ModelViewMatrix[4] << " " << ModelViewMatrix[8] << " " << ModelViewMatrix[12] << " " <<
		ModelViewMatrix[1] << " " << ModelViewMatrix[5] << " " << ModelViewMatrix[9] << " " << ModelViewMatrix[13] << " " <<
		ModelViewMatrix[2] << " " << ModelViewMatrix[6] << " " << ModelViewMatrix[10] << " " << ModelViewMatrix[14] << std::endl;*/
}

void QGLViewerWidget::keyPressEvent(QKeyEvent* _event)
{
	switch (_event->key())
	{
	case Qt::Key_Q:
	case Qt::Key_Escape:
		qApp->quit();
		break;
	}
	_event->ignore();
}

void QGLViewerWidget::translation(QPoint p)
{
	double z = -(ModelViewMatrix[2] * Center[0] +
		ModelViewMatrix[6] * Center[1] +
		ModelViewMatrix[10] * Center[2] +
		ModelViewMatrix[14]) /
		(ModelViewMatrix[3] * Center[0] +
			ModelViewMatrix[7] * Center[1] +
			ModelViewMatrix[11] * Center[2] +
			ModelViewMatrix[15]);

	double w = width(); double h = height();
	double aspect = w / h;
	double near_plane = 0.01 * Radius;
	double top = tan(fovy() / 2.0f * M_PI / 180.0f) * near_plane;
	double right = aspect * top;

	double dx = p.x() - last_point_2D_.x();
	double dy = p.y() - last_point_2D_.y();

	translate(OpenMesh::Vec3d(2.0 * dx / w * right / near_plane * z,
		-2.0 * dy / h * top / near_plane * z,
		0.0f));
}

void QGLViewerWidget::translate(const OpenMesh::Vec3d& _trans)
{
	// Translate the object by _trans
	// Update modelview_matrix_
	makeCurrent();
	glLoadIdentity();
	glTranslated(_trans[0], _trans[1], _trans[2]);
	glMultMatrixd(&ModelViewMatrix[0]);
	glGetDoublev(GL_MODELVIEW_MATRIX, &ModelViewMatrix[0]);
}

void QGLViewerWidget::rotation(QPoint p)
{
	OpenMesh::Vec3d  newPoint3D;
	bool newPoint_hitSphere = map_to_sphere(p, newPoint3D);
	if (newPoint_hitSphere)
	{
		OpenMesh::Vec3d axis = last_point_3D_ % newPoint3D;
		if (axis.sqrnorm() < 1e-7)
		{
			axis = OpenMesh::Vec3d(1, 0, 0);
		}
		else
		{
			axis.normalize();
		}
		// find the amount of rotation
		OpenMesh::Vec3d d = last_point_3D_ - newPoint3D;
		double t = 0.5 * d.norm() / TRACKBALL_RADIUS;
		if (t < -1.0) t = -1.0;
		else if (t > 1.0) t = 1.0;
		double phi = 2.0 * asin(t);
		double  angle = phi * 180.0 / M_PI;
		rotate(axis, angle);
		//std::cout << "angle is: " << angle << "  " << "axis is : " << axis[0] << " " << axis[1] << " " << axis[2] << std::endl;//**********by hzb
		//angle is: 0.124397  axis is : 0.162599 0.725334 0.668918

	}
	//std::cout << "=======p : " << p.x() << " " << p.y() << std::endl;
}
void QGLViewerWidget::rotate(const OpenMesh::Vec3d& _axis, double _angle)
{
	// Rotate around center center_, axis _axis, by angle _angle
	// Update modelview_matrix_

	OpenMesh::Vec3d t(ModelViewMatrix[0] * Center[0] +
		ModelViewMatrix[4] * Center[1] +
		ModelViewMatrix[8] * Center[2] +
		ModelViewMatrix[12],
		ModelViewMatrix[1] * Center[0] +
		ModelViewMatrix[5] * Center[1] +
		ModelViewMatrix[9] * Center[2] +
		ModelViewMatrix[13],
		ModelViewMatrix[2] * Center[0] +
		ModelViewMatrix[6] * Center[1] +
		ModelViewMatrix[10] * Center[2] +
		ModelViewMatrix[14]);

	makeCurrent();
	glLoadIdentity();
	glTranslatef(t[0], t[1], t[2]);
	glRotated(_angle, _axis[0], _axis[1], _axis[2]);
	glTranslatef(-t[0], -t[1], -t[2]);
	glMultMatrixd(&ModelViewMatrix[0]);
	glGetDoublev(GL_MODELVIEW_MATRIX, &ModelViewMatrix[0]);
}

bool QGLViewerWidget::map_to_sphere(const QPoint& _v2D, OpenMesh::Vec3d& _v3D)
{
	// This is actually doing the Sphere/Hyperbolic sheet hybrid thing,
	// based on Ken Shoemake's ArcBall in Graphics Gems IV, 1993.
	double x = (2.0 * _v2D.x() - width()) / width();
	double y = -(2.0 * _v2D.y() - height()) / height();
	double xval = x;
	double yval = y;
	double x2y2 = xval * xval + yval * yval;

	const double rsqr = TRACKBALL_RADIUS * TRACKBALL_RADIUS;
	_v3D[0] = xval;
	_v3D[1] = yval;
	if (x2y2 < 0.5 * rsqr)
	{
		_v3D[2] = sqrt(rsqr - x2y2);
	}
	else
	{
		_v3D[2] = 0.5 * rsqr / sqrt(x2y2);
	}

	return true;
}

void QGLViewerWidget::update_projection_matrix()
{
	makeCurrent();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (PERSPECTIVE == pro_mode_)
	{
		gluPerspective(45.0, (GLfloat)width() / (GLfloat)height(), 0.01 * Radius, 100.0 * Radius);

	}
	else if (ORTHOTROPIC2D == pro_mode_) //not work for 
	{
		gluOrtho2D(w_left, w_right, w_bottom, w_top);
	}
	else
	{
	}

	glGetDoublev(GL_PROJECTION_MATRIX, &ProjectionMatrix[0]);

	//glGetDoublev(GL_PROJECTION_MATRIX, projection_matrix_);
	glMatrixMode(GL_MODELVIEW);
}

void QGLViewerWidget::update_projection_matrix_one_viewer()
{
	makeCurrent();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width() / (GLfloat)height(), 0.01 * Radius, 100.0 * Radius);
	glGetDoublev(GL_PROJECTION_MATRIX, &ProjectionMatrix[0]);
	glMatrixMode(GL_MODELVIEW);
}
void QGLViewerWidget::set_Texture_path(std::string t_path)
{
	TexturePath = t_path;
}

void QGLViewerWidget::hzb_view()
{
	//QPoint newPoint2D{ 549, 420 };
	// enable GL context
	//makeCurrent();
	//if (last_point_ok_)
	//{
	//	rotation(newPoint2D);
	//} // end of if
	//// remember this point
	//last_point_2D_ = newPoint2D;
	//last_point_ok_ = map_to_sphere(last_point_2D_, last_point_3D_);
	//// trigger redraw
	//updateGL();
	//translation(newPoint2D);
	//bird
	//0.680321 -0.332097 0.653352 -0.364692 // -0.179149 0.789056 0.587618 -0.54647 // -0.710678 -0.516816 0.477316 -1.87564
	/*ModelViewMatrix[0] = 0.680321;
	ModelViewMatrix[4] = -0.332097;
	ModelViewMatrix[8] = 0.653352;
	ModelViewMatrix[12] = -0.364692;


	ModelViewMatrix[1] = -0.179149;
	ModelViewMatrix[5] = 0.789056;
	ModelViewMatrix[9] = 0.587618;
	ModelViewMatrix[13] = -0.54647;


	ModelViewMatrix[2] = -0.710678;
	ModelViewMatrix[6] = -0.516816;
	ModelViewMatrix[10] = 0.477316;
	ModelViewMatrix[14] = -1.87564;*/

	//hand 
	//0.895092 0.442138 0.0574514 0.606003 // 0.0333999 -0.194982 0.980223 -3.78882 // 0.444603 -0.875478 -0.18929 -27.147
	/*ModelViewMatrix[0] = 0.895092;
	ModelViewMatrix[4] = 0.442138;
	ModelViewMatrix[8] = 0.0574514;
	ModelViewMatrix[12] = 0.606003;


	ModelViewMatrix[1] = 0.0333999;
	ModelViewMatrix[5] = -0.194982;
	ModelViewMatrix[9] = 0.980223;
	ModelViewMatrix[13] = -3.78882;


	ModelViewMatrix[2] = 0.444603;
	ModelViewMatrix[6] = -0.875478;
	ModelViewMatrix[10] = -0.18929;
	ModelViewMatrix[14] = -27.147;*/

	//管子
	//0.999015 0.00975265 0.0432864 -0.00607433 // -0.00384442 0.9909 -0.134531 -0.618481 // -0.0442048 0.134232 0.98996 -14.3531
	/*ModelViewMatrix[0] = 0.999015;
	ModelViewMatrix[4] = 0.00975265;
	ModelViewMatrix[8] = 0.0432864;
	ModelViewMatrix[12] = -0.00607433;


	ModelViewMatrix[1] = -0.00384442;
	ModelViewMatrix[5] = 0.9909;
	ModelViewMatrix[9] = -0.134531;
	ModelViewMatrix[13] = -0.618481;


	ModelViewMatrix[2] = -0.0442048;
	ModelViewMatrix[6] = 0.134232;
	ModelViewMatrix[10] = 0.98996;
	ModelViewMatrix[14] = -14.3531;*/

	//wa
	//0.906225 -0.421282 0.0351278 0.0681411 // 0.0338874 0.155213 0.987286 0.291547 // -0.421385 -0.893516 0.15494 -9.69503
	/*ModelViewMatrix[0] = 0.906225;
	ModelViewMatrix[4] = -0.421282;
	ModelViewMatrix[8] = 0.0351278;
	ModelViewMatrix[12] = 0.0681411;


	ModelViewMatrix[1] = 0.0338874;
	ModelViewMatrix[5] = 0.155213;
	ModelViewMatrix[9] = 0.987286;
	ModelViewMatrix[13] = 0.291547;


	ModelViewMatrix[2] = -0.421385;
	ModelViewMatrix[6] = -0.893516;
	ModelViewMatrix[10] = 0.15494;
	ModelViewMatrix[14] = -9.69503;*/

	//wa2  
	//0.911673 0.397317 -0.104804 -0.0869556 // 0.0417227 0.164226 0.985535 0.289773  // 0.408783 -0.902861 0.133142 -9.70068
	/*ModelViewMatrix[0] = 0.911673;
	ModelViewMatrix[4] = 0.397317;
	ModelViewMatrix[8] = -0.104804;
	ModelViewMatrix[12] = -0.0869556;


	ModelViewMatrix[1] = 0.0417227  ;
	ModelViewMatrix[5] = 0.164226  ;
	ModelViewMatrix[9] = 0.985535  ;
	ModelViewMatrix[13] = 0.289773;


	ModelViewMatrix[2] = 0.408783 ;
	ModelViewMatrix[6] = -0.902861  ;
	ModelViewMatrix[10] = 0.133142  ;
	ModelViewMatrix[14] = -9.70068;*/

	//wa3
	//0.745057 0.666252 0.030924 -0.0805306 // -0.493068 0.51897 0.69822 0.706512  // 0.449152 -0.535463 0.715188 -11.1754
	/*ModelViewMatrix[0] = 0.745057  ;
	ModelViewMatrix[4] = 0.666252  ;
	ModelViewMatrix[8] = 0.030924  ;
	ModelViewMatrix[12] = -0.0805306;


	ModelViewMatrix[1] = -0.493068  ;
	ModelViewMatrix[5] = 0.51897  ;
	ModelViewMatrix[9] = 0.69822  ;
	ModelViewMatrix[13] = 0.706512;


	ModelViewMatrix[2] = 0.449152  ;
	ModelViewMatrix[6] = -0.535463  ;
	ModelViewMatrix[10] = 0.715188  ;
	ModelViewMatrix[14] = -11.1754;*/

	//shuanghuan
	//0.683225 -0.67707 0.273393 -0.000387781 // 0.357223 0.636483 0.683558 0.000443583 // -0.636832 -0.369362 0.676739 -8.64433
	/*ModelViewMatrix[0] = 0.683225;
	ModelViewMatrix[4] = -0.67707;
	ModelViewMatrix[8] = 0.273393;
	ModelViewMatrix[12] = -0.000387781;


	ModelViewMatrix[1] = 0.357223  ;
	ModelViewMatrix[5] = 0.636483  ;
	ModelViewMatrix[9] = 0.683558  ;
	ModelViewMatrix[13] = 0.000443583;


	ModelViewMatrix[2] = -0.636832  ;
	ModelViewMatrix[6] = -0.369362  ;
	ModelViewMatrix[10] = 0.676739  ;
	ModelViewMatrix[14] = -8.64433  ;*/
	//shuanghuan1
	//-0.727232 0.186162 -0.660634 0.000291237 // -0.382175 0.689653 0.61505 0.00107953 // 0.570113 0.69977 -0.430398 -6.91127
	/*ModelViewMatrix[0] = -0.727232;
	ModelViewMatrix[4] = 0.186162;
	ModelViewMatrix[8] = -0.660634;
	ModelViewMatrix[12] = 0.000291237;


	ModelViewMatrix[1] = -0.382175;
	ModelViewMatrix[5] = 0.689653;
	ModelViewMatrix[9] = 0.61505;
	ModelViewMatrix[13] = 0.00107953;


	ModelViewMatrix[2] = 0.570113;
	ModelViewMatrix[6] = 0.69977;
	ModelViewMatrix[10] = -0.430398;
	ModelViewMatrix[14] = -6.91127;*/

	//bird
	//0.720122 0.294602 -0.628152 0.282266 //-0.0627845 0.929304 0.363874 -5.15008 // 0.690958 -0.222598 0.68773 -20.2795
	/*ModelViewMatrix[0] = 0.720122;
	ModelViewMatrix[4] = 0.294602;
	ModelViewMatrix[8] = -0.628152;
	ModelViewMatrix[12] = 0.282266;


	ModelViewMatrix[1] = -0.0627845;
	ModelViewMatrix[5] = 0.929304;
	ModelViewMatrix[9] = 0.363874;
	ModelViewMatrix[13] = -5.15008;


	ModelViewMatrix[2] = 0.690958;
	ModelViewMatrix[6] = -0.222598;
	ModelViewMatrix[10] = 0.68773;
	ModelViewMatrix[14] = -20.2795;*/
	//bird1
	//-0.596231 -0.270424 0.755854 -1.31275 // 0.0256553 0.934625 0.354631 -5.3391 // -0.802361 0.230838 -0.550334 -12.1566
	/*ModelViewMatrix[0] = -0.596231;
	ModelViewMatrix[4] = -0.270424;
	ModelViewMatrix[8] = 0.755854;
	ModelViewMatrix[12] = -1.31275;


	ModelViewMatrix[1] = 0.0256553;
	ModelViewMatrix[5] = 0.934625;
	ModelViewMatrix[9] = 0.354631;
	ModelViewMatrix[13] = -5.3391;


	ModelViewMatrix[2] = -0.802361;
	ModelViewMatrix[6] = 0.230838;
	ModelViewMatrix[10] = -0.550334;
	ModelViewMatrix[14] = -12.1566;*/
	//chair
	//0.973424 0.228826 -0.0022626 -4.35401 // -0.0117051 0.0596831 0.998116 -5.12093 // 0.228539 -0.971596 0.0607707 -14.5404
	ModelViewMatrix[0] = 0.973424;
	ModelViewMatrix[4] = 0.228826;
	ModelViewMatrix[8] = -0.0022626;
	ModelViewMatrix[12] = -4.35401;


	ModelViewMatrix[1] = -0.0117051;
	ModelViewMatrix[5] = 0.0596831;
	ModelViewMatrix[9] = 0.998116;
	ModelViewMatrix[13] = -5.12093;


	ModelViewMatrix[2] = 0.228539;
	ModelViewMatrix[6] = -0.971596;
	ModelViewMatrix[10] = 0.0607707;
	ModelViewMatrix[14] = -14.5404;
	//wujiaoxing
	//0.964457 0.241678 -0.106697 1.55915  // -0.240395 0.970348 0.0249497 -0.3508 //  0.109563 0.00158542 0.993959 -73.7892
	/*ModelViewMatrix[0] = 0.964457  ;
	ModelViewMatrix[4] = 0.241678  ;
	ModelViewMatrix[8] = -0.106697  ;
	ModelViewMatrix[12] = 1.55915;


	ModelViewMatrix[1] = -0.240395  ;
	ModelViewMatrix[5] = 0.970348  ;
	ModelViewMatrix[9] = 0.0249497  ;
	ModelViewMatrix[13] = -0.3508;


	ModelViewMatrix[2] = 0.109563  ;
	ModelViewMatrix[6] = 0.00158542  ;
	ModelViewMatrix[10] = 0.993959 ;
	ModelViewMatrix[14] = -73.7892;*/

	//wujiaoxing2
	//0.895596 0.169383 0.411352 0.322984 // -0.30959 0.901332 0.302894 -1.14123 // -0.31946 -0.398623 0.85967 -76.6264
	/*ModelViewMatrix[0] = 0.895596  ;
	ModelViewMatrix[4] = 0.169383  ;
	ModelViewMatrix[8] = 0.411352  ;
	ModelViewMatrix[12] = 0.322984;


	ModelViewMatrix[1] = -0.30959  ;
	ModelViewMatrix[5] = 0.901332  ;
	ModelViewMatrix[9] = 0.302894 ;
	ModelViewMatrix[13] = -1.14123;


	ModelViewMatrix[2] = -0.31946  ;
	ModelViewMatrix[6] = -0.398623;
	ModelViewMatrix[10] = 0.85967  ;
	ModelViewMatrix[14] = -76.6264;*/

	//wujiaoxing3
	//0.787665 0.34026 0.513615 -0.0789624 // -0.192116 0.927737 -0.31998 0.593573 // -0.585378 0.153362 0.796117 -76.8167
	/*ModelViewMatrix[0] = 0.787665  ;
	ModelViewMatrix[4] = 0.34026  ;
	ModelViewMatrix[8] = 0.513615  ;
	ModelViewMatrix[12] = -0.0789624;


	ModelViewMatrix[1] = -0.192116  ;
	ModelViewMatrix[5] = 0.927737  ;
	ModelViewMatrix[9] = -0.31998 ;
	ModelViewMatrix[13] = 0.593573;


	ModelViewMatrix[2] = -0.585378  ;
	ModelViewMatrix[6] = 0.153362  ;
	ModelViewMatrix[10] = 0.796117  ;
	ModelViewMatrix[14] = -76.8167;*/

	view_all();
}


void QGLViewerWidget::view_all()
{
	OpenMesh::Vec3d _trans = OpenMesh::Vec3d(-(ModelViewMatrix[0] * Center[0] +
		ModelViewMatrix[4] * Center[1] +
		ModelViewMatrix[8] * Center[2] +
		ModelViewMatrix[12]),
		-(ModelViewMatrix[1] * Center[0] +
			ModelViewMatrix[5] * Center[1] +
			ModelViewMatrix[9] * Center[2] +
			ModelViewMatrix[13]),
		-(ModelViewMatrix[2] * Center[0] +
			ModelViewMatrix[6] * Center[1] +
			ModelViewMatrix[10] * Center[2] +
			ModelViewMatrix[14] +
			3.0 * Radius));

	makeCurrent();
	glLoadIdentity();
	glTranslated(_trans[0], _trans[1], _trans[2]);
	glMultMatrixd(&ModelViewMatrix[0]);
	glGetDoublev(GL_MODELVIEW_MATRIX, &ModelViewMatrix[0]);
	 
	//std::cout << "============ view_all ==========" << std::endl;


}

void QGLViewerWidget::set_scene_pos(const OpenMesh::Vec3d& _center, float _radius)
{
	Center = _center;
	Radius = _radius;

	update_projection_matrix();
	view_all();
	std::cout << "======= set_scene_pos ==========" << std::endl;

}

void QGLViewerWidget::LoadTexture()
{
	glGenTextures(1, &glTextureID);
	glBindTexture(GL_TEXTURE_2D, glTextureID);

	// load and generate texture
	int width, height, nChannels;
	//unsigned char* data = stbi_load("../src/Images/tiling patterns/R-C3.jpg", &width, &height, &nChannels, 0);
	//unsigned char* data = stbi_load("../src/Images/tiling patterns/circle.jpg", &width, &height, &nChannels, 0);
	unsigned char* data = stbi_load("../src/Images/tiling patterns/tex_d1.png", &width, &height, &nChannels, 0); 
	//unsigned char* data = stbi_load("../src/Images/tiling patterns/pie-factory.png", &width, &height, &nChannels, 0);
	//unsigned char* data = stbi_load("../src/Images/tiling patterns/cross.jpg", &width, &height, &nChannels, 0);
	//std::string s = TexturePath + "/Images/tiling patterns/tex_d1.png";
	//unsigned char* data = stbi_load(s.data(), &width, &height, &nChannels, 0);//texture-grid//icon2.png


	GLint internalFormat = GL_RGBA;
	if (nChannels == 1) internalFormat = GL_RED;
	if (nChannels == 2) internalFormat = GL_RG;
	if (nChannels == 3) internalFormat = GL_RGB;
	if (nChannels == 4) internalFormat = GL_RGBA;

	if (data)	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		assert(false);
	}

	// wrap parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	stbi_image_free(data);
}