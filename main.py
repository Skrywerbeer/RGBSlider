#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 23 00:42:53 2017

@author: liquidsquid
"""

from PyQt5.QtWidgets import QApplication, QMainWindow
import serial
from serial.tools import list_ports

import design

class RGBSliderApp(QMainWindow, design.Ui_MainWindow):
	
	def __init__(self):
		super().__init__()
		self.setupUi(self)
		
		self.updateBtn.clicked.connect(self.updateColors)
		
		self.connection = serial.Serial(list_ports.comports()[0].device, 38400)
		
	def updateColors(self):
		red = self.redLCD.intValue()
		green = self.greenLCD.intValue()
		blue = self.blueLCD.intValue()
		
		self.connection.write(bytes([0]))
		while (int.from_bytes(self.connection.read(1), byteorder='big')) != 0:
			pass
		self.connection.write(bytes([red, green, blue]))
		
	

def main():
	app = QApplication([])
	window = RGBSliderApp()
	window.show()
	app.exec_()
	
if __name__ == '__main__':
	main()