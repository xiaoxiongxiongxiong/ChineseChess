#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChineseChess.h"

#define CHESS_GRID_SIZE 59  // 宽度59
#define RED_GRID_SIZE   57  // 红区高57
#define BLACK_GRID_SIZE 58  // 黑区高58

class ChineseChess : public QMainWindow
{
    Q_OBJECT

public:
    ChineseChess(QWidget *parent = nullptr);
    ~ChineseChess();

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    Ui::ChineseChessClass ui;
};

