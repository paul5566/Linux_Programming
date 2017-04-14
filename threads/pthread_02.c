/* An example of pthread API */

#include <stdio.h>
#include <errno.h>
#include <pthread.h>

/* A global variable for saving retrun value from thread.
 * We can use a pointer to integer point to this return value in the main process.
 */
int thread_return_value;

// compute successive prime numbers
void * compute_prime (void* arg)
{

	int candidate = 2;
	int n = *((int*) arg);

	while (1) {
		int factor;
		int is_prime = 1;

		// test primality by successive division.
		for (factor = 2; factor < candidate; ++factor){

			if (candidate % factor == 0) {
				is_prime = 0;
				break;
			}
		}
		// is the prime number or not
		if (is_prime) {
			if (--n == 0){
				thread_return_value = candidate;
				pthread_exit(&thread_return_value);
			}
		}
		++candidate;
	}
	pthread_exit(0);
}

int main ()
{

	int * prime;
	int which_prime = 10;
	int which_prime_origianl = which_prime;
	int ret;
	pthread_t thread;

	// create a new thread
	ret = pthread_create (&thread, NULL, &compute_prime, &which_prime);
	if (ret != 0)
		perror("pthread_create");

	// wait for the prime number thread to complete, and obtain the return value from thread.
	ret = pthread_join (thread, (void **) &prime);
	if (ret != 0)
		perror("pthread_join");

	printf("The %d-th prime number is %d.\n", which_prime_origianl, *prime);

	return 0;
}
