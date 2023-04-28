#pragma once

#include <QObject>

#include "ChessSquare.h"
#include "ChessEnums.h"

class ChessPiece
{

public:
    ChessPiece(const PieceType &pieceType, const bool dark);

    ChessSquare chessSquare() const { return m_chessSquare; }
    PieceType type() const { return m_type; }
    bool dark() const { return m_dark; }

    void setChessSquare(const ChessSquare chessSquare);

private:
    ChessSquare m_chessSquare;
    PieceType m_type = PieceType::None;
    bool m_dark = false;
};
