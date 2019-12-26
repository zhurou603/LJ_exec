#ifndef RECORD_H
#define RECORD_H

#include"definition.h"

//实际保存的记录
class Record{
 public:
  Record(Value val) : value_(val) {}
  
  void set(Value value){
    value_ = value;
  }

  Value get_value() const{
    return value_;
  }
  
 private:
  Value value_;  
};

#endif