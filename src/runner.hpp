#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <ctime>

#include "matrix.hpp"
#include "gnuplot.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::microseconds microseconds;

class Runner {
    
public:
    
    unsigned int kmax = 0;
    
    unsigned int r = 0;
    
    unsigned int min = 0;
    
    unsigned int max = 0;

    std::vector<microseconds> bruteForce;
    
    std::vector<microseconds> strassen;
    
    Runner(unsigned int kmax, unsigned int r, unsigned int min, unsigned int max);
    
    std::vector<Matrix*> matrices;
    
    void execute();
    
    void test();
    
};

#endif /* RUNNER_HPP */
