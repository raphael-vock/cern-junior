#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>

#include "acceleratorwidgetgl.h"

AcceleratorWidgetGL::AcceleratorWidgetGL(QWidget* parent, Vector3D origin) :
	QOpenGLWidget(parent),
	Accelerator(&view, origin)
{
	setMouseTracking(true);
	timerId = startTimer(20);
	stopwatch.restart();
}

void AcceleratorWidgetGL::initializeGL(void){
	view.init();
	setWindowTitle("CERN Junior");
}

void AcceleratorWidgetGL::timerEvent(QTimerEvent*){
	/* Q_UNUSED(event); */
	/* double dt(time_factor * stopwatch.restart() / 1000.0); */
	double dt(timestep/simcst::DEPTH_FACTOR);
	for(int i(1); i <= simcst::DEPTH_FACTOR; ++i) evolve(dt);
	update();
}

void AcceleratorWidgetGL::resizeGL(int width, int height){
	glViewport(0.0, 0.0, width, height);// draw on entire screen

	QMatrix4x4 matrix;
	matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrix);
}

void AcceleratorWidgetGL::paintGL(void){
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	update_pov_matrix();
	draw();
}

void AcceleratorWidgetGL::update_pov_matrix(void){
	if(pov_mode != FREE_POV){
		if(particles.empty()){
			view.initializePosition();
			pov_mode = FREE_POV;
			return;
		}else{
			pov_particle = pov_particle % particles.size();
		}
	}

	switch(pov_mode){
		case THIRD_PERSON:{
			view.set_third_person_view(*particles[pov_particle]);
			break;
		}
		case FIRST_PERSON:{
			view.set_first_person_view(*particles[pov_particle]);
			break;
		}
		default: return; // do nothing by default
	}
}

void AcceleratorWidgetGL::update_free_pov(QKeyEvent* event){
	const double small_angle(event->modifiers() & Qt::ShiftModifier ? 5 : 2);
	const double small_increment(event->modifiers() & Qt::ShiftModifier ? 0.5 : 0.2);

	switch(event->key()){
		case Qt::Key_Left:
			view.rotate(small_angle, 0.0, -1.0, 0.0);
			break;
		case Qt::Key_Right:
			view.rotate(small_angle, 0.0, +1.0, 0.0);
			break;
		case Qt::Key_Up:
			view.rotate(small_angle, -1.0, 0.0, 0.0);
			break;
		case Qt::Key_Down:
			view.rotate(small_angle, +1.0, 0.0, 0.0);
			break;
		case Qt::Key_W:
			if(not(event->modifiers() & Qt::ControlModifier)){
				view.translate(0.0, 0.0, small_increment);
			}
			break;
		case Qt::Key_S:
			view.translate(0.0, 0.0, -small_increment);
			break;
		case Qt::Key_A:
			view.translate(small_increment, 0.0, 0.0);
			break;
		case Qt::Key_D:
			view.translate(-small_increment, 0.0, 0.0);
			break;
		case Qt::Key_Q:
			view.rotate(small_angle, 0.0, 0.0, -1.0);
			break;
		case Qt::Key_E:
			view.rotate(small_angle, 0.0, 0.0, +1.0);
			break;
	}
}

void AcceleratorWidgetGL::keyPressEvent(QKeyEvent* event){
	if(pov_mode == FREE_POV){
		update_free_pov(event);
	}

	switch(event->key()){
		case Qt::Key_W:
			if(event->modifiers() & Qt::ControlModifier){
				// Close on Ctrl-W (Windows/Linux) or Cmd-W (Mac):
				close();
			}else{
				++ pov_particle;
			}
			break;
		case Qt::Key_S:
			-- pov_particle;
			if(pov_particle < 0){
				pov_particle += particles.size();
			}
			break;
		case Qt::Key_Space:
			pause();
			break;
		case Qt::Key_Plus:
			increase_speed();
			break;
		case Qt::Key_Equal:
			decrease_speed();
			break;
		case Qt::Key_M:
			view.toggle_matrix_mode();
			break;
		case Qt::Key_1:
			if(pov_mode == FIRST_PERSON) return;
			pov_mode = FIRST_PERSON;
			break;
		case Qt::Key_2:
			if(pov_mode == FREE_POV) return;
			view.initializePosition();
			pov_mode = FREE_POV;
			break;
		case Qt::Key_3:
			if(pov_mode == THIRD_PERSON) return;
			pov_mode = THIRD_PERSON;
			break;
	};
	update();
}

void AcceleratorWidgetGL::mousePressEvent(QMouseEvent* event){
	if(pov_mode != FREE_POV) return;

	lastMousePosition = event->pos();
}

void AcceleratorWidgetGL::mouseMoveEvent(QMouseEvent* event){
	if(pov_mode != FREE_POV) return;

	if(event->buttons() & Qt::LeftButton){
		constexpr double angle(0.1); // in degrees

		QPointF d = event->pos() - lastMousePosition;
		lastMousePosition = event->pos();

		view.rotate(-angle * d.manhattanLength(), d.y(), d.x(), 0.0);

		update();
	}
}

void AcceleratorWidgetGL::pause(void){
	if(timerId == 0){
		timerId = startTimer(20);
		stopwatch.restart();
	}else{
		killTimer(timerId);
		timerId = 0;
	}
}
