import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

TapHandler {

    signal pieceMoved(var from, var to)

    property var selectedPiece

    function moveSelectedPiece(boardIndex) {
        selectedPiece.highlighted = false
        var fromRankAndFile = chessModel.rankAndFile(selectedPiece.boardIndex)
        var toRankAndFile = chessModel.rankAndFile(boardIndex)
        pieceMoved(fromRankAndFile, toRankAndFile)
        selectedPiece = undefined
    }

    onTapped: (eventPoint) => {
                  var result = view3D.pick(eventPoint.position.x, eventPoint.position.y)

                  if (result.objectHit) {
                      var objectHit = result.objectHit

                      if (objectHit.objectName) {

                          if (objectHit !== selectedPiece) {

                              if (selectedPiece) {
                                  moveSelectedPiece(objectHit.boardIndex)
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
                              moveSelectedPiece(objectHit.boardIndex)
                          }
                      }
                  }
              }
}
