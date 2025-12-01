#pragma once

#include <array>
#include "ChineseChessUnit.h"

#define CHESS_PIECE_SIZE 48  // 棋子大小

#define GRID_ROW_NUM 10  // 横向棋格个数
#define GRID_COL_NUM 9   // 纵向棋格个数

#define GRID_HORI_SIZE 59  // 棋格宽度
#define GRID_VERT_SIZE 57  // 棋格高度

// 棋子信息
typedef struct _ChessPieceInfo
{
	CHESS_COLOR_TYPE color;  // 阵营
	CHESS_ROLE_TYPE role;    // 角色
	int x;                   // 横坐标
	int y;                   // 纵坐标
} ChessPieceInfo;

class ChineseChessManager
{
public:
	// 删除拷贝
	ChineseChessManager(const ChineseChessManager & other) = delete;
	// 删除赋值
	ChineseChessManager & operator=(const ChineseChessManager &) = delete;
	// 删除移动
	ChineseChessManager(ChineseChessManager && other) noexcept = delete;
	// 删除移动赋值
	ChineseChessManager & operator=(ChineseChessManager &&) noexcept = delete;

	// 全局唯一访问点
    static ChineseChessManager & getInstance()
	{
        static ChineseChessManager instance;  // C++11 起：线程安全！
        return instance;
    }

	// 初始化棋盘，左上角坐标
	void init(int x, int y);

	// 移动棋子
	bool movePiece(int srcX, int srcY, int dstX, int dstY);

private:
	ChineseChessManager() = default;
	~ChineseChessManager() = default;

	// 给棋子赋值
	void setValue(ChessPieceInfo & cpi, CHESS_COLOR_TYPE color, CHESS_ROLE_TYPE role);

	// 移动帥/將
	bool moveGeneral(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol);

	// 移动士/仕
	bool moveAdvisor(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol);

	// 移动象/相
	bool moveElephant(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol);

	// 移动马
	bool moveHorse(int srcRow, int srcCol, int dstRow, int dstCol);

	// 移动车
	bool moveChariot(int srcRow, int srcCol, int dstRow, int dstCol);

	// 移动炮
	bool moveCannon(int srcRow, int srcCol, int dstRow, int dstCol);

	// 移动兵/卒
	bool moveSolder(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol);

private:
	// 左上角横坐标
	int m_iPosX = 0;
	// 左上角纵坐标
	int m_iPosY = 0;

	// 棋盘信息
	std::array<std::array<ChessPieceInfo, GRID_COL_NUM>, GRID_ROW_NUM> m_struChessBoard;
};
