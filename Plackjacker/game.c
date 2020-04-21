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
int i, k; //for loop
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
int checkwin(struct hand player, int score, int turn, int win);
struct Deck shuffle();
struct hand sort(struct hand player, int amount);

//Check win functons
int pair(struct hand player, int turn);
int twopair(struct hand player, int turn);
int twentyone(struct hand player);
int threeofkind(struct hand player, int turn);
int straight(struct hand player);
int flush(struct hand player);
int fullhouse(struct hand player);
int fourofkind(struct hand player, int turn);
int straightflush(struct hand player);


int main()
{
	// Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("Plackjacker");
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
	int p_turn = 2;
	int d_turn = 2;
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
	for (i = 0;i < 4;i += 2) {

		player.card[j].number = outdeck.card[i].number;
		player.card[j].symbol = outdeck.card[i].symbol;
		p_score += givescore(player.card[j].number);
		p_ace += checkace(player.card[j].number);

		if (i == 2) {
			dealer.card[j].number = outdeck.card[i+1].number;
			dealer.card[j].symbol = outdeck.card[i+1].symbol;
			d_score += givescore(dealer.card[j].number);
			d_ace += checkace(dealer.card[j].number);

			if (d_score == 21) {
				d_win = 14;
			}
			else {
				dealer.card[j].number = 'X';
				dealer.card[j].symbol = 'X';
				d_score -= givescore(dealer.card[j].number);

			}

		} else {
			dealer.card[j].number = outdeck.card[i+1].number;
			dealer.card[j].symbol = outdeck.card[i+1].symbol;
			d_score += givescore(dealer.card[j].number);
			d_ace += checkace(dealer.card[j].number);
		}

		j++;//Count Card
	}


	while (p_score > 21 && p_ace > 0) {
				d_score -= 10;
				d_ace--;
			}

	while (d_score > 21 && d_ace > 0) {
				d_score -= 10;
				d_ace--;
			}

	//Player's hand
	player = sort(player, p_turn);
	printf("Your hand have:");
	printplayer(player, p_turn);
	printf("\n");
	printf("Your Score: %d\n\n", p_score);


	//Dealer's hand
	printf("\nDealer's hand have:");
	printplayer(dealer, d_turn);
	printf("\n");
	printf("Dealer's Score: %d\n\n", d_score);


	//Player turn
	p_win = checkwin(player, p_score, p_turn, p_win);

	if (p_win != 14 && d_win != 14) {
		//When player want to hit a card.
		while (hitstay()) 
		{
			printf("\n================================================================================\n");

			player.card[p_turn].number = outdeck.card[j].number;
			player.card[p_turn].symbol = outdeck.card[j].symbol;
			p_score += givescore(outdeck.card[j].number);
			p_ace += checkace(player.card[j].number);

			//Decrese Ace
			while (p_score > 21 && p_ace > 0) {
				p_score -= 10;
				p_ace--;
			}

			p_turn++;
			j++;//Count card

			//Show hand
			player = sort(player, p_turn);
			printf("\nYour hand have:");
			printplayer(player, p_turn);
			printf("\n");
			printf("Your Score: %d\n\n", p_score);

			if (p_score >= 21)
				break;

			if (p_turn == 5)
				break;


			scanf("%c", &choice);

		}
	}

	//Check the player's hand
	p_win = checkwin(player, p_score, p_turn, p_win);


	//Dealer's turn
	//Return dealer's second card.
	dealer.card[1].number = outdeck.card[3].number;
	dealer.card[1].symbol = outdeck.card[3].symbol;
	d_score += givescore(dealer.card[3].number);

	//Dealer check the hand
	d_win = checkwin(dealer, d_score, d_turn, d_win);

	//Dealer try to defeat player
	if (d_win != 14 && p_score <= 21 && d_score <= p_score) {
		printf("1\n");
		while (d_win < p_win || p_win == 0)
		{
			printf("2\n");
			dealer.card[d_turn].number = outdeck.card[j].number;
			dealer.card[d_turn].symbol = outdeck.card[j].symbol;
			d_score += givescore(outdeck.card[j].number);
			d_ace += checkace(dealer.card[j].number);

			//Decrese Ace
			while (d_score > 21 && d_ace > 0) {
				d_score -= 10;
				d_ace--;
			}

			d_turn++;
			j++;//Count card

			//Show hand
			dealer = sort(dealer, d_turn);

			//Check the dealer's hand
			d_win = checkwin(dealer, d_score, d_turn, d_win);

			//Can beat the player?
			if (d_win >= p_win)
				break;

			if (d_score >= 21)
				break;

			if (d_turn == 5)
				break;
		}
	}

	printf("================================================================================\n");
	printf("                                    Game End!!!\n");
	printf("================================================================================\n\n");

	printf("\nYour hand have:");
	printplayer(player, p_turn);
	printf("\n");
	printf("Your Score: %d\n\n", p_score);

	printf("\nDealer's hand have:");
	printplayer(dealer, d_turn);
	printf("\n");
	printf("Dealer's Score: %d\n\n", d_score);

	printf("P: %d D: %d\n", p_win, d_win);

	//Check who win
	if (p_score > 21) {
		printf("\nYou Lose!!!\n\n");
	}
	else if (d_score > 21) {
		printf("\nYou Win!!!\n\n");
	}
	else if (p_win == d_win) {

		if (p_score > d_score)
			printf("\nYou win!!!\n\n");
		else if (p_score < d_score)
			printf("\nYou Lose!!!\n\n");
		else
			printf("\nDraw!!!\n\n");
	}
	else if (p_win > d_win) {
		printf("\nYou win!!!\n\n");
	}
	else {
		printf("\nYou Lose!!!\n\n");
	}


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

int checkwin(struct hand player, int score, int turn, int win)
{
	if (turn == 2 && score == 21)
		win = 14;

	//Get pair at least
	if (win != 14 && score <= 21) {

		if (fourofkind(player, turn))

			win = 12;

		else if (threeofkind(player, turn)) {
			if (score == 21)
				win = 7;
			else
				win = 6;
		}

		else if (twopair(player, turn)) {
			if (score == 21)
				win = 2;
			else
				win = 5;
		}

		else if (pair(player, turn)) {
			if (score == 21)
				win = 1;
			else
				win = 4;
		}
	}

	//Get Five Cards
	if (turn == 5 && score <= 21) {

		win = 8;

		if (straight(player)) {
			win = 9;
		}
		if (flush(player)) {
			win = 10;
		}
		if (fullhouse(player)) {
			win = 11;
		}
		if (straightflush(player)) {
			win = 13;
		}

	}

	//Only score 21
	if (score == 21 && win != 14) {
		win = 3;
	}

	return win;
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
	char temp1, temp2;

	for (i = 0;i < amount;i++) 
	{
		for(k = i + 1;k < amount;k++)
		{
			if (player.card[i].number > player.card[k].number) {
				if (player.card[i].number == 'A') {
					continue;
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
			else {

				if (player.card[k].number == 'A') {
					temp1 = player.card[k].number;
					temp2 = player.card[k].symbol;
					player.card[k].number = player.card[i].number;
					player.card[k].symbol = player.card[i].symbol;
					player.card[i].number = temp1;
					player.card[i].symbol = temp2;
				}
				else if (player.card[i].number == 'K') {
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


//Poker Functions
int pair(struct hand player, int turn)
{
	int c = 0; //Count pairs

	for (i = 0;i < turn;i++) {
		for(k = i+1;k < turn;k++) {
			if (player.card[i].number == player.card[k].number) 
				c++;
			else
				break;
		}
	}

	return c;
}

int twopair(struct hand player, int turn)
{
	if (pair(player, turn) == 2)
		return 2;
	else
		return 0;
}

int threeofkind(struct hand player, int turn)
{
	int c = 0; //Count card

	for (i = 0;i < turn;i++) {
		for(k = i+1;k < turn;k++) {
			if (player.card[i].number == player.card[k].number) 
				c++;
			else
				break;
		}
	}

	if (c == 3)
		return 6;
	else
		return 0;
}


int straight(struct hand player)
{
	int start;

	for (i = 0;i < 13;i++) {
		if (player.card[0].number == num_deck[i]) {
			start = i;
		}
	}

	for (i = 0;i < 5;i++) {
		if (player.card[i].number != num_deck[start]) {
			return 0;
		}
		start++;
	}

	return 9;
}

int flush(struct hand player)
{
	for (i = 0;i < 4;i++) {
		if (player.card[i].symbol != player.card[i+1].symbol) {
			return 0;
		}
	}

	return 10;
}

int fullhouse(struct hand player)
{
	int t = 0, c = 0; //t for that number is three of kind.

	for (i = 0;i < 5;i++) {
		for(k = i+1;k < 5;k++) {
			if (player.card[i].number == player.card[k].number) {
				c++;
				if (c == 3)
					t = k;
			}
			else
				break;
		}
	}

	if (t == 3) {
		return 0;
	
	} else if (t == 2) {

		if (player.card[3].number == player.card[4].number)
			return 11;

	} else if (t == 4) {

		if (player.card[0].number == player.card[1].number)
			return 11;
	}

	return 0;

}

int fourofkind(struct hand player, int turn)
{
	int c = 0; //Count card

	for (i = 0;i < turn;i++) {
		for(k = i+1;k < turn;k++) {
			if (player.card[i].number == player.card[k].number) 
				c++;
			else
				break;
		}
	}

	if (c == 4)
		return 12;
	else
		return 0;
}

int straightflush(struct hand player)
{
	if (straight(player) && flush(player))
		return 13;
	else
		return 0;
}
