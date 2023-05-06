import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import QtQuick.Layouts

import Chess

Item {

    ColumnLayout {
        anchors { centerIn: parent }

        TextField {
            id: textField
        }

        Button {
            text: "Join Server"

            onClicked: {
                chessController.sendTextMessage("{\"command\":\"joinServer\",\"serverName\":\"" + textField.text + "\"}")
                chessController.pushPage(ChessPage.Gameplay)
            }
        }

        Button {
            text: "Create Server"


            onClicked: {
                chessController.sendTextMessage("{\"command\":\"createServer\",\"serverName\":\"" + textField.text + "\"}")
                chessController.pushPage(ChessPage.Gameplay)
            }
        }
    }

    //    View3D {
    //        id: view3D
    //        anchors { fill: parent }

    //        environment: SceneEnvironment {
    //            clearColor: "skyblue"
    //            backgroundMode: SceneEnvironment.Color
    //            antialiasingMode: SceneEnvironment.MSAA
    //            antialiasingQuality: SceneEnvironment.VeryHigh
    //            temporalAAEnabled: true
    //            temporalAAStrength: 2.0
    //        }

    //        DirectionalLight {
    //            eulerRotation.y: -45
    //            ambientColor: Qt.darker("white")
    //        }
    //    }

    //    Canvas {
    //        anchors { fill: parent }

    //        property string titleString: "Qt Quick"

    //        onPaint: {
    //            var context = getContext("2d")
    //            context.font = '700 90px Verdana'
    //            context.textAlign = "center"

    //            var centerX = width / 2
    //            var centerY = height / 2
    //            var angle = Math.PI * 0.6
    //            var radius = 300

    //            context.fillStyle = "#000000"

    //            context.save()
    //            context.translate(centerX, centerY)
    //            context.rotate(-1 * angle / 2)
    //            context.rotate(-1 * (angle / titleString.length) / 2)

    //            for (var n = 0; n < titleString.length; n++) {
    //                context.rotate(angle / titleString.length)
    //                context.save()
    //                context.translate(0, -1 * radius)
    //                var char1 = titleString[n]
    //                context.fillText(char1, 0, 0)
    //                context.restore()
    //            }

    //            context.restore()
    //        }
    //    }
}
