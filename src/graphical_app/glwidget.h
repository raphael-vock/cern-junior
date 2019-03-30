#pragma once

#include <QOpenGLWidget>
#include <QTime>

#include "opengl_view.h"
#include "../general/drawable.h"
#include "../accelerator/accelerator.h"

class GLWidget : public QOpenGLWidget, public Accelerator{
	private:
		virtual void initializeGL() override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL() override;

		// Event handling
		virtual void keyPressEvent(QKeyEvent* event) override;
		virtual void timerEvent(QTimerEvent*) override;
		void pause();

		// viewpoint
		OpenGLView view;

		// timer
		int timerId;
		QTime stopwatch;
	public:
		GLWidget(QWidget* parent = nullptr) : QOpenGLWidget(parent), Accelerator(&view){}
		virtual ~GLWidget(){}
};
