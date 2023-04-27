#pragma once

#include <QObject>

#include "ChessPiece.h"

class ChessSquare
{

public:
    ChessSquare(const int rank, const QChar &file);

    int rank() const { return m_rank; }
    QChar file() const { return m_file; }
    ChessPiece piece() const { return m_piece; }

    void setPiece(const ChessPiece &piece) { m_piece = piece; }

private:
    int m_rank = 0;
    QChar m_file;
    ChessPiece m_piece;
};
