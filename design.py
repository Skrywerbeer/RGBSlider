# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.7
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(466, 352)
        MainWindow.setStyleSheet("background-color: rgb(85, 87, 83);")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.redLabel = QtWidgets.QLabel(self.centralwidget)
        self.redLabel.setObjectName("redLabel")
        self.verticalLayout_3.addWidget(self.redLabel)
        self.redLCD = QtWidgets.QLCDNumber(self.centralwidget)
        self.redLCD.setDigitCount(3)
        self.redLCD.setObjectName("redLCD")
        self.verticalLayout_3.addWidget(self.redLCD)
        self.redSlider = QtWidgets.QSlider(self.centralwidget)
        self.redSlider.setMaximum(255)
        self.redSlider.setOrientation(QtCore.Qt.Vertical)
        self.redSlider.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.redSlider.setObjectName("redSlider")
        self.verticalLayout_3.addWidget(self.redSlider, 0, QtCore.Qt.AlignHCenter)
        self.gridLayout.addLayout(self.verticalLayout_3, 0, 0, 1, 1)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.greenLabel = QtWidgets.QLabel(self.centralwidget)
        self.greenLabel.setObjectName("greenLabel")
        self.verticalLayout_2.addWidget(self.greenLabel)
        self.greenLCD = QtWidgets.QLCDNumber(self.centralwidget)
        self.greenLCD.setDigitCount(3)
        self.greenLCD.setObjectName("greenLCD")
        self.verticalLayout_2.addWidget(self.greenLCD)
        self.greenSlider = QtWidgets.QSlider(self.centralwidget)
        self.greenSlider.setMaximum(255)
        self.greenSlider.setOrientation(QtCore.Qt.Vertical)
        self.greenSlider.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.greenSlider.setObjectName("greenSlider")
        self.verticalLayout_2.addWidget(self.greenSlider, 0, QtCore.Qt.AlignHCenter)
        self.gridLayout.addLayout(self.verticalLayout_2, 0, 1, 1, 1)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.blueLabel = QtWidgets.QLabel(self.centralwidget)
        self.blueLabel.setObjectName("blueLabel")
        self.verticalLayout.addWidget(self.blueLabel)
        self.blueLCD = QtWidgets.QLCDNumber(self.centralwidget)
        self.blueLCD.setFrameShape(QtWidgets.QFrame.Box)
        self.blueLCD.setFrameShadow(QtWidgets.QFrame.Raised)
        self.blueLCD.setDigitCount(3)
        self.blueLCD.setSegmentStyle(QtWidgets.QLCDNumber.Filled)
        self.blueLCD.setObjectName("blueLCD")
        self.verticalLayout.addWidget(self.blueLCD)
        self.blueSlider = QtWidgets.QSlider(self.centralwidget)
        self.blueSlider.setMaximum(255)
        self.blueSlider.setOrientation(QtCore.Qt.Vertical)
        self.blueSlider.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.blueSlider.setObjectName("blueSlider")
        self.verticalLayout.addWidget(self.blueSlider, 0, QtCore.Qt.AlignHCenter)
        self.gridLayout.addLayout(self.verticalLayout, 0, 2, 1, 1)
        self.updateBtn = QtWidgets.QPushButton(self.centralwidget)
        self.updateBtn.setObjectName("updateBtn")
        self.gridLayout.addWidget(self.updateBtn, 1, 1, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        self.blueSlider.valueChanged['int'].connect(self.blueLCD.display)
        self.greenSlider.valueChanged['int'].connect(self.greenLCD.display)
        self.redSlider.valueChanged['int'].connect(self.redLCD.display)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "RGBSlider"))
        self.redLabel.setText(_translate("MainWindow", "Red"))
        self.greenLabel.setText(_translate("MainWindow", "Green"))
        self.blueLabel.setText(_translate("MainWindow", "Blue"))
        self.updateBtn.setText(_translate("MainWindow", "Update color"))

