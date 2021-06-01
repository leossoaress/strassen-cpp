#include "matrix.hpp"

Matrix::Matrix(unsigned int rows, unsigned int columns) {
    data.resize(rows, std::vector<int>(columns));
    this->rows = rows;
    this->columns = columns;
}

Matrix::Matrix(unsigned int rows, unsigned int columns, unsigned int min, unsigned int max) {
    data.resize(rows, std::vector<int>(columns));
    
    this->rows = rows;
    this->columns = columns;
    
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            data[i][j] = (rand() % (max - min)) + min;
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
    
    for (int i = 0; i < this->rows - xsize; i++) {
        for (int j = 0; j < this->columns - ysize; j++) {
            result.data[i][j] = this->data[i+x0][j+y0];
        }
    }
    
    return result;
}

Matrix Matrix::concatenate(Matrix *a, Matrix *b, Matrix *c, Matrix *d) {
    
    Matrix* result = new Matrix(a->rows * 2, a->columns * 2);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->columns; j++) {
            result->data[i][j] = a->data[i][j];
        }
    }
    
    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->columns; j++) {
            result->data[i][j+b->columns] = b->data[i][j];
        }
    }
    
    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < c->columns; j++) {
            result->data[i+c->rows][j] = c->data[i][j];
        }
    }
    
    for (int i = 0; i < d->rows; i++) {
        for (int j = 0; j < d->columns; j++) {
            result->data[i+d->rows][j+d->columns] = d->data[i][j];
        }
    }
    
    return *result;
}

Matrix Matrix::strassen(Matrix *m1, Matrix *m2) {
    
    if (m1->rows == 1 && m2->rows) {
        Matrix result = Matrix(1, 1);
        result.data[0][0] = m1->data[0][0] * m2->data[0][0];
        return result;
    }
    
    unsigned int n = m1->rows / 2;
    
    Matrix a1 = m1->split(0, n, 0, n);
    Matrix b1 = m1->split(0, n, n, n);
    Matrix c1 = m1->split(n, n, 0, n);
    Matrix d1 = m1->split(n, n, n, n);
    
    Matrix a2 = m2->split(0, n, 0, n);
    Matrix b2 = m2->split(0, n, n, n);
    Matrix c2 = m2->split(n, n, 0, n);
    Matrix d2 = m2->split(n, n, n, n);
    
    Matrix tmp1 = b2.sub(&d2); // b2 - d2
    Matrix tmp2 = a1.sum(&b1); // a1 + b1
    Matrix tmp3 = c1.sum(&d1); // c1 + d1
    Matrix tmp4 = c2.sub(&a2); // c2 - a2
    Matrix tmp5 = a1.sum(&d1); // a1 + d1
    Matrix tmp6 = a2.sum(&d2); // a2 + d2
    Matrix tmp7 = b1.sub(&d1); // b1 - d1
    Matrix tmp8 = c2.sum(&d2); // c2 + d2
    Matrix tmp9 = a1.sub(&c1); // a1 - c1
    Matrix tmp10 = a2.sum(&b2); // a2 + b2
    
    Matrix p1 = Matrix::strassen(&a1, &tmp1);
    Matrix p2 = Matrix::strassen(&tmp2, &d2);
    Matrix p3 = Matrix::strassen(&tmp3, &a2);
    Matrix p4 = Matrix::strassen(&d1, &tmp4);
    Matrix p5 = Matrix::strassen(&tmp5, &tmp6);
    Matrix p6 = Matrix::strassen(&tmp7, &tmp8);
    Matrix p7 = Matrix::strassen(&tmp9, &tmp10);
    
    Matrix tmp11 = p5.sum(&p4); // p5 + p4
    Matrix tmp12 = p6.sub(&p2); // p6 - p2
    Matrix tmp13 = p1.sum(&p5); // p1 - p5
    Matrix tmp14 = p3.sum(&p7); // p3 + p7
    
    Matrix c11 = tmp11.sum(&tmp12); // p5 + p4 - p2 _ p6
    Matrix c12 = p1.sum(&p2); // p1 + p2
    Matrix c21 = p3.sum(&p4); // p3 + p4
    Matrix c22 = tmp13.sub(&tmp14); // p1 + p5 - p3 - p7
    
    Matrix result = Matrix::concatenate(&c11, &c12, &c21, &c22);
    return result;
}
