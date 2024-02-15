#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#include <mpi.h>

int main(int argc, char **argv) {

  MPI_Comm comm;
  MPI_Init(&argc,&argv);
  comm = MPI_COMM_WORLD;
  int nprocs,procno;
  MPI_Comm_size(comm,&nprocs);
  MPI_Comm_rank(comm,&procno);

  const int l_array_size = 3;
  const int array_size = l_array_size * nprocs;
  const int rand_range = 100;
  
  int local_array[l_array_size];
  int global_array[array_size];

  srand((int)(procno*(double)RAND_MAX/nprocs));

  if (procno == 0) {
    cout << "Start: ";
    for (int i = 0; i < array_size; i++) {
      global_array[i] = rand() % rand_range;
      cout << global_array[i] << " ";
    }
    cout << "\n";
  }

  MPI_Scatter(global_array, l_array_size, MPI_INT,
	      local_array, l_array_size, MPI_INT,
	      0, comm);

  for (int i = 0; i < nprocs; i++) {
    int rec_array[l_array_size];
    int merge_array[2 * l_array_size];
    
    // Even phase
    if (i % 2 == 0) {
      if (procno % 2 != 0) {
	// Odd send right
	if (procno >= nprocs - 1) { continue; }
	  MPI_Sendrecv(local_array, l_array_size, MPI_INT, procno + 1, 0,
		       rec_array, l_array_size, MPI_INT, procno + 1, 0,
		       comm, MPI_STATUS_IGNORE);	  
      }
      else {
	// Even send left
	if (procno <= 0) { continue; }
	MPI_Sendrecv(local_array, l_array_size, MPI_INT, procno - 1, 0,
		     rec_array, l_array_size, MPI_INT, procno - 1, 0,
		     comm, MPI_STATUS_IGNORE);
      }

      // Sort
      merge(local_array, local_array + l_array_size,
	  rec_array, rec_array + l_array_size,
	  merge_array);
      sort(merge_array, merge_array + 2 * l_array_size);

      if (procno % 2 == 0) {
	copy(merge_array + l_array_size, merge_array + 2 * l_array_size, local_array); 
      }
      else {
	copy(merge_array, merge_array + l_array_size, local_array);
      }
    }

    // Odd phase
    else {
      if (procno % 2 == 0) {
	// Even send right
	if (procno >= nprocs - 1) { continue; }
	MPI_Sendrecv(local_array, l_array_size, MPI_INT, procno + 1, 0,
		     rec_array, l_array_size, MPI_INT, procno + 1, 0,
		     comm, MPI_STATUS_IGNORE);
      }
      else {
	// Odd send left
	if (procno <= 0) { continue; }
	MPI_Sendrecv(local_array, l_array_size, MPI_INT, procno - 1, 0,
		     rec_array, l_array_size, MPI_INT, procno - 1, 0,
		     comm, MPI_STATUS_IGNORE);
      }

      // Sort
      merge(local_array, local_array + l_array_size,
	    rec_array, rec_array + l_array_size,
	    merge_array);
      sort(merge_array, merge_array + 2 * l_array_size);
    
      if (procno % 2 != 0) {
	copy(merge_array + l_array_size, merge_array + 2 * l_array_size, local_array); 
      }
      else {
	copy(merge_array, merge_array + l_array_size, local_array);
      }
    }
  }

  MPI_Gather(local_array, array_size / nprocs, MPI_INT,
	     global_array, array_size / nprocs, MPI_INT,
	     0, comm);

  MPI_Finalize();

  if (procno == 0) {
    cout << "End: ";
    for (int i = 0; i < array_size; i++) {
      cout << global_array[i] << " ";
    }
    cout << "\n";
  }
  
  return 0;
}
