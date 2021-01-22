/**
 * Simulate a student hanging out
 */

#include <stdio.h>
#include "ta.h"

void hang_out(int lnumber, int sleep_time) 
{
	// Print to console who is programming and for how long
   	printf("\tStudent %d hanging out for %d seconds\n", lnumber, sleep_time );

	// Program
   	sleep(sleep_time);
}
