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
      openmapper_engine_(new openmapper::OpenMapper(flags_)),
      tracking_image_(false) {
  ui->setupUi(this);
  ui->myGLWidget->openmapper_engine_ = openmapper_engine_;

  connect(ui->myGLWidget, SIGNAL(xRotationChanged(int)), ui->rotXSlider,
          SLOT(setValue(int)));
  connect(ui->myGLWidget, SIGNAL(yRotationChanged(int)), ui->rotYSlider,
          SLOT(setValue(int)));
  connect(ui->myGLWidget, SIGNAL(zRotationChanged(int)), ui->rotZSlider,
          SLOT(setValue(int)));

  LOG(INFO) << "Starting the engine...";
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

  if (tracking_image_) {
    input_source_->grabImage();
    cv::Mat img = input_source_->getCurrentImage();

    bool tracking = openmapper_engine_->trackImage(
        img, input_source_->getCurrentImageTimeSec());
    std::shared_ptr<std::vector<double>> pos(new std::vector<double>);
    std::shared_ptr<std::vector<double>> rot(new std::vector<double>);

    // Get pose of the camera in the fixed coordinate system.
    openmapper_engine_->getPose(pos, rot);

    LOG(INFO) << "Pose: " << (*pos)[0] << " " << (*pos)[1] << " " << (*pos)[2];

    // Show the image in a Qlabel.
    cv::Mat img2 = openmapper_engine_->cur_img_w_features_;
    cvtColor(img2, img2, CV_BGR2RGB);
    ui->image_label->setPixmap(QPixmap::fromImage(QImage(
        img2.data, img2.cols, img2.rows, img2.step, QImage::Format_RGB888)));
  }
}

void Window::initialize_input() {
  input_source_.reset(new openmapper::InputSource());
  std::string device;
  device = "0";
  LOG(INFO) << "Source is set to live video from camera device " << device;
  input_source_->setInput(openmapper::InputSource::kCamera, device);
}

void Window::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape) {
    // Close the window.
    close();
  } else if (e->key() == Qt::Key_Space) {
    // Start or stop tracking.
    if (tracking_image_) {
      // Engine is already running, lets stop it.
      tracking_image_ = false;
      LOG(WARNING) << "Going to stop the engine.";
    } else {
      LOG(WARNING) << "Going to start the engine.";
      tracking_image_ = true;
    }

  } else {
    QWidget::keyPressEvent(e);
  }
}
