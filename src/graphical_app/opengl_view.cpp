#include "opengl_view.h"
#include "vertex_shader.h"
#include "content.h"

void OpenGLView::draw(const Content &to_draw){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// skeleton polygons

	QMatrix4x4 matrix;
	for(Particle* p : *to_draw.getUniverse()->getParticle_list()){
		if(p->alive){
			std::array<double,3> coords(p->getPosition().getCoords());

			matrix.translate(coords[0], coords[1], coords[2]);
			matrix.scale(p->getRadius());

			drawSphere(matrix, p->getColor());

			matrix.setToIdentity();
		}
	}
}

void OpenGLView::init(){
	 //* Initializes the OpenGL POV, and builds the shader.

	prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
	prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

	prog.bindAttributeLocation("vertex", VertexId);
	prog.bindAttributeLocation("color", ColorId);

	// compiles
	prog.link();

	// binds
	prog.bind();

	// activates
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	sphere.initialize();
	initializePosition();
}

void OpenGLView::initializePosition(){
	pov_matrix.setToIdentity();
	pov_matrix.translate(0.0, 0.0, -30.0);
	/* pov_matrix.rotate(60.0, 0.0, 1.0, 0.0); */
	/* pov_matrix.rotate(45.0, 0.0, 0.0, 1.0); */
}

void OpenGLView::translate(double x, double y, double z){
	// left-multiplies!
	QMatrix4x4 translation;
	translation.translate(x, y, z);
	pov_matrix = translation * pov_matrix;
}

void OpenGLView::rotate(double angle, double x, double y, double z){
	// left-multiplies!
	QMatrix4x4 rotation;
	rotation.rotate(angle, x, y, z);
	pov_matrix = rotation * pov_matrix;
}

void OpenGLView::drawCube(QMatrix4x4 const& pov, RGB color){
	prog.setUniformValue("view", pov_matrix * pov);

	glBegin(GL_QUADS);
	// X = +1 face
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
	prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);
	prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);
	prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
	prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);

	// X = -1 face
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
	prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
	prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);
	prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);
	prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);

	// Y = +1 face
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
	prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);
	prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);
	prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
	prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);

	// Y = -1 face
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
	prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
	prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);
	prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);
	prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);

	// Z = +1 face
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
	prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);
	prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);
	prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
	prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);

	// Z = -1 face
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);
	prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
	prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);
	prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);
	prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);

	glEnd();
}

void OpenGLView::drawSphere (QMatrix4x4 const& pov, RGB color){
	prog.setUniformValue("view", pov_matrix * pov);
	prog.setAttributeValue(ColorId, color[0], color[1], color[2]);  // colors
	sphere.draw(prog, VertexId); // draws sphere
}

void OpenGLView::drawAxes (QMatrix4x4 const& pov, bool is_in_color){
	prog.setUniformValue("view", pov_matrix * pov);

	glBegin(GL_LINES);

	// X-axis
	if(is_in_color) prog.setAttributeValue(ColorId, 1.0, 0.0, 0.0);// red
	else prog.setAttributeValue(ColorId, 1.0, 1.0, 1.0); // white

	prog.setAttributeValue(VertexId, 0.0, 0.0, 0.0);
	prog.setAttributeValue(VertexId, 1.0, 0.0, 0.0);

	// Y-axis
	if(is_in_color) prog.setAttributeValue(ColorId, 0.0, 1.0, 0.0); // green
	prog.setAttributeValue(VertexId, 0.0, 0.0, 0.0);
	prog.setAttributeValue(VertexId, 0.0, 1.0, 0.0);

	// Z-axis
	if(is_in_color) prog.setAttributeValue(ColorId, 0.0, 0.0, 1.0); // blue
	prog.setAttributeValue(VertexId, 0.0, 0.0, 0.0);
	prog.setAttributeValue(VertexId, 0.0, 0.0, 1.0);

	glEnd();
}
