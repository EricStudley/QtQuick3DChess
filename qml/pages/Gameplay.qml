import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import QtQuick.Layouts

import Chess

import "gameplay"

Item {
    property int squareSize: 100
    property int rowCount: 8
    property int squareCount: 64
    property int boardWidth: squareSize * rowCount

    View3D {
        id: view3D
        anchors { fill: parent }

        environment: SceneEnvironment {
            clearColor: "skyblue"
            backgroundMode: SceneEnvironment.Color
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.VeryHigh
            temporalAAEnabled: true
            temporalAAStrength: 2.0
        }

        OrbitCameraController {
            anchors { fill: parent }
            origin: scene
            camera: perspectiveCamera
        }

        DirectionalLight {
            eulerRotation.y: -45
            ambientColor: Qt.darker("white")
        }

        OrthographicCamera {
            id: perspectiveCamera
            position: Qt.vector3d(0, -1300, 1000)
            lookAtNode: scene
        }

        Node {
            id: scene
            eulerRotation.z: 180-45

            ChessBoard {
                x: (squareSize / 2) - (boardWidth / 2)
                y: -(squareSize / 2) + (boardWidth / 2)
                selectedRankAndFile: pieceSelector.selectedPiece ? pieceSelector.selectedPiece.rankAndFile : ""

                ChessPieces { }
            }
        }

        PieceSelector {
            id: pieceSelector
            onPieceMoved: (from, to) => {
                              chessController.sendTextMessage("{\"move\": { \"from\":\""+ from +"\", \"to\":\""+ to +"\" } }")
                          }
        }
    }
}
