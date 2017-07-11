// (c) 2017 OpenMapper

#include <QtWidgets>

#include "ui_window.h"

#include "openmapper_desktop/config.h"
#include "openmapper_desktop/myglwidget.h"
#include "openmapper_desktop/window.h"

Window::Window(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Window),
      flags_{path_to_vocabulary, path_to_settings},
      openmapper_engine_(new openmapper::OpenMapper(flags_)) {
  ui->setupUi(this);
  ui->myGLWidget->openmapper_engine_ = openmapper_engine_;

  connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider,
          SLOT(setValue(int)));
  connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider,
          SLOT(setValue(int)));
  connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider,
          SLOT(setValue(int)));

  LOG(INFO) << "Starting the engine. ";
  initialize_input();
  timerId = startTimer(50);
}

Window::~Window() {
  killTimer(timerId);
  delete ui;
}

void Window::timerEvent(QTimerEvent *event) {
  CHECK_NOTNULL(input_source_.get());
  CHECK(input_source_->isInputModeSet());

  input_source_->grabImage();
  cv::Mat img = input_source_->getCurrentImage();

  bool tracking = openmapper_engine_->trackImage(
      img, input_source_->getCurrentImageTimeSec());
  std::shared_ptr<std::vector<double>> pos(new std::vector<double>);
  std::shared_ptr<std::vector<double>> rot(new std::vector<double>);

  // Get pose of the camera in the fixed coordinate system.
  openmapper_engine_->getPose(pos, rot);

  LOG(INFO) << "Pose: " << (*pos)[0] << " " << (*pos)[1] << " " << (*pos)[2];
}

void Window::initialize_input() {
  input_source_.reset(new openmapper::InputSource());
  std::string device;
  device = "0";
  LOG(INFO) << "Source is set to live video from camera device " << device;
  input_source_->setInput(openmapper::InputSource::kCamera, device);
}

void Window::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
}
