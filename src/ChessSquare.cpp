#include "ChessSquare.h"

#include "ChessEnums.h"

ChessSquare::ChessSquare()
{

}

ChessSquare::ChessSquare(const QChar &file, const int rank) :
    m_file(file)
    , m_rank(rank)
    , m_boardIndex(ChessEnums::boardIndex(file, rank))
{
}
