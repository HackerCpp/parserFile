from LogData.QtGui import *
from LogData.QtCore import *

class Settings(QWidget):
	def __init__(self, parent=None):
		QWidget.__init__(self, parent)
		self.m_mainVLayout = QVBoxLayout()
		self.setLayout(self.m_mainVLayout)
		self.settings = QSettings("settings.ini",QSettings.IniFormat)
		self.settings.beginGroup("drawSettings");
		self.pixelPerMm = self.settings.value("scalePixelPerMm")
		self.pictureHeight = self.settings.value("pictureHeight")
		self.scaleForDepth = self.settings.value("scaleForDepth")
		self.scaleForTime = self.settings.value("scaleForTime")
		self.formatImg = self.settings.value("formatImg")
		self.isDrawTime = self.settings.value("isDrawTime")
		self.settings.endGroup();
		self.m_labelscalePixelPerMm = QLabel("Pixel Per Mm : " + self.pixelPerMm);
		
		self.m_mainVLayout.addWidget(self.m_labelscalePixelPerMm)

ettings = Settings()
ettings.show()

