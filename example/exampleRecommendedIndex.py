#!/bin/python

import eisgenerator as eis

model = eis.Model("c{1e-6}r{1e3}")
print(f"model: {model}")

eis.Log.level = eis.Log.level.WARN
print(f'set log level: {eis.Log.level}')

with eis.ostream_redirect(stdout=True, stderr=True):
	data = model.execute(1e6)
print(f"data for omega={data.omega}: {data}")

model = eis.Model("c{1e-6~1e-5}r{1e3~1e4}")

omegaRange = eis.Range(1, 1000, 25, True)

indecies = model.getRecommendedParamIndices(omegaRange, 0.01, True)

print(f"found {len(indecies)} interesting indecies")

sweep = model.executeSweep(omegaRange.getRangeVector(), indecies[0])

spectra = eis.EisSpectra()
spectra.data = sweep
spectra.model = model.getModelStrWithParam(200)

print(spectra)
