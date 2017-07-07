// main.cpp

#include <string>
#include <vector>
#include <iostream>

#include <QApplication>
#include <QDesktopWidget>

#include "window.h"
//#include "wrapper.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Window window;
  window.resize(window.sizeHint());
  int desktopArea =
      QApplication::desktop()->width() * QApplication::desktop()->height();
  int widgetArea = window.width() * window.height();

  window.setWindowTitle("OpenGL with Qt");

  if (((float)widgetArea / (float)desktopArea) < 0.75f) {
    window.show();
  } else {
    window.showMaximized();
  }

/*
  std::vector<double> pos;
  std::vector<double> rot;
  openmapper_wrapper::Wrapper wrapper;
  wrapper.GetPose(pos, rot);
  std::cout << "tata " << pos[0] << " " << pos[1] << " " << '\n';
*/
  return app.exec();
}
