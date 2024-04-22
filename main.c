#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine()
{
	printf("Threads Testing\n");
	sleep(2);
	printf("Ending thread\n");
}
// pthread returns int 0 if successful and a number other than 0 if an error occurs
int main(int argc, char *argv[])
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0) // the wait but for thread.
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return 0;
}
