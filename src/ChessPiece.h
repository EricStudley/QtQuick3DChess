#pragma once

#include <QObject>

#include "ChessEnums.h"

class ChessPiece
{

public:
    ChessPiece(const PieceType &pieceType, const bool dark);

    int boardIndex() const { return m_boardIndex; }
    int rank() const { return m_rank; }
    QChar file() const { return m_file; }
    PieceType type() const { return m_type; }
    bool dark() const { return m_dark; }

    void setBoardIndex(const int boardIndex);
    void setRank(const int rank);
    void setFile(const QChar file);

private:
    void updateBoardIndex();

private:
    int m_boardIndex;
    int m_rank = 0;
    QChar m_file;
    PieceType m_type = PieceType::None;
    bool m_dark = false;
};
