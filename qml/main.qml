import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Chess

Window {
    id: window
    visible: true
    width: 1200
    height: 900
    title: qsTr("Qt Quick 3D Chess")

    StackView {
        id: stackView
        anchors { fill: parent }

        Component.onCompleted: push(pageItem(ChessPage.Gameplay))

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
