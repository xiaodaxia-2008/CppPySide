import FiberArt
import shiboken6
from PySide6 import QtCore, QtWidgets

print("FiberArt.GetMainWindow()")
win_ptr: QtWidgets.QMainWindow = FiberArt.GetMainWindow()
print(f"window pointer: {win_ptr}")
win = shiboken6.wrapInstance(win_ptr, QtWidgets.QMainWindow)
print("After FiberArt.GetMainWindow()")

win.setWindowTitle("change from python")

dw = QtWidgets.QDockWidget()

QtWidgets.QApplication.instance()
btn = QtWidgets.QPushButton("push me", parent=win)
btn.clicked.connect(lambda: print("button is clicked, call python slot!"))

dw.setWidget(btn)
win.addDockWidget(QtCore.Qt.DockWidgetArea.LeftDockWidgetArea, dw)
