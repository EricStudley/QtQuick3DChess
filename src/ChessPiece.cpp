#include "ChessPiece.h"

ChessPiece::ChessPiece(const PieceType &pieceType, const bool dark) :
    m_type(pieceType)
  , m_dark(dark)
{
    updateBoardIndex();
}

void ChessPiece::setRank(const int rank)
{
    m_rank = rank;
    updateBoardIndex();
}

void ChessPiece::setFile(const QChar file)
{
    m_file = file;
    updateBoardIndex();
}

void ChessPiece::setBoardIndex(const int boardIndex)
{
    m_boardIndex = boardIndex;

    m_rank = ChessEnums::rank(boardIndex);
    m_file = ChessEnums::file(boardIndex);
}

void ChessPiece::updateBoardIndex()
{
    m_boardIndex = ChessEnums::boardIndex(m_file, m_rank);
}
