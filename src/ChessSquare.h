#pragma once

#include <QObject>

class ChessSquare
{

public:
    ChessSquare();
    ChessSquare(const QChar &file, const int rank);

    int boardIndex() const { return m_boardIndex; }
    QChar file() const { return m_file; }
    int rank() const { return m_rank; }

private:
    int m_boardIndex;
    QChar m_file;
    int m_rank = 0;
};
