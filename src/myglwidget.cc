// (c) 2017 OpenMapper

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <QtOpenGL>
#include <QtWidgets>

#include "openmapper_desktop/myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
  xRot = 0;
  yRot = 0;
  zRot = 0;
  renderer_.reset(new openmapper::Renderer);
}

MyGLWidget::~MyGLWidget() {}

QSize MyGLWidget::minimumSizeHint() const { return QSize(50, 50); }

QSize MyGLWidget::sizeHint() const { return QSize(400, 400); }

// TODO(gocarlos): remove those functions.
static void qNormalizeAngle(int &angle) {}
void MyGLWidget::setXRotation(int angle) {}
void MyGLWidget::setYRotation(int angle) {}
void MyGLWidget::setZRotation(int angle) {}

void MyGLWidget::initializeGL() {
  qglClearColor(Qt::black);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  static GLfloat lightPosition[4] = {0, 0, 10, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  // Pass the pointer to the renderer in order to let it access the data should
  // should be rendered.
  renderer_->openmapper_engine_ = openmapper_engine_;
}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
  draw();
}

void MyGLWidget::resizeGL(int width, int height) {
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
#ifdef QT_OPENGL_ES_1
  glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
  glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
  glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event) { lastPos = event->pos(); }

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8 * dy);
    setZRotation(zRot + 8 * dx);
  }

  lastPos = event->pos();
}

void MyGLWidget::draw() {
  renderer_->drawMapPoints();
  renderer_->drawCurrentImage();
}
