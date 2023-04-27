#include "ChessModel.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "ChessEnums.h"

ChessModel::ChessModel(QObject* parent) :
    QAbstractListModel(parent)
{
    qDebug() << "Board Index for A1:" << ChessEnums::boardIndex('A', 1);
    qDebug() << "Board Index for A1:" << ChessEnums::boardIndex('H', 8);

    qDebug() << "File for index 0:" << ChessEnums::file(0);
    qDebug() << "Rank for index 0:" << ChessEnums::rank(0);

    qDebug() << "File for index 63:" << ChessEnums::file(63);
    qDebug() << "Rank for index 63:" << ChessEnums::rank(63);
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
    const ChessPiece* object = m_objects[row];

    if (role == TypeRole)
        return object->type();
    else if (role == FileRole)
        return object->file();
    else if (role == RankRole)
        return object->rank();
    else if (role == DarkRole)
        return object->dark();

    return {};
}

bool ChessModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    const int row = index.row();
    ChessPiece* object = m_objects[row];

    if (role == RankRole)
        object->setRank(value.toInt());
    else if (role == FileRole)
        object->setFile(value.toChar());

    emit dataChanged(index, index);

    return true;
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

    QJsonObject piecesObject = objectList["pieces"].toObject();

    beginResetModel();

    m_objects.clear();

    for (const QString& pieceKey : piecesObject.keys()) {
        QJsonValue value = piecesObject.value(pieceKey);

        QChar file = pieceKey.front();
        int rank = pieceKey.back().digitValue();

//        ChessPiece* newObject = new ChessPiece(rank, file);

//        QJsonObject pieceObject = updatedObject["piece"].toObject();

//        if (!pieceObject.isEmpty()) {
//            QString typeString = pieceObject["type"].toString();
//            PieceType type = ChessEnums::fromString(typeString);

//            QJsonObject side = pieceObject["side"].toObject();
//            QString sideName = side["name"].toString();
//            ChessPiece piece = ChessPiece(type, sideName != "white");
//            newObject->setPiece(piece);
//        }

//        m_objects += newObject;
    }

    endResetModel();
}
