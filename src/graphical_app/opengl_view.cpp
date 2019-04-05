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

void OpenGLView::draw(const Segment &to_draw){
	prog.setUniformValue("view", pov_matrix);

	glBegin(GL_LINES);

	setShaderColor(to_draw.getColor());
	setShaderPoint(to_draw.getA());
	setShaderPoint(to_draw.getB());

	glEnd();
}

void OpenGLView::draw(const Beam &to_draw){
	to_draw.draw_particles();
}

void OpenGLView::draw(const Particle &to_draw){
	drawSphere(to_draw.getPosition(), to_draw.getRadius(), to_draw.getColor());
}

void OpenGLView::draw(const StraightSection &to_draw){
	to_draw.draw_particles();
	drawElement(to_draw, RGB::WHITE);
}

void OpenGLView::draw(const ElectricElement &to_draw){
	to_draw.draw_particles();
	drawElement(to_draw, RGB::ELECTRIC_BLUE);
}

void OpenGLView::draw(const MagneticElement &to_draw){
	to_draw.draw_particles();
	drawElement(to_draw, RGB::RED);
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

void OpenGLView::drawSphere(const Vector3D &x, double r, RGB color){
	QMatrix4x4 matrix;
	matrix.translate(x[0], x[1], x[2]);
	matrix.scale(r);

	prog.setUniformValue("view", pov_matrix * matrix);
	setShaderColor(color);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	sphere.draw(prog, VertexId);
}

void OpenGLView::drawTorusSection(const Element& E, const RGB &color){
	try{
		const Vector3D center(E.center());
		const Vector3D p1(E.getEntry_point());
		const Vector3D p2(E.getExit_point());

		const Vector3D u(-E.getBasis_vector_u());
		const Vector3D v(-E.getBasis_vector_v());
		const Vector3D w(E.getBasis_vector_w());

		const double major_radius(Vector3D::distance(center, p1));
		const double minor_radius(E.getRadius());
		const double p(1/M_PI*asin( Vector3D::distance(p1, p2)/(2*major_radius))); // proportion of the torus to be drawn (0 ≤ p ≤ 1)

		const double lambda(TORUS_QUAD_LENGTH/minor_radius);
		const double mu(1.0/(p*major_radius/TORUS_TUBE_HEIGHT));

		const int num_cylinders(ceil(2*M_PI*major_radius*p/TORUS_TUBE_HEIGHT));
		const int num_quads(2*M_PI*minor_radius/TORUS_QUAD_LENGTH);

		prog.setUniformValue("view", pov_matrix);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		for(int i(0); i < num_quads; ++i){
			glBegin(GL_QUAD_STRIP);
			for(int j(0); j <= p*num_cylinders; ++j){
				setShaderColor(j % HIGHLIGHT_COLOR_FREQUENCY == 0 ? color : RGB::WHITE);
				for(int k(1); k >= 0; --k){
					double s((i + k) % num_quads + 0.5);
					double t(num_cylinders/2 + j % num_cylinders);

					double x((major_radius + minor_radius * cos(s * lambda)) * cos(t * mu));
					double y((major_radius + minor_radius * cos(s * lambda)) * sin(t * mu));
					double z(minor_radius * sin(s * lambda));
					Vector3D P(center + x*u + y*v + z*w);
					glVertex3d(P[0], P[1], P[2]);
				}
			}
			glEnd();
		}
	}
	catch(std::exception){ throw excptn::ELEMENT_DEGENERATE_GEOMETRY; }
}

void OpenGLView::drawCylinder(const Vector3D &basepoint, const Vector3D &direction, double radius, const RGB &color){
	const int num_cylinders(direction.norm()/CYLINDER_TUBE_HEIGHT); // number of small cylinders
	const int num_quads(2*M_PI*radius / CYLINDER_QUAD_LENGTH); // number of quads per small cylinder
	Vector3D small_direction(CYLINDER_TUBE_HEIGHT*direction.unitary()); // direction of the small cylinders

	Vector3D u(direction.unitary());
	Vector3D v(radius*u.orthogonal());
	u = u^v;

	QMatrix4x4 translation;
	translation.translate(basepoint[0], basepoint[1], basepoint[2]);
	prog.setUniformValue("view", pov_matrix * translation);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for(int i(0); i <= num_cylinders; ++i){
		/* if(i == num_cylinders) small_direction = direction.unitary()*(2*M_PI*radius / CYLINDER_QUAD_LENGTH - num_quads); */

		glBegin(GL_QUAD_STRIP);
		setShaderColor(i % HIGHLIGHT_COLOR_FREQUENCY == 0 ? color : RGB::WHITE);
		for(int j(0); j <= num_quads; ++j){
			Vector3D P(i*small_direction + cos(2*M_PI*j/num_quads)*u + sin(2*M_PI*j/num_quads)*v);
			Vector3D Q(P + small_direction);

			glVertex3d(P[0], P[1], P[2]);
			glVertex3d(Q[0], Q[1], Q[2]);
		}
		glEnd();
	}
}

void OpenGLView::drawElement(const Element &E, const RGB &color){
	double r(E.getRadius());
	if(E.is_straight()){
		Vector3D entry_point(E.getEntry_point());
		drawCylinder(entry_point, E.getExit_point() - entry_point, r, color);
	}else{
		drawTorusSection(E, color);
	}
}
