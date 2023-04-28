#include "ChessController.h"

ChessController::ChessController(ChessModel *ChessModel, QObject *parent)
    : QObject { parent }
    , m_chessModel { ChessModel }
{

}
