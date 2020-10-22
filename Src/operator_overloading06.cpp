#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

class Vector2 
{
public: 
	Vector2(float x, float y): x(x), y(y){}
	Vector2 operator+(const Vector2 &vec) const {return Vector2(x+vec.x, y+vec.y);}
	Vector2 operator*(float value) const {return Vector2(x*value, y*value);}
	Vector2 operator-() const {return Vector2(-x,-y);} 
	Vector2& operator+=(const Vector2 &vec) {x +=vec.x; y+=vec.y; return *this;}
	Vector2& operator*=(float value) { x*= value; y *= value; return *this; }

	friend Vector2 operator*(float value, const Vector2 &vec)
	{
		return Vector2(value * vec.x, value * vec.y);
	}

	std::string toString() const
	{
		return "Vector2[" +std::to_string(x)+", "+std::to_string(y)+"]";
	}
private: 
	float x, y;
};

PYBIND11_MODULE(operator_overloading, m)
{
	m.doc() = "Operator Overloading using Pybind11";
	py::class_<Vector2>(m, "Vector2")
		.def(py::init<float, float>())
		.def(py::self+py::self)
		.def(py::self+=py::self)
		.def(py::self*=float())
		.def(float()*py::self)
		.def(py::self*float())
		.def(-py::self)
		.def("__repr__", &Vector2::toString); 
}