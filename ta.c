/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"



/**
* Simulates the ta. Also is the function used for creating the ta thread.
**/
void *ta_loop(void *param)
{
	// variables
	int help_time;

	/* seed random generator */
   	srandom((unsigned)time(NULL));

   	while (1) 
	{
    	/* wait for a student to show up */
      	if (sem_wait(&chairs_sem) != 0)
         	printf("%s\n",strerror(errno));

   		/* acquire the mutex lock */
      	if (pthread_mutex_lock(&mutex_lock) != 0)
          	printf("%s\n",strerror(errno));

		// Decrement the number of students waiting to be helped
		students_waiting = students_waiting - 1;

      	/* indicate the TA is ready to help a student */
      	if (sem_post(&ta_lock) != 0)
          	printf("%s\n",strerror(errno));

      	/* release mutex lock */
      	if (pthread_mutex_unlock(&mutex_lock) != 0)
          	printf("%s\n",strerror(errno));

      	/* helping students random time */
		help_time = (int)((random() % MAX_SLEEP_TIME) + 1);
		help_student(help_time);
   	}
}

