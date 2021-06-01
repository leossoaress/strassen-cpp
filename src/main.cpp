#include <iostream>
#include "reader.hpp"
#include "runner.hpp"

int main(int argc, const char * argv[]) {

  Reader* reader = new Reader("./data/input.txt");
    
  std::cout << "Kmax: " << reader->kmax << std::endl;
  std::cout << "r: " << reader->r << std::endl;
  std::cout << "Amin: " << reader->min << std::endl;
  std::cout << "Amax: " << reader->max << std::endl << std::endl;
  
  Runner *runner = new Runner(reader->kmax, reader->r, reader->min, reader->max);
  
  runner->test();
      
  return 0;
}