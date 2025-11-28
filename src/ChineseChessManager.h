#pragma once

class ChinessChessUnit;

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

private:
	ChineseChessManager() = default;
	~ChineseChessManager() = default;

	
};
