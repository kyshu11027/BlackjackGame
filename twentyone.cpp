/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: 
 * USC email: 
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  for (int i = NUM_CARDS-1; i>=0; i--){
    int j = rand()%(i+1);
    int temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
   if (id>=0 && id<=12){               //prints out cards of int id 0-12
      cout <<type[id] <<"-"<<suit[0];
  }
  else if (id>12 && id<=25){          //prints out cards of int id 13-25
      cout <<type[id-13] <<"-"<<suit[1];
  }
  else if (id>25 && id<=38){          //prints out cards of int id 26-38
      cout <<type[id-26] <<"-"<<suit[2];
  }
  else if (id>38 && id<=51){          //prints out cards of int id 39-51
      cout <<type[id-39] <<"-"<<suit[3];
  }
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for (int i = 0; i< numCards; i++){
    printCard(hand[i]);
    cout<< " ";
  }
  cout<<endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int sum=0;  //sum is equal to the score of the hand 
  int soft=0; //soft is a variable I save ACE Cards
    for(int i=0;i<numCards;i++){
      sum= sum + cardValue(hand[i]); //This line adds each cards value
      if (cardValue(hand[i])==11){  //If an ace is added it is recored in soft
          soft++;
      }
    }
    while (sum>21 && soft>0){ 
      sum=sum - 10; 
      soft--;
    }                      
    return sum;
  /*int score = 0;
  int ace_count = 0;
  for (int i = 0; i< numCards; i++){
    score = score + cardValue(hand[i]);
    if (cardValue(hand[i] == 11)){
      ace_count++;
    }
  }
  while(score>21 && ace_count>0){
    score = score - 10;
    ace_count--;
  }

  return score;*/
}

/**
 * Main program logic for the game of 21
 */

int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  
  char endgame = 'y';
  while (endgame == 'y'){
    //initializing the cards
    for (int i = 0; i<NUM_CARDS; i++){
      cards[i] = i;
    }
     shuffle(cards);

    //also create variables to track the number of cards dealt and the number of cards dealt to the dealer and player specifically.
    int dealt = 0;

    //first thing to do is to deal out the cards first to the player then to the dealer twice.
    for(int i = 0; i<2; i++){
      phand[i] = cards[dealt++];
      dhand[i] = cards[dealt++];
    }
    int p_dealt = 2;
    int d_dealt = 2;
    int pcards = 2;
    int dcards = 2;
    //displaying the dealer's cards with the question mark.
    cout<<"Dealer: ? ";
    printCard(dhand[1]);
    cout<<endl;

    //now a loop to allow the player to hit or stay. But prevents them from hitting if they reach 21 or over
    while (getBestScore(phand, pcards)<21){
      //displaying the hand every time.
      cout<< "Player: ";
      printHand(phand, pcards);

      //getting user input.
      char inp;
      cout<< "Type 'h' to hit or 's' to stay\n";
      cin>>inp;

      if (inp == 'h'){
        //dealing a card to the player.
        phand[p_dealt++] = cards[dealt++];
        pcards++;
      }
      else if (inp == 's'){
        break;
      }
      else{
        exit(0);
      }
    }

    //now all the possible scenarios for the game.
    if (getBestScore(phand, pcards)==21){
      cout<< "Player: ";
      printHand(phand, pcards);
    }
    if (getBestScore(phand, pcards) <=21){
      //now the dealer draws if needed (less than 17 score)
      while (getBestScore(dhand, dcards)<17){
        dhand[d_dealt++] = cards[dealt++];
        dcards++;
      }
      // if the dealer busts after drawing cards
      if (getBestScore(dhand, dcards)>21){
        cout<< "Dealer: ";
        printHand(dhand, dcards);
        cout<< "Dealer Busts\n";
        cout<<"Win "<<getBestScore(phand, pcards)<< " "<< getBestScore(dhand, dcards)<<endl;
      }
      //if the dealer wins based off of a higher score
      else if (getBestScore(dhand, dcards)>getBestScore(phand, pcards)){
        cout<< "Dealer: ";
        printHand(dhand, dcards);
        cout<<"Lose "<<getBestScore(phand, pcards)<< " "<< getBestScore(dhand, dcards)<<endl;
      }
      //if the player wins based off of a higher score
      else if (getBestScore(dhand, dcards)<getBestScore(phand, pcards)){
        cout<< "Dealer: ";
        printHand(dhand, dcards);
        cout<<"Win "<<getBestScore(phand, pcards)<< " "<< getBestScore(dhand, dcards)<<endl;
      }
      //if the two scores tie
      else {
        cout<< "Dealer: ";
        printHand(dhand, dcards);
        cout<<"Tie "<<getBestScore(phand, pcards)<< " "<< getBestScore(dhand, dcards)<<endl;
      }
    }
    else if (getBestScore(phand, pcards)>21){
      cout<< "Player: ";
      printHand(phand, pcards);
      cout<<endl;
      cout<< "Player Busts\n";
      cout<<"Lose "<<getBestScore(phand, pcards)<< " "<< getBestScore(dhand, dcards)<<endl;
    }

    //asking end game message
    cout<<"Would you like to play again? 'y' for yes and 'n' for no\n";
    cin>> endgame;
  }
  cout<<endl;
  return 0;
}
