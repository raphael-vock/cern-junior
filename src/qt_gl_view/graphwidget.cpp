#include <QMatrix4x4>
#include "graphwidget.h"
#include "vertex_shader.h"
#include "acceleratorwidgetgl.h"
#include "../physics/beam.h"
#include <array>

// ======================================================================
void GraphWidget::initializeGL()
{
  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  prog.bindAttributeLocation("vertex",  VertexId);
  prog.bindAttributeLocation("color", ColorId);

  prog.link();

  prog.bind();
  setWindowTitle("Graph");
}

// ======================================================================
void GraphWidget::resizeGL(int width, int height)
{
  glViewport(10, 10, width-20, height-20); // on laisse une marge de 10px de chaque coté
}

// ======================================================================
void GraphWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 matrix;
  prog.setUniformValue("view", matrix);              

  /* drawing the window */
  matrix.setToIdentity();
  matrix.ortho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);         
  prog.setUniformValue("projection", matrix);

  prog.setAttributeValue(ColorId, 1.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);                                    
  prog.setAttributeValue(VertexId, -1.0, -1.0, 2.0);       
  prog.setAttributeValue(VertexId, +1.0, -1.0, 2.0);       
  prog.setAttributeValue(VertexId, +1.0, +1.0, 2.0);
  prog.setAttributeValue(VertexId, -1.0, +1.0, 2.0);
  glEnd();

  if (not beams.empty()) {
	  /* evaluate coefficients */
	  std::array<double, 3> radial_coefficients = beams[0]->radial_ellipse_coefficients();
	  double emittance = beams[0]->radial_emittance();

	  std::cout << "hi" << "\n";

	  /* adapt projection for the graph */
	  matrix.setToIdentity();
	  double xmin(-2);
	  double xmax(+2);
	  double ymin(-2);
	  double ymax(+2);
	  double xpas((xmax - xmin) / 128.0);
	  matrix.ortho(xmin, xmax, ymin, ymax, -10.0, 10.0);
	  prog.setUniformValue("projection", matrix);

	  /* drawing axis */
	  prog.setAttributeValue(ColorId, 0.0, 0.0, 1.0);
	  glBegin(GL_LINES);                                        // la primitive LINES dessine une ligne par paire de points (n/2 lignes)
	  prog.setAttributeValue(VertexId, xmin, 0.0, -1.0);        // le -1.0 dans la composante z met les axes en arrière plan
	  prog.setAttributeValue(VertexId, xmax, 0.0, -1.0);
	  prog.setAttributeValue(VertexId, 0.0, ymin, -1.0);
	  prog.setAttributeValue(VertexId, 0.0, ymax, -1.0);
	  glEnd();

	  /* draw the ellipse */
	  prog.setAttributeValue(ColorId, 0.0, 1.0, 0.0);

	  // lower part of the ellipse
	  glBegin(GL_LINE_STRIP);                                   
	  for (double x(xmin); x <= xmax; x += xpas) {
	    double delta = radial_coefficients[1]*radial_coefficients[1]*x*x - radial_coefficients[2]*(radial_coefficients[0]*radial_coefficients[0]*x*x - emittance); 
	    double y = 1e-7*(-radial_coefficients[1]*x - sqrt(delta))/radial_coefficients[2];
	    prog.setAttributeValue(VertexId, x, y, 0.0);
	  }
	  glEnd();

	  // upper part of the ellipse
	  glBegin(GL_LINE_STRIP);                                   
	  for (double x(xmin); x <= xmax; x += xpas) {
	    double delta = radial_coefficients[1]*radial_coefficients[1]*x*x - radial_coefficients[2]*(radial_coefficients[0]*radial_coefficients[0]*x*x - emittance); 
	    double y = 1e-7*(-radial_coefficients[1]*x + sqrt(delta))/radial_coefficients[2];
	    prog.setAttributeValue(VertexId, x, y, 0.0);
	  }
	  glEnd();
	}
}
