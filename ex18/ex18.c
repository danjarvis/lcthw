#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17 */
void die(const char *message)
{
	if (errno)
		perror(message);
	else
		printf("ERROR: %s\n", message);

	exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_cb)(int *numbers, int count, compare_cb cmp);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++) {
		for (j = 0; j < count - 1; j++) {
			if (cmp(target[j], target[j+1]) > 0) {
				temp = target[j+1];
				target[j+1] = target[j];
				target[j] = temp;
			}
		}
	}

	return target;
}

/**
 * Shell Sort
 * http://en.wikipedia.org/wiki/Shell_sort
 */
int *shell_sort(int *numbers, int count, compare_cb cmp)
{
	int * gaps = NULL;
	int gap = 1;
	int temp = 0;
	int i = 2;
	int j;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error");

	memcpy(target, numbers, count * sizeof(int));

	// Generate gaps (e.g. [701, 301, 132, 57, 10, 4, 1]
	// Courtesy of Noah Massey
	gaps = malloc(2 * sizeof(int));
	gaps[0] = 1;
	do {
		if (i == gap) {
			i *=2;
			gaps = realloc(gaps, i * sizeof(int));
		}
		gaps[gap] = (gaps[gap-1] * 7) / 4 + 1;
	} while (gaps[gap++] < count);

	while (gap--) {
		for (i = gaps[gap]; i < count; i++) {
			temp = target[i];
			for (j = i; j >= gaps[gap] && (cmp(target[j - gaps[gap]], temp) > 0); j -= gaps[gap]) {
				target[j] = target[j - gaps[gap]];
			}
			target[j] = temp;
		}
	}

	free(gaps);
	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	else
		return a % b;
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out
 */
void test_sorting(int *numbers, int count, char *description, sort_cb sort, compare_cb cmp)
{
	int i = 0;
	int *sorted = sort(numbers, count, cmp);

	if (!sorted)
		die("Failed to sort as requested.");

	printf("%s :: ", description);
	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		die("USAGE: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;
	int *numbers = malloc(count * sizeof(int));
	
	if (!numbers)
		die("Memory error.");

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, "Bubble Sort :: Normal ", bubble_sort, sorted_order);
	test_sorting(numbers, count, "Bubble Sort :: Reverse", bubble_sort, reverse_order);
	test_sorting(numbers, count, "Bubble Sort :: Strange", bubble_sort, strange_order);
	test_sorting(numbers, count, "Shell Sort  :: Normal ", shell_sort, sorted_order);
	test_sorting(numbers, count, "Shell Sort  :: Reverse", shell_sort, reverse_order);
	test_sorting(numbers, count, "Shell Sort  :: Strange", shell_sort, strange_order);

	free(numbers);

	return 0;
}
