#include "matrix.hpp"

Matrix::Matrix(unsigned int rows_, const unsigned int columns_, int value) : rows(rows_), columns(columns_) {

  this->arr = new int*[rows];

  for(unsigned int i = 0; i < rows_; ++i) {
    this->arr[i] = new int[columns]{value};
  }

}

Matrix::Matrix(unsigned int rows_, const unsigned int columns_) : rows(rows_), columns(columns_) {}

Matrix::Matrix(unsigned int rows_, unsigned int columns_, unsigned int min, unsigned int max) : rows(rows_), columns(columns_) {
    
  this->arr = new int*[rows];

  for(unsigned int i = 0; i < rows_; ++i) {
    this->arr[i] = new int[columns];
  }
    
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++) {
      this->arr[i][j] = (rand() % (max - min)) + min;
    }
  }

}


Matrix::~Matrix(void) {}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::multiply(Matrix* b) {
    
    Matrix result = Matrix(rows, b->columns);
    int temp = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < b->columns; j++) {
            temp = 0;
            for (int l = 0; l < b->columns; l++) {
                temp += data[i][l] * b->data[l][j];
            }
            result.data[i][j] = temp;
        }
    }
    
    return result;
}

Matrix Matrix::sum(Matrix *b) {
    Matrix result = Matrix(rows, b->columns);
    
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < b->columns; j++) {
            result.data[i][j] = this->data[i][j] + b->data[i][j];
        }
    }
    
    return result;
}

Matrix Matrix::sub(Matrix *b) {
    Matrix result = Matrix(this->rows, b->columns);
    
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < b->columns; j++) {
            result.data[i][j] = this->data[i][j] - b->data[i][j];
        }
    }
    
    return result;
}

Matrix Matrix::split(unsigned int x0, unsigned int xsize, unsigned int y0, unsigned int ysize) {
  
  Matrix result = Matrix(xsize, ysize);
  result.arr = new int*[xsize];

  for (size_t i = 0; i < xsize; i++) {
    result.arr[i] = (this->arr[i+x0] + y0);
  }

  return result;
}

Matrix Matrix::concatenate(Matrix a, Matrix b, Matrix c, Matrix d) {
    
    Matrix* result = new Matrix(a.rows * 2, a.columns * 2, 0);
    
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            result->arr[i][j] = a.arr[i][j];
        }
    }
    
    for (int i = 0; i < b.rows; i++) {
        for (int j = 0; j < b.columns; j++) {
            result->arr[i][j+b.columns] = b.arr[i][j];
        }
    }
    
    for (int i = 0; i < c.rows; i++) {
        for (int j = 0; j < c.columns; j++) {
            result->arr[i+c.rows][j] = c.arr[i][j];
        }
    }
    
    for (int i = 0; i < d.rows; i++) {
        for (int j = 0; j < d.columns; j++) {
            result->arr[i+d.rows][j+d.columns] = d.arr[i][j];
        }
    }
    
    return *result;
}

Matrix Matrix::strassen(Matrix m1, Matrix m2) {
    
  if (m1.rows <= 32) {
    Matrix result = m1 * m2;
    return result;
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

  Matrix result = Matrix(this->rows, m.rows, 0);

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      result[i][j] = this->arr[i][j] + m[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator - (Matrix& m) {

  Matrix result = Matrix(this->rows, m.rows, 0);

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      result[i][j] = this->arr[i][j] - m[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator * (const Matrix& m) {
    
  Matrix result = Matrix(this->rows, m.rows, 0);
    
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      for (int l = 0; l < m.columns; l++) {
        result.arr[i][j] += this->arr[i][l] * m.arr[l][j];
      }
    }
  }
  
  return result;
}

int* const Matrix::operator [] ( int const x ) {
  return this->arr[x];
}

std::ostream& operator<< (std::ostream &out, const Matrix &m) {

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      out << m.arr[i][j] << " ";
    }
    out << std::endl;
  }

  return out;

}
