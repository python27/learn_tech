#!/usr/bin/python
#-*- coding:utf-8 -*-

import sys
from PyQt4 import QtGui


class Example(QtGui.QWidget):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):

        ###############################
        #okButton = QtGui.QPushButton("Ok")
        #cancelButton = QtGui.QPushButton("Cancel")

        #hbox = QtGui.QHBoxLayout()
        #hbox.addStretch(1)
        #hbox.addWidget(okButton)
        #hbox.addWidget(cancelButton)

        #vbox = QtGui.QVBoxLayout()
        #vbox.addStretch(1)
        #vbox.addLayout(hbox)

        #self.setLayout(vbox)
        ##############################

        title = QtGui.QLabel("Title")
        author = QtGui.QLabel("Author")
        review = QtGui.QLabel("Review")

        titleEdit = QtGui.QLineEdit()
        authorEdit = QtGui.QLineEdit()
        reviewEdit = QtGui.QTextEdit()

        grid = QtGui.QGridLayout()
        grid.setSpacing(10)

        grid.addWidget(title, 0, 0)
        grid.addWidget(titleEdit, 0, 1)

        grid.addWidget(author, 2, 0)
        grid.addWidget(authorEdit, 2, 1)

        grid.addWidget(review, 3, 0)
        grid.addWidget(reviewEdit, 3, 1, 5, 1)

        self.setLayout(grid)

        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle("Layout")
        self.show()


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

