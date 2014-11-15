/**************************************************************************************
* Course: CS 4540 – Operating Systems – Fall 2014
* Assignment <4>  – Process Synchronization
* Name: <Waleed Gudah>
* E-mail: <waleed.h.gudah@wmich.edu>
* Submitted: <11/16/14>

	Write a multithreaded version of this algorithm that creates five
	threads, each of which:

		(i) generates a predefined number of random points

		(ii) determines if the points fall within the circle, and 

		(iii) counts the number of points that fall within the circle.
	
	Each thread updates the shared global count circleCount of all points that fall within the circle. Protect against
	race conditions on updates to circleCount by using mutex locks.
	When all thread have exited, the parent thread will calculate and output the estimated value of π.

 NOTE: 
		"make" to compile, "./pSync" to run
/****************************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NR_PTS 10000000
#define NR_THREADS 5
#define NR_PTRS_PER_THREAD NR_PTS/NR_THREADS

long circleCount = 0;	
pthread_t *threads;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *monteCarloPi(void *thread_ID) {

	long i;
	int a = (int) thread_ID;
	long incircle_thread = 0;
	unsigned int rand_state = rand();

	for (i = 0; i < NR_PTRS_PER_THREAD; i++) {
	
		double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
		double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
	
		if (x * x + y * y < 1) {

			incircle_thread++;
			
			}

		}

	float Pi = (4. * (double)incircle_thread) / ((double)NR_PTRS_PER_THREAD * 1);
	printf("Thread [%d] Reports Pi to be : %f\n" ,a,Pi);
	
	/* Preventing against race conditions on Global circleCount 
	   (1) Apply the mutual exclusion lock
	   (2) Add # of points inside the circle to the Global total 
	   (3) Unlock the mutual exclusion lock
	 */

		pthread_mutex_lock(&mutex);

		circleCount += incircle_thread;

		pthread_mutex_unlock(&mutex);

}

void createThreads(){
	
	int i;
	
	int *a = malloc(sizeof(*a));

	threads = malloc(NR_THREADS * sizeof(pthread_t));

	pthread_attr_t attr;
		
	pthread_attr_init(&attr);
	
	for (i = 0; i < NR_THREADS; i++) {
		
		pthread_create(&threads[i], &attr, monteCarloPi,  (void *) i);

	}

}

void joinThreads(){

	int i;

	for (i = 0; i < NR_THREADS; i++) {
		
		pthread_join(threads[i], NULL);
		
	}
	
	pthread_mutex_destroy(&mutex);
	
	free(threads);
}
/* Calculate Pi by the Monte Carlo method. Program arguments are the total number of random
 * points to use in the calculation and the number of threads to use. 
 */
int main(int argc, const char *argv[]) {

	float Pi;

	createThreads();

	joinThreads();
	
	Pi = (4. * (double)circleCount) / ((double)NR_PTRS_PER_THREAD * NR_THREADS);

	printf("Final Pi: %f\n", Pi);
	
return 0;

}