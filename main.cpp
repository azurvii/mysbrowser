#include <QApplication>
#include "MyBrowser.h"

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	MyBrowser w;
	w.show();
	return a.exec();
}

