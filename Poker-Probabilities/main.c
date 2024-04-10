#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DECKSIZE 52
typedef struct
{
   int pips;
   char suit;
} card;

card deck[DECKSIZE] = {0, 0};
char suits[] = {'C', 'H', 'S', 'D'};
char *crdNames[] = {"ace", "deuce", "three", "four", "five", "six", "seven",
                    "eight", "nine", "ten", "jack", "queen", "king"};
card hand[5] = {0};
card *pHand = hand;
card *pDeck = deck;

/***************************************************************************
 *  FORWARD DECLARATIONS
 **************************************************************************/
void swap(card *, card *);
void initialize(card *);
void display(card *);
void shuffle(card *);
void dealHand(card *, card *, int counter);
void copytoHandFromDeck(card *deck, card *hand);
void arrangeHand(card *hand);
int isXofAKind(int valOfX, int toIgnore);
int isFullHouse();
int isOnePair();
int isTwoPair();
int isThreeOfAKind();
int isFourOfAKind();
int isFlush();
int isStraight();
int isStraightFlush();
/**************************************************************************/

int handsDealt = 1;
int totalNumHandsDealt = 0;
int onePair = 0;
int twoPair = 0;
int threeOfKind = 0;
int fourOfKind = 0;
int flushes = 0;
int houses = 0;
int straights = 0;
int straightFlushes =0;
int handsToDeal = 0;
int onePairOdds = 0;
int twoPairOdds = 0;
int threeOdds = 0;
int fourOdds = 0;
int houseOdds = 0;
int flushOdds = 0;
int straightOdds = 0;
int straightFlushOdds = 0;
int main(void)
{
   srand(time(NULL));

   printf("Initializing deck..\n\r");
   initialize(deck);
   printf("Displaying unshuffled deck\n\r");
   display(deck);
   printf("Shuffling the deck...\n\r");
   shuffle(deck);
   printf("Shuffled deck\n\r");
   display(deck);

   // gathers the # of hands to deal
   printf("Enter number of hands to deal:\n");
   scanf("%d", &handsToDeal);

   // Runs until the give number of hands is dealt
   for (int i = 0; i < handsToDeal; i++)
   {

      // Deck needs to be reshuffled every 10 hands dealt.
      if (handsDealt <= 10)
      {
         dealHand(hand, deck, handsDealt); // deals the hand
         arrangeHand(hand); // arranges / sorts

         totalNumHandsDealt++;  // incr total num of hands dealt
         handsDealt++; // incr handsDealt, used for reshuffling when cards too low

         // calculating the occurances of each hand
         straights += isStraight();
         flushes += isFlush();
         houses += isFullHouse();
         onePair += isOnePair();
         twoPair += isTwoPair();
         threeOfKind += isThreeOfAKind();
         fourOfKind += isFourOfAKind();
         straightFlushes += isStraightFlush();

      

         // calculates the odds for each hand. begins calculation when the occurances is greater than 0
         if (onePair > 0) onePairOdds = (int)(totalNumHandsDealt / onePair);
         if (twoPair > 0) twoPairOdds = (int)(totalNumHandsDealt / twoPair);
         if (threeOfKind > 0) threeOdds = (int)(totalNumHandsDealt / threeOfKind);
         if (fourOfKind > 0) fourOdds = (int)(totalNumHandsDealt / fourOfKind);
         if (straights > 0) straightOdds = (int)(totalNumHandsDealt / straights);
         if (flushes > 0) flushOdds = (int)(totalNumHandsDealt / flushes);
         if (houses > 0) houseOdds = (int)(totalNumHandsDealt / houses);
         if (straightFlushes > 0) straightFlushOdds = (int)(totalNumHandsDealt/straightFlushes);

         // print the odds
         printf("1P: %d:1 || 2P: %d:1 || 3K: %d:1 || 4K %d:1 || House: %d:1 || Straight: %d:1 || Flush: %d:1 || Straight Flush: %d:1 \r", onePairOdds, twoPairOdds, threeOdds, fourOdds, houseOdds, straightOdds, flushOdds,straightFlushOdds);
      }
      else 
      {
         // shuffles the deck and resets the handsDealt = 1
         shuffle(deck);
         handsDealt = 1;
      }
   }
   printf("\n");
}

// Initializes the deck 
void initialize(card *deck)
{
   for (int crdctr = 0; crdctr < DECKSIZE; deck++, crdctr++)
   {
      deck->pips = crdctr % 13 + 1;
      deck->suit = suits[(crdctr) / 13];
   }
}
// Displays the deck
void display(card *deck)
{
   for (int crdctr = 0; crdctr < DECKSIZE; deck++, crdctr++)
   {
      printf("%dof%c", deck->pips, deck->suit);
      printf((crdctr + 1) % 13 ? "   " : "\n");
   }
   printf("\n");
}
// Shuffles the deck
void shuffle(card *deck)
{
   int swapCard;
   for (int crdctr = 0; crdctr < DECKSIZE; crdctr++)
   {
      swapCard = rand() % DECKSIZE;
      swap(deck + crdctr, deck + swapCard);
   }
}
// Swaps Two cards
void swap(card *p, card *q)
{
   card tmp;
   tmp = *p;
   *p = *q;
   *q = tmp;
}

