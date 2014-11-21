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
#include <errno.h>

#define NR_PTS 10000000
#define NR_THREADS 5
#define NR_PTRS_PER_THREAD NR_PTS/NR_THREADS

/*Error handling for pthread_create and pthread_join*/
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

long circleCount = 0;	/* Global Circle Count */
pthread_t *threads;		/* Thread Identifier Decleration */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Mutex init */

/* 
   *monteCarloPi() is our pthread_create entry point, It calculates 
   an approximation of Pi using the "Monte Carlo" Method. It creates
   a specified # of random points and determines the number of points
   that fall within an inner circle, and calculates pi using, 
   i) (circle_area) / (square_area) = approx.. 
   ii) For r = 1, (circle_area) / (square_area) = π r 2 / (2r) 2 = π /4.
*/

void *monteCarloPi(void *thread_ID) {

	long i;							/* Counter */
	int a = (int) thread_ID;		/* This threads # */
	long incircle_thread = 0; 		/* # of points in this threads circle */
	unsigned int rand_state = rand(); /* Random Generator */
	
	/* Create NR_PTRS_PER_THREAD # of points */
	for (i = 0; i < NR_PTRS_PER_THREAD; i++) {
		
		double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
		double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
		
		/* If current point is within the circle */
		if (x * x + y * y < 1) {
		
			/* Increase # incircle count */
			incircle_thread++;
			
			}

		}

	/* calculate this threads approximation of Pi */
	float Pi = (4. * (double)incircle_thread) / 
				((double)NR_PTRS_PER_THREAD * 1);

	/* Report to the console, this threads calculation of Pi */
	printf("Thread [%d] Reports Pi to be [%f]\n" ,a,Pi);
	
	/* Preventing against race conditions on Global circleCount 
	   (1) Apply the mutual exclusion lock
	   (2) Add # of points inside the circle to the Global total 
	   (3) Unlock the mutual exclusion lock
	 */

		pthread_mutex_lock(&mutex);

		circleCount += incircle_thread;

		pthread_mutex_unlock(&mutex);

return NULL;

}

/*
   Createthreads() creates NR_THREADS # of threads,allocates 
   space for each one.If there is no pthread_create error
*/
void createThreads(){
	
	int i, s; /* Declare Count and ErrorNumber variables */

	threads = malloc(NR_THREADS * sizeof(pthread_t)); /* Allocate space for next thread */

	pthread_attr_t attr; /* Pthread attribute init */
		
	pthread_attr_init(&attr); /* Pthread attribute init */
	
	printf("\n----------------------------------------\n*Creating [%d] Threads\n\n", NR_THREADS);
	/* Create 1 thread for each NR_THREADS */
	for (i = 0; i < NR_THREADS; i++) {
		
		s = pthread_create(&threads[i], &attr, monteCarloPi,  (void *) i);
	 	 /*if we recieve anything other than 0 we have a create error*/
		 if (s != 0){
		 	/*handle error*/
			handle_error_en(s, "pthread_create");
		 
		 }
	}

}

/*
   joinThreads() Joins NR_THREADS # of threads, frees
   space for each one. If there is no pthread_join error
*/
void joinThreads(){

	int i,s; /* Declare Count and Error # Variable
		
	/* Join 1 thread for each NR_THREADS */
	for (i = 0; i < NR_THREADS; i++) {
		
		s = pthread_join(threads[i], NULL);
		 /*if we recieve anything other than 0 we have a join error*/
		 if (s != 0){
		 	/*handle error*/
			handle_error_en(s, "pthread_join");
		 
		 }

	}

	/* Destroy mutex */
	pthread_mutex_destroy(&mutex);
	
	/* Prompt user, all threads joined */
	printf("\n*[%d] Threads Rejoined\n\n", NR_THREADS);
	
	/* Free allocated space used by threads */
	free(threads);
}
/* main() acts as the controller, first calling createThreads
   to create our 5 threads, then calling joinThreads to join each thread
   and finally, on return, calculating Pi using the 5 threads results
*/

int main() {

	float Pi; /* Declare float for final Pi calculation */

	createThreads(); /* Create threads */

	joinThreads(); /* Join threads */
	
	/*Calculate Pi using Monte Carlo method and Global incircle count*/
	Pi = (4. * (double)circleCount) / ((double)NR_PTRS_PER_THREAD * NR_THREADS);
	
	/* Prompt user with final approximation of Pi */
	printf("Final Estimation of Pi: %f\n\n----------------------------------------\n", Pi);
	
return 0;

}