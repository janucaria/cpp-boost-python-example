#include <iostream>
#include <string>

#include <boost/python.hpp>

struct hello_world
{
    void say_hello() { std::cout << "Hello world!" << std::endl; }
};

using namespace boost::python;

BOOST_PYTHON_MODULE(janucaria)
{
	class_< hello_world >("HelloWorld")
	  .def("say_hello", &hello_world::say_hello);
}
