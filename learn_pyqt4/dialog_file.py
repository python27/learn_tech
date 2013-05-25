#!/usr/bin/python
#-*- coding:utf-8 -*-

import sys
from PyQt4 import QtGui


class Example(QtGui.QMainWindow):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):
        self.textEdit = QtGui.QTextEdit()
        self.setCentralWidget(self.textEdit)
        self.statusBar()

        openFile = QtGui.QAction(QtGui.QIcon("web.png"), "open", self)
        openFile.setShortcut("Ctrl+O")
        openFile.setStatusTip("Open new File")
        openFile.triggered.connect(self.showDialog)

        menubar = self.menuBar()
        filemenu = menubar.addMenu("&File")
        filemenu.addAction(openFile)

        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle("Input Dialog")
        self.show()

    def showDialog(self):
        fname = QtGui.QFileDialog.getOpenFileName(self, "Open File",
        "/home/python27")

        f = open(fname, "r")

        with f:
            data = f.read()
            self.textEdit.setText(data)


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()