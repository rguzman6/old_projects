/*
 * This program generates a list of n random integers.
 *
 * First, it reads an integer n. It then generates a sequence n random integers.
 */

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <omp.h>

using namespace std;

int largerCountWithLoop(int * A, int n);
int largerCountWithLoop_OMP(int * A, int n);

int main()
{
    double wtime;
    int n;
    printf ( "How many random numbers do you want to generate?\n" );
    scanf ( "%d", &n );
    int * A;
    A = new int[n];

    //generate n of random numbers
    srand( (unsigned) time(NULL) );
    
    for(int i = 0; i < n; i++)
      {
         A[i] = rand() % 100;
      }

    int num_procs = omp_get_num_procs ( );
    int max_threads = omp_get_max_threads ( );
    printf ( " Number of processors available = %d\n", num_procs ); 
    printf ( " Number of threads = %d\n", max_threads );
    
    //executing largerCountWithLoop and also measuring its execution time
    wtime = omp_get_wtime ( );
    int sum1 = largerCountWithLoop(A, n);
    wtime = omp_get_wtime ( ) - wtime;
    printf( "\n larger count loop is %d\n", sum1 );
    printf ( " time  %14f\n\n", wtime );

    //executing largerCountWithLoop_OMP and also measuring its execution time
    wtime = omp_get_wtime ( );
    int sum2 = largerCountWithLoop_OMP(A, n);
    wtime = omp_get_wtime ( ) - wtime;
    printf( " larger count loop OMP is %d\n", sum2 );
    printf ( " time  %14f\n\n", wtime );
}

int largerCountWithLoop(int * A, int n)
 {
   //TO BE COMPLETED
   int count = 0; 
   for(int i = 0; i < n; i++)
     {
       if(A[i] > 20)
	 {
	   count++; 
	 }
     }
   return count; 
 }

int largerCountWithLoop_OMP(int * A, int n)
 {
   //TO BE COMPLETED
   int i, count = 0;
  
//indicating multithreading
//indicates the shared values and private values between the threads
#pragma omp parallel shared(A, n) private(i)

//for loop will be divided among threads
//at end of parallel, count will be reduced using + operation
#pragma omp for reduction(+:count)
   for(i = 0; i < n; i++)
     {
       if(A[i] > 20)
	 {
	   count++; 
	 }
     }
   return count; 
 }

