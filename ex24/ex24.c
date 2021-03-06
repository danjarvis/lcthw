#include <stdio.h>
#include <stdlib.h>
#include "../ex20/dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
	BLUE,
	GREEN,
	BROWN,
	BLACK,
	OTHER
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
	"Blue",
	"Green",
	"Brown",
	"Black",
	"Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

int main(int argc, char *argv[])
{
	Person you = { .age = 0 };
	int i = 0;
	int rc = 0;
	char age[] = {};
	char *in = NULL;

	printf("What's your First Name? ");
	in = fgets(you.first_name, MAX_DATA-1, stdin);
	check(in != NULL, "Failed to read first name.");

	printf("What's your Last Name? ");
	in = fgets(you.last_name, MAX_DATA-1, stdin);
	check(in != NULL, "Failed to read last name.");

	printf("How old are you? ");
	in = fgets(age, sizeof(int) - 1, stdin);
	you.age = atoi(in);
	check(you.age > 0, "You have to enter a number.");

	printf("What color are your eyes:\n");
	for (i = 0; i <= OTHER; i++) {
		printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	int eyes = -1;
	rc = fscanf(stdin, "%d", &eyes);
	check(rc > 0, "You have to enter a number.");

	you.eyes = eyes - 1;
	check(you.eyes <= OTHER && you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	rc = fscanf(stdin, "%f", &you.income);
	check(rc > 0, "Enter a floating point number.");

	printf("------ RESULTS ------\n");

	printf("First Name: %s", you.first_name);
	printf("Last Name: %s", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);

	return 0;

error:
	return 1;
}
