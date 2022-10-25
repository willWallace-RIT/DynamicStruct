#pragma once
#include <unordered_map>
#include <memory>
#include <cstring>
struct DynoStructVariable{
  unsigned int size;
  unsigned int byteoffset;
};
template<typename T>
class DynamicStruct{
  public:
    DynamicStruct(std::shared_ptr<char> data,size_t size){
      this->data = data;
      this->size = size;
      currentOffset = 0;

    }
    bool add(T identifier,const void* data,size_t size){
      auto result = variableSet.find(identifier);
      if(size+currentOffset < this->size){
        if(result == variableSet.end()){
          variableSet.insert(std::pair<T,DynoStructVariable>(identifier,{static_cast<unsigned int>(size),currentOffset}));
          memcpy(this->data.get()+currentOffset,data,size);
          currentOffset+=size;
        return true;
      }
      }
      return false;
    }
    bool set(T identifier,const void* data, size_t size){ 
      auto result = variableSet.find(identifier);
      if(result != variableSet.end()){
        memcpy(this->data.get()+result.second().byteoffset,data,size);
        return true;
      }
      return false;
    }
    DynoStructVariable getVariableInfo(T identifier){
      auto result = variableSet.find(identifier);
      if(result != variableSet.end()){
        return result->second;
          
      }
      return {0};
    }
  private:
    std::unordered_map<T,DynoStructVariable> variableSet;
    size_t size;
    std::shared_ptr<char> data;
    uint32_t currentOffset;
  };
