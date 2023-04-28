#pragma once

#include "ChessPiece.h"

#include <QAbstractListModel>

class ChessModel : public QAbstractListModel
{
    Q_OBJECT

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
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Q_INVOKABLE void processMessage(const QJsonObject &message);
    Q_INVOKABLE QString rankAndFile(const int boardIndex);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ChessPiece*> m_objects;
};
