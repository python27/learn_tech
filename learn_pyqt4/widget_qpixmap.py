#!/usr/bin/python
#-*- coding:utf-8 -*-

import sys
from PyQt4 import QtGui
from PyQt4 import QtCore


class Example(QtGui.QWidget):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):

        pixmap = QtGui.QPixmap("redrock.png")

        lbl = QtGui.QLabel(self)
        lbl.setPixmap(pixmap)

        hbox = QtGui.QHBoxLayout(self)
        hbox.addWidget(lbl)

        self.setLayout(hbox)
        self.setWindowTitle("Red Rock")
        self.move(300, 200)
        self.show()


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()