#pragma once

#include <QOpenGLWidget>
/* #include <QTime> */

#include "opengl_view.h"
#include "../general/drawable.h"
#include "../scatterplot/scatterplot.h"

class ScatterPlotWidgetGL : public QOpenGLWidget, public ScatterPlot{
	private:
		virtual void resizeGL(int width, int height) override;

		// viewpoint
		OpenGLView view;

	public:
		virtual void initializeGL(void) override;
		virtual void paintGL(void) override;

		ScatterPlotWidgetGL(QWidget* parent) : QOpenGLWidget(parent), ScatterPlot(&view){}
		virtual ~ScatterPlotWidgetGL(){}
};
