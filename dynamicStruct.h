#pragma once
#include <unordered_map>
#include <memory>
#include <cstring>
#include <iostream>
#include <type_traits>
struct DynoStructVariable{
  unsigned int size;
  unsigned int byteoffset;
};
template<typename T>
class DynamicStruct{
  public:
    DynamicStruct(std::shared_ptr<char>& data,size_t size){
      this->data = data;
      this->size = size;
      currentOffset = 0;
    }

    bool add(T identifier,const void* data,size_t size){
      auto result = variableSet.find(identifier);
      if(size+currentOffset <= this->size){
        if(result == variableSet.end()){
          variableSet.insert(std::pair<T,DynoStructVariable>(identifier,{static_cast<unsigned int>(size),currentOffset}));
          memcpy(this->data.get()+currentOffset,data,size);
          currentOffset+=size;
          return true;
        }
      }
      return false;
    }
    template<typename R>
      void copyCmd(const void* data, size_t size){
        memcpy(this->data.get()+currentOffset,data,size);
        currentOffset+=size;
      }
    template<typename R>
      void copyCmd(std::shared_ptr<R> xc,const void* data,size_t offset, size_t size){
        memcpy(xc.get()+offset,data,size);
      }
    template<typename R>
      bool addFromArray(T identifier,const R* data,size_t size){
        auto result = variableSet.find(identifier);
        if(size+currentOffset <= this->size){
          if(result == variableSet.end()){
            variableSet.insert(std::pair<T,DynoStructVariable>(identifier,{static_cast<unsigned int>(size),currentOffset}));
            size_t elemCount = ((size_t)(size/sizeof(R)));
            if(std::is_same<R,char>::value){
              if(*((char*)(data+elemCount-1))=='\0'){
                elemCount--;
                variableSet[identifier] = {variableSet[identifier].size-1,variableSet[identifier].byteoffset};
              }
            }
            R val;
            for(size_t i = 0;i<elemCount;i++){
              val = (*(data+i));
              copyCmd<R>(&val,sizeof(R));
            }
            return true;
          }
        }
        return false;
      }
    bool set(T identifier,const void* data, size_t size){ 
      auto result = variableSet.find(identifier);
      if(result != variableSet.end()){
        if(size+result->second.byteoffset < this->size){
          memcpy(this->data.get()+result->second.byteoffset,data,size);
          return true;

        }
      }
      return false;
    }

    template<typename R> 
      bool setArrayElem(T identifier,const void* data,unsigned int index){ 
        auto result = variableSet.find(identifier); 
        if(result != variableSet.end()){
          if(index<((result->second.size/sizeof(R)))){ 
            memcpy(this->data.get()+(result->second.byteoffset+(index*sizeof(R))),data,sizeof(R));
            return true;
          }
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
    template<typename R>
      R getValue(T identifier){
        R* ptr = (R*)(data.get()+getVariableInfo(identifier).byteoffset); 
        //std::shared_ptr<char> xc = std::make_shared<char>(;
        //memcpy(data.get()+getVariableInfo(indentifier).byteoffset,xc.get(),getVariableInfo(indenfier).size);
        //T* val = (T*)xc.get();
        return *ptr;
      }
    template<typename R>
      void getValuePtr(std::shared_ptr<R>& xc,T identifier){
        //xc = std::make_shared<R>((size_t)(getVariableInfo(identifier).size));
        size_t elemCount = ((size_t)(getVariableInfo(identifier).size/sizeof(R)));
        //R* ptr = (R*)(data.get()+getVariableInfo(identifier).byteoffset)
        //
        //std::shared_ptr<char> xc = std::make_shared<char>(;
        for(int i = 0;i<elemCount;i++){
          copyCmd(xc,data.get()+(getVariableInfo(identifier).byteoffset+(i*sizeof(R))),i,sizeof(R));
        }
        //T* val = (T*)xc.get();
      }
  private:
    std::unordered_map<T,DynoStructVariable> variableSet;
    size_t size;
    std::shared_ptr<char> data;
    uint32_t currentOffset;
};
