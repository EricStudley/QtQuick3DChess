import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebSockets

import Chess

Window {
    id: window
    visible: true
    width: 1200
    height: 900
    title: qsTr("Qt Quick 3D Chess")

    Connections {
        target: chessController

        function onSendTextMessage(textMessage) { socket.sendTextMessage(textMessage) }
    }

    WebSocket {
        id: socket
        url: "ws://localhost:9001" //"wss://qtquick3dchess.onrender.com/"
        active: true

        onStatusChanged: {
            if (socket.status === WebSocket.Open) {
                console.log("Client connected.")
            }
        }

        onTextMessageReceived: (message) => chessModel.processMessage(JSON.parse(message))
    }

    StackView {
        id: stackView
        anchors { fill: parent }

        Component.onCompleted: push(pageItem(ChessPage.Welcome))

        function pageItem(page) {
            switch (page) {
            case ChessPage.Welcome: return "qrc:/qml/pages/Welcome.qml"
            case ChessPage.Gameplay: return "qrc:/qml/pages/Gameplay.qml"
            }
        }

        Connections {
            target: chessController

            function onPushPage(page) { stackView.push(stackView.pageItem(page)) }

            function onPopPage() { stackView.pop() }

            function onReplacePage(page) { stackView.replace(stackView.pageItem(page)) }
        }
    }
}
