import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

Node {

    Repeater3D {
        model: squareCount

        Model {
            scale: Qt.vector3d(1, 1, 0.05)
            position: Qt.vector3d(x, y, -(scale.z * squareSize))
            source: "#Cube"
            pickable: true

            property real x: (index % rowCount) * squareSize
            property real y: squareSize * Math.floor(index / rowCount)

            materials: PrincipledMaterial {
                baseColor: lightSquare ? "#FFFFFF" : "#000000"

                property bool evenRowIndex: index % 2
                property bool evenColumnIndex: (y / squareSize) % 2

                property bool lightSquare: evenColumnIndex ? evenRowIndex : !evenRowIndex
            }
        }
    }
}
