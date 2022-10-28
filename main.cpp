#include "dynamicStruct.h"
#include <memory>
#include <string>
#include <iostream>
int main(){
  int x = 4;
  std::string bleh = "peaches";
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
  size_t size = sizeof(x)+sizeof(y)+sizeof(float)*6+sizeof(char)*sizeof(bleh);
  std::shared_ptr<char> data(new char[size]());
  DynamicStruct dS = DynamicStruct<std::string>(data,size);
  std::cout<< "set x"<<std::endl;
  dS.add("x",&x,sizeof(x));
  dS.addFromArray<char>("bleh",(bleh.c_str()),sizeof(bleh.c_str())*sizeof(char));
  dS.add("w",&w,sizeof(float));
  //dS.add("t",&t,sizeof(float));
  dS.addFromArray<float>("blue",z,sizeof(float)*4);
  std::cout<< "set z"<<std::endl;
  dS.add("y",&y,sizeof(y));
  
  std::cout<<dS.getValue<int>("x")<<std::endl;
  std::cout<<dS.getValue<float>("w")<<std::endl;
  //std::cout<<dS.getValue<float>("t")<<std::endl;
  std::cout<<dS.getValue<float>("y")<<std::endl;
  std::shared_ptr<float> xc (new float[(size_t)4]);
  dS.getValuePtr<float>(xc,"blue");
  std::cout<<&xc<<std::endl;
   
  for(int i = 0; i<(int)(dS.getVariableInfo("blue").size/sizeof(float));i++){
    std::cout<<*(xc.get()+i)<<std::endl;
    std::cout<<(xc.get()+i)<<std::endl;
  }
  
  std::shared_ptr<char> xc2 (new char[dS.getVariableInfo("bleh").size/sizeof(char)]);
  dS.getValuePtr<char>(xc2,"bleh");
  std::cout<<&xc2<<std::endl;
   
  std::cout<<(xc2.get())<<std::endl;
  int change = 5;
  dS.set("x",&change,sizeof(int));
  
  std::cout<<dS.getValue<int>("x")<<std::endl;
  char charchange = 'b';
  dS.setArrayElem<char>("bleh",&charchange,0);
  charchange = 'd';
  
  dS.setArrayElem<char>("bleh",&charchange,6);
  dS.getValuePtr<char>(xc2,"bleh");
  std::cout<<xc2.get()<<std::endl;
  std::cout << std::endl;
  return 0;
}

