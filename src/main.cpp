#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/iostream.h>

#include <eisgenerator/model.h>
#include <eisgenerator/eistype.h>
#include <eisgenerator/log.h>
#include <vector>
#include <sstream>

namespace py = pybind11;

using namespace eis;

std::string reprEisSpectra(const EisSpectra& spectra)
{
	std::stringstream ss;
	spectra.saveToStream(ss);
	return ss.str();
}

std::string reprDataPoint(const DataPoint& dp)
{
	std::stringstream ss;
	ss<<std::scientific;
	ss<<'('<<dp.im.real()<<'+'<<dp.im.imag()<<"j)";
	return ss.str();
}

PYBIND11_MODULE(_core, m)
{
	py::class_<Model>(m, "Model")
		.def(py::init<const std::string&, size_t, bool>(),
			 py::arg("str"), py::arg("paramSweepCount") = 100, py::arg("defaultToRange") = false)
		.def("execute", &Model::execute, py::arg("omaga"), py::arg("omaga") = 0)
		.def("executeSweep", static_cast<std::vector<DataPoint> (Model::*)(const std::vector<fvalue>&, size_t)>(&Model::executeSweep),
			 py::arg("omega"), py::arg("index") = 0)
		.def("executeAllSweeps", &Model::executeAllSweeps)
		.def("getModelStr", &Model::getModelStr)
		.def("getModelStrWithParam", static_cast<std::string (Model::*)(size_t)>(&Model::getModelStrWithParam),
			 py::arg("index") = 0)
		.def("getUuid", &Model::getUuid)
		.def("compile", &Model::compile)
		.def("isReady", &Model::isReady)
		.def("resolveSteps", &Model::resolveSteps)
		.def("getRequiredStepsForSweeps", &Model::getRequiredStepsForSweeps)
		.def("getCppCode", &Model::getCode)
		.def("getTorchScript", &Model::getTorchScript)
		.def("getCompiledFunctionName", &Model::getCompiledFunctionName)
		.def("__repr__", &Model::getModelStr);
	py::class_<DataPoint>(m, "DataPoint")
		.def(py::init<std::complex<fvalue>, fvalue>(), py::arg("im") = std::complex<fvalue>(0, 0), py::arg("omega") = 100)
		.def_readwrite("omega", &DataPoint::omega)
		.def_readwrite("im", &DataPoint::im)
		.def("__gt__", &DataPoint::operator>)
		.def("__lt__", &DataPoint::operator<)
		.def("__eq__", &DataPoint::operator==)
		.def("__add__", &DataPoint::operator+)
		.def("complexVectorLength", &DataPoint::complexVectorLength)
		.def("__repr__", &reprDataPoint);
	py::class_<Range>(m, "Range")
		.def(py::init<fvalue, fvalue, size_t, bool>(),
			py::arg("startI"),
			py::arg("endI"),
			py::arg("countI"),
			py::arg("logI") = false)
		.def_readwrite("start", &Range::start)
		.def_readwrite("end", &Range::end)
		.def_readwrite("count", &Range::count)
		.def_readwrite("log", &Range::log)
		.def("stepSize", &Range::stepSize)
		.def("stepValue", &Range::stepValue)
		.def("center", &Range::center)
		.def("at", &Range::at)
		.def("__getitem__", &Range::at)
		.def("getString", &Range::getString)
		.def("getRangeVector", &Range::getRangeVector)
		.def("fromString", &Range::fromString)
		.def_static("rangesFromParamString", &Range::rangesFromParamString);
	py::class_<EisSpectra>(m, "EisSpectra")
		.def(py::init<>())
		.def_readwrite("data", &EisSpectra::data)
		.def_readwrite("model", &EisSpectra::model)
		.def_readwrite("header", &EisSpectra::header)
		.def_readwrite("labels", &EisSpectra::labels)
		.def_readwrite("labelNames", &EisSpectra::labelNames)
		.def_static("loadFromDisk", &EisSpectra::loadFromDisk)
		.def("setLabel", &EisSpectra::setLabel)
		.def("setSzLabels", &EisSpectra::setSzLabels)
		.def("setLabels", static_cast<void (EisSpectra::*)(const std::vector<double>&)>(&EisSpectra::setLabels))
		.def("getSzLabels", &EisSpectra::getSzLabels)
		.def("getFvalueLabels", &EisSpectra::getFvalueLabels)
		.def("saveToDisk", &EisSpectra::saveToDisk)
		.def("__repr__", &reprEisSpectra);
	py::class_<Log>(m, "Log")
		.def_readwrite_static("level", &Log::level);
	py::enum_<Log::Level>(m, "Level")
		.value("DEBUG", Log::DEBUG)
		.value("INFO", Log::INFO)
		.value("WARN", Log::WARN)
		.value("ERROR", Log::ERROR);
	py::register_exception<parse_errror>(m, "ParseError");
	py::register_exception<file_error>(m, "FileError");
	py::add_ostream_redirect(m, "ostream_redirect");
	m.def("eisDistance", &eisDistance);
	m.def("eisNyquistDistance", &eisNyquistDistance);
	m.attr("__version__") = "1.0";
}
