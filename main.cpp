#include <QApplication>
#include "MyBrowser.h"
#include <QDebug>

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	QApplication::setApplicationName("mysbrowser");
	MyBrowser w;
	w.show();
	return a.exec();
}

