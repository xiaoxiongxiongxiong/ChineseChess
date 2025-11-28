#include "ChineseChess.h"
#include <QPainter>
#include <QPixmap>

ChineseChess::ChineseChess(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

ChineseChess::~ChineseChess()
{}

void ChineseChess::paintEvent(QPaintEvent * event)
{
    //QPainter painter(this);

    //// 加载第一个图片
    //QPixmap pixmap1(":/ChineseChess/res/RedGeneral.png");
    //// 绘制第一个图片到指定位置
    //painter.drawPixmap(40, 140, 50, 50, pixmap1); // 参数分别为 x, y, width, height
}
