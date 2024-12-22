#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "get_next_line.h"

void	print_results(int line_count, int total_chars, double time_taken)
{
	printf("📊 Test Results:\n");
	printf("✓ Lines read: %d\n", line_count);
	printf("✓ Total characters: %d\n", total_chars);
	printf("⏱  Time taken: %.4f seconds\n\n", time_taken);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;
	int		total_chars;
	struct timeval	start, end;
	double	time_taken;

	printf("\n=== GET_NEXT_LINE BATTLE TESTER ===\n\n");
	if (argc != 2)
	{
		fprintf(stderr, "❌ Usage: %s <filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("📂 Testing file: %s\n", argv[1]);
	printf("🔄 Buffer size: %d\n\n", BUFFER_SIZE);
	gettimeofday(&start, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("❌ Error opening file");
		return (EXIT_FAILURE);
	}
	line_count = 0;
	total_chars = 0;
	printf("📖 Reading file contents:\n");
	printf("------------------------\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		total_chars += ft_strlen(line);
		printf("📝 Line %d: %s", line_count, line);
		free(line);
	}
	printf("------------------------\n\n");
	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start.tv_sec) + 
		((end.tv_usec - start.tv_usec) / 1000000.0);
	print_results(line_count, total_chars, time_taken);
	if (close(fd) == -1)
	{
		perror("❌ Error closing file");
		return (EXIT_FAILURE);
	}
	printf("✅ Test completed successfully!\n\n");
	return (EXIT_SUCCESS);
}
