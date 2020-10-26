// #include <exception>
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>

namespace py = pybind11;

class CustomException: public std::exception
{
public:
	explicit CustomException(const char* m): message(m){}
	const char* what() const noexcept override {return message.c_str();}
private:
	std::string message;
};

class X
{
public:
	X(int value): data(value){}
	operator int() const {return data;}
	int get() const {return data;}
private:
	int data;
};

void printer(const X& x)
{
	py::print(x.get());
}

PYBIND11_MODULE(exception_handle, m)
{
	m.doc() = "Handle Exception throw from Python side and C++ side";
	// py::register_exception<CustomException>(m, "CustomException", PyExc_ValueError); // Quick register exception
	static py::exception<CustomException> ex(m, "CustomException");
	py::register_exception_translator([](std::exception_ptr p) {
		try
		{
			if (p) std::rethrow_exception(p);
		}catch (const CustomException &e)
		{
			// exc(e.what()); // throw CustomException
			PyErr_SetString(PyExc_ValueError, e.what()); // Translated to python RuntimeError
		};
	});


	m.def("throwException",[](){throw CustomException("This is a custom exception");}); 


	// Handling Exception from Python in C++
	m.def("throwExceptionfromPy",[](){
		try
		{
			py::eval("raise ValueError('Invalid Error!!')");
		}
		catch(py::value_error &e)
		{
			py::print("This will never be printed");
		}
		catch(py::error_already_set &e)
		{
			py::print("ValueError from Python is caught");
		}
	});

	m.def("printer", &printer);

	py::class_<X>(m, "X")
		.def(py::init<int>())
		.def("get", &X::get);
	py::implicitly_convertible<X, py::int_>();
}