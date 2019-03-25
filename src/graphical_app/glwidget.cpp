#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

void GLWidget::initializeGL(){
	view.init();
}

void GLWidget::timerEvent(QTimerEvent* event){
	if(not isPaused){
		Q_UNUSED(event);
		double dt = stopwatch.restart() / 1000.0;
		update();
	}
}

void GLWidget::resizeGL(int width, int height){
	glViewport(0, 0, width, height);// draw on entire screen

	QMatrix4x4 matrix;
	matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrix);
}

void GLWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	content.draw();
}


void GLWidget::keyPressEvent(QKeyEvent* event){
	constexpr double small_angle(5); // in degrees
	constexpr double small_increment(0.5);

	switch(event->key()){
		case Qt::Key_P:
			if(isPaused){
				timerId = startTimer(20);
				isPaused = false;
			}else{
				isPaused = true;
				killTimer(timerId);
			}
			break;
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
			// close on Ctrl-w (Windows/Linux) or Cmd-w (Mac):
			if(event->modifiers() & Qt::ControlModifier) close();

			else view.translate(0.0, 0.0, small_increment);
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

		case Qt::Key_R:
			view.translate(0.0, -small_increment, 0.0);
			break;

		case Qt::Key_F:
			view.translate(0.0, small_increment, 0.0);
			break;

		case Qt::Key_Q:
			view.rotate(small_angle, 0.0, 0.0, -1.0);
			break;

		case Qt::Key_E:
			view.rotate(small_angle, 0.0, 0.0, +1.0);
			break;

		case Qt::Key_Home:
			view.initializePosition();
			break;
	};

	update();
}
