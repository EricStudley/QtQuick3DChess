#include "ChessModel.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "ChessEnums.h"

ChessModel::ChessModel(QObject* parent) :
    QAbstractListModel(parent)
{
}

int ChessModel::rowCount([[maybe_unused]] const QModelIndex& parent) const
{
    return m_objects.count();
}

QVariant ChessModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_objects.count())
        return {};

    const int row = index.row();
    const ChessSquare* object = m_objects[row];

    if (role == TypeRole)
        return object->piece().type();
    else if (role == FileRole)
        return object->file();
    else if (role == RankRole)
        return object->rank();
    else if (role == DarkRole)
        return object->piece().dark();

    return {};
}

QHash<int, QByteArray> ChessModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "role_type";
    roles[RankRole] = "role_rank";
    roles[FileRole] = "role_file";
    roles[DarkRole] = "role_dark";
    return roles;
}

void ChessModel::processMessage(const QJsonObject& message)
{
    if (message.isEmpty())
        return;

    QJsonValue objectList = message["objects"];

    QJsonArray playerObjects = objectList["event"].toObject()["board"].toObject()["squares"].toArray();

    beginResetModel();

    m_objects.clear();

    for (const QJsonValue& updatedValue : playerObjects) {
        QJsonObject updatedObject = updatedValue.toObject();
        QChar file = updatedObject["file"].toString().front();
        int rank = updatedObject["rank"].toInt();

        ChessSquare* newObject = new ChessSquare(rank, file);

        QJsonObject pieceObject = updatedObject["piece"].toObject();

        if (!pieceObject.isEmpty()) {
            QString typeString = pieceObject["type"].toString();
            PieceType type = ChessEnums::fromString(typeString);

            QJsonObject side = pieceObject["side"].toObject();
            QString sideName = side["name"].toString();
            ChessPiece piece = ChessPiece(type, sideName != "white");
            newObject->setPiece(piece);
        }

        m_objects += newObject;
    }

    endResetModel();



    //        if (m_objects.contains(uuid)) {
    //            oldUuidSet.insert(uuid);

    //            int objectIndex = m_objectUuids.indexOf(uuid);

    //            setData(index(objectIndex, 0), type, TypeRole);
    //            setData(index(objectIndex, 0), rank, RankRole);
    //            setData(index(objectIndex, 0), file, FileRole);
    //            setData(index(objectIndex, 0), dark, DarkRole);
    //        }
    //        else {
    //            ChessSquare* newObject = new ChessSquare();
    //            newObject->setType(static_cast<ChessEnums::PieceType>(type));

    //            beginInsertRows(QModelIndex(), m_objectUuids.length(), m_objectUuids.length());
    //            m_objects[uuid] = newObject;
    //            m_objectUuids.append(uuid);
    //            endInsertRows();
    //        }

    //        newUuidSet.insert(uuid);
    //    }

    //    const QSet<QString> removedUuidSet = oldUuidSet - newUuidSet;

    //    for (const QString& removedUuid : removedUuidSet) {
    //        int objectIndex = m_objectUuids.indexOf(removedUuid);
    //        beginRemoveRows(QModelIndex(), objectIndex, objectIndex);
    //        m_objects.remove(removedUuid);
    //        m_objectUuids.removeAll(removedUuid);
    //        endRemoveRows();
    //    }
}
