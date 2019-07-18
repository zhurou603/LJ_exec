//测试矩阵最大规模为max_size * max_size
const int max_size = 10000;

//Matrix类含两个private成员变量row_,column_
//元素为long long的数组矩阵matrix
//分别为矩阵的行数，列数，和行数和列数的最大限度
//Init()将内存内矩阵区域初始化为０,防止结果的不确定性
//Init_random()将矩阵内元素随机初始化
//构造函数:传入矩阵的row和column

class Matrix{
 public:
	long long**  matrix;
	void Init();
	void Init_random();
	int GetRow() const{
		return row_;
	}
	int GetColumn() const{
		return column_;
	}
	Matrix(int row, int column) : row_(row), column_(column){};
 private:
	int row_;
	int column_;
};
