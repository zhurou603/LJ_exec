import numpy as np

def	zeros(row,column):
	return [[0 for i in range(column)] for j in range(row)]

def dot(x,y):
	x = np.array(x)
	y = np.array(y)
	if(x.ndim == 1):
		x = x.reshape(1,x.shape[0])
	x_row = len(x)
	x_column = len(x[0])
	y_row = len(y)
	y_column = len(y[0])
	if(x_column != y_row):
		print("size doesn't match")
		return None
	result = zeros(x_row,y_column)
	for i in range(x_row):
		for j in range(y_column):
			for k in range(y_row):
				result[i][j] += x[i][k] * y[k][j]
	if(x_row == 1):
		return np.array(result).reshape((y_column,))
	return np.array(result)