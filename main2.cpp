#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char **argv)
{
    py::initialize_interpreter();
    std::string fname = "D:\\AppSource\\CppPySide\\MyScript2.py";
    try {
        py::eval_file(fname);
    }
    catch (const py::error_already_set &e) {
        std::cerr << "Python error: " << e.what() << std::endl;
    }
    catch (...) {
        // Handle other exceptions here
        std::cerr << "Unknown error occurred" << std::endl;
    }
    py::finalize_interpreter();
    return 0;
}
