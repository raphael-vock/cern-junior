#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include "opengl_view.h"
#include "content.h"

class GLWidget : public QOpenGLWidget{
	public:
		GLWidget(QWidget* parent = nullptr) : QOpenGLWidget(parent), c(&view){}
		virtual ~GLWidget() {}

	private:
		virtual void initializeGL()                  override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL()                       override;

		// Event handling
		virtual void keyPressEvent(QKeyEvent* event) override;

		// viewpoint
		OpenGLView view;

		// to be drawn
		Content c;
};

#endif
