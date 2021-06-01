#include "runner.hpp"

Runner::Runner(unsigned int kmax, unsigned int r, unsigned int min, unsigned int max) {
    this->kmax = kmax;
    this->r = r;
    this->min = min;
    this->max = max;
}

void Runner::execute() {

  for (int i = 5; i <= this->kmax; i++) {

    for (int j = 0; j < this->r; j++) {
      this->matrices.push_back(new Matrix(pow(2, i), pow(2, i), this->min, this->max));
    }

    Clock::time_point t0 = Clock::now();

    for (int l = 0; l < this->r / 2; l += 2) {
      this->matrices[l]->multiply(this->matrices[l + 1]);
    }

    Clock::time_point t1 = Clock::now();
    microseconds ms = std::chrono::duration_cast<microseconds>(t1 - t0);
    this->bruteForce.push_back(ms);
    
    std::cout << "Naive k:" << i << "  " << pow(2,i) << "x" << pow(2,i) << std::endl;
    std::cout << "Time total: " << ms.count() << std::endl;
    std::cout << "Time avarage: " <<  ms.count() / r << " microseconds" << std::endl << std::endl;

    t0 = Clock::now();

    for (int l = 0; l < this->r / 2; l += 2) {
      Matrix::strassen(this->matrices[l], this->matrices[l + 1]);
    }

    t1 = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(t1 - t0);
    this->strassen.push_back(ms);

    std::cout << "Strassen k:" << i << "  " << pow(2,i) << "x" << pow(2,i) << std::endl;
    std::cout << "Time total: " << ms.count() << std::endl;
    std::cout << "Time avarage: " <<  ms.count() / r << " microseconds" << std::endl << std::endl;

    this->matrices.clear();
  }

  std::ofstream outFile("./output/output.csv");
  outFile << "k,strassen,standard\n";

  for( int i = 0; i < this->strassen.size(); ++i) {
    outFile << std::to_string(i+5) + " " + std::to_string(this->strassen[i].count()) + " " + std::to_string(this->bruteForce[i].count()) + "\n";
  }

  outFile.close();

  Gnuplot plot;

  plot("set terminal png size 1024,768");
  plot("set output 'output/output.png'");

  plot("set title \"Comparativo Strassen x Naive\" ");
  plot("set xlabel \"Valor de k, ou seja, o tamanho do matriz (no units)\" ");
  plot("set ylabel \"Tempo médio para cada multiplicação (us)\" ");

  plot("set xtics 5,1," + std::to_string(this->kmax));
  plot("plot 'output/output.csv' using 1:2 with lines t\"strassen\", 'output/output.csv' using 1:3 with lines t\"naive\"");

  plot("set terminal qt");
  plot("set title \"Comparativo Strassen x Naive\" ");
  plot("set xlabel \"Valor de k, ou seja, o tamanho do matriz (no units)\" ");
  plot("set ylabel \"Tempo médio para cada multiplicação (us)\" ");

  plot("set xtics 5,1," + std::to_string(this->kmax));
  plot("plot 'output/output.csv' using 1:2 with lines t\"strassen\", 'output/output.csv' using 1:3 with lines t\"naive\"");
}


void Runner::test() {
    
    Matrix *a = new Matrix(4, 4, this->min, this->max);
    Matrix *b = new Matrix(4, 4, this->min, this->max);

    a->print();
    std::cout << std::endl;

    b->print();
    std::cout << std::endl;

    Matrix result = a->multiply(b);
    result.print();
}
