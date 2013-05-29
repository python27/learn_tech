#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import random
from PyQt4 import QtGui, QtCore


class Example(QtGui.QWidget):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):

        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle("Draw Points")
        self.show()

    def paintEvent(self, event):

        qp = QtGui.QPainter()
        qp.begin(self)

        qp.setPen(QtCore.Qt.red)
        size = self.size()

        for i in range(1000):
            x = random.randint(1, size.width() - 1)
            y = random.randint(1, size.height() - 1)
            qp.drawPoint(x, y)
        qp.end()


def main():

    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()