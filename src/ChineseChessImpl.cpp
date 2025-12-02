#include "ChineseChessImpl.h"

void ChineseChessImpl::init(int x, int y)
{
    for (int i = 0; i < GRID_ROW_NUM; i++)
    {
        for (int j = 0; j < GRID_COL_NUM; j++)
        {
            m_struChessBoard[i][j].x = x + j * GRID_HORI_SIZE;
            m_struChessBoard[i][j].y = y + i * GRID_VERT_SIZE;
            setValue(m_struChessBoard[i][j], CHESS_COLOR_NONE, CHESS_ROLE_NONE);
        }
    }

    // 黑方
    setValue(m_struChessBoard[0][0], CHESS_COLOR_BLACK, CHESS_ROLE_CHARIOT);
    setValue(m_struChessBoard[0][1], CHESS_COLOR_BLACK, CHESS_ROLE_HORSE);
    setValue(m_struChessBoard[0][2], CHESS_COLOR_BLACK, CHESS_ROLE_ELEPHANT);
    setValue(m_struChessBoard[0][3], CHESS_COLOR_BLACK, CHESS_ROLE_ADVISOR);
    setValue(m_struChessBoard[0][4], CHESS_COLOR_BLACK, CHESS_ROLE_GENERAL);
    setValue(m_struChessBoard[0][5], CHESS_COLOR_BLACK, CHESS_ROLE_ADVISOR);
    setValue(m_struChessBoard[0][6], CHESS_COLOR_BLACK, CHESS_ROLE_ELEPHANT);
    setValue(m_struChessBoard[0][7], CHESS_COLOR_BLACK, CHESS_ROLE_HORSE);
    setValue(m_struChessBoard[0][8], CHESS_COLOR_BLACK, CHESS_ROLE_CHARIOT);
    setValue(m_struChessBoard[2][1], CHESS_COLOR_BLACK, CHESS_ROLE_CANNON);
    setValue(m_struChessBoard[2][7], CHESS_COLOR_BLACK, CHESS_ROLE_CANNON);
    setValue(m_struChessBoard[3][0], CHESS_COLOR_BLACK, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[3][2], CHESS_COLOR_BLACK, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[3][4], CHESS_COLOR_BLACK, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[3][6], CHESS_COLOR_BLACK, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[3][8], CHESS_COLOR_BLACK, CHESS_ROLE_SOLDIER);

    // 红方
    setValue(m_struChessBoard[9][0], CHESS_COLOR_RED, CHESS_ROLE_CHARIOT);
    setValue(m_struChessBoard[9][1], CHESS_COLOR_RED, CHESS_ROLE_HORSE);
    setValue(m_struChessBoard[9][2], CHESS_COLOR_RED, CHESS_ROLE_ELEPHANT);
    setValue(m_struChessBoard[9][3], CHESS_COLOR_RED, CHESS_ROLE_ADVISOR);
    setValue(m_struChessBoard[9][4], CHESS_COLOR_RED, CHESS_ROLE_GENERAL);
    setValue(m_struChessBoard[9][5], CHESS_COLOR_RED, CHESS_ROLE_ADVISOR);
    setValue(m_struChessBoard[9][6], CHESS_COLOR_RED, CHESS_ROLE_ELEPHANT);
    setValue(m_struChessBoard[9][7], CHESS_COLOR_RED, CHESS_ROLE_HORSE);
    setValue(m_struChessBoard[9][8], CHESS_COLOR_RED, CHESS_ROLE_CHARIOT);
    setValue(m_struChessBoard[7][1], CHESS_COLOR_RED, CHESS_ROLE_CANNON);
    setValue(m_struChessBoard[7][7], CHESS_COLOR_RED, CHESS_ROLE_CANNON);
    setValue(m_struChessBoard[6][0], CHESS_COLOR_RED, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[6][2], CHESS_COLOR_RED, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[6][4], CHESS_COLOR_RED, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[6][6], CHESS_COLOR_RED, CHESS_ROLE_SOLDIER);
    setValue(m_struChessBoard[6][8], CHESS_COLOR_RED, CHESS_ROLE_SOLDIER);

    m_iPosX = x;
    m_iPosY = y;
}

bool ChineseChessImpl::findPiece(int x, int y, ChessPieceInfo & cpi)
{
    int row = -1;
    int col = -1;
    if (!calcRowAndCol(x, y, row, col))
        return false;

    cpi = m_struChessBoard[row][col];

    return true;
}

