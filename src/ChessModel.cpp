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
    const ChessPiece* object = m_objects[row];

    if (role == BoardIndexRole)
        return object->boardIndex();
    else if (role == TypeRole)
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

    if (role == BoardIndexRole)
        object->setBoardIndex(value.toInt());

    emit dataChanged(index, index);

    return true;
}

QHash<int, QByteArray> ChessModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BoardIndexRole] = "role_boardIndex";
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

    QJsonObject piecesObject = message["objects"]["pieces"].toObject();

    beginResetModel();

    m_objects.clear();

    for (const QString& pieceKey : piecesObject.keys()) {
        QJsonValue pieceValue = piecesObject.value(pieceKey);
        QChar file = pieceKey.front();
        int rank = pieceKey.back().digitValue();
        QChar pieceNotation = pieceValue.toVariant().toString()[0];
        PieceType type = ChessEnums::fromNotation(pieceNotation);

        ChessPiece* newObject = new ChessPiece(type, pieceValue.toString()[0].isLower());
        newObject->setRank(rank);
        newObject->setFile(file);

        m_objects += newObject;
    }

    endResetModel();
}

QString ChessModel::rankAndFile(const int boardIndex)
{
    QChar file = ChessEnums::file(boardIndex);
    int rank = ChessEnums::rank(boardIndex);
    return file + QString::number(rank);
}
