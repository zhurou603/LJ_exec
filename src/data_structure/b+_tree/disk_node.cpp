#include"disk_node.h"

off_t DiskNode::number = 0;

//IO part:
//打开文件
bool DiskNode::open_file(const char* mode){
	leave_fp = fopen(leave_file.c_str(), mode);
	if(!leave_fp){
	  return false;
	}
	return true;
}


//关闭文件
bool DiskNode::close_file(){
	if(0 != fclose(leave_fp)){
		return false;
	}
	return true;
}

//从磁盘读
int DiskNode::map(void* block, off_t offset, size_t size){
	if(open_file()){
	  fseek(leave_fp, offset,SEEK_SET);
	  size_t nr = fread(block, size, 1, leave_fp);
	  if(0 == nr){
	    cout << "从文件中读取offset为  " << offset << "结构失败" << endl;
	    return 0;
	  }
	  close_file();
	  return nr;
	}
}


//写指定结构到磁盘
int DiskNode::unmap(void* block, off_t offset, size_t size){
	if(open_file()){
	  fseek(leave_fp, offset,SEEK_SET);
	  size_t wr = 0;
	  if(0 == (wr = fwrite(block, size, 1, leave_fp))){
	    cout << "写结构到磁盘文件失败" << endl;
	    return 0;
	  }
	  close_file();
	  return wr;
	}
}

//需要IO时从磁盘读入数据并重建vector
void DiskNode::read_key_value_from_disk(){
	//先读入数据到disk_data结构
	map(&disk_data,leave_offset,leaves_size);
	for(int i = 0; i < vector_size; i++){
		//重构vector供其他函数使用,栈上分配Record对象
		leaves_.push_back(make_pair(disk_data[i].key, make_shared<Record>(disk_data[i].value)));
	}
	//表示成功读入内存
	is_in_memory = true;
}

bool DiskNode::write_key_value_to_disk(){
	//把vector<Pair>的key value数据存到一块4KB的磁盘数据
	//先构造disk_data结构
	for(int i = 0; i < leaves_.size(); i++){
		disk_data[i].key = leaves_[i].first;
		disk_data[i].value = leaves_[i].second->get_value();
	}
	//然后存到文件对应offset的位置
	unmap(&disk_data, leave_offset, leaves_size);
	//更改vector_size
	vector_size = leaves_.size();
}

void DiskNode::free_space(){
	//用完则释放内存
	leaves_.clear();
	//表示此时vector不可用
	is_in_memory = false;
}

int DiskNode::create_and_append(Key key, Value value){
	//如果不在内存则需要IO	
	if(!is_in_memory){
		read_key_value_from_disk();
	}
	if(is_in_memory){
		//读接口，不需要写回
		shared_ptr<Record> check = search(key);
		if(!check){
		  shared_ptr<Record> new_record = make_shared<Record>(value);
		  //找到合适的位置插入为了保持有序。
			//写接口，需要写回
		  insert(key, new_record);
		}
	}
  return leaves_.size();
}

void DiskNode::insert(Key key, shared_ptr<Record> record){
	if(!is_in_memory){
		read_key_value_from_disk();
	}
	//找到第一个大于key的位置插入
  auto searching = leaves_.begin();
  while(searching != leaves_.end() && searching->first < key) searching++;
  leaves_.insert(searching, Pair(key,record));
	//写回
	write_key_value_to_disk();
}


shared_ptr<Record> DiskNode::search(Key key){
	//如果要搜索则要vector在内存
	if(!is_in_memory){
		read_key_value_from_disk();
	}
	auto searching = leaves_.begin();
  while(searching != leaves_.end()){
    if(searching->first == key){
      return searching->second;
    }
    searching++;
  }
  return nullptr;
}

void DiskNode::move_half_to(shared_ptr<DiskNode> receiver){
	if(!is_in_memory){
		read_key_value_from_disk();
	}
  receiver->copy_half_from(leaves_);
  int size = leaves_.size();
  for(int i = min_size(); i < size; i++){
    leaves_.pop_back();
  } 
	write_key_value_to_disk();
}

void DiskNode::copy_half_from(const vector<Pair>& origin_keys){
	//先保证leaves可访问
	if(!is_in_memory){
		read_key_value_from_disk();
	}  
	//先拷贝后半部分
  for(int i = min_size(); i < origin_keys.size(); i++){
    //移动前先把parent信息更改为接受者
    leaves_.push_back(origin_keys[i]);
  }
	//更新后要写回
	write_key_value_to_disk();
}

