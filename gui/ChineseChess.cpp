#include "ChineseChess.h"
#include <QPainter>
#include <QMessageBox>

#include "PromptBox.h"

ChineseChess::ChineseChess(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
        if ("m_labLogo" == lab->objectName() || "m_labTitle" == lab->objectName())
            continue;
        auto pos = lab->pos();
        lab->setProperty("src_x", pos.x());
        lab->setProperty("src_y", pos.y());
        lab->hide();
    }

    ui.m_btnWithdraw->setEnabled(false);
    ui.m_btnDraw->setEnabled(false);
    ui.m_btnConcede->setEnabled(false);

    connect(ui.m_btnSetting, SIGNAL(clicked()), this, SLOT(onBtnClickedSetting()));
    connect(ui.m_btnMinimize, SIGNAL(clicked()), this, SLOT(onBtnClickedMinimize()));
    connect(ui.m_btnClose, SIGNAL(clicked()), this, SLOT(onBtnClickedClose()));
    connect(ui.m_btnStart, SIGNAL(clicked()), this, SLOT(onBtnClickedStart()));
    connect(ui.m_btnWithdraw, SIGNAL(clicked()), this, SLOT(onBtnClickedWithdraw()));
    connect(ui.m_btnDraw, SIGNAL(clicked()), this, SLOT(onBtnClickedDraw()));
    connect(ui.m_btnConcede, SIGNAL(clicked()), this, SLOT(onBtnClickedConcede()));
}

ChineseChess::~ChineseChess()
{}

void ChineseChess::onBtnClickedSetting()
{
    PromptBox pb(this);
    if (CHESS_COLOR_BLACK == m_uiColor)
        pb.setMessage(QStringLiteral("黑方请求悔棋？"));
    else
        pb.setMessage(QStringLiteral("红方请求悔棋？"));
    pb.exec();
}

void ChineseChess::onBtnClickedMinimize()
{
    if (Qt::WindowMinimized == this->windowState())
        this->showNormal();
    else
        this->showMinimized();
}

void ChineseChess::onBtnClickedClose()
{
    QApplication * app;
    app->quit();
}

void ChineseChess::onBtnClickedStart()
{
    if (m_blPlaying)
        return;

    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
        if ("m_labLogo" == lab->objectName() || "m_labTitle" == lab->objectName())
            continue;
        auto x = lab->property("src_x").toInt();
        auto y = lab->property("src_y").toInt();
        lab->move(x, y);

        updateLabelStyleSheet(lab);
        lab->show();
    }

    m_struPieces.role = CHESS_ROLE_NONE;
    m_struPieces.color = CHESS_COLOR_NONE;
    const auto & pos = ui.m_labBlackChariotLeft->pos();
    ChineseChessImpl::getInstance().init(pos.x(), pos.y());
    m_blPlaying = true;

    ui.m_btnWithdraw->setEnabled(true);
    ui.m_btnDraw->setEnabled(true);
    ui.m_btnConcede->setEnabled(true);
}

void ChineseChess::onBtnClickedWithdraw()
{
    if (!m_blPlaying)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("对局未进行！"));
        return;
    }

    PromptBox pb(this);
    if (CHESS_COLOR_BLACK == m_uiColor)
        pb.setMessage(QStringLiteral("黑方请求悔棋？"));
    else
        pb.setMessage(QStringLiteral("红方请求悔棋？"));
    pb.exec();
}

void ChineseChess::onBtnClickedDraw()
{
    if (!m_blPlaying)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("对局未进行！"));
        return;
    }

    PromptBox pb(this);
    //int res = 0;
    if (CHESS_COLOR_BLACK == m_uiColor)
        pb.setMessage(QStringLiteral("黑方请求和棋？"));
    else
        pb.setMessage(QStringLiteral("红方请求和棋？"));
    pb.exec();
    //if (QMessageBox::Ok == res)
    //{
    //    QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("和棋！"));
    //    m_blPlaying = false;
    //}
}

void ChineseChess::onBtnClickedConcede()
{
    if (!m_blPlaying)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("对局未进行！"));
        return;
    }

    if (CHESS_COLOR_BLACK == m_uiColor)
        QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("黑方认输，红方胜！"));
    else
        QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("红方认输，黑方胜！"));
    m_blPlaying = false;
}

