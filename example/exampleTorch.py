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

parameters = eis.getModelParameters(model, 0)
omegas = torch.logspace(0, 5, 10)
print(f'Parameters:\n{parameters}\nOmegas:\n{omegas}\n')

print(modelFn(parameters, omegas))
