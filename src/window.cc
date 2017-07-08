// (c) 2017 OpenMapper

#include <QtWidgets>

#include "openmapper_desktop/myglwidget.h"
#include "openmapper_desktop/window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) : QWidget(parent), ui(new Ui::Window) {
  ui->setupUi(this);

  connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider,
          SLOT(setValue(int)));
  connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider,
          SLOT(setValue(int)));
  connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider,
          SLOT(setValue(int)));
}

Window::~Window() { delete ui; }

void Window::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
}
