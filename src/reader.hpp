#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <fstream>
#include <string>

class Reader {

public:
    
  unsigned int kmax = 0;
  
  unsigned int r = 0;
  
  unsigned int min = 0;
  
  unsigned int max = 0;
  
  Reader(std::string filename);
    
};

#endif /* READER_HPP */
