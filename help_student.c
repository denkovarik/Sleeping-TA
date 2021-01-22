/**
 * Simulate helping a student
 */

#include <stdio.h>
#include "ta.h"

void help_student(int sleep_time)
{
	// Print to screen who is being helped and for how long
   	printf("Helping a student for %d seconds waiting students = %d\n", sleep_time, students_waiting);

	// get help
   	sleep(sleep_time);
}
