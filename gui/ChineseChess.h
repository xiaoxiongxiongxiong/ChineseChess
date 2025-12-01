#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChineseChess.h"

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

