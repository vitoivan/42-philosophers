#include <pthread.h>
#include <stdio.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	worker(char *str)
{
	printf("%s", str);
}

int	main(int argc, char **argv)
{
	pthread_t	**threads;
	int			i;
	int			number_of_threads;
	char		str[10];

	i = 0;
	number_of_threads = 6;
	threads = (pthread_t **)malloc(sizeof(pthread_t *) * number_of_threads);
	while (i < number_of_threads)
	{
		sprintf(str, "Index: %d\n", i);
		threads[i] = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_create(threads[i], NULL, (void *)worker, str);
		i++;
	}
	i = 0;
	while (i < number_of_threads)
	{
		pthread_join(*threads[i], NULL);
		i++;
	}
	return (0);
}
