#include "ChessPiece.h"

ChessPiece::ChessPiece()
{

}

ChessPiece::ChessPiece(const PieceType &type, const bool dark) :
    m_type(type)
  , m_dark(dark)
{

}
