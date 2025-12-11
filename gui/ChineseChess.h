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
    // 设置
    void onBtnClickedSetting();

    // 最小化
    void onBtnClickedMinimize();

    // 关闭
    void onBtnClickedClose();

    // 开始
    void onBtnClickedStart();

    // 悔棋
    void onBtnClickedWithdraw();

    // 和棋
    void onBtnClickedDraw();

    // 认输
    void onBtnClickedConcede();

protected:
    void mousePressEvent(QMouseEvent * event) override;//鼠标点击
    void mouseMoveEvent(QMouseEvent * event) override;//鼠标移动
    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    QLabel * findLabel(const QPoint & pos);

    void updateLabelStyleSheet(QLabel * lab, bool flag = false);

private:
    Ui::ChineseChessClass ui;

    bool m_blPressed = false;
    QPoint m_ptPos{};
    QPoint m_ptDst{};

    // 默认红方先手
    CHESS_COLOR_TYPE m_uiColor = CHESS_COLOR_RED;

    // 原位置和目标位置
    ChessPieceInfo m_struPieces{};

    // 是否对局完成
    bool m_blPlaying = false;
};

