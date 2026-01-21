#pragma once

#include <QDialog>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include "ui_PromptBox.h"

class PromptBox : public QDialog
{
    Q_OBJECT

public:
    PromptBox(QWidget *parent = nullptr);
    ~PromptBox();

    void setMessage(const QString & msg);

protected:
    void paintEvent(QPaintEvent * ev) override;

    void mousePressEvent(QMouseEvent * event) override;//鼠标点击
    void mouseMoveEvent(QMouseEvent * event) override;//鼠标移动
    void mouseReleaseEvent(QMouseEvent * event) override;

private:
    Ui::PromptBoxClass ui;
    QPixmap m_pixmap;

    bool m_blPressed = false;
    QPoint m_ptPos{};
};

