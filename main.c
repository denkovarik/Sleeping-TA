#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"



pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];



/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
	int i;						// counter
	students_waiting = 0;		// Initialize # waiting students

	// Create the general Mutex Lock used to synchronize handling of semaphores 
	// and global variables. For example, this mutex is used to synchronize the
	// modification of studentes_waiting variable, the chairs_sem semaphore, 
	// and the ta_lock semaphore
   	if (pthread_mutex_init(&mutex_lock, NULL) != 0)
      	printf("%s\n",strerror(errno));
	
	// Create semaphore to simulate the chairs outside the office, and check
	// for errors in creating int
   	if (sem_init(&chairs_sem, 0, 0) != 0)
      	printf("error init chairs_sem\n"); 
	
	// Create semaphore lock to synchronize access to the ta. Indicate if an
	// error had occured.
   	if (sem_init(&ta_lock, 0, 0) != 0)
      	printf("error init ta_lock\n");

	// Initialize array to hold student ids
   	for (i = 0; i < NUM_OF_STUDENTS; i++)
      	student_id[i] = i;

}



/**
* Creates and initializes all student threads in the program
**/
void create_students()
{
	// variable declarations
	int i, error;

	// Create n students
   	for (i = 0; i < NUM_OF_STUDENTS; i++) 
	{
		// Allocate and initialize argument to pass the student id into 
		// student_loop function
		int *arg = malloc(sizeof(*arg));
		*arg = student_id[i];

		// Create student thread and pass in student id as argument to the 
		// student_loop function
        error = pthread_create(&(students[i]), NULL, &student_loop, (void *)arg);
        if (error != 0)								// Indicate if error occured
            printf("\nStudent %d can't be created\n", i);
   	}
}



/**
* Creates and initializes the ta thread in the program
**/
void create_ta()
{
	// Create ta thread
	int error = pthread_create(&(ta), NULL, &ta_loop, NULL);
	
	// Check that ta was successfully created
    if (error != 0)
    	printf("\nTa did not come into work today!\n");
}



/**
* The main function which serves as the start of the program
**/
int main(void)
{
	int i;				// Counter

   	init();				// General initializations
   	create_ta();		// Create the ta thread
   	create_students();	// Create the student threads



	// Wait for all the student threads to finish before ta can go home
   	for (i = 0; i < NUM_OF_STUDENTS; i++)
    	pthread_join(students[i], NULL);

   	/* when all students have finished, we will cancel the TA thread */	
   	if (pthread_cancel(ta) != 0)
      	printf("%s\n",strerror(errno));		// Indicate if error had occured

   	return 0;
}

