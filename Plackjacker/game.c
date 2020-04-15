#include <stdio.h>
#include <string.h>
#include <ctype.h>

void menu();
void tutorial();
void game();
int compare();

int main()
{
	menu();
	return 0;
}

void menu()
{
	char choice; 

	printf("================================================================================\n");
	printf("                             Welcome to Plackjaker\n");
	printf("================================================================================\n\n");
	printf("           Type S to Start the game or T to goto the tutorial.\n\n");

	printf("Enter the character:");
	scanf(" %c", &choice);
	if (toupper(choice) == 'S')
		game();
	else if (toupper(choice) == 'T')
		tutorial();
}

void game()
{
	char choice;
	printf("\n\n================================================================================\n");
	printf("                                   Game Start!!!\n");
	printf("================================================================================\n\n");
}

void tutorial()
{
	char choice;
	printf("\n\n================================================================================\n");
	printf("                               Tutorial and Rules\n");
	printf("================================================================================\n\n");
}