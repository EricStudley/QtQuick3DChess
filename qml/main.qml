import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls

Window {
    id: window
    visible: true
    width: 1200
    height: 900
    color: "black"
    title: qsTr("Qt Quick 3D Chess")

    property int squareSize: 100
    property int rowCount: 8
    property int squareCount: 64
    property int boardWidth: squareSize * rowCount

    View3D {
        id: view3D
        anchors { fill: parent }

        environment: SceneEnvironment {
            clearColor: "grey"
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
            rotation: 90
        }

        DirectionalLight {
            eulerRotation.x: -45
            ambientColor: Qt.darker("slategrey")
            castsShadow: true
        }

        PerspectiveCamera {
            id: perspectiveCamera
            eulerRotation.z: 90
            position: Qt.vector3d(1000, 0, 1000)
            lookAtNode: scene
        }

        Node {
            id: scene

            ChessBoard {
                x: (squareSize / 2) - (boardWidth / 2)
                y: x
            }
        }

        MouseArea {
            z: 1000
            anchors { fill: parent }

            property var selectedPiece

            onClicked: (mouse) => {
                           var result = view3D.pick(mouse.x, mouse.y)

                           if (result.objectHit) {
                               var objectHit = result.objectHit

                               if (objectHit.objectName) {
                                   if (selectedPiece) {
                                       selectedPiece.highlighted = false
                                   }

                                   if (objectHit !== selectedPiece) {
                                       selectedPiece = objectHit
                                       selectedPiece.highlighted = true
                                   }
                                   else {
                                       selectedPiece.highlighted = false
                                       selectedPiece = {}
                                   }
                               }
                               else {
                                   if (selectedPiece) {
                                       selectedPiece.x = objectHit.x
                                       selectedPiece.y = objectHit.y
                                       selectedPiece.highlighted = false
                                       selectedPiece = {}
                                   }
                               }
                           }
                       }
        }
    }
}
