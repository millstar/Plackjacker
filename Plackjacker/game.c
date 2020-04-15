#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>  

//Global Variabales
int i;
char choice;
char num_deck[14] = {'A', '2', '3', '4', '5', '6', '7', '8' , '9', ':', 'J', 'Q', 'K'};
char sym_deck[5] = {'C', 'D', 'H', 'S'};

//Global Strutures
struct cards
{
	char number;
	char symbol;
};

struct hand
{
	struct cards card[5];
};


//Functions
void menu();
void tutorial();
void game();
void r_card(); //Random card
void printplayer(struct hand player);

int main()
{
	menu();
	return 0;
}

void menu()
{ 
	system("cls");
	printf("================================================================================\n");
	printf("                             Welcome to Plackjaker\n");
	printf("================================================================================\n\n");
	printf("           Type S to start the game or T to goto the tutorial.\n\n");

	printf("Enter the character:");
	scanf(" %c", &choice);

	//Try again if it's not in choice.
	while (toupper(choice) != 'S' ) {
		printf("Please Enter the correct character:");
		scanf(" %c", &choice);
	}

	//Choice
	if (toupper(choice) == 'S')
		game();
	else if (toupper(choice) == 'T')
		tutorial();
}

void game()
{
	system("cls");

	int turn = 0;
	int p_score = 0;
	int d_score = 0;

	printf("\n\n================================================================================\n");
	printf("                                   Game Started!!!\n");
	printf("================================================================================\n\n");

	printf("Remember Club = C  Diamond = D  Heart = H  Spade = S\n\n");

	struct hand player;
	struct hand dealer;

	// Reset Hand
	for (i = 0;i < 5;i++) {
		player.card[i].number = '0';
		player.card[i].symbol = '0';
		dealer.card[i].number = '0';
		dealer.card[i].symbol = '0';
	}

	//Player hand
	printf("Your hand have: ");
	printplayer(player);
	printf("\n");
	printf("Your Score: %d\n\n", p_score);

	printf("Dealer's hand has: ");
	printplayer(dealer);
	printf("\n");
	printf("Dealer Score: %d\n", d_score);
}

void tutorial()
{
	system("cls");
	printf("\n\n================================================================================\n");
	printf("                               Tutorial and Rules\n");
	printf("================================================================================\n\n");
}

void printplayer(struct hand player)
{
	for (i = 0;i < 5;i++) {
		if (player.card[i].number == ':')
			printf(" 10%c", player.card[i].symbol);
		else
			printf(" %c%c", player.card[i].number, player.card[i].symbol);
	}

}


int sum()
{

}