#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <fstream>

using namespace std;

int interpolate_affinity_cutoff(int nthreads) {
  int x1 = 8, y1 = 467;
  int x2 = 16, y2 = 828;

  return y1 + ((y2 - y1) / (x2 - x1)) * (nthreads - x1);
}

int main(int argc, char **argv) {

  // Output file
  ofstream outputFile("execution_times.txt");
  outputFile << "vectorsize sequential_time parallel_time" << endl;

  int vectorsize = 10;
  if (argc == 2)
    vectorsize = atoi(argv[1]);
  printf("Using vectorsize: %d\n", vectorsize);

  int nthreads;
#pragma omp parallel
#pragma omp master
  nthreads = omp_get_num_threads();
  
  double* invec = new double[vectorsize];
  double* outvec = new double[vectorsize];

  if (!invec || !outvec) {
    printf("Could not allocate\n");
    return 1;
  }

  for (int i = 0; i < vectorsize; i++) {
    invec[i] = (double)rand()/RAND_MAX;
    outvec[i] = 0;
  }

  // Sequential version
  {
    double tstart = omp_get_wtime();
    double factor = 1.0;
    for (int iloop = 0; iloop < 500; ++iloop) {
      for (int i = 0; i < vectorsize; ++i) {
	outvec[i] += invec[i] * factor;
      }
      factor /= 1.1;
    }
    double duration = omp_get_wtime() - tstart;
    printf("Sequential t= %8.5f sec\n", duration);
  }

  // Parallel version
  {
    double tstart = omp_get_wtime();
    double factor = 1.0;
    int affinity_cutoff = interpolate_affinity_cutoff(nthreads);
#pragma omp parallel for if(vectorsize > affinity_cutoff) default(none) shared(invec, outvec, vectorsize) private(factor)
    for (int iloop = 0; iloop < 500; ++iloop) {
      for (int i = 0; i < vectorsize; ++i) {
        outvec[i] += invec[i] * factor;
      }
      factor /= 1.1;
    }
    double duration = omp_get_wtime() - tstart;
    printf("Threads %2d t= %8.5f sec\n", nthreads, duration);
  }

  double s = 0.0;
  for (int i = 0; i < vectorsize; i++) {
    s += outvec[i];
  }
  if (s < 0) printf("%e\n", s);

  // Prevent memory leak :D
  delete[] invec;
  delete[] outvec;
  
  return 0;
}
