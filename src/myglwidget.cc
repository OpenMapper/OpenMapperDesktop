// (c) 2017 OpenMapper

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <QtOpenGL>
#include <QtWidgets>

#include "openmapper_desktop/myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
		QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
	xRot = 0;
	yRot = 0;
	zRot = 0;

}

MyGLWidget::~MyGLWidget() {
}

QSize MyGLWidget::minimumSizeHint() const {
	return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const {
	return QSize(400, 400);
}

static void qNormalizeAngle(int &angle) {
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle) {
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void MyGLWidget::setYRotation(int angle) {
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void MyGLWidget::setZRotation(int angle) {
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void MyGLWidget::initializeGL() {
	qglClearColor(Qt::black);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
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

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
	lastPos = event->pos();
}

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
	//qglColor(Qt::red);

	const std::vector<cv::Point3f>& vpMPs =
			openmapper_engine_->map_->getFeaturesPosition();

	constexpr float point_size = 2.0f:
	
	glPointSize(point_size);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);

	for (std::size_t i = 0u; i < vpMPs.size(); ++i) {
		glVertex3f(vpMPs[i].x, vpMPs[i].y, vpMPs[i].z));
	}
	glEnd();

}