bool ChineseChessImpl::movePiece(int srcX, int srcY, int dstX, int dstY)
{
    //获取当前行、列
    int srcRow = -1;
    int srcCol = -1;
    if (!calcRowAndCol(srcX, srcY, srcRow, srcCol))
        return false;

    // 是否存在有效棋子
    if (CHESS_ROLE_NONE == m_struChessBoard[srcRow][srcCol].role)
        return false;

    // 获取目标行、列
    int dstRow = -1;
    int dstCol = -1;
    if (!calcRowAndCol(dstX, dstY, dstRow, dstCol))
        return false;

    // 如果位置相同，则不进行移动
    if (srcRow == dstRow && srcCol == dstCol)
        return false;

    // 如果目标位置跟当前棋子同一阵营，则不可移动
    if (m_struChessBoard[srcRow][srcCol].color == m_struChessBoard[dstRow][dstCol].color)
        return false;

    bool res = false;
    const auto & cpi = m_struChessBoard[srcRow][srcCol];
    switch (cpi.role)
    {
    case CHESS_ROLE_GENERAL:
        res = moveGeneral(cpi.color, srcRow, srcCol, dstRow, dstCol);
        break;
    case CHESS_ROLE_ADVISOR:
        res = moveAdvisor(cpi.color, srcRow, srcCol, dstRow, dstCol);
        break;
    case CHESS_ROLE_ELEPHANT:
        res = moveElephant(cpi.color, srcRow, srcCol, dstRow, dstCol);
        break;
    case CHESS_ROLE_CHARIOT:
        res = moveChariot(srcRow, srcCol, dstRow, dstCol);
        break;
    case CHESS_ROLE_HORSE:
        res = moveHorse(srcRow, srcCol, dstRow, dstCol);
        break;
    case CHESS_ROLE_CANNON:
        res = moveCannon(srcRow, srcCol, dstRow, dstCol);
        break;
    case CHESS_ROLE_SOLDIER:
        res = moveSolder(cpi.color, srcRow, srcCol, dstRow, dstCol);
        break;
    default:
        break;
    }

    if (res)
    {
        setValue(m_struChessBoard[dstRow][dstCol], cpi.color, cpi.role);
        setValue(m_struChessBoard[srcRow][srcCol], CHESS_COLOR_NONE, CHESS_ROLE_NONE);
    }

    return res;
}

bool ChineseChessImpl::calcRowAndCol(int x, int y, int & row, int & col)
{
    //获取当前行
    row = (y - m_iPosY) / GRID_VERT_SIZE;
    // 校验有效性
    if (row < 0 || row >= GRID_ROW_NUM)
        return false;

    // 获取当前列
    col = (x - m_iPosX) / GRID_HORI_SIZE;
    // 校验有效性
    if (col < 0 || col >= GRID_COL_NUM)
        return false;

    return true;
}

void ChineseChessImpl::setValue(ChessPieceInfo & cpi, CHESS_COLOR_TYPE color, CHESS_ROLE_TYPE role)
{
    cpi.color = color;
    cpi.role = role;
}

bool ChineseChessImpl::moveGeneral(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 只能3、4、5这3列移动
    if (dstCol < 3 || dstCol > 5)
        return false;

    // 黑方只能在0~2行移动
    if (CHESS_COLOR_BLACK == color && (dstRow < 0 || dstRow > 2))
        return false;

    // 红方只能在7~9行移动
    if (CHESS_COLOR_RED == color && (dstRow < 7 || dstRow > 9))
        return false;

    // 只能移动一步，所以只有行或列发生改变
    if (1 != std::abs(srcRow - dstRow) + std::abs(srcCol - dstCol))
        return false;

    return true;
}

bool ChineseChessImpl::moveAdvisor(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 只能3、4、5这3列移动
    if (dstCol < 3 || dstCol > 5)
        return false;

    // 黑方只能在0~2行移动
    if (CHESS_COLOR_BLACK == color && (dstRow < 0 || dstRow > 2))
        return false;

    // 红方只能在7~9行移动
    if (CHESS_COLOR_RED == color && (dstRow < 7 || dstRow > 9))
        return false;

    // 只能斜着走，所以行和列同时发生改变
    if (1 != std::abs(srcRow - dstRow) || 1 != std::abs(srcCol - dstCol))
        return false;

    return true;
}