// Deals the hand by taking 5 cards off the deck.
// uses the int counter to "offset" after each hand is dealt. counter is basically # of handsDealt
// ex: counter is passed in as 1, indicating the very first hand
// so the end is 1 * 5 = 5
// start = end - 5 = 0 
// so iterate through 0 < 5
// when counter = 2
// end = 2 * 5 = 10
// start = 10 - 5 = 5 
// so iterate through 5 < 10
void dealHand(card *hand, card *deck, int counter)
{
   int end = counter * 5;
   int start = end - 5;
   int i = 0; // iterates through the 0-5 for the hand
   // iterate based on the calculated index and pick the 5 from the deck
   for (int current = start; current < end; current++)
   {
      (hand + i)->pips = (deck + current)->pips;
      (hand + i)->suit = (deck + current)->suit;
      i++;
   }
}

// sorts the contents of the hand by the value of pips.
// from smallest to greatest, using bubble sort.
void arrangeHand(card *hand)
{
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < (5 - i - 1); j++)
      {
         if ((hand + j)->pips > (hand + (j + 1))->pips)
         {
            swap((hand + j), (hand + (j + 1)));
         }
      }
   }
}

// Checks to see if all 5 suits are the same. 
// As it iterates through the cards in hand, it checks if the suit of the current is not equal to the suit of the next card.
// if its not, returns a 0, else, it continues and if the end of the array is reached, and it hasn't returned a 0, it returns a 1.
int isFlush()
{
   for (int i = 0; i < 4; i++)
   {
      // if the suit of the current != the suit of the next, return 0 (can't be flush)
      if (((hand + i)->suit) != (hand + i + 1)->suit)
      {
         return 0;
      }
   }
   return 1; // returns 1 when the hand has been iterated through and has not returned 0.
}

// checks if pips are sequentially incremented
// Since the hand is arranged (sorted) from least to greatest, the method compares the current value to the next one.
int isStraight()
{
   for (int i = 0; i < 4; i++)
   {
      // if the current pip != (the next pip++) ex: 1 != (1++) <- which is 2, then its not sequentially incremented
      if ((hand + i + 1)->pips != (hand + i)->pips + 1)
      {
         return 0; // return zero if its not sequentially incremented
      }
   }
   return 1; // returns 1 if it never returns 0
}

// Compares the current value against the next value. If they are the same, add to ctr. 
// once ctr reaches valOfX, so using above example, valOfX = 3, and there are 3 1's, it returns the pip, which is 1
int isXofAKind(int valOfX, int toIgnore)
{
   int ctr = 1; // intialized with 1.
   for (int i = 0; i < 5; i++)
   {
      // if the next pip != num to ignore AND the next pip == the previous pip, increment counter.
      // ex: 2 2 1 5 3. second element: 2, first element 2, so the ctr goes up by 1, now ctr == 2, which is true since theres two 2's
      if ((hand + i + 1)->pips != toIgnore && (hand + i + 1)->pips == (hand + i)->pips)
      {
         ctr++;
         if (ctr == valOfX) // if the hand contains # of repeating hands we're looking for, return it.
            return (hand + i + 1)->pips;
      }
      else // else, reset the ctr to 1
      {
         ctr = 1;
      }
   }
   return 0; // return 0 after the loop has been exhausted and none were found based on given conditions
}

// Checks if the hand is a full house. So using isXofAKind, it checks if there are 3 repeating cards and 2 repeating cards
// ex: 3 3 3 2 2. Calls isXofAKind to find the 3 and 2. If both return > 0, then function returns 1, else 0
int isFullHouse()
{
   int threeSame = 0; // used to store the return value for 3 repeating pips
   int twoSame = 0; // used to store the return value for 2 repeating pips
   threeSame = isXofAKind(3, 0); // finds 3 repeating pips, if any
   twoSame = isXofAKind(2, threeSame); // finds 2 repeating pips, if any

   if (threeSame && twoSame) // if threeSame && twoSame return value (<= 1), return 1.
      return 1;
   else
      return 0; // if either threeSame or twoSame returns 0, then it can't a house and returns 0.
}

// checks to see if there is a pair of same pip value, using isXOfaKind
// if it does, return 1, else return 0
int isOnePair()
{
   int returned = 0; // used to store the return value.
   returned = isXofAKind(2, 0); // checks if the hand contains 2 of the same pip value
   if (returned) // if something is returned, it's true, so return 1
      return 1;
   else
      return 0; // else return 0
}

// checks for pairs of two in hand, returns 1 is it does, 0 if it doesn't. isXofAKind used to determine.
int isTwoPair()
{
   int hasOnePair = 0;
   int hasAnotherPair = 0;

   hasOnePair = isXofAKind(2, 0); // checks for the first pair
   if (hasOnePair) // if the first pair is found, looks for the second
   {
      hasAnotherPair = isXofAKind(2, hasOnePair); // looks for second pair, ignoring the first found pair
      if (hasOnePair && hasAnotherPair) // if it has two pairs, returns 1
      {
         return 1;
      }
      else
         return 0;
   }
   else // if it doensn't have two pairs, returns 0
   {
      return 0;
   }
}
// looks for 3 pips that share the same value
int isThreeOfAKind()
{
   int returned = 0;
   returned = isXofAKind(3, 0); // returns the pip occuring 3 times, if any.
   if (returned) // if returned, return 1
   {
      return 1;
   }
   else
      return 0;
}

// looks for 4 pips that share the same value
int isFourOfAKind()
{
   int returned = 0;
   returned = isXofAKind(4, 0); // looks for 4 same value pips
   if (returned) 
      return 1;
   else
      return 0;
}
// if both straight and a flush, return 1
int isStraightFlush(){
  if (isStraight() && isFlush()){
   return 1;
  } 
  else{
   return 0;
  }
}