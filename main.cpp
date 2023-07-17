#include <iostream>
#include <pybind11/embed.h>

#include <QApplication>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVersionNumber>

namespace py = pybind11;

py::object WrapQtObject(void *instance, const char *qobject_name,
                        bool is_borrow = true)
{
    PyObject *module = PyImport_ImportModule("shiboken6");
    PyObject *dict = PyModule_GetDict(module);
    PyObject *func = PyMapping_GetItemString(dict, "wrapInstance");
    PyObject *args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, PyLong_FromVoidPtr(instance));
    module = PyImport_ImportModule("PySide6.QtWidgets");
    dict = PyModule_GetDict(module);
    PyTuple_SetItem(args, 1, PyMapping_GetItemString(dict, qobject_name));
    PyObject *obj = PyObject_CallObject(func, args);
    py::handle h(obj);
    return is_borrow ? py::reinterpret_borrow<py::object>(h)
                     : py::reinterpret_steal<py::object>(h);
}

class MainWindow : public QMainWindow
{
    static MainWindow *sm_win;

public:
    static MainWindow *GetInstance() { return sm_win; }

    MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = {0})
        : QMainWindow(parent, flags)
    {
        if (!sm_win)
        {
            sm_win = this;
        }
        else
        {
            std::cout << "main window already exits." << std::endl;
            return;
        }

        setWindowTitle("FiberArt");
        auto cw = new QWidget;
        auto vb = new QVBoxLayout(cw);
        m_execute_btn = new QPushButton("execute");
        m_script_path =
            new QLineEdit("D:\\AppSource\\CppPySide\\MyScript.py");
        m_select_script = new QPushButton("select script");
        vb->addWidget(m_execute_btn);
        auto hb = new QHBoxLayout;
        hb->addWidget(m_script_path);
        hb->addWidget(m_select_script);
        vb->addLayout(hb);
        setCentralWidget(cw);

        connect(m_execute_btn, &QPushButton::clicked, this,
                &MainWindow::ExecuteScript);
        connect(m_select_script, &QPushButton::clicked, this,
                &MainWindow::SelectScript);
    }

    ~MainWindow() {}

    void SelectScript()
    {
        auto fname = QFileDialog::getOpenFileName(this, "Select file", ".",
                                                  "python(*.py)");
        if (!fname.isEmpty())
        {
            m_script_path->setText(fname);
        }
    }

    void ExecuteScript()
    {
        auto fname = m_script_path->text();
        try
        {
            py::eval_file(fname.toStdString());
        }
        catch (const py::error_already_set &e)
        {
            std::cerr << "Python error: " << e.what() << std::endl;
        }
        catch (...)
        {
            // Handle other exceptions here
            std::cerr << "Unknown error occurred" << std::endl;
        }
    }

private:
    QPushButton *m_execute_btn;
    QLineEdit *m_script_path;
    QPushButton *m_select_script;
};

MainWindow *MainWindow::sm_win = nullptr;

PYBIND11_EMBEDDED_MODULE(FiberArt, m)
{
    m.def("GetMainWindow", []()
          { return WrapQtObject(MainWindow::GetInstance(), "QMainWindow", true); });
}

int main(int argc, char **argv)
{
    py::initialize_interpreter();
    // auto m_globals = py::globals();
    // auto m_locals = py::dict();
    // py::exec("from PySide6 import QtWidgets", m_globals, m_locals);
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    app.exec();
    py::finalize_interpreter();
    return 0;
}
