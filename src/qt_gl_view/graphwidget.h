#pragma once

#include <QOpenGLWidget>        
#include <QOpenGLShaderProgram> 
#include <vector>

#include "acceleratorwidgetgl.h"

class GraphWidget : public QOpenGLWidget {
public:
  GraphWidget(std::vector<Beam*> const& beams, QTime* time, QWidget* parent = nullptr)
    : QOpenGLWidget(parent), beams(beams), stopwatch(time) {}
  virtual ~GraphWidget() {}

private:
  std::vector<Beam*> beams;

  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  QOpenGLShaderProgram prog;
  QTime* stopwatch;
};
