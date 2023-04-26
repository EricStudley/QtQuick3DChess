import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

import "pieces"

Node {

    Rook {
    }

    Knight {
        x: 100
    }

    Bishop {
        x: 200
    }

    Queen {
        x: 300
    }

    King {
        x: 400
    }

    Bishop {
        x: 500
    }

    Knight {
        x: 600
    }

    Rook {
        x: 700
    }

    Repeater3D {
        model: 8

        Pawn {
            x: index * squareSize
            y: 100
        }
    }

    Repeater3D {
        model: 8

        Pawn {
            x: index * squareSize
            y: 600
            dark: true
        }
    }

    Rook {
        y: 700
        dark: true
    }

    Knight {
        y: 700
        x: 100
        dark: true
    }

    Bishop {
        y: 700
        x: 200
        dark: true
    }

    Queen {
        y: 700
        x: 300
        dark: true
    }

    King {
        y: 700
        x: 400
        dark: true
    }

    Bishop {
        y: 700
        x: 500
        dark: true
    }

    Knight {
        y: 700
        x: 600
        dark: true
    }

    Rook {
        y: 700
        x: 700
        dark: true
    }
}
