#include "ChessPiece.h"

ChessPiece::ChessPiece(const PieceType &pieceType, const bool dark) :
    m_type(pieceType)
    , m_dark(dark)
{
}

void ChessPiece::setChessSquare(const ChessSquare chessSquare)
{
    m_chessSquare = chessSquare;
}
