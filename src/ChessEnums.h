#pragma once

#include <QObject>
#include <QDebug>

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

    static PieceType fromNotation(QChar &notation) {
        notation = notation.toUpper();

        if (notation == 'P')
            return Pawn;
        else if (notation == 'R')
            return Rook;
        else if (notation == 'N')
            return Knight;
        else if (notation == 'B')
            return Bishop;
        else if (notation == 'Q')
            return Queen;
        else if (notation == 'K')
            return King;
        else
            return None;
    }

    static int boardIndex(const QChar file, const int rank) {
        int fileIndex = (file.toUpper().toLatin1() - 'A');
        int rowIndex = rank * ROW_COUNT;
        return fileIndex + rowIndex - ROW_COUNT;
    }

    static QChar file(const int boardIndex) {
        int fileIndex = boardIndex % ROW_COUNT;
        char file = 'A' + fileIndex;
        return QChar(file);
    }

    static int rank(const int boardIndex) {
        return qFloor(boardIndex / ROW_COUNT) + 1;
    }

private:
    explicit ChessEnums() = delete;
};

typedef ChessEnums::PieceType PieceType;
typedef ChessEnums::Side Side;
