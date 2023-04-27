#pragma once

#include <QObject>

static auto constexpr ROW_COUNT = 8;

class ChessEnums
{
    Q_GADGET

public:
    enum PieceType {
        None = 0,
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };
    Q_ENUM(PieceType)

    enum Side {
        Light,
        Dark
    };
    Q_ENUM(Side)

    static PieceType fromNotation(const QString &notation) {
        if (notation == 'a')
            return Pawn;
    }

    static PieceType fromString(const QString &string) {
        if (string == "pawn")
            return Pawn;
        else if (string == "rook")
            return Rook;
        else if (string == "knight")
            return Knight;
        else if (string == "bishop")
            return Bishop;
        else if (string == "queen")
            return Queen;
        else if (string == "king")
            return King;
        else
            return None;
    }

    static int pieceIndex(int rank, char file) {
        int fileInt = (file - 'a');
        int rowIndex = fileInt * ROW_COUNT;
        return rowIndex + rank;
    }

private:
    explicit ChessEnums() = delete;
};

typedef ChessEnums::PieceType PieceType;
typedef ChessEnums::Side Side;
