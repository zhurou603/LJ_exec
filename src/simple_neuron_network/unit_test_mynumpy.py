import unittest
import numpy as np
import my_numpy as mnp

class TestMatrixMul(unittest.TestCase):
	def test_vector_matrix(self):
		#列表行向量和np矩阵
		x1 = [1,2,3,4,5]
		y1 = np.array([[3,4],[7,6],[6,3],[4,8],[3,7]])
		test = list(mnp.dot(x1,y1))
		answer = list(np.dot(np.array(x1), y1))
		self.assertEqual(test, answer)

		#np行向量和列表矩阵
		x2 = np.array(x1)
		y2 = list(y1)
		test = list(mnp.dot(x2,y2))
		answer = list(np.dot(x2,y1))
		self.assertEqual(test, answer)

		x1 = [1,2,3,4,5]
		y1 = [[1,2],[3,4],[5,6],[7,8],[9,10]]
		test = list(mnp.dot(x1,y1))
		answer = list(np.dot(x1,y1))
		self.assertEqual(test, answer)

	def test_matrix_matrix(self):
		#(2,3)(3,4)=>(2,4)
		#(3,2)(3,2)=>None
		x1 = [[1,2,3],[4,5,6]]
		y1 = [[1,2,3,4],[2,3,4,5],[5,4,6,7]]
		test = list(mnp.dot(x1,y1))
		test = [list(i) for i in test]
		answer = list(np.dot(x1,y1))
		answer = [list(i) for i in answer]
		self.assertEqual(test, answer)

		x2 = [[1,2],[3,4],[4,5]]
		y2 = [[5,6],[7,8],[1,2]]
		test = mnp.dot(x2,y2)
		self.assertEqual(None,test)

if __name__ == '__main__':
	unittest.main()
