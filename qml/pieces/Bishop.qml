import QtQuick
import QtQuick3D

Model {
    objectName: "Bishop"
    scale: Qt.vector3d(squareSize, squareSize, squareSize)
    eulerRotation: dark ? Qt.vector3d(0, 0, -90) : Qt.vector3d(0, 0, 90)
    source: "qrc:/res/meshes/bishop.mesh"
    pickable: true

    Behavior on x { SmoothedAnimation { } }
    Behavior on y { SmoothedAnimation { } }

    property bool dark: false
    property bool highlighted: false

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
