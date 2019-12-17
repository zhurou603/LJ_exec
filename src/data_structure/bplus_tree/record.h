#ifndef RECORD_H
#define RECORD_H

#include"definition.h"

class Record{
 public:
  Record(ValueType val) : value(val) {}
  void set_value(ValueType val){
    value = val;
  }

  ValueType get_value(){
    return value;
  }
 private:
  ValueType value;
};

#endif