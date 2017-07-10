// (c) 2017 OpenMapper

#ifndef OPENMAPPER_DESKTOP_MYGLWIDGET_H_
#define OPENMAPPER_DESKTOP_MYGLWIDGET_H_

#include <glog/logging.h>
#include <QGLWidget>
#include "openmapper_desktop/config.h"

class MyGLWidget: public QGLWidget {
Q_OBJECT
public:
	explicit MyGLWidget(QWidget *parent = 0);
	~MyGLWidget();
	std::shared_ptr<openmapper::OpenMapper> openmapper_engine_;

signals:

public slots:

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public slots:
	// slots for xyz-rotation slider
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	// signaling rotation from mouse movement
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

private:
	void draw();

	int xRot;
	int yRot;
	int zRot;

	QPoint lastPos;
};

#endif  // OPENMAPPER_DESKTOP_MYGLWIDGET_H_
