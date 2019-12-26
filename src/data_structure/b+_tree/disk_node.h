#include"leaf_node.h"
#include<cstring>

struct DiskRecord{
	Key key;
	Value value;
};

class DiskNode : public LeafNode {
 public:
	DiskNode(int d) : LeafNode(d), leave_offset(4096*number), leave_file("./data/leaves_key_value.bin"), is_in_memory(true), leaves_size(4096){
		memset(&disk_data,0,sizeof(disk_data));
		number++;
	}
  DiskNode(int d, shared_ptr<Node> p) : LeafNode(d, p), leave_offset(4096*number), leave_file("./data/leaves_key_value.bin"), is_in_memory(true), leaves_size(4096){
		memset(&disk_data,0,sizeof(disk_data));
		number++;
	}
	virtual ~DiskNode(){}
	//重新定义需要IO的虚函数
	//可读
	shared_ptr<Record> search(Key key);

	//可写
	//向leaves创建记录并添加,返回当前size以便调整
  int create_and_append(Key key, Value value);
	void insert(Key key, shared_ptr<Record> record);
	void move_half_to(shared_ptr<DiskNode> receiver);
	void copy_half_from(const vector<Pair>& origin_keys);
	void free_space();

 private:
	//IO part:
	bool open_file(const char* mode = "rb+");
	bool close_file();
	int map(void* block, off_t offset, size_t size);
	int unmap(void* block, off_t offset, size_t size);
	void read_key_value_from_disk();
	bool write_key_value_to_disk();
	//释放内存,通常在一个大的写操作完成之后


	//表明现在有几个disknode被创建，用于指明offset
	static off_t number;
	//该结点在文件中的偏移
	off_t leave_offset;
	const string leave_file;
	FILE* leave_fp;
	bool is_in_memory;
	//4KB
	const size_t leaves_size;
	//记录最后一次IO进磁盘的vector有多少元素
	int vector_size;
	DiskRecord disk_data[512];
};
