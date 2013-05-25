#!/usr/bin/python
#-*- coding:utf-8 -*-

import sys
from PyQt4 import QtGui
from PyQt4 import QtCore


class communicate(QtCore.QObject):
    closeApp = QtCore.pyqtSignal()


class Example(QtGui.QMainWindow):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):
        self.c = communicate()
        self.c.closeApp.connect(self.close)

        self.setGeometry(300, 300, 200, 150)
        self.setWindowTitle("Emit Signal")
        self.show()

    def mousePressEvent(self, e):
        self.c.closeApp.emit()


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

