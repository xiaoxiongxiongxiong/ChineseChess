#include "ChineseChessUnit.h"

ChinessChessUnit::ChinessChessUnit(CHESS_COLOR_TYPE color, CHESS_ROLE_TYPE role) :
    _color(color),
    _role(role)
{
}

ChinessChessUnit::~ChinessChessUnit()
{
}

bool ChinessChessUnit::init(const QString & img, int x, int y, int w, int h)
{
    if (!_img.load(img))
        return false;

    _x = x;
    _y = y;
    _width = w;
    _height = h;

    _inited.store(true);

    return true;
}

bool ChinessChessUnit::move(int x, int y)
{
    if (!_inited.load())
        return false;

    _x = x;
    _y = y;

    return true;
}

QPixmap ChinessChessUnit::getPixmap()
{
    return _img;
}

// ªÒ»°Œª÷√
QRect ChinessChessUnit::rect() const
{
    return QRect(_x, _y, _width, _height);
}