bool ChineseChessImpl::moveElephant(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 黑象 不能过河
    if (CHESS_COLOR_BLACK == color && dstRow > 4)
        return false;

    // 红相 不能过河
    if (CHESS_COLOR_RED == color && dstRow < 5)
        return false;

    // 田字，行和列同时发生2格变化
    if (2 != std::abs(srcRow - dstRow) || 2 != std::abs(srcCol - dstCol))
        return false;

    // 田字中心不能存在其它棋子
    int row = srcRow + (dstRow - srcRow) / 2;
    int col = srcCol + (dstCol - srcCol) / 2;
    if (CHESS_ROLE_NONE != m_struChessBoard[row][col].role)
        return false;

    return true;
}

bool ChineseChessImpl::moveHorse(int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 非日字
    int row = std::abs(srcRow - dstRow);
    int col = std::abs(srcCol - dstCol);
    if (0 == row || 0 == col || 3 != row + col)
        return false;

    // 横日
    if (2 == col)
    {
        if (dstCol > srcCol && CHESS_ROLE_NONE != m_struChessBoard[srcRow][srcCol + 1].role)
            return false;

        if (dstCol < srcCol && CHESS_ROLE_NONE != m_struChessBoard[srcRow][srcCol - 1].role)
            return false;
    }
    else // 竖日
    {
        if (dstRow > srcRow && CHESS_ROLE_NONE != m_struChessBoard[srcRow + 1][srcCol].role)
            return false;

        if (dstRow < srcRow && CHESS_ROLE_NONE != m_struChessBoard[srcRow - 1][srcCol].role)
            return false;
    }

    return true;
}

bool ChineseChessImpl::moveChariot(int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 只能直线，所以行或列只能有一个发生改变
    if (srcRow != dstRow && srcCol != dstCol)
        return false;

    // 横向移动
    if (srcRow == dstRow)
    {
        int colBegin = srcCol;
        int colEnd = dstCol;
        if (srcCol > dstCol)
        {
            colBegin = dstCol;
            colEnd = srcCol;
        }

        for (int i = colBegin + 1; i < colEnd; i++)
        {
            if (CHESS_ROLE_NONE != m_struChessBoard[srcRow][i].role)
                return false;
        }
    }
    else // 纵向移动
    {
        int rowBegin = srcRow;
        int rowEnd = dstRow;
        if (srcRow > dstRow)
        {
            rowBegin = dstRow;
            rowEnd = srcRow;
        }

        for (int i = rowBegin + 1; i < rowEnd; i++)
        {
            if (CHESS_ROLE_NONE != m_struChessBoard[i][srcCol].role)
                return false;
        }
    }

    return true;
}

bool ChineseChessImpl::moveCannon(int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 只能直线，所以行或列只能有一个发生改变
    if (srcRow != dstRow && srcCol != dstCol)
        return false;
    
    // 与目标位置中间棋子个数
    int cnt = 0;

    // 横向移动
    if (srcRow == dstRow)
    {
        int colBegin = srcCol;
        int colEnd = dstCol;
        if (srcCol > dstCol)
        {
            colBegin = dstCol;
            colEnd = srcCol;
        }

        for (int i = colBegin + 1; i < colEnd; i++)
        {
            if (CHESS_ROLE_NONE != m_struChessBoard[srcRow][i].role)
                cnt++;
        }
    }
    else // 纵向移动
    {
        int rowBegin = srcRow;
        int rowEnd = dstRow;
        if (srcRow > dstRow)
        {
            rowBegin = dstRow;
            rowEnd = srcRow;
        }

        for (int i = rowBegin + 1; i < rowEnd; i++)
        {
            if (CHESS_ROLE_NONE != m_struChessBoard[i][srcCol].role)
                cnt++;
        }
    }

    if (cnt > 1)
        return false;

    if (CHESS_ROLE_NONE == m_struChessBoard[dstRow][dstCol].role && 1 == cnt)
        return false;

    if (CHESS_ROLE_NONE != m_struChessBoard[dstRow][dstCol].role && 1 != cnt)
        return false;

    return true;
}

bool ChineseChessImpl::moveSolder(CHESS_COLOR_TYPE color, int srcRow, int srcCol, int dstRow, int dstCol)
{
    // 兵/卒只能向前或横移
    if (CHESS_COLOR_BLACK == color && srcRow > dstRow)
        return false;
   
    if (CHESS_COLOR_RED == color && srcRow < dstRow)
        return false;

    // 只能移动一格
    if (1 != std::abs(srcRow - dstRow) + std::abs(srcCol - dstCol))
        return false;

    return true;
}
