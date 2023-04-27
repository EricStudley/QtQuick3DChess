#pragma once

#include <QObject>
#include <QPoint>

#include "ChessEnums.h"

class ChessPiece
{

public:
    ChessPiece();
    ChessPiece(const PieceType &type, const bool dark);

    PieceType type() const { return m_type; }
    bool dark() const { return m_dark; }

private:
    PieceType m_type = PieceType::None;
    bool m_dark = false;
};
