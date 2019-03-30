#include "opengl_view.h"
#include "vertex_shader.h"

#include "../accelerator/accelerator.h"

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
	// TODO
}

void OpenGLView::draw(const Electric_element &to_draw){
	// TODO
}

void OpenGLView::draw(const Magnetic_element &to_draw){
	// TODO
}

void OpenGLView::draw(const Accelerator &to_draw){
	to_draw.draw_particles();
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
	glEnable(GL_CULL_FACE);

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

void OpenGLView::drawSphere(QMatrix4x4 const& pov, RGB color){
	prog.setUniformValue("view", pov_matrix * pov);
	setShaderColor(color);
	sphere.draw(prog, VertexId); // draws sphere
}

void OpenGLView::drawTorus(QMatrix4x4 const& pov, const RGB& color, int section, double major_radius, double minor_radius){
    prog.setUniformValue("view", pov_matrix * pov);
    setShaderColor(color);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    #define TWOPI 2.0 * M_PI
    int num_quads = 100, num_cylinders = 100;
    for (int i = 0; i < num_quads; i++) {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= num_cylinders/section; j++) {
            for (int k = 1; k >= 0; k--) {

            double s = (i + k) % num_quads + 0.5;
            double t = j % num_cylinders;

            double x = (major_radius + minor_radius * cos(s * TWOPI / num_quads)) * cos(t * TWOPI / num_cylinders);
            double y = (major_radius + minor_radius * cos(s * TWOPI / num_quads)) * sin(t * TWOPI / num_cylinders);
            double z = minor_radius * sin(s * TWOPI / num_quads);
            glVertex3d(x, y, z);
        }
        }
        glEnd();
}
}

void OpenGLView::drawDisc(QMatrix4x4 const& pov, const RGB& color, double radius){

    prog.setUniformValue("view", pov_matrix * pov);
    setShaderColor(color);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int slices(100);

    glBegin(GL_TRIANGLE_FAN);
    for (int i(0); i < slices; ++i){
        glVertex3d(0, 0, 0);
        glVertex3d(radius*cos(TWOPI*i/double(slices)), radius*sin(TWOPI*i/double(slices)), 0);
        glVertex3d(radius*cos(TWOPI*(i+1)/double(slices)), radius*sin(TWOPI*(i+1)/double(slices)), 0);
    }
    glEnd();
  }

void OpenGLView::drawCylinder(QMatrix4x4 const& pov, const RGB& color, double radius, double height){

    prog.setUniformValue("view", pov_matrix * pov);
    setShaderColor(color);

    unsigned int slices(100);
    #define TWOPI 2.0 * M_PI
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (unsigned int i(0); i <= slices; ++i){
            glBegin(GL_QUADS);
	    glVertex3d(radius*cos(TWOPI*i/double(slices)), radius* sin(TWOPI*i/double(slices)), 0);
            glVertex3d(radius*cos(TWOPI*i/double(slices)), radius* sin(TWOPI*i/double(slices)), height);
            glVertex3d(radius*cos(TWOPI*((i+1)%slices)/double(slices)), radius* sin(TWOPI*((i+1)%slices)/double(slices)), height);
            glVertex3d(radius*cos(TWOPI*((i+1)%slices)/double(slices)), radius* sin(TWOPI*((i+1)%slices)/double(slices)), 0);
    }
    glEnd();
  }

void OpenGLView::drawBasicAccelerator(QMatrix4x4 const& pov, const RGB& color, double major_radius, double minor_radius){

    prog.setUniformValue("view", pov_matrix * pov);
    setShaderColor(color);

  // for some unknow reason translation has to be 10
    float translation(10);

    QMatrix4x4 matrix, matrix2, matrix3, matrix4, matrix5, matrix6, matrix7, matrix8, matrix9;

  // drawing the four curved elements on the edges
    matrix5.translate(translation, translation, 0);
    drawTorus(matrix5, color, 4, major_radius, minor_radius);

    matrix4.translate(-translation, -translation, 0);
    matrix4.rotate(180, 0.0, 0.0, 1.0);
    drawTorus(matrix4, color, 4, major_radius, minor_radius);

    matrix8.translate(-translation, translation, 0);
    matrix8.rotate(90, 0.0, 0.0, 1.0);
    drawTorus(matrix8, color, 4, major_radius, minor_radius);

    matrix9.translate(translation, -translation, 0);
    matrix9.rotate(270, 0.0, 0.0, 1.0);
    drawTorus(matrix9, color, 4, major_radius, minor_radius);
 
  // drawing the four straight elements connecting curved elements
    matrix2.translate(translation + major_radius, translation, 0);
    matrix2.rotate(90, 1.0, 0.0);
    drawCylinder(matrix2, color, minor_radius);
   
    matrix3.translate(translation, translation + major_radius, 0);
    matrix3.rotate(270, 0.0, 1.0);
    drawCylinder(matrix3, color, minor_radius);
   
    matrix6.translate(-translation - major_radius, -translation, 0);
    matrix6.rotate(270, 1.0, 0.0);
    drawCylinder(matrix6, color, minor_radius);
   
    matrix7.translate(-translation, -translation - major_radius, 0);
    matrix7.rotate(90, 0.0, 1.0);
    drawCylinder(matrix7, color, minor_radius);
 }                                          
