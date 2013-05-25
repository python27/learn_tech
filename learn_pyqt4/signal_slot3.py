#!/usr/bin/python
#-*- coding:utf-8 -*-

import sys
from PyQt4 import QtGui
from PyQt4 import QtCore


class Example(QtGui.QMainWindow):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):

        button1 = QtGui.QPushButton("Button1", self)
        button1.move(30, 50)
        button2 = QtGui.QPushButton("Button2", self)
        button2.move(150,50)

        button1.clicked.connect(self.buttonClicked)
        button2.clicked.connect(self.buttonClicked)

        self.statusBar()

        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle("Event Handler")
        self.show()

    def buttonClicked(self):

        sender = self.sender()
        self.statusBar().showMessage(sender.text() + "was pressed")


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

