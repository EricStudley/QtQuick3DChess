#pragma once

#include <QObject>

#include "ChessEnums.h"

class ChessPiece
{

public:
    ChessPiece(const PieceType &pieceType, const bool dark);

    int rank() const { return m_rank; }
    QChar file() const { return m_file; }
    PieceType type() const { return m_type; }
    bool dark() const { return m_dark; }

    void setRank(const int rank);
    void setFile(const QChar file);

    void setBoardIndex(const int boardIndex);

private:
    void updateBoardIndex();

private:
    int m_boardIndex;

    int m_rank = 0;
    QChar m_file;
    PieceType m_type = PieceType::None;
    bool m_dark = false;
};
