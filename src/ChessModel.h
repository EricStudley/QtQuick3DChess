#pragma once

#include "ChessSquare.h"

#include <QAbstractListModel>

class ChessModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ChessModel(QObject *parent = nullptr);

    enum DisplayRoles {
        TypeRole = Qt::UserRole + 1,
        FileRole,
        RankRole,
        DarkRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void processMessage(const QJsonObject &message);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ChessSquare*> m_objects;
};
