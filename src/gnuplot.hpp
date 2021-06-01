#ifndef GNUPLOT_HPP
#define GNUPLOT_HPP

#include <iostream>
#include <string>

class Gnuplot {

public:

  Gnuplot();

  ~Gnuplot();

  void operator () (const std::string & command);

protected:

  FILE *gnuplotpipe;

};

#endif