// (c) 2017 OpenMapper

#ifndef OPENMAPPER_DESKTOP_WINDOW_H_
#define OPENMAPPER_DESKTOP_WINDOW_H_

#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include <QWidget>
#include <QSlider>

#include "openmapper/openmapper.h"

namespace Ui {
class Window;
}

class Window: public QWidget {
Q_OBJECT

public:
	explicit Window(QWidget *parent = 0);
	~Window();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	Ui::Window *ui;
};

#endif // OPENMAPPER_DESKTOP_WINDOW_H_
