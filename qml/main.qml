import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import QtQuick.Layouts
import QtWebSockets

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

    WebSocket {
        id: socket
        url: "ws://localhost:9001"
        active: true

        onStatusChanged: {
            if (socket.status === WebSocket.Open) {
                console.log("Client connected.")
                socket.sendTextMessage("{\"command\":\"join\"}")
            }
        }

        onTextMessageReceived: (message) => chessModel.processMessage(JSON.parse(message))
    }

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
            ambientColor: Qt.darker("slategrey")
            castsShadow: true
            shadowFactor: 50
            shadowMapQuality: Light.ShadowMapQualityHigh
        }

        OrthographicCamera {
            id: perspectiveCamera
            position: Qt.vector3d(0, -1300, 1000)
            lookAtNode: scene
        }

        Node {
            id: scene
            eulerRotation.z: -45

            ChessBoard {
                x: (squareSize / 2) - (boardWidth / 2)
                y: x

                ChessPieces { }
            }
        }

        PieceSelector { }
    }

    RowLayout {

        TextInput {
            id: textInput
            width: 200
            height: 100
        }

        Button {
            text: "Send"

            onClicked: {
                socket.sendTextMessage("{\"move\":\"" + textInput.text + "\"}")
                textInput.clear()
            }
        }
    }
}
