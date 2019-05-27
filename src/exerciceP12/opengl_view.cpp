#include <cmath> // for trig functions

#include "opengl_view.h"
#include "vertex_shader.h"

#include "../misc/constants.h"
#include "../misc/exceptions.h"

#include "../accelerator/accelerator.h"
#include "../physics/beam.h"

using namespace simcst;

void OpenGLView::setShaderColor(const RGB &color){
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
}

void OpenGLView::setShaderPoint(const Vector3D &point){
	prog.setAttributeValue(VertexId, point[0], point[1], point[2]);
}

void OpenGLView::draw(const Box &to_draw){
	std::array<Vector3D,8> points(to_draw.getVertices());

	prog.setUniformValue("view", pov_matrix);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUAD_STRIP);
	for(int i(0); i <= 9; ++i){
		glVertex3d(points[i%8][0], points[i%8][1], points[i%8][2]);
	}
	glEnd();
}

void OpenGLView::draw(const Beam &to_draw){
	// TODO
}

void OpenGLView::draw(const Particle &to_draw){
	setShaderColor(to_draw.getColor());
	drawSphere(to_draw, to_draw.getRadius());
}

void OpenGLView::draw(const Element &to_draw){
	if(matrix_mode){
		setShaderColor(RGB::PURPLE);
		to_draw.draw_tree();
	}

	setShaderColor(*to_draw.getColor());
	if(to_draw.is_straight()) drawStraightElement(to_draw);
	else drawCurvedElement(to_draw);
}

void OpenGLView::draw(const Accelerator &to_draw){
	to_draw.draw_elements();
	if(not matrix_mode){
		to_draw.draw_particles();
	}
}

void OpenGLView::init(){
	 // initializes the OpenGL POV, and builds the shader.

	prog.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
	prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

	prog.bindAttributeLocation("vertex", VertexId);
	prog.bindAttributeLocation("color", ColorId);

	// compiles
	prog.link();

	// binds
	prog.bind();

	// activates
	glEnable(GL_DEPTH_TEST);
	/* glEnable(GL_CULL_FACE); */
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(0.1);

	sphere.initialize();
	initializePosition();
}

void OpenGLView::initializePosition(){
	pov_matrix.setToIdentity();
	pov_matrix.translate(0.0, 0.0, -5.0);
}

void OpenGLView::set_first_person_view(const Particle &p){
	pov_matrix.setToIdentity();

	Vector3D center_point(p + p.getRadius()*(p.getVelocity().unitary() + vctr::Z_VECTOR));
	Vector3D focal_point(center_point + p.getVelocity());

	QVector3D eye(center_point[0], center_point[1], center_point[2]);
	QVector3D center(focal_point[0], focal_point[1], focal_point[2]);
	QVector3D up(0,0,1);

	pov_matrix.lookAt(eye, center, up);
}

void OpenGLView::set_third_person_view(const Particle &p){
	initializePosition();

	translate(p);
	translate(0,0,4);
}

void OpenGLView::translate(double x, double y, double z){
	QMatrix4x4 translation;
	translation.translate(x, y, z);
	pov_matrix = translation * pov_matrix;
}

void OpenGLView::rotate(double angle, double x, double y, double z){
	QMatrix4x4 rotation;
	rotation.rotate(angle, x, y, z);
	pov_matrix = rotation * pov_matrix;
}

void OpenGLView::drawSphere(const Vector3D &x, double r){
	QMatrix4x4 matrix;
	matrix.translate(x[0], x[1], x[2]);
	matrix.scale(r);

	prog.setUniformValue("view", pov_matrix * matrix);
	// TODO mutualize
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	sphere.draw(prog, VertexId);
}

void OpenGLView::drawCylinder(const Vector3D &basepoint, const Vector3D &direction, double radius){
	Vector3D u(direction.unitary());
	Vector3D v(radius*u.orthogonal());
	u = u^v;

	const double lambda(QUAD_LENGTH/radius);
	const int num_quads(ceil(2*M_PI/lambda));

	QMatrix4x4 translation;
	translation.translate(basepoint[0], basepoint[1], basepoint[2]);
	prog.setUniformValue("view", pov_matrix * translation);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUAD_STRIP);
	for(int i(0); i <= num_quads; ++i){
		Vector3D P(cos(i*lambda)*u + sin(i*lambda)*v);
		Vector3D Q(P + direction);

		glVertex3d(P[0], P[1], P[2]);
		glVertex3d(Q[0], Q[1], Q[2]);
	}
	glEnd();
}

void OpenGLView::drawCurvedElement(const Element &E){
	try{
		const Vector3D center(E.center());
		const Vector3D p1(E.getEntry_point());
		const Vector3D p2(E.getExit_point());

		const Vector3D u(E.getBasis_vector_u());
		const Vector3D v(E.getBasis_vector_v());

		const double major_radius(Vector3D::distance(center, p1));
		const double minor_radius(E.getRadius());

		const double theta(2.0*asin( Vector3D::distance(p1, p2)/(2.0*major_radius)));

		const int num_cylinders(theta*major_radius/TUBE_HEIGHT);

		for(int i(0); i < num_cylinders; i += GAP_RATIO){
			double alpha(i * theta / num_cylinders);
			Vector3D base(center + major_radius*(cos(alpha)*u + sin(alpha)*v));
			drawCylinder(base, TUBE_HEIGHT*(sin(alpha)*u - cos(alpha)*v), minor_radius);
		}
	}
	catch(std::exception){ throw excptn::ELEMENT_DEGENERATE_GEOMETRY; }
}

void OpenGLView::drawStraightElement(const Element &E){
	const Vector3D direction(E.getExit_point() - E.getEntry_point());
	const double d(direction.norm());

	const Vector3D small_direction(TUBE_HEIGHT * direction.unitary());
	const int num_cylinders(d/TUBE_HEIGHT);

	const double r(E.getRadius());
	const Vector3D base(E.getEntry_point());

	for(int i(0); i < num_cylinders; i += GAP_RATIO){
		drawCylinder(base + i*small_direction, small_direction, r);
	}
}
