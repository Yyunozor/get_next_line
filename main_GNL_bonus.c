/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_GNL_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:10:50 by anpayot           #+#    #+#             */
/*   Updated: 2024/12/30 16:15:47 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "get_next_line_bonus.h"

#define MAX_TEST_FILES 4

typedef struct	s_test_stats
{
	int		line_count;
	int		total_chars;
	double	time_taken;
}	t_test_stats;

void	print_results(t_test_stats *stats, const char *filename)
{
	printf("\n📊 Results for %s:\n", filename);
	printf("✓ Lines read: %d\n", stats->line_count);
	printf("✓ Total characters: %d\n", stats->total_chars);
	printf("⏱  Time taken: %.4f seconds\n", stats->time_taken);
}

void	test_single_file(const char *filename)
{
	int				fd;
	char			*line;
	t_test_stats	stats;
	struct timeval	start, end;

	printf("\n🔍 Testing single file: %s\n", filename);
	gettimeofday(&start, NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("❌ Error opening file");
		return ;
	}
	stats.line_count = 0;
	stats.total_chars = 0;
	printf("\n📖 File contents:\n");
	printf("------------------------\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		stats.line_count++;
		stats.total_chars += ft_strlen(line);
		printf("📝 Line %d: %s", stats.line_count, line);
		free(line);
	}
	printf("------------------------\n");
	close(fd);
	gettimeofday(&end, NULL);
	stats.time_taken = (end.tv_sec - start.tv_sec) + 
		((end.tv_usec - start.tv_usec) / 1000000.0);
	print_results(&stats, filename);
}

void	test_multiple_files(char **filenames, int file_count)
{
	int				fds[MAX_TEST_FILES];
	char			*lines[MAX_TEST_FILES];
	t_test_stats	stats[MAX_TEST_FILES];
	int				active_files;
	struct timeval	start, end;
	int				i;

	printf("\n🔄 Testing multiple files simultaneously\n");
	gettimeofday(&start, NULL);
	active_files = 0;
	for (i = 0; i < file_count && i < MAX_TEST_FILES; i++)
	{
		fds[i] = open(filenames[i], O_RDONLY);
		if (fds[i] == -1)
		{
			perror("❌ Error opening file");
			continue;
		}
		stats[i].line_count = 0;
		stats[i].total_chars = 0;
		active_files++;
	}

	printf("\n📖 Interleaved reading:\n");
	printf("------------------------\n");
	while (active_files > 0)
	{
		active_files = 0;
		for (i = 0; i < file_count && i < MAX_TEST_FILES; i++)
		{
			if (fds[i] != -1)
			{
				lines[i] = get_next_line(fds[i]);
				if (lines[i])
				{
					stats[i].line_count++;
					stats[i].total_chars += ft_strlen(lines[i]);
					printf("📝 File %d, Line %d: %s", 
						i + 1, stats[i].line_count, lines[i]);
					free(lines[i]);
					active_files++;
				}
				else
				{
					close(fds[i]);
					fds[i] = -1;
				}
			}
		}
	}
	printf("------------------------\n");

	gettimeofday(&end, NULL);
	double total_time = (end.tv_sec - start.tv_sec) + 
		((end.tv_usec - start.tv_usec) / 1000000.0);

	for (i = 0; i < file_count && i < MAX_TEST_FILES; i++)
	{
		stats[i].time_taken = total_time;
		print_results(&stats[i], filenames[i]);
	}
}

void	test_invalid_fd(void)
{
	char	*line;

	printf("\n🔍 Testing invalid file descriptors\n");
	printf("------------------------\n");
	printf("Testing fd = -1: ");
	line = get_next_line(-1);
	printf("%s\n", line ? "❌ Failed" : "✅ Success");
	free(line);

	printf("Testing fd = 1023: ");
	line = get_next_line(1023);
	printf("%s\n", line ? "❌ Failed" : "✅ Success");
	free(line);

	printf("Testing closed fd: ");
	int	fd = open("test.txt", O_RDONLY);
	close(fd);
	line = get_next_line(fd);
	printf("%s\n", line ? "❌ Failed" : "✅ Success");
	free(line);
	printf("------------------------\n");
}

int	main(int argc, char **argv)
{
	printf("\n=== GET_NEXT_LINE BONUS TESTER ===\n");
	printf("🔄 Buffer size: %d\n", BUFFER_SIZE);

	if (argc < 2)
	{
		fprintf(stderr, "❌ Usage: %s <file1> [file2] [file3] [file4]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	// Test invalid file descriptors
	test_invalid_fd();

	// Test single file reading
	test_single_file(argv[1]);

	// Test multiple files if more than one file is provided
	if (argc > 2)
	{
		test_multiple_files(argv + 1, argc - 1);
	}

	printf("\n✅ All tests completed!\n\n");
	return (EXIT_SUCCESS);
}
