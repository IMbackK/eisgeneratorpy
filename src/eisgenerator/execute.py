from ._core import Model, Log

models = dict()

def compileModel(model: Model) -> bool:
	try:
		import torch
	except  ModuleNotFoundError:
		Log.print("Could not import torch, torch must be availble to compile a torch model.", Log.level.ERROR)
		return False

	script = model.getTorchScript()
	if len(script) == 0:
		Log.print("eisgenerator reports that this model can not be executed as a torch script.", Log.level.ERROR)
		return False

	try:
		exec(script)
		fn_name = model.getCompiledFunctionName()
		models[fn_name] = locals()[fn_name]
	except SyntaxError as err:
		Log.print(f'could not compile model: {err}', Log.level.ERROR)
		return False

	return True


def getModelFunction(model: Model):
	fn_name = model.getCompiledFunctionName()

	if fn_name not in models:
		Log.print("You must first compile a model before getting its function", Log.level.ERROR)
		return None

	return models[fn_name]


