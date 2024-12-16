#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "get_next_line.h"

void	print_results(int line_count, int total_chars, double cpu_time_used)
{
	printf("📊 Test Results:\n");
	printf("✓ Lines read: %d\n", line_count);
	printf("✓ Total characters: %d\n", total_chars);
	printf("⏱  Time taken: %.4f seconds\n\n", cpu_time_used);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;
	int		total_chars;
	clock_t	start;
	clock_t	end;
	double	cpu_time_used;

	printf("\n=== GET_NEXT_LINE BATTLE TESTER ===\n\n");
	if (argc != 2)
	{
		fprintf(stderr, "❌ Usage: %s <filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("📂 Testing file: %s\n", argv[1]);
	printf("🔄 Buffer size: %d\n\n", BUFFER_SIZE);
	start = clock();
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
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	print_results(line_count, total_chars, cpu_time_used);
	if (close(fd) == -1)
	{
		perror("❌ Error closing file");
		return (EXIT_FAILURE);
	}
	printf("✅ Test completed successfully!\n\n");
	return (EXIT_SUCCESS);
}
