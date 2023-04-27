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

            property real x: (index % rowCount) * squareSize
            property real y: squareSize * Math.floor(index / rowCount)
        }
    }
}
