#include "scatterplotwidgetgl.h"

void ScatterPlotWidgetGL::initializeGL(void){
	view.init();
}

void ScatterPlotWidgetGL::resizeGL(int width, int height){
	glViewport(0.0, 0.0, width, height);// draw on entire screen

	QMatrix4x4 matrix;
	matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrix);
}

void ScatterPlotWidgetGL::paintGL(void){
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
}
