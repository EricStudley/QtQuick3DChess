#include "ChessModel.h"

#include <QDebug>
#include <QJsonObject>

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
    const QString key = m_objectUuids.at(row);
    const ChessPiece* object = m_objects[key];

    if (role == UuidRole)
        return object->uuid();
    else if (role == TypeRole)
        return object->type();
    else if (role == StateRole)
        return object->state();
    else if (role == StyleRole)
        return object->style();
    else if (role == PositionRole)
        return object->position();
    else if (role == DirectionRole)
        return object->direction();
    else if (role == MovingRole)
        return object->moving();

    return {};
}

bool ChessModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    const int row = index.row();
    const QString key = m_objectUuids.at(row);
    ChessPiece* object = m_objects[key];

    if (role == UuidRole)
        object->setUuid(value.toString());
    else if (role == TypeRole)
        object->setType(value.value<ChessPiece::PieceType>());
    else if (role == StateRole)
        object->setState(value.toString());
    else if (role == StyleRole)
        object->setStyle(value.toInt());
    else if (role == PositionRole)
        object->setPosition(value.toPoint());
    else if (role == DirectionRole)
        object->setDirection(value.toInt());
    else if (role == MovingRole)
        object->setMoving(value.toBool());

    emit dataChanged(index, index);

    return true;
}

QHash<int, QByteArray> ChessModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UuidRole] = "role_uuid";
    roles[TypeRole] = "role_type";
    roles[StateRole] = "role_state";
    roles[StyleRole] = "role_style";
    roles[PositionRole] = "role_position";
    roles[MovingRole] = "role_moving";
    roles[DirectionRole] = "role_direction";
    return roles;
}

void ChessModel::processMessage(const QJsonObject& message)
{
    qDebug() << message;
}

//void ChessModel::updateObjects(const QJsonObject& updatedObjects)
//{
//    if (updatedObjects.isEmpty())
//        return;

//    QSet<QString> oldUuidSet;
//    QSet<QString> newUuidSet;

//    for (const QJsonValue& updatedValue : updatedObjects) {
//        QJsonObject updatedObject = updatedValue.toObject();
//        QString uuid = updatedObject.value("uuid").toString();
//        int style = updatedObject.value("style").toInt();
//        int x = updatedObject.value("x").toInt();
//        int y = updatedObject.value("y").toInt();
//        QPoint position = QPoint(x, y);
//        bool moving = updatedObject.value("moving").toBool();
//        int direction = updatedObject.value("direction").toInt();
//        int type = updatedObject.value("type").toInt();
//        QString state = updatedObject.value("state").toString();
//        bool alive = updatedObject.value("is_alive").toBool();

//        if (!alive) {

//            if (m_objects.contains(uuid)) {
//                oldUuidSet.insert(uuid);
//            }
//            continue;
//        }

//        if (m_objects.contains(uuid)) {
//            oldUuidSet.insert(uuid);

//            int objectIndex = m_objectUuids.indexOf(uuid);

//            setData(index(objectIndex, 0), style, StyleRole);
//            setData(index(objectIndex, 0), position, PositionRole);
//            setData(index(objectIndex, 0), moving, MovingRole);
//            setData(index(objectIndex, 0), direction, DirectionRole);
//        }
//        else {
//            ChessPiece* newObject = new ChessPiece();
//            newObject->setUuid(uuid);
//            newObject->setType(static_cast<ChessPiece::PieceType>(type));
//            newObject->setState(state);
//            newObject->setStyle(style);
//            newObject->setPosition(position);
//            newObject->setDirection(direction);
//            newObject->setMoving(moving);

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
//}
