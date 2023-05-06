#pragma once

#include <QObject>

#include "ChessModel.h"
#include "ChessEnums.h"

class ChessController : public QObject
{
    Q_OBJECT

public:
    explicit ChessController(ChessModel *chessModel, QObject *parent = nullptr);

signals:
    void sendTextMessage(const QString &textMessage);

    void pushPage(ChessEnums::ChessPage page);
    void popPage();
    void replacePage(ChessEnums::ChessPage page);

private:
    ChessModel *m_chessModel { nullptr };
};
