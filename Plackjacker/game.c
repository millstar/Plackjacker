#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>  
#include <windows.h>

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

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
void newgame();
void printplayer(struct hand player, int amount);
int checkdeck(char card[], struct Deck deck2, int count);
int givescore(char card);
int hitstay();
int checkace(char card);
struct Deck shuffle();
struct hand sort(struct hand player, int amount);

//Check win functons
int pair(struct hand player);
int twopair(struct hand player);
int twentyone(struct hand player);
int pair21(struct hand player);
int twopair21(struct hand player);
int threeofkind(struct hand player);
int threeofkind21(struct hand player);
int fivecards(struct hand player);
int straight(struct hand player);
int flush(struct hand player);
int fullhouse(struct hand player);
int fourofkind(struct hand player);
int straightflush(struct hand player);
int blackjack(struct hand player);


int main()
{
	// Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("Advanced C tutorial - programming-technique.blogspot.com");
    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 80, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    // Change the console window size:
        // Create a COORD to hold the buffer size:
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

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
	int j = 0;
	int turn = 2;
	int p_score = 0;
	int d_score = 0;
	int p_ace = 0;
	int d_ace = 0;
	int p_win = 0;
	int d_win = 0;

	struct hand player;
	struct hand dealer;
	struct Deck outdeck;

	printf("================================================================================\n");
	printf("                                   Game Started!!!\n");
	printf("================================================================================\n\n");

	printf("Remember Club = C  Diamond = D  Heart = H  Spade = S\n\n");


	outdeck = shuffle();


	// Reset Hand
	for (i = 0;i < 5;i++) {
		player.card[i].number = '0';
		player.card[i].symbol = '0';
		dealer.card[i].number = '0';
		dealer.card[i].symbol = '0';
	}

	//First two card
	for (i = 0;i < 2;i++) {

		player.card[j].number = outdeck.card[i].number;
		player.card[j].symbol = outdeck.card[i].symbol;
		p_score += givescore(player.card[j].number);
		p_ace += checkace(player.card[j].number);

		if (i == 1) {
			dealer.card[j].number = 'X';
			dealer.card[j].symbol = 'X';
		} else {
			dealer.card[j].number = outdeck.card[i+1].number;
			dealer.card[j].symbol = outdeck.card[i+1].symbol;
			d_score += givescore(dealer.card[j].number);
			d_ace += checkace(dealer.card[j].number);
		}

		j++;//Count Card
	}


	//Player's hand
	player = sort(player, j);
	printf("Your hand have:");
	printplayer(player, j);
	printf("\n");
	printf("Your Score: %d\n\n", p_score);


	//Dealer's hand
	printf("Dealer's hand has:");
	printplayer(dealer, j);
	printf("\n");
	printf("Dealer Score: %d\n\n", d_score);

	//Player turn
	//When player want to hit a card.
	while (hitstay()) 
		{
			turn++;

			if (turn == 6)
				break;

			player.card[j].number = outdeck.card[j].number;
			player.card[j].symbol = outdeck.card[j].symbol;
			p_score += givescore(outdeck.card[j].number);
			p_ace += checkace(player.card[j].number);

			j++;//Count card

			//Show hand
			player = sort(player, j);
			printf("\nYour hand have:");
			printplayer(player, j);
			printf("\n");
			printf("Your Score: %d\n\n", p_score);

			if (p_score >= 21)
				break;

			scanf("%c", &choice);

		}

	//Check the player's hand


	printf("%d\n\n", p_win);

	printf("P: %d D: %d\n\n", p_ace, d_ace);
	
	newgame();
}

void tutorial()
{
	system("cls");
	printf("================================================================================\n");
	printf("                               Tutorial and Rules\n");
	printf("================================================================================\n\n");
}

void newgame()
{
	while (1) {
		printf("Do you want to start new game? (Y/N): ");
		scanf(" %c", &choice);
		printf("\n");

		if (toupper(choice) == 'Y') {
			game();
			break;
		}
		else if (toupper(choice) == 'N') {
			menu();
			break;
		} 
	}
}

//Function parts
void printplayer(struct hand player,  int amount)
{
	for (i = 0;i < amount;i++) {
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

int givescore(char card)
{
	if (card == 'X')
		return 0;
	else if (card == 'J' || card == 'Q' || card == 'K')
		return 10;
	else if (card == 'A')
		return 11;
	else
		return (int)(card) - 48;
}

int hitstay()
{
	while (1)
	{
		printf("Do you want Hit or Stay? (H/S): ");
		scanf(" %c", &choice);

		if (toupper(choice) == 'H') {
			return 1;
			break;
		}
		else if (toupper(choice) == 'S') {
			return 0;
			break;
		}
	}		
}

int checkace(char card)
{
	if (card == 'A')
		return 1;
	else
		return 0;
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

struct hand sort(struct hand player, int amount)
{
	int k;
	char temp1, temp2;

	for (i = 0;i < amount;i++) 
	{
		for(k = i + 1;k < amount;k++)
		{
			if (player.card[i].number > player.card[k].number) {
				if (player.card[i].number == 'A') {
					continue;
				}
				else if (player.card[i].number == 'K') {
					temp1 = player.card[i].number;
					temp2 = player.card[i].symbol;
					player.card[i].number = player.card[k].number;
					player.card[i].symbol = player.card[k].symbol;
					player.card[k].number = temp1;
					player.card[k].symbol = temp2;
				}
				else {
					temp1 = player.card[i].number;
					temp2 = player.card[i].symbol;
					player.card[i].number = player.card[k].number;
					player.card[i].symbol = player.card[k].symbol;
					player.card[k].number = temp1;
					player.card[k].symbol = temp2;
				}
			}
		}
	}

	return player;
}


//int pair(struct hand player)

//int twopair(struct hand player);
//int twentyone(struct hand player);
//int pair21(struct hand player);
//int twopair21(struct hand player);
//int threeofkind(struct hand player);
//int threeofkind21(struct hand player);
//int fivecards(struct hand player);
//int straight(struct hand player);
//int flush(struct hand player);
//int fullhouse(struct hand player);
//int fourofkind(struct hand player);
//int straightflush(struct hand player);
//int blackjack(struct hand player);
