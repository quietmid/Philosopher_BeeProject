#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//void* routine(void *arg)
//{
//	printf("Threads Testing\n");
//	return NULL;
//}
//// pthread returns int 0 if successful and a number other than 0 if an error occurs
//int main(int argc, char *argv[])
//{
//	pthread_t t1;

//	if (pthread_create(&t1, NULL, &routine, NULL))
//	{
//		perror("failed to create thread\n");
//		return 1;
//	}
//	sleep(2);
//	//pthread_detach(t1);
//	if (pthread_join(t1, NULL)) // the wait but for thread.
//		return 3;
//	printf("Exiting the main function.\n");
//	sleep(3);
//	return 0;
//}

#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

int main()
{
    struct timeval start, end;

    gettimeofday(&start, NULL); // Get the current time before sleeping
    usleep(500000);  // Expected sleep: 500 milliseconds (0.5 seconds)
    gettimeofday(&end, NULL);  // Get the time after sleeping

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;

    double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

    printf("Expected sleep duration: "BOLD_CYAN"\t500 milliseconds\n"RESET);
    printf("Actual sleep duration: "BOLD_CYAN"\t\t%.2f milliseconds\n\n"RESET, elapsedMilliseconds);

    return 0;
}