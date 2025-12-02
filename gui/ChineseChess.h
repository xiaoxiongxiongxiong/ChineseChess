#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include "ui_ChineseChess.h"
#include "../src/ChineseChessImpl.h"

class ChineseChess : public QMainWindow
{
    Q_OBJECT

public:
    ChineseChess(QWidget *parent = nullptr);
    ~ChineseChess();

public slots:
    void onBtnClickedStart();

protected:
    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    QLabel * findLabel(const QPoint & pos);

    void updateLabelStyleSheet(QLabel * lab, bool flag = false);

private:
    Ui::ChineseChessClass ui;

    // 默认红方先手
    CHESS_COLOR_TYPE m_uiColor = CHESS_COLOR_RED;

    // 原位置和目标位置
    ChessPieceInfo m_struPieces{};
};

