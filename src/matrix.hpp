#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <ctime>

class Matrix {
        
public:
    
  unsigned int rows = 0;
  
  unsigned int columns = 0;
  
  std::vector< std::vector<int> > data;
  
  Matrix(void);
  
  ~Matrix(void);
  
  Matrix(unsigned int row, unsigned int column);
  
  Matrix(unsigned int row, unsigned int column, unsigned int min, unsigned int max);
  
  Matrix multiply(Matrix* b);
  
  Matrix sum(Matrix* b);
  
  Matrix sub(Matrix* b);
  
  static Matrix concatenate(Matrix a, Matrix b, Matrix c, Matrix d);
  
  static Matrix strassen(Matrix a, Matrix b);
  
  Matrix split(unsigned int x0, unsigned int xsize, unsigned int y0, unsigned int ysize);
  
  void print();

  Matrix operator + (const Matrix & b);

  Matrix operator - (const Matrix & b);

  Matrix operator * (const Matrix & b);
  
};


#endif /* MATRIX_HPP */
