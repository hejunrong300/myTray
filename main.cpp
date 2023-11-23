#include "mytraywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	myTrayWidget w;
	w.show();

	return a.exec();
}
