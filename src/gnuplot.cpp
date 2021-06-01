#include "gnuplot.hpp"

Gnuplot::Gnuplot() {
  this->gnuplotpipe = popen("gnuplot -persist", "w");
  if(!this->gnuplotpipe) std::cerr << "Gnuplot Not found!";
}

Gnuplot::~Gnuplot() {
  fprintf(this->gnuplotpipe, "exit\n");
  pclose(this->gnuplotpipe);
}

void Gnuplot::operator() (const std::string & command) {
  fprintf(this->gnuplotpipe, "%s\n", command.c_str());
  fflush(this->gnuplotpipe);
}