#include "ChineseChess.h"
#include <QPainter>
#include <QMessageBox>

ChineseChess::ChineseChess(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
        lab->hide();
    }

    connect(ui.m_btnStart, SIGNAL(clicked()), this, SLOT(onBtnClickedStart()));
}

ChineseChess::~ChineseChess()
{}

void ChineseChess::onBtnClickedStart()
{
    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
        lab->show();
    }

    m_struPieces.role = CHESS_ROLE_NONE;
    m_struPieces.color = CHESS_COLOR_NONE;
    const auto & pos = ui.m_labBlackChariotLeft->pos();
    ChineseChessImpl::getInstance().init(pos.x(), pos.y());
    m_blOver = false;
}

void ChineseChess::mouseReleaseEvent(QMouseEvent * event)
{
    if (Qt::LeftButton != event->button() || m_blOver)
        return;

    auto pos = event->pos();

    ChessPieceInfo cpi{};
    if (!ChineseChessImpl::getInstance().findPiece(pos.x(), pos.y(), cpi))
        return;

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
            m_struPieces.role = CHESS_ROLE_NONE;
            m_struPieces.color = CHESS_COLOR_NONE;

            auto res = ChineseChessImpl::getInstance().isOver(cpi.color);
            switch (res)
            {
            case CHESS_RESULT_RWIN:
            {
                m_blOver = true;
                QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("红方胜！"));
            }
                break;
            case CHESS_RESULT_BWIN:
            {
                m_blOver = true;
                QMessageBox::information(this, QStringLiteral("对局结果"), QStringLiteral("黑方胜！"));
            }
                break;
            default:
                break;
            }
            return;
        }
    }

    auto labels = this->findChildren<QLabel *>();
    for (const auto & lab : labels)
    {
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
