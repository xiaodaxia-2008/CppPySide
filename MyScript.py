import sys
import pprint

print(sys.executable)
print(sys.version)
pprint.pprint(sys.path)

from PySide6 import QtWidgets
from PySide6 import QtCore

print("import FiberArt")
import FiberArt

print("FiberArt.GetMainWindow()")
win: QtWidgets.QMainWindow = FiberArt.GetMainWindow()
print("After FiberArt.GetMainWindow()")
print(win)
win.setWindowTitle("change from python")

dw = QtWidgets.QDockWidget()

QtWidgets.QApplication.instance()
btn = QtWidgets.QPushButton("push me", parent=win)
btn.clicked.connect(lambda: print("button is clicked, call python slot!"))

dw.setWidget(btn)
win.addDockWidget(QtCore.Qt.DockWidgetArea.LeftDockWidgetArea, dw)

# app = QtWidgets.QApplication()
# win = QtWidgets.QMainWindow()
# win.show()
# app.exec()
