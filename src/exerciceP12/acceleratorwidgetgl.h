#pragma once

#include <QOpenGLWidget>
#include <QTime>

#include "opengl_view.h"
#include "../general/drawable.h"
#include "../physics/accelerator.h"

class AcceleratorWidgetGL : public QOpenGLWidget, public Accelerator{
	private:
		virtual void initializeGL(void) override;
		virtual void resizeGL(int width, int height) override;
		virtual void paintGL(void) override;

		// Event handling
		virtual void keyPressEvent(QKeyEvent* event) override;
		virtual void mousePressEvent(QMouseEvent* event) override;
		virtual void mouseMoveEvent(QMouseEvent* event) override;
		virtual void timerEvent(QTimerEvent*) override;

		void pause(void);

		QPoint lastMousePosition; // for remembering mouse position

		// time control
		double timestep = simcst::DEFAULT_TIMESTEP;

		void increase_speed(void){ timestep *= sqrt(2); }
		void decrease_speed(void){ timestep /= sqrt(2); }

		// viewpoint
		OpenGLView view;
		enum POV_TYPE{ FIRST_PERSON, THIRD_PERSON, FREE_POV };
		POV_TYPE pov_mode = FREE_POV;

		int pov_particle = 0;

		void update_free_pov(QKeyEvent* event);
		void update_pov_matrix(void);

		// timer
		int timerId;
		QTime stopwatch;
	public:
		AcceleratorWidgetGL(QWidget* parent, Vector3D origin) : QOpenGLWidget(parent), Accelerator(&view, origin){ setMouseTracking(true); }
		virtual ~AcceleratorWidgetGL(void){}
};
