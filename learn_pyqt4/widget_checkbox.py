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
        cbx = QtGui.QCheckBox("Show title", self)
        cbx.move(20, 20)
        cbx.toggle()
        cbx.stateChanged.connect(self.changeTitle)

        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle("Input Dialog")
        self.show()

    def changeTitle(self, state):
        if state == QtCore.Qt.Checked:
            self.setWindowTitle("QtGui.QCheckBox")
        else:
            self.setWindowTitle("")


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()