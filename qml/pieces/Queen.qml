import QtQuick
import QtQuick3D

Model {
    objectName: "Queen"
    scale: Qt.vector3d(100, 100, 100)
    eulerRotation: dark ? Qt.vector3d(0, 0, 90) : Qt.vector3d(0, 0, 0)
    source: "qrc:/res/meshes/queen.mesh"
    pickable: true

    property bool dark: false
    property bool highlighted: false

    materials: [
        DefaultMaterial {
            diffuseColor: highlighted ? "#FF5CB3FF"
                                      : dark ? "#FF2C2C35"
                                             : "#FFFFDB9F"
        },
        DefaultMaterial {
            diffuseColor: "#FFCCCCCC"
        }
    ]
}
