import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

Node {

    Repeater3D {
        model: [
            56, 57, 58, 59, 60, 61, 62, 63,
            48, 49, 50, 51, 52, 53, 54, 55,
            40, 41, 42, 43, 44, 45, 46, 47,
            32, 33, 34, 35, 36, 37, 38, 39,
            24, 25, 26, 27, 28, 29, 30, 31,
            16, 17, 18, 19, 20, 21, 22, 23,
            8, 9, 10, 11, 12, 13, 14, 15,
            0, 1, 2, 3, 4, 5, 6, 7
        ]

        Model {
            scale: Qt.vector3d(1, 1, 0.05)
            position: Qt.vector3d(x, y, -(scale.z * squareSize))
            source: "#Cube"
            pickable: true

            property string boardIndex: modelData

            property real x: (index % rowCount) * squareSize
            property real y: -squareSize * Math.floor(index / rowCount)

            materials: PrincipledMaterial {
                baseColor: dark ? "#000000" : "#FFFFFF"

                property bool evenRowIndex: index % 2
                property bool evenColumnIndex: (y / squareSize) % 2

                property bool dark: evenColumnIndex ? !evenRowIndex : evenRowIndex
            }
        }
    }
}
