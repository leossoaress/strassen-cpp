#include "matrix.hpp"

Matrix::Matrix(unsigned int rows, unsigned int columns): rows(rows), columns(columns) {
  data.resize(rows, std::vector<int>(columns));
}

Matrix::Matrix(unsigned int rows, unsigned int columns, unsigned int min, unsigned int max): rows(rows), columns(columns) {
  
  data.resize(rows, std::vector<int>(columns));
  
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++) {
      data[i][j] = (rand() % (max - min)) + min;
    }
  }

}


Matrix::~Matrix(void) {}

Matrix Matrix::split(unsigned int x0, unsigned int xsize, unsigned int y0, unsigned int ysize) {
  
  Matrix result = Matrix(xsize, ysize);
  
  for (int i = 0; i < xsize; i++) {
    std::vector<int> temp(this->data[i+x0].begin() + y0, this->data[i+x0].begin() + y0 + ysize); 
    result.data[i] = temp;
  }
  
  return result;
}

Matrix Matrix::concatenate(Matrix a, Matrix b, Matrix c, Matrix d) {
    
  Matrix result = Matrix(a.rows * 2, a.columns * 2);
  
  for (int i = 0; i < a.rows; i++) {
    for (int j = 0; j < a.columns; j++) {
      result.data[i][j] = a.data[i][j];
    }
  }
  
  for (int i = 0; i < b.rows; i++) {
    for (int j = 0; j < b.columns; j++) {
      result.data[i][j+b.columns] = b.data[i][j];
    }
  }
  
  for (int i = 0; i < c.rows; i++) {
    for (int j = 0; j < c.columns; j++) {
      result.data[i+c.rows][j] = c.data[i][j];
    }
  }
  
  for (int i = 0; i < d.rows; i++) {
    for (int j = 0; j < d.columns; j++) {
      result.data[i+d.rows][j+d.columns] = d.data[i][j];
    }
  }
  
  return result;
}

Matrix Matrix::strassen(Matrix m1, Matrix m2) {
    
  if (m1.rows <= 32) {
    return m1 * m2;
  }
  
  unsigned int n = m1.rows / 2;
  
  Matrix a1 = m1.split(0, n, 0, n);
  Matrix b1 = m1.split(0, n, n, n);
  Matrix c1 = m1.split(n, n, 0, n);
  Matrix d1 = m1.split(n, n, n, n);
  
  Matrix a2 = m2.split(0, n, 0, n);
  Matrix b2 = m2.split(0, n, n, n);
  Matrix c2 = m2.split(n, n, 0, n);
  Matrix d2 = m2.split(n, n, n, n);
    
  Matrix p1 = Matrix::strassen(a1, b2 - d2);
  Matrix p2 = Matrix::strassen(a1 + b1, d2);
  Matrix p3 = Matrix::strassen(c1 + d1, a2);
  Matrix p4 = Matrix::strassen(d1, c2 - a2);
  Matrix p5 = Matrix::strassen(a1 + d1, a2 + d2);
  Matrix p6 = Matrix::strassen(b1 - d1, c2 + d2);
  Matrix p7 = Matrix::strassen(a1 - c1, a2 + b2);
  
  Matrix c11 = p5 + p4 - p2 + p6;
  Matrix c12 = p1 + p2;
  Matrix c21 = p3 + p4;
  Matrix c22 = p1 + p5 - p3 - p7;
  
  Matrix result = Matrix::concatenate(c11, c12, c21, c22);
  return result;
}

Matrix Matrix::operator + (Matrix& m) {

  Matrix result = Matrix(this->rows, m.rows);

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      result[i][j] = this->data[i][j] + m[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator - (Matrix& m) {

  Matrix result = Matrix(this->rows, m.rows);

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      result[i][j] = this->data[i][j] - m[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator * (const Matrix& m) {
    
  Matrix result = Matrix(this->rows, m.rows);
    
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      for (int l = 0; l < m.columns; l++) {
        result.data[i][j] += this->data[i][l] * m.data[l][j];
      }
    }
  }
  
  return result;
}

std::vector<int> Matrix::operator [] ( int const x ) {
  return this->data[x];
}

std::ostream& operator<< (std::ostream &out, const Matrix &m) {

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      out << m.data[i][j] << " ";
    }
    out << std::endl;
  }

  return out;

}