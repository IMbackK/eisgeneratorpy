# eisgeneratorpy

Python3 bindings for [eisgenerator](https://git-ce.rwth-aachen.de/carl_philipp.klemm/eisgenerator)

## Requirements

* git
* c++11  capable compiler (GCC, CLANG)
* cmake 3.20 or higher
* libeisgenerator from [eisgenerator](https://git-ce.rwth-aachen.de/carl_philipp.klemm/eisgenerator)
* [pybind11](https://github.com/pybind/pybind11)
* pip

## Compile/Install Procedure

* `git clone https://git-ce.rwth-aachen.de/carl_philipp.klemm/eisgeneraorpy.git`
* `cd eisgeneraorpy`
* `pip install .`

## Usage

These bindings provide only a subset of the functionality provided by eisgenerator.

The main suported classes are

* `eisgenerator.Model`
	* corrisponds too [eis::Model](https://uvos.xyz/kiss/eisgeneratordoc/classeis_1_1Model.html)
	* only a subset of members are suported includeing the execute* family and the code generation members
* `eisgenerator.DataPoint`
	* corrisponds too [eis::DataPoint](https://uvos.xyz/kiss/eisgeneratordoc/classeis_1_1DataPoint.html)
* `eisgenerator.Range`
	* corrisponds too [eis::Range](https://uvos.xyz/kiss/eisgeneratordoc/classeis_1_1Range.html)
* `eisgenerator.EisSpectra`
	* corrisponds too [eis::EisSpectra](https://uvos.xyz/kiss/eisgeneratordoc/classeis_1_1EisSpectra.html)
* `eisgenerator.Log`
	* corrisponds too [eis::Log](https://uvos.xyz/kiss/eisgeneratordoc/classeis_1_1Log.html)

TorchScript exectution is performed differently than on the C++ and two extra functions are provided for this:

* `eisgenerator.compileModel`
	* compiles the model to a torch object and caches it internally, returns True if this was sucessfull
* `eisgenerator.getModelFunction`
	* returns the a fuction object to use the model, or None on failure
	* the returned function takes two torch.Tensor parameters
		1. a 1d, (n) sized tensor containing the model parameters
		2. a 1d, (n) sized tensor with omega values to calculate the impance at
	* a 1d complex tensor is returned with the impedance values
