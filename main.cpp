#include "dynamicStruct.h"
#include <memory>
#include <string>
#include <iostream>
int main(){
  int x = 4;
  std::string bleh = "peaches";
  float y = 4.5f;
  size_t size = sizeof(x)+sizeof(bleh)+sizeof(y);
  std::shared_ptr<char> data = std::make_shared<char>(size);
  DynamicStruct dS = DynamicStruct<std::string>(data,size);
  dS.add("x",&x,sizeof(x));
  dS.add("y",&y,sizeof(y));
  dS.add("bleh",&bleh,sizeof(bleh));

  std::shared_ptr<char> xc = std::make_shared<char>(sizeof(x));
  memcpy(data.get()+dS.getVariableInfo("x").byteoffset,xc.get(),dS.getVariableInfo("x").size);
  int* xp = (int*)xc.get();
  std::cout<<*xp<<std::endl;
  return 0;
}
