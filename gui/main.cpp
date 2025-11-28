#include "ChineseChess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChineseChess window;
    window.show();
    return app.exec();
}
