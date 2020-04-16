#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>  

//Global Variabales
int i;
char choice;
char num_deck[14] = "A23456789:JQK";  // ':' is mean 10.
char sym_deck[5] = "CDHS";

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

struct Deck
{
	struct cards card[52];
};


//Functions
void menu();
void tutorial();
void game();
void printplayer(struct hand player);
int checkdeck(char card[], struct Deck deck2, int count);
int givescore(char card);
struct Deck shuffle();

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

	//Declare variables
	int turn = 0;
	int p_score = 0;
	int d_score = 0;
	int ace_p = 0;
	int ace_d = 0;

	struct hand player;
	struct hand dealer;
	struct Deck outdeck;

	printf("\n\n================================================================================\n");
	printf("                                   Game Started!!!\n");
	printf("================================================================================\n\n");

	printf("Remember Club = C  Diamond = D  Heart = H  Spade = S\n\n");


	outdeck = shuffle();

	//Print Deck
	for (i = 0;i < 52;i++) {
		printf("%c%c\n", outdeck.card[i].number, outdeck.card[i].symbol);
	}

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


int checkdeck(char card[], struct Deck deck, int count)
{
	int chk = 0;

	for (i = 0;i < count;i++)
	{
		if (card[0] == deck.card[i].number && card[1] == deck.card[i].symbol) {
			chk = 1;
			break;
		}
	}

	return chk;
}

struct Deck shuffle()
{
	struct Deck deck;
	int r_num, r_sym;
	int count = 0;
	char card[3];

	//Shuffle Deck
	srand(time(NULL));

	//First card in deck
	r_num = rand() % 13;
	r_sym = rand() % 4;
	deck.card[0].number = num_deck[r_num];
	deck.card[0].symbol = sym_deck[r_sym];

	for (i = 1;i < 52;i++) {

		count += 1;

		do {
			r_num = rand() % 13;
			r_sym = rand() % 4;
			card[0] = num_deck[r_num];
			card[1] = sym_deck[r_sym];
		} while (checkdeck(card, deck, count));

		deck.card[i].number = card[0];
		deck.card[i].symbol = card[1];
	}

	return deck;
}