#include "dynamicStruct.h"
#include <memory>
#include <string>
#include <iostream>
int main(){
  int x = 4;
  //std::string bleh = "peaches";
  float y = 4.5f;
  float w = 5.5f;
  float t = 6.5f;
  float z[4];
  z[0]=1.1f;
  z[1]=2.1f;
  z[2]=3.1f;
  z[3]=4.1f;
  //std::cout<<sizeof(float)<<std::endl;
  //size_t size = sizeof(x)+(sizeof(bleh.c_str())*sizeof(char))+1+sizeof(y);
  size_t size = sizeof(x)+sizeof(y)+sizeof(float)*6;
  std::shared_ptr<char> data = std::make_shared<char>(size);
  DynamicStruct dS = DynamicStruct<std::string>(data,size);
  std::cout<< "set x"<<std::endl;
  dS.add("x",&x,sizeof(x));
  // dS.addFromArray<char>("bleh",(bleh.c_str()),sizeof(bleh.c_str())*sizeof(char));
  dS.add("w",&w,sizeof(float));
  //dS.add("t",&t,sizeof(float));
  dS.addFromArray<float>("blue",z,sizeof(float)*4);
  std::cout<< "set z"<<std::endl;
  dS.add("y",&y,sizeof(y));
  std::cout<< "set y"<<std::endl;
  std::cout<<dS.getValue<int>("x")<<std::endl;
  std::cout<<dS.getValue<float>("w")<<std::endl;
  //std::cout<<dS.getValue<float>("t")<<std::endl;
  std::cout<<dS.getValue<float>("y")<<std::endl;
  std::shared_ptr<float> xc = std::make_shared<float>(dS.getVariableInfo("blue").size/sizeof(float));
  dS.getValuePtr<float>(xc,"blue");

  for(int i = 0; i<(int)(dS.getVariableInfo("blue").size/sizeof(float));i++){
    std::cout<<*(xc.get()+i)<<std::endl;
  }
  std::cout << std::endl;
  return 0;
}

