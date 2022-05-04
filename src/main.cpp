#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/iostream.h>

#include <eisgenerator/model.h>
#include <eisgenerator/eistype.h>
#include <eisgenerator/log.h>
#include <vector>

namespace py = pybind11;

using namespace eis;

PYBIND11_MODULE(_core, m)
{
	py::class_<Model>(m, "Model")
		.def(py::init<const std::string&>())
		.def("execute", &Model::execute)
		.def("executeSweep", &Model::executeSweep)
		.def("executeParamByIndex", &Model::executeParamByIndex)
		.def_static("getRequiredStepsForSweeps", &Model::getRequiredStepsForSweeps)
		.def("getFlatParametersCount", &Model::getFlatParametersCount);
	py::class_<DataPoint>(m, "DataPoint")
		.def_readwrite("omega", &DataPoint::omega)
		.def_readwrite("im", &DataPoint::im);
	py::class_<Range>(m, "Range")
		.def(py::init<fvalue, fvalue, size_t, bool>(),
			py::arg("startI"),
			py::arg("endI"),
			py::arg("countI"),
			py::arg("logI") = false)
		.def_readwrite("start", &Range::start)
		.def_readwrite("end", &Range::end)
		.def_readwrite("count", &Range::count)
		.def_readwrite("log", &Range::log);
	py::class_<Log>(m, "Log")
		.def_readwrite_static("level", &Log::level);
	py::enum_<Log::Level>(m, "Level")
		.value("DEBUG", Log::DEBUG)
		.value("INFO", Log::INFO)
		.value("WARN", Log::WARN)
		.value("ERROR", Log::ERROR);
	py::add_ostream_redirect(m, "ostream_redirect");
	m.attr("__version__") = "1.0";
}
