// (c) 2017 OpenMapper

#ifndef OPENMAPPER_DESKTOP_WINDOW_H_
#define OPENMAPPER_DESKTOP_WINDOW_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <QSlider>
#include <QWidget>

#include <opencv2/core/core.hpp>
#include <openmapper_desktop/config.h>

namespace Ui {
class Window;
}

class Window : public QWidget {
  Q_OBJECT

 public:
  explicit Window(QWidget *parent = 0);
  ~Window();

 protected:
  void keyPressEvent(QKeyEvent *event);
  void timerEvent(QTimerEvent *event);
  void initialize_input();

 private:
  Ui::Window *ui;
  int timerId;
  //
  // The input source manages the input images. It gets the images over opencv
  // from a camera or movie.
  //
  std::shared_ptr<openmapper::InputSource> input_source_;

  std::vector<std::string> flags_;
  std::shared_ptr<openmapper::OpenMapper> openmapper_engine_;
};

#endif  // OPENMAPPER_DESKTOP_WINDOW_H_
