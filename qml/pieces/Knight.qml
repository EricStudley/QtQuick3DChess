import QtQuick
import QtQuick3D

Model {
    objectName: "Knight"
    scale: Qt.vector3d(squareSize, squareSize, squareSize)
    eulerRotation: dark ? Qt.vector3d(0, 0, 90) : Qt.vector3d(0, 0, -90)
    source: "qrc:/res/meshes/knight.mesh"
    pickable: true

    property bool dark: false
    property bool highlighted: false

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
