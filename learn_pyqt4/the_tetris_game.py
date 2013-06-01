#!usr/bin/python
#


import sys
import random
from PyQt4 import QtGui, QtCore


class Tetris(QtGui.QMainWindow):

    def __init__(self):
        QtGui.QMainWindow.__init__(self)

        self.setGeometry(300, 300, 180, 380)
        self.setWindowTitle("Tetris")
        self.tetrisboard = Board(self)

        self.setCentralWidget(self.tetrisboard)
        self.connect(self.tetrisboard, QtCore.SIGNAL(
            "messageToStatusbar(QString)"),
                self.statusbar, QtCore.SLOT("showMessage(QString)"))

        self.tetrisboard.start()
        self.center()

    def center(self):
        screen = QtGui.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width()) / 2,
            (screen.height() - size.height()) / 2)


class Board(QtGui.QFrame):

    BoardWidth = 10
    BoardHeight = 22
    Speed = 300

    def __init__(self, parent):
        QtGui.QFrame.__init__(self, parent)

        self.timer = QtCore.QBasicTimer()
        self.isWaitingAferLine = False
        self.curPiece = Shape()
        self.nextPiece = Shape()
        self.curX = 0
        self.curY = 0
        self.numLinesRemoved = 0
        self.board = []

        self.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.isStarted = False
        self.isPaused = False
        self.clearBoard()

        self.nextPiece.setRandomShape()

    def shapeAt(self, x, y):
        return self.board[y * Board.BoardWidth + x]

    def setShapeAt(self, x, y, shape):
        self.board[(y * Board.BoardWidth) + x] = shape

    def squareWidth(self):
        return self.contentsRect().width() / Board.BoardWidth

    def squareHeight(self):
        return self.contentsRect().height() / Board.BoardHeight

    def start(self):
        if self.isPaused:
            return

        self.isStarted = True
        self.isWaitingAferLine = False
        self.numLinesRemoved = 0
        self.clearBoard()

        self.emit(QtCore.SIGNAL("messageToStatusbar(QString)"),
            str(self.numLinesRemoved))

        self.timer.start(Board.Speed, self)

    def pause(self):
        if not self.isStarted:
            return

        self.isPaused = not self.isPaused

        if self.isPaused:
            self.timer.stop()
            self.emit(QtCore.SIGNAL("messageToStatusbar(QString)"), "paused")
        else:
            self.timer.start(Board.Speed, self)
            self.emit(QtCore.SIGNAL("messageToStatubar(QString)"),
                str(self.numLinesRemoved))

        self.update()

    def paintEvent(self, event):
        pass


class Tetrominoes(object):
    NoShape = 0
    ZShape = 1
    SShape = 2
    LineShape = 3
    TShape = 4
    SquareShape = 5
    LShape = 6
    MirroredShape = 7


class Shape(object):
    coordsTable = (
        ((0, 0), (0, 0), (0, 0), (0, 0)),
        ((0, -1), (0, 0), (-1, 0), (-1, 1)),
        ((0, -1), (0, 0), (1, 0), (1, 1)),
        ((0, -1), (0, 0), (0, 1), (0, 2)),
        ((-1, 0), (0, 0), (1, 0), (0, 1)),
        ((0, 0), (1, 0), (0, 1), (1, 1)),
        ((-1, -1), (0, -1), (0, 0), (0, 1)),
        ((1, -1), (0, -1), (0, 0), (0, 1))
    )

    def __init__(self):
        self.coords = [[0, 0] for i in range(4)]
        self.pieceShape = Tetrominoes.NoShape

        self.setShape(Tetrominoes.NoShape)

    def shape(self):
        return self.pieceShape

    def setShape(self, shape):
        table = Shape.coordsTable[shape]
        for i in range(4):
            for j in range(2):
                self.coords[i][j] = table[i][j]

        self.pieceShape = shape

    def setRandomShape(self):
        self.setShape(random.randint(1, 7))

    def x(self, index):
        return self.coords[index][0]

    def y(self, index):
        return self.coords[index][1]

    def setX(self, index, x):
        self.coords[index][0] = x

    def setY(self, index, y):
        self.coords[index][1] = y

    def minX(self):
        m = self.coords[0][0]
        for i in range(4):
            m = min(m, self.coords[i][0])
        return m

    def maxX(self):
        m = self.coords[0][0]
        for i in range(4):
            m = max(m, self.coords[i][0])
        return m

    def minY(self):
        m = self.coords[0][1]
        for i in range(4):
            m = min(m, self.coords[i][1])
        return m

    def maxY(self):
        m = self.coords[0][1]
        for i in range(4):
            m = max(m, self.coords[i][1])
        return m

    def rotatedLeft(self):
        if self.pieceShape == Tetrominoes.SquareShape:
            return self

        result = Shape()
        result.pieceShape = self.pieceShape
        for i in range(4):
            result.setX(i, self.y(i))
            result.setY(i, -self.x(i))

        return result

    def rotatedRight(self):
        if self.pieceShape == Tetrominoes.SquareShape:
            return self

        result = Shape()
        result.pieceShape = self.pieceShape
        for i in range(4):
            result.setX(i, -self.y(i))
            result.setY(i, self.x(i))
        return result


app = QtGui.QApplication(sys.argv)
tetris = Tetris()
tetris.show()
sys.exit(app.exec_())