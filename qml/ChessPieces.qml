import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

import Chess

Node {

    Repeater3D {
        model: chessModel

        ChessPiece {
            position: Qt.vector3d(x, y, 0)
            type: role_type
            dark: role_dark
            boardIndex: role_boardIndex
            rankAndFile: chessModel.rankAndFile(boardIndex)

            property real x: (boardIndex % rowCount) * squareSize
            property real y: (squareSize * Math.floor(boardIndex / rowCount)) - ((rowCount - 1) * squareSize)
        }
    }
}
