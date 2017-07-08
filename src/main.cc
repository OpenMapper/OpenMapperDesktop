// (c) 2017 OpenMapper

#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include <QApplication>
#include <QDesktopWidget>

#include "openmapper_desktop/window.h"
#include "openmapper/openmapper.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Window window;
	window.resize(window.sizeHint());
	int desktopArea = QApplication::desktop()->width()
			* QApplication::desktop()->height();
	int widgetArea = window.width() * window.height();

	window.setWindowTitle("OpenGL with Qt");

	if (((float) widgetArea / (float) desktopArea) < 0.75f) {
		window.show();
	} else {
		window.showMaximized();
	}

	std::string path_to_vocabulary =
			"../thirdparty/slam_engine/ORB_SLAM2/Vocabulary/ORBvoc.txt";
	std::string path_to_settings =
			"../thirdparty/slam_engine/ORB_SLAM2/Vocabulary/webcam.yaml";

	std::vector<std::string> flags;
	flags.push_back(path_to_vocabulary);
	flags.push_back(path_to_settings);

	std::shared_ptr<std::vector<double>> pos(new std::vector<double>);
	std::shared_ptr<std::vector<double>> rot(new std::vector<double>);

	openmapper::OpenMapper OpenMapper_engine(flags);
	OpenMapper_engine.getPose(pos, rot);
	std::cout << "Position " << (*pos)[0] << " " << (*pos)[1] << " " << '\n';

	return app.exec();
}
