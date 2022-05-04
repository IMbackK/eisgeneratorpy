#!/bin/python

import eisgeneratorpy as eis

def printData(data):
	print('Omega, Re, Im')
	for i in data:
		print(f'{i.omega},{i.im.real},{i.im.imag}')

model = eis.Model("C{1e-6}R{1e3}")

eis.Log.level = eis.Log.level.DEBUG
print(f'set log level: {eis.Log.level}')

with eis.ostream_redirect(stdout=True, stderr=True):
	data = model.execute(1e6)
print(data.im)

ranges = list([])
neededParameters = model.getFlatParametersCount()
for i in range(neededParameters):
	ranges.append(eis.Range(1, 1000, 1000, True))

omegaRange = eis.Range(1, 1000, 25, True)

print('Ranges:')
for eisRange in ranges:
	print(f'{eisRange.start} {eisRange.end} {eisRange.count}')

neededIterations = model.getRequiredStepsForSweeps(list(ranges))
print(f'will need {neededIterations} iterations')
for i in range(neededIterations):
	#print(f'Spectra {i}:')
	sweep = model.executeParamByIndex(ranges, omegaRange, i)
	#printData(sweep)
