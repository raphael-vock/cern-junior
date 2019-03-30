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

void OpenGLView::draw(const Arrow &to_draw){
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
	drawCylinder(to_draw.getEntry_point(), to_draw.getExit_point(), to_draw.getRadius());
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
	prog.setUniformValue("view", pov_matrix * pov);
	setShaderColor(color);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(int i(0); i < TORUS_NUM_QUADS; ++i){
		glBegin(GL_QUAD_STRIP);
		for(int j(0); j <= TORUS_NUM_CYLINDERS*proportion; ++j){
			for(int k(1); k >= 0; --k){
				double s((i + k) % TORUS_NUM_QUADS + 0.5);
				double t(j % TORUS_NUM_CYLINDERS);

				double x((major_radius + minor_radius * cos(s * 2*M_PI / TORUS_NUM_QUADS)) * cos(t * 2*M_PI / TORUS_NUM_CYLINDERS));
				double y((major_radius + minor_radius * cos(s * 2*M_PI / TORUS_NUM_QUADS)) * sin(t * 2*M_PI / TORUS_NUM_CYLINDERS));
				double z(minor_radius * sin(s * 2*M_PI / TORUS_NUM_QUADS));
				glVertex3d(x,y,z);
			}
		}
		glEnd();
	}
}

void OpenGLView::drawCylinder(const Vector3D &start, const Vector3D &end, double radius, const RGB &color){
	Vector3D direction(end - start);
	double height(direction.norm());

	double alpha(acos((direction|vctr::Z_VECTOR)/height));
	Vector3D axis(vctr::Z_VECTOR ^ direction);

	QMatrix4x4 translation;
	translation.translate(start[0], start[1], start[2]);

	prog.setUniformValue("view", pov_matrix * translation);
	setShaderColor(color);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(int i(0); i <= CYLINDER_NUM_SLICES; ++i){
		std::array<Vector3D,4> vertices;
		vertices[0] = Vector3D(
			radius*cos(2*M_PI*i/double(CYLINDER_NUM_SLICES)),
			radius*sin(2*M_PI*i/double(CYLINDER_NUM_SLICES)),
			0.0
		);
		vertices[1] = Vector3D(
			radius*cos(2*M_PI*(i+1)/double(CYLINDER_NUM_SLICES)),
			radius* sin(2*M_PI*(i+1)/double(CYLINDER_NUM_SLICES)),
			0.0
		);
		vertices[0].rotate(axis, alpha);
		vertices[1].rotate(axis, alpha);
		vertices[2] = vertices[1] + direction;
		vertices[3] = vertices[0] + direction;

		glBegin(GL_QUADS);
		for(int i(0); i <= 3; ++i) glVertex3d(vertices[i][0], vertices[i][1], vertices[i][2]);
	}
	glEnd();
}

/* void OpenGLView::drawBasicAccelerator(QMatrix4x4 const& pov, const RGB& color, double major_radius, double minor_radius){ */
/* 	prog.setUniformValue("view", pov_matrix * pov); */
/* 	setShaderColor(color); */

/* 	// for some unknow reason translation has to be 10 */
/* 	float translation(10); */

/* 	QMatrix4x4 matrix, matrix2, matrix3, matrix4, matrix5, matrix6, matrix7, matrix8, matrix9; */

/* 	// drawing the four curved elements on the edges */
/* 	matrix5.translate(translation, translation, 0); */
/* 	drawTorus(matrix5, color, 4, major_radius, minor_radius); */

/* 	matrix4.translate(-translation, -translation, 0); */
/* 	matrix4.rotate(180, 0.0, 0.0, 1.0); */
/* 	drawTorus(matrix4, color, 4, major_radius, minor_radius); */

/* 	matrix8.translate(-translation, translation, 0); */
/* 	matrix8.rotate(90, 0.0, 0.0, 1.0); */
/* 	drawTorus(matrix8, color, 4, major_radius, minor_radius); */

/* 	matrix9.translate(translation, -translation, 0); */
/* 	matrix9.rotate(270, 0.0, 0.0, 1.0); */
/* 	drawTorus(matrix9, color, 4, major_radius, minor_radius); */

/* 	// drawing the four straight elements connecting curved elements */
/* 	matrix2.translate(translation + major_radius, translation, 0); */
/* 	matrix2.rotate(90, 1.0, 0.0); */
/* 	drawCylinder(matrix2, color, minor_radius); */

/* 	matrix3.translate(translation, translation + major_radius, 0); */
/* 	matrix3.rotate(270, 0.0, 1.0); */
/* 	drawCylinder(matrix3, color, minor_radius); */

/* 	matrix6.translate(-translation - major_radius, -translation, 0); */
/* 	matrix6.rotate(270, 1.0, 0.0); */
/* 	drawCylinder(matrix6, color, minor_radius); */

/* 	matrix7.translate(-translation, -translation - major_radius, 0); */
/* 	matrix7.rotate(90, 0.0, 1.0); */
/* 	drawCylinder(matrix7, color, minor_radius); */
/* } */                                          
