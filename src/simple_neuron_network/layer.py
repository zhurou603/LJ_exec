# -*- coding:utf-8 -*-
import numpy as np

class InputLayer(object):
	def __init__(self,shape):
		self.shape = shape
		self.data = None

#全连接层
class FullConnected(object):
	def __init__(self,pre_size,output_size):
		self.pre_size = pre_size
		self.output_size = output_size
		self.w = np.random.randn(pre_size,output_size)
		self.b = np.random.randn(output_size)
		self.x = None
		self.dw = None
		self.db = None
		self.dx = None

	def feedforward(self,x):
		self.x = x
		return np.dot(x,self.w) + self.b

	#y为某一上游传来的偏导数
	def backward(self,y):
		trans = self.x.reshape(self.x.shape[0],1)
		self.dw = np.dot(trans,y.reshape(1,y.shape[0]))
		self.db = y
		self.dx = np.dot(y,self.w.transpose())
		return self.dx

class Sigmoid(object):
	def __init__(self,input_size):
		self.input_size = input_size
		self.x = None
		self.y = None
		self.dx = None

	def feedforward(self,x):
		self.x = x
		self.y = self.sigmoid(x)
		return self.y

	def backward(self,value):
		self.dx = value * self.y * (1 - self.y)
		return self.dx

	def sigmoid(self,x):
		#return 1.0/(1.0 + np.exp(-x))
		return .5 * (1 + np.tanh(.5 * x))

class SoftmaxLoss(object):
	def __init__(self,input_size):
		self.input_size = input_size
		self.y = None
		self.t = None
		self.loss = None
		self.x = None
		self.dx = None
	
	def feedforward(self,x,t):
		self.x = x
		y = self.softmax(x)
		self.y = y
		self.t = t
		self.loss = self.crossentropy(y,t)
		return self.loss

	def backward(self):
		self.dx = self.y - self.t
		return self.dx

	def softmax(self,x):
		x = x - np.max(x)
		return np.exp(x) / np.sum(np.exp(x))

	def crossentropy(self,y,t):
		delta = 1e-7
		return -np.sum(t * np.log(y+delta))
			












		





