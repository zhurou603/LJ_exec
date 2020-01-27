# -*- coding:utf-8 -*-

import layer
import numpy as np

class Network(object):
	def __init__(self,input_size,hidden_size,output_size):
		layers = [
			layer.InputLayer((input_size,)),
			layer.FullConnected(input_size, hidden_size),
			layer.Sigmoid(hidden_size),
			layer.FullConnected(hidden_size,output_size),
			layer.SoftmaxLoss(output_size)
		]
		self.layers = layers

	def training(self, x_train, y_train, x_test, y_test, epochs, learning_rate):
		for i in range(epochs):
			#x是(784,)向量，y是(10,)向量
			for x,t in zip(x_train,y_train):
				y = self.feedforward(x)
				loss = self.layers[4].feedforward(y,t)
				#sgd
				self.sgd(learning_rate)

			print("Epochs:{0}".format(i+1), end = '    ')
			self.evaluate(x_test,y_test)

	def sgd(self,learning_rate):
		value = self.layers[4].backward()
		value = self.layers[3].backward(value)
		self.layers[3].w = self.layers[3].w - learning_rate * self.layers[3].dw
		self.layers[3].b = self.layers[3].b - learning_rate * self.layers[3].db
		value = self.layers[2].backward(value)
		value = self.layers[1].backward(value)
		self.layers[1].w = self.layers[1].w - learning_rate * self.layers[1].dw
		self.layers[1].b = self.layers[1].b - learning_rate * self.layers[1].db

	def evaluate(self,x_test, y_test):
		list = [np.argmax(self.feedforward(x)) for x,y in zip(x_test,y_test) if np.argmax(self.feedforward(x)) == y]
		print(list[0:10])
		count = sum([1 for x,y in zip(x_test,y_test) if np.argmax(self.feedforward(x)) == y])
		accuracy = (count / len(y_test))*100
		print(count, " / ", len(y_test), "   ", accuracy)
		
		
	def feedforward(self,x):
		self.layers[0].data = x
		y = self.layers[1].feedforward(self.layers[0].data)
		y = self.layers[2].feedforward(y)
		y = self.layers[3].feedforward(y)
		return y
