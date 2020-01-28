# -*- coding:utf-8 -*-

import layer
import numpy as np

class Network(object):
	def __init__(self,layers):
		self.layers = layers
		self.loss = None

	def training(self, x_train, y_train, x_test, y_test, epochs, learning_rate):
		for i in range(epochs):
			#x是(784,)向量，y是(10,)向量
			for x,t in zip(x_train,y_train):
				#除最后一层
				y = self.feedforward(x)
				#最后一层
				self.layers[-1](y,input_size = y.shape[0],t = t)
				#backward
				self.backward()
				#sgd
				self.sgd(learning_rate)

			print("Epochs:{0}".format(i+1), end = '    ')
			self.evaluate(x_test,y_test)

	def backward(self):
		value = self.loss
		for i in range(-1,-len(self.layers),-1):
			value = self.layers[i].backward(value)
		return value

	def sgd(self,learning_rate):
		for l in range(-1,-len(self.layers),-1):
			self.layers[l].w = self.layers[l].w - learning_rate * self.layers[l].dw
			self.layers[l].b = self.layers[l].b - learning_rate * self.layers[l].db

	def evaluate(self,x_test, y_test):
		list = [np.argmax(self.predict(x)) for x,y in zip(x_test,y_test) if np.argmax(self.predict(x)) == y]
		print(list[0:10])
		count = sum([1 for x,y in zip(x_test,y_test) if np.argmax(self.predict(x)) == y])
		accuracy = (count / len(y_test))*100
		print(count, " / ", len(y_test), "   ", accuracy)
		
		
	def feedforward(self,x):
		y = x
		size = self.layers[0].input_size[0]
		for l in range(1,len(self.layers)-1):
			y = self.layers[l](y,input_size = size)
			size = self.layers[l].output_size
		return y

	def predict(self,x):
		y = x
		size = self.layers[0].input_size[0]
		for l in range(1,len(self.layers)):
			y = self.layers[l](y,input_size = size)
			size = self.layers[l].output_size
		return y
