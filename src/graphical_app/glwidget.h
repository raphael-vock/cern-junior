#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTime>
#include "opengl_view.h"
#include "content.h"

class GLWidget : public QOpenGLWidget{
	public:
		GLWidget(QWidget* parent, Universe& my_universe) : QOpenGLWidget(parent), content(&view, my_universe){}
		virtual ~GLWidget(){}
		void setUniverse(Universe my_universe);

	private:
		virtual void initializeGL()                  override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL()                       override;

		// Event handling
		virtual void keyPressEvent(QKeyEvent* event) override;
		virtual void timerEvent(QTimerEvent*)        override;

		// internal handling
		void pause();

		// viewpoint
		OpenGLView view;

		// timer
		int timerId;
		QTime stopwatch;

		// to be drawn
		Content content;
};

#endif
