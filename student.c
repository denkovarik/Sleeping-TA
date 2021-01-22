/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"



/**
* Simulates the student. Also is the function used for creating the student 
* thread
**/
void *student_loop(void *param)
{
   	/* varaibles */
	int times_through_loop = 0;		// Number of times the while loop itereates
	int id = *((int *)param);		// The student id passed into the function
	int programming_time;			// The time student programs
   	
	srandom((unsigned)time(NULL));	// Seed for random number generator
	

   	while (times_through_loop < 5) 
	{
		// Calculate the amount of time to program
		programming_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		// Program
		hang_out(id, programming_time);

      	/* acquire the mutex lock */
      	if (pthread_mutex_lock(&mutex_lock) != 0)
         	printf("StudentA %s\n",strerror(errno));

      	/* is there a seat available */
      	if (students_waiting < NUM_OF_SEATS) 
		{
			// Increment the number of students waiting
			students_waiting = students_waiting + 1;

			// Print to screen that student is waiting to be helped
         	printf("\t\tStudent %d takes a seat waiting = %d\n", id, students_waiting);
			
			// Notify ta that student is waiting to be helped
         	if (sem_post(&chairs_sem) != 0)
             	printf("StudentB %s\n",strerror(errno));

			// Release the mutex lock so someone else can use it
         	if (pthread_mutex_unlock(&mutex_lock))
             	printf("StudentC %s\n",strerror(errno));

			// Aquire ta_lock causing student to what for help from ta
         	if (sem_wait(&ta_lock) != 0)
             	printf("StudentD %s\n",strerror(errno));
			
			// Print to screen that student is receiving help
         	printf("Student %d receiving help\n", id);

			// Increment loop counter
			times_through_loop = times_through_loop + 1;					
       	} 
		// All chair outside office are full
       	else {
          	printf("\t\t\tStudent %d will try later\n", id);
          	pthread_mutex_unlock(&mutex_lock);		// Come bakck later
       	}
   	}
}

