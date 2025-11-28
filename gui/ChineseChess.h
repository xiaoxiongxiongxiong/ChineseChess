#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChineseChess.h"

#define CHESS_GRID_SIZE 59

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

