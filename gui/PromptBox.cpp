#include "PromptBox.h"

PromptBox::PromptBox(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 加载 PNG（假设 background.png 有透明通道）
    QPixmap pixmap(":/ChineseChess/res/PromptBox.png");
    resize(pixmap.size());

    // 从 alpha 通道生成遮罩
    QBitmap mask = pixmap.createMaskFromColor(Qt::transparent, Qt::MaskInColor);
    setMask(mask);

    m_pixmap = pixmap;
}

PromptBox::~PromptBox()
{}

void PromptBox::setMessage(const QString & msg)
{
    ui.m_labMessage->setText(msg);
}

void PromptBox::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
}

void PromptBox::mousePressEvent(QMouseEvent * event)
{
    m_blPressed = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    m_ptPos = event->globalPos();
}

void PromptBox::mouseMoveEvent(QMouseEvent * event)
{
    if (m_blPressed)
    {
        int dx = event->globalX() - m_ptPos.x();
        int dy = event->globalY() - m_ptPos.y();
        m_ptPos = event->globalPos();
        move(x() + dx, y() + dy);
    }
}

void PromptBox::mouseReleaseEvent(QMouseEvent * event)
{
    int dx = event->globalX() - m_ptPos.x();
    int dy = event->globalY() - m_ptPos.y();
    move(x() + dx, y() + dy);
    m_blPressed = false; // 鼠标松开时，置为false
}
