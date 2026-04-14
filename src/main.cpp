#include <QApplication>
#include "zenedit.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ZenEdit window;
    window.show();
    return app.exec();
}
