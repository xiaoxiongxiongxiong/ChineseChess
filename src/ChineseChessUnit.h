#pragma once

#include <atomic>
#include <QPixmap>

// 棋子颜色
typedef enum _CHESS_COLOR_TYPE
{
	CHESS_COLOR_NONE,
	CHESS_COLOR_RED,    // 红方
	CHESS_COLOR_BLACK,  // 黑方
	CHESS_COLOR_MAX
} CHESS_COLOR_TYPE;

// 棋子角色
typedef enum _CHESS_ROLE_TYPE
{
	CHESS_ROLE_NONE,
	CHESS_ROLE_GENERAL,   // 帅/将
	CHESS_ROLE_ADVISOR,   // 士/仕
	CHESS_ROLE_ELEPHANT,  // 相/相
	CHESS_ROLE_CHARIOT,   // 车/俥
	CHESS_ROLE_HORSE,     // 马
	CHESS_ROLE_CANNON,    // 炮
	CHESS_ROLE_SOLDIER,   // 兵/卒
	CHESS_ROLE_MAX
} CHESS_ROLE_TYPE;

class ChinessChessUnit
{
public:
	ChinessChessUnit(CHESS_COLOR_TYPE color, CHESS_ROLE_TYPE role);
	virtual ~ChinessChessUnit();

	// 初始化棋子
	bool init(const QString & img, int x, int y, int w, int h);

	// 移动棋子到指定位置
	bool move(int x, int y);

	// 获取图像
	QPixmap getPixmap();

	// 获取位置
	QRect rect() const;

private:
    // 阵营
	CHESS_COLOR_TYPE _color = CHESS_COLOR_NONE;
    // 角色
	CHESS_ROLE_TYPE _role = CHESS_ROLE_NONE;
	// 图片
	QPixmap _img;
	// 横坐标
	int _x = 0;
	// 纵坐标
	int _y = 0;
	// 宽度
	int _width = 0;
	// 高度
	int _height = 0;
	// 是否已初始化
	std::atomic_bool _inited = { false };
};
