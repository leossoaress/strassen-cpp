#include "reader.hpp"

Reader::Reader(std::string filename) {
    
  std::ifstream indata;
  indata.open(filename.c_str());
  
  if(!indata) {
    std::cerr << "Error: file could not be opened" << std::endl;
    exit(1);
  }
  
  indata >> this->kmax;
  indata >> this->r;
  indata >> this->min;
  indata >> this->max;
  
  indata.close();
}
