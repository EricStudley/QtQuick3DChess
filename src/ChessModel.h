#pragma once

#include "ChessPiece.h"

#include <QAbstractListModel>
#include <QJsonObject>

class ChessModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap availableMoves READ availableMoves WRITE setAvailableMoves NOTIFY availableMovesChanged)

public:
    explicit ChessModel(QObject *parent = nullptr);

    enum DisplayRoles {
        TypeRole = Qt::UserRole + 1,
        BoardIndexRole,
        FileRole,
        RankRole,
        DarkRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void processMessage(const QJsonObject &message);
    Q_INVOKABLE QString rankAndFile(const int boardIndex);

    // Q_PROPERTY READ
    QVariantMap availableMoves() const;

    // Q_PROPERTY WRITE
    void setAvailableMoves(const QVariantMap &newAvailableMoves);

signals:
    void availableMovesChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ChessPiece*> m_objects;

    // Q_PROPERTY MEMBER
    QVariantMap m_availableMoves;
};
