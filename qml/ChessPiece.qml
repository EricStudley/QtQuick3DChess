import QtQuick
import QtQuick3D

import Chess

Model {
    visible: type
    objectName: type
    scale: Qt.vector3d(squareSize, squareSize, squareSize)
    eulerRotation: dark ? Qt.vector3d(0, 0, 0) : Qt.vector3d(0, 0, 180)
    pickable: true
    source: switch (type) {
            case PieceType.None: return ""
            case PieceType.Pawn: return "qrc:/res/meshes/pawn.mesh"
            case PieceType.Rook: return "qrc:/res/meshes/rook.mesh"
            case PieceType.Knight: return "qrc:/res/meshes/knight.mesh"
            case PieceType.Bishop: return "qrc:/res/meshes/bishop.mesh"
            case PieceType.Queen: return "qrc:/res/meshes/queen.mesh"
            case PieceType.King: return "qrc:/res/meshes/king.mesh"
            }

    property int rank: 0
    property string file: ""
    property bool dark: false
    property bool highlighted: false
    property int boardIndex: 0

    property int type

    signal updateBoardIndex(var index)

    Behavior on x { SmoothedAnimation { } }
    Behavior on y { SmoothedAnimation { } }

    materials: [
        PrincipledMaterial {
            baseColor: highlighted ? "#FF5CB3FF"
                                   : dark ? "#FF2C2C35"
                                          : "#FFFFDB9F"
            roughness: 0.6
            cullMode: Material.NoCulling
            alphaMode: PrincipledMaterial.Opaque
        }
    ]
}
