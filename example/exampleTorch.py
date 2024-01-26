#!/bin/python

import eisgenerator as eis
import torch

eis.Log.level = eis.Log.level.ERROR
print(f'set log level: {eis.Log.level}')

model = eis.Model("cr")
print(f"model: {model}")

script = model.getTorchScript()
print(f'TorchScript:\n{script}')

eis.compileModel(model)

modelFn = eis.getModelFunction(model)

parameters = torch.empty((2))
parameters[0] = 1e-6
parameters[1] = 100
omegas = torch.logspace(0, 5, 10)

print(modelFn(parameters, omegas))
