
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//////////////////////////
// produce a number 1 - 10
int hit() {
    int result = 0;
    result = rand() % 10 + 2;
    return result;
}


///////////////////////////
// add value of dealer hand
int calculateDealerHand(int dealerHand[], int dealerCount) { // calculate value of dealer hand
    int dealerCountSum = 0; // initialize dealer hand value
    for (int i = 0; i < dealerCount; i++){  // iterate through dealer hand
        dealerCountSum += dealerHand[i];
    }
    return dealerCountSum; // return to main function dealer hand value
}


///////////////////////////
// add value of player hand
int calculateHand(int playerHand[], int playerCount) { // calculate value of player hand
    int countSum = 0;   // initialize player hand value
    for (int i = 0; i < playerCount; i++){  // iterate through player hand
        countSum += playerHand[i];
    }
    return countSum;    // return to main function player hand value
}


////////////////////////
// calculation for advantage probability
double calculateAdvantageProbability(int countSum, int remainingCards) {
    int favorableCards = 21 - countSum; // calculate the best card to get blackjack
    double probability = static_cast<double>(favorableCards) / remainingCards; // calculate the probability percentage to get favorable card
    return probability; // return probability result to main
}


////////////////
// Dealer stuff
void dealer(int dealerHand[], int& dealerCount, int& dealerCountSum) {
        dealerHand[dealerCount++] = hit();
        dealerCountSum = calculateDealerHand(dealerHand, dealerCount);
        cout << "Dealer: ";

        for(int i = 0; i < dealerCount; i++) {
            cout << dealerHand[i] << " ";
        }
        cout << endl;
        cout << "Dealer hand value: " << dealerCountSum;
        cout << endl;
    return;
}


////////////
// Recursive function that ask player for input depending on position
bool recursiveFunction(int playerHand[], int& playerCount, int& countSum, int dealerHand[], int& dealerCount, int& dealerCountSum, int remainingCards) {
    
    if (countSum == 21) {
        cout << "You got Black Jack!";
        cout << endl;
        cout << endl;
        return false;
    }
    
    cout << endl;
    cout << "Would you like to hit or stand?" << endl;
    cout << "Enter 1 to hit or 2 to stand: " << endl;
    int playerChoice;
    cin >> playerChoice; // Player enter input

    // if player enters 1 and count is less than 21 then player hits
    if (playerChoice == 1 && countSum < 21) {
        playerHand[playerCount++] = hit();  // player hits
        countSum = calculateHand(playerHand, playerCount);  // recalculate player value
        cout << "Player: ";

        // iterate through player hand
        for(int i = 0; i < playerCount; i++) {
            cout << playerHand[i] << " "; // display player hand
        }
        cout << endl;
        cout << "Player hand value: " << countSum; // display player hand value
        cout << endl;

        // Calculate probability..............................
        // int remainingCards = 52 - playerCount - dealerCount;
        double probability = calculateAdvantageProbability(countSum, remainingCards);
        cout << "Player advantage probability: " << probability * 100 << "%";
        cout << endl;

        // If player count is greater than 21 then player bust
        if (countSum > 21) {
            cout << "You bust.";
            cout << endl;
            cout << "Dealer won";
            cout << endl;
            return false;  // End the game
        }

        
        return recursiveFunction(playerHand, playerCount, countSum, dealerHand, dealerCount, dealerCountSum, remainingCards);
    
    } else if (playerChoice == 2) {
        dealer(dealerHand, dealerCount, dealerCountSum);
        // Show dealer cards
        // Call dealer
        return false;

    }
    return true;
}



////////////
int main() {

    srand(static_cast<int>(time(0)));

    int deck[52] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11,
                    2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11,
                    2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11,
                    2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11};
    int playerHand[10]; // max amount of cards player can hold
    int playerCount = 0; // amount of cards player currently has
    int dealerHand[10]; // max amount of cards dealer can hold
    int dealerCount = 0; // amount of cards dealer currently has
    int blackJack = 21;

    // Produce the first card for the dealer
    dealerHand[dealerCount++] = deck[rand() % 52];
    int dealerCountSum = calculateDealerHand(dealerHand, dealerCount); // produce the dealer hand value for first card


    playerHand[playerCount++] = deck[rand() % 52]; // add a card to playerCount
    playerHand[playerCount++] = deck[rand() % 52]; // add a second card to playerCount
    int countSum = calculateHand(playerHand, playerCount); // call calculateHand function and return countSum to main

    cout << endl;
    cout << "Welcome to Blackjack" << endl;
    cout << endl;
    cout << "Dealer: " << dealerHand[0] << " Hidden" << endl; // Display dealer first card with second card hidden
    cout << "Dealer count: " << dealerCountSum << endl; // Display dealer hand value
    cout << "Player: " << playerHand[0] << " "<< playerHand[1] << endl; // Display player first and second card
    cout << "Player count: " << countSum;   // Display player hand value
    cout << endl;


    // Probability counter
    int remainingCards = 52 - playerCount - dealerCount;
    double probability = calculateAdvantageProbability(countSum, remainingCards);
    cout << "Player advantage probability: " << probability * 100 << "%" << endl;

    // call recursive function
    recursiveFunction(playerHand, playerCount, countSum, dealerHand, dealerCount, dealerCountSum, remainingCards);


    // Winner depending on score outcome
    if (dealerCountSum > countSum) {
        cout << "Dealer won" << endl;
    } else if(countSum > dealerCountSum && countSum <= blackJack) {
        cout << "Player won" << endl;
    }

    cout << endl;
    return 0;

}

