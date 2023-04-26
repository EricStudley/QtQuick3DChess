#pragma once

#include "ChessPiece.h"

#include <QAbstractListModel>

class ChessModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ChessModel(QObject *parent = nullptr);

    enum DisplayRoles {
        UuidRole = Qt::UserRole + 1,
        TypeRole,
        StateRole,
        StyleRole,
        PositionRole,
        MovingRole,
        DirectionRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Q_INVOKABLE void processMessage(const QJsonObject &message);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
//    void updateObjects(const QJsonObject &updatedObjects);

    QMap<QString, ChessPiece*> m_objects;
    QStringList m_objectUuids;
};