void ChineseChess::mousePressEvent(QMouseEvent * event)
{
    m_blPressed = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    m_ptPos = event->globalPos();
}

void ChineseChess::mouseMoveEvent(QMouseEvent * event)
{
    if (m_blPressed)
    {
        int dx = event->globalX() - m_ptPos.x();
        int dy = event->globalY() - m_ptPos.y();
        m_ptPos = event->globalPos();
        move(x() + dx, y() + dy);
    }
}

void ChineseChess::mouseReleaseEvent(QMouseEvent * event)
{
    if (Qt::LeftButton != event->button())
        return;

    ChessPieceInfo cpi{};
    auto pos = event->pos();
    auto ret = ChineseChessImpl::getInstance().findPiece(pos.x(), pos.y(), cpi);
    if (!m_blPlaying || !ret)
    {
        int dx = event->globalX() - m_ptPos.x();
        int dy = event->globalY() - m_ptPos.y();
        move(x() + dx, y() + dy);
        m_blPressed = false; // 鼠标松开时，置为false
        return;
    }

    // 棋子未选中
    if (CHESS_ROLE_NONE == m_struPieces.role)
    {
        if (CHESS_ROLE_NONE == cpi.role)
            return;
        if (m_uiColor != cpi.color)
            return;
        m_struPieces = cpi;
    }
    else
    {
        // 同一阵营，更换棋子
        if (cpi.color == m_struPieces.color)
        {
            m_struPieces = cpi;
        }
        else
        {
            if (!ChineseChessImpl::getInstance().movePiece(m_struPieces.x, m_struPieces.y, cpi.x, cpi.y))
                return;

            auto * label = findLabel(QPoint(cpi.x, cpi.y));
            if (label)
                label->hide();

            label = findLabel(QPoint(m_struPieces.x, m_struPieces.y));
            if (nullptr != label)
            {
                label->move(QPoint(cpi.x, cpi.y));
                //updateLabelStyleSheet(label);
            }

            m_uiColor = CHESS_COLOR_BLACK == m_uiColor ? CHESS_COLOR_RED : CHESS_COLOR_BLACK;

            auto res = ChineseChessImpl::getInstance().isOver(m_struPieces.color);
            switch (res)
            {
            case CHESS_RESULT_RWIN:
            {
                m_blPlaying = false;
                QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("红方胜！"));
            }
                break;
            case CHESS_RESULT_BWIN:
            {
                m_blPlaying = false;
                QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("黑方胜！"));
            }
                break;
            default:
                break;
            }
            m_struPieces.role = CHESS_ROLE_NONE;
            m_struPieces.color = CHESS_COLOR_NONE;
            return;
        }
    }

    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
        if ("m_labLogo" == lab->objectName() || "m_labTitle" == lab->objectName())
            continue;
        pos = lab->pos();
        if (pos.x() == cpi.x && pos.y() == cpi.y)
            updateLabelStyleSheet(lab, true);
        else
            updateLabelStyleSheet(lab);
    }
}

QLabel * ChineseChess::findLabel(const QPoint & pos)
{
    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
        if (lab->isHidden())
            continue;
        auto pt = lab->pos();
        if (pos == pt)
            return lab;
    }
    return nullptr;
}

void ChineseChess::updateLabelStyleSheet(QLabel * lab, bool flag)
{
    if (!lab)
        return;

    // 确保 widget 有 objectName（用于精准定位）
    QString objName = lab->objectName();
    if (objName.isEmpty())
    {
        objName = "border_toggle_" + QString::number(reinterpret_cast<quintptr>(lab));
        lab->setObjectName(objName);
    }

    QString currentStyle = lab->styleSheet();
    QString borderRule = QString("border: 3px dashed red;");

    // 检查是否已存在该边框规则
    if (currentStyle.contains(borderRule) || !flag)
    {
        // 已存在 → 移除
        currentStyle.replace(borderRule, "");
        lab->setStyleSheet(currentStyle.trimmed());
    }
    else
    {
        // 不存在 → 添加（追加到末尾）
        lab->setStyleSheet(currentStyle + " " + borderRule);
    }
}
