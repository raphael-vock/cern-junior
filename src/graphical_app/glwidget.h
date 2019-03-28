#pragma once

#include <QOpenGLWidget>
#include <QTime>

#include "opengl_view.h"
#include "../general/drawable.h"
#include "../accelerator/accelerator.h"

class GLWidget : public QOpenGLWidget{
	private:
		virtual void initializeGL() override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL() override;

		// Event handling
		virtual void keyPressEvent(QKeyEvent* event) override;
		virtual void timerEvent(QTimerEvent*) override;

		// internal handling
		void pause();

		// viewpoint
		OpenGLView view;

		// timer
		int timerId;
		QTime stopwatch;

		// to be drawn
		Accelerator* content;
	public:
		GLWidget(QWidget* parent = nullptr, Accelerator* my_content = nullptr) : QOpenGLWidget(parent), content(my_content){ content->initialize(&view); }
		virtual ~GLWidget(){}
};
