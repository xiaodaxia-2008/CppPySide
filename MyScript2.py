import sys
import pprint

print(sys.executable)
print(sys.version)
pprint.pprint(sys.path)

from PySide6 import QtWidgets
from PySide6 import QtCore

app = QtWidgets.QApplication()
win = QtWidgets.QMainWindow()
win.show()
app.exec()
