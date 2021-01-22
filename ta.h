/**
 * Header file for sleeping TA
 */

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


/* the maximum time (in seconds) to sleep */
#define MAX_SLEEP_TIME         5

/* number of maximum waiting students */
#define MAX_WAITING_STUDENTS   3

/* number of potential students */
#define NUM_OF_STUDENTS        5

/* number of available seats */
#define NUM_OF_SEATS           3

/* semaphores and mutex lock */
pthread_mutex_t mutex_lock;	// For modifying global variables and semaphores

/* semaphore declarations */
sem_t chairs_sem;		// simulates the chairs outside the office
sem_t ta_lock;			// synchronizes and controls access to the ta

/* the number of waiting students */
int students_waiting;

/* student being served */
int student_being_served;

/* the numeric id of each student */
int student_id[NUM_OF_STUDENTS];

/* student function prototype */
void *student_loop(void *param);

/* ta function prototype */
void *ta_loop(void *param);

/* hang_out prototype */
void hang_out(int lnumber, int sleep_time); 

/* help_student prototype */
void help_student(int sleep_time);
