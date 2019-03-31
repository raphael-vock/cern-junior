#include <cmath> // for acos

#include "opengl_view.h"
#include "vertex_shader.h"

#include "../misc/constants.h"
#include "../accelerator/accelerator.h"

using namespace simcst;

void OpenGLView::setShaderColor(const RGB &color){
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
}

void OpenGLView::setShaderPoint(const Vector3D &point){
	prog.setAttributeValue(VertexId, point[0], point[1], point[2]);
}

void OpenGLView::draw(const Segment &to_draw){
	prog.setUniformValue("view", pov_matrix);

	glBegin(GL_LINES);

	setShaderColor(to_draw.getColor());
	setShaderPoint(to_draw.getA());
	setShaderPoint(to_draw.getB());

	glEnd();
}

void OpenGLView::draw(const Particle &to_draw){
	std::array<double,3> coords(to_draw.getPosition().getCoords());

	QMatrix4x4 matrix;
	matrix.translate(coords[0], coords[1], coords[2]);
	matrix.scale(to_draw.getRadius());

	drawSphere(matrix, to_draw.getColor());
}

void OpenGLView::draw(const StraightSection &to_draw){
	Vector3D entry_point(to_draw.getEntry_point());
	drawCylinder(entry_point, to_draw.getExit_point() - entry_point, to_draw.getRadius());
}

void OpenGLView::draw(const Electric_element &to_draw){
	// TODO
}

void OpenGLView::draw(const Magnetic_element &to_draw){
	// TODO
}

void OpenGLView::draw(const Accelerator &to_draw){
	to_draw.draw_elements();
}

void OpenGLView::init(){
	 // Initializes the OpenGL POV, and builds the shader.

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
	/* pov_matrix.rotate(60.0, 0.0, 1.0, 0.0); */
	/* pov_matrix.rotate(45.0, 0.0, 0.0, 1.0); */
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

void OpenGLView::drawSphere(const QMatrix4x4 &pov, RGB color){
	prog.setUniformValue("view", pov_matrix * pov);
	setShaderColor(color);
	sphere.draw(prog, VertexId);
}

void OpenGLView::drawTorusSection(const QMatrix4x4 &pov, double major_radius, double minor_radius, double proportion, const RGB &color){
	constexpr double lambda(2*M_PI/TORUS_NUM_QUADS);
	constexpr double mu(2*M_PI/TORUS_NUM_CYLINDERS);

	prog.setUniformValue("view", pov_matrix * pov);
	setShaderColor(color);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(int i(0); i < TORUS_NUM_QUADS; ++i){
		glBegin(GL_QUAD_STRIP);
		for(int j(0); j <= TORUS_NUM_CYLINDERS * proportion; ++j){
			for(int k(1); k >= 0; --k){
				double s((i + k) % TORUS_NUM_QUADS + 0.5);
				double t(j % TORUS_NUM_CYLINDERS);

				double x((major_radius + minor_radius * cos(s * lambda)) * cos(t * mu));
				double y((major_radius + minor_radius * cos(s * lambda)) * sin(t * mu));
				double z(minor_radius * sin(s * lambda));
				glVertex3d(x,y,z);
			}
		}
		glEnd();
	}
}

void OpenGLView::drawCylinder(const Vector3D &basepoint, const Vector3D &direction, double radius, const RGB &color){
	constexpr double h(2*M_PI/CYLINDER_NUM_SIDES);
	constexpr int offset(CYLINDER_NUM_SIDES * CYLINDER_SPIRAL_RATIO);
	Vector3D u(direction.unitary());
	Vector3D v(radius*u.orthogonal());
	u = u^v;

	QMatrix4x4 translation;
	translation.translate(basepoint[0], basepoint[1], basepoint[2]);
	prog.setUniformValue("view", pov_matrix * translation);
	setShaderColor(color);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	for(int i(0); i <= CYLINDER_NUM_SIDES; ++i){
		Vector3D P(cos(i*h)*u + sin(i*h)*v);
		Vector3D Q(cos((i+offset)*h)*u + sin((i+offset)*h)*v + direction);

		glVertex3d(P[0], P[1], P[2]);
		glVertex3d(Q[0], Q[1], Q[2]);
	}
	glEnd();
}
