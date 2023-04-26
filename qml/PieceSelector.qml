import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

TapHandler {

    property var selectedPiece

    function moveSelectedPiece(x, y) {
        selectedPiece.x = x
        selectedPiece.y = y
        selectedPiece.highlighted = false
        selectedPiece = undefined
    }

    onTapped: (eventPoint) => {
                  var result = view3D.pick(eventPoint.position.x, eventPoint.position.y)

                  if (result.objectHit) {
                      var objectHit = result.objectHit

                      if (objectHit.objectName) {

                          if (objectHit !== selectedPiece) {
                              if (selectedPiece) {
                                  objectHit.visible = false
                                  moveSelectedPiece(objectHit.x, objectHit.y)
                              }
                              else {
                                  selectedPiece = objectHit
                                  selectedPiece.highlighted = true
                              }
                          }
                          else {
                              selectedPiece.highlighted = false
                              selectedPiece = undefined
                          }
                      }
                      else {
                          if (selectedPiece) {
                              moveSelectedPiece(objectHit.x, objectHit.y)
                          }
                      }
                  }
              }
}
