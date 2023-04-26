#pragma once

#include <QObject>
#include <QPoint>

class ChessPiece
{
    Q_GADGET

public:
    enum PieceType {
        Unknown = 0,
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn
    };
    Q_ENUM(PieceType)

    ChessPiece();

    QString uuid() const { return m_uuid; }
    PieceType type() const { return m_type; }
    QString state() const { return m_state; }
    QPoint position() const { return m_position; }
    int style() const { return m_style; }
    bool moving() const { return m_moving; }
    int direction() const { return m_direction; }

    void setUuid(const QString &uuid) { m_uuid = uuid; }
    void setType(const PieceType &type) { m_type = type; }
    void setState(const QString &state) { m_state = state; }
    void setPosition(const QPoint &position) { m_position = position; }
    void setStyle(const int style) { m_style = style; }
    void setMoving(const bool moving) { m_moving = moving; }
    void setDirection(const int &direction) { m_direction = direction; }

private:
    QString m_uuid;
    PieceType m_type = Unknown;
    QString m_state;
    QPoint m_position;
    int m_style = 0;
    bool m_moving = false;
    int m_direction = 0;
};
