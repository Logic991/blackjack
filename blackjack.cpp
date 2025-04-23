#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void play();

struct Cards {
    int value;
    string symbol;
    string rank;

    // Constructor for initializing card
    Cards(int v, string s, string r) : value(v), symbol(s), rank(r) {}
};

vector<Cards> deck;

void createDeck() {
    string symbol[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string rank[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int value[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck.push_back(Cards(value[j], symbol[i], rank[j])); // Use constructor to create cards
        }
    }
}

Cards drawCard() {
    int c = rand() % deck.size();
    Cards card = deck[c];
    deck.erase(deck.begin() + c); // Correct way to erase an element from the deck
    return card;
}

int calculateScore(vector<Cards> hand) {
    int score = 0;
    int aces = 0;
    for (int i = 0; i < hand.size(); i++) {
        score += hand[i].value;
        if (hand[i].rank == "A") {
            aces++;
        }
    }

    while (score > 21 && aces > 0) {
        score -= 10;  // Adjust for Ace as 1 instead of 11
        aces--;
    }
    return score;
}

void playAgain() {
    char playAgain;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgain;

    if (playAgain == 'y' || playAgain == 'Y') {
        // Clear screen based on OS
        #ifdef _WIN32
            system("cls");
        #elif __APPLE__ || __linux__
            system("clear");
        #endif

        play(); // Replay the game
    }
}

void play() {
    createDeck();
    vector<Cards> playersHand, dealersHand;

    // Deal initial cards
    playersHand.push_back(drawCard());
    playersHand.push_back(drawCard());
    dealersHand.push_back(drawCard());
    dealersHand.push_back(drawCard());

    // Player's turn
    while (1) {
        cout << "Your hand: ";
        for (int i = 0; i < playersHand.size(); i++) {
            cout << playersHand[i].rank << " of " << playersHand[i].symbol << " /// ";
        }
        cout << "(Score: " << calculateScore(playersHand) << ")" << endl;

        cout << "Dealer's visible card: " << dealersHand[0].rank << " of " << dealersHand[0].symbol << endl;

        if (calculateScore(playersHand) == 21) {
            cout << "Blackjack! You win!" << endl;
            playAgain();
        }

        int choice;
        cout << "Will you stand(0) or hit(1)?: ";
        cin >> choice;

        if (choice == 1) {
            playersHand.push_back(drawCard());
            cout << "You have pulled: " << playersHand[playersHand.size() - 1].rank << " of " << playersHand[playersHand.size() - 1].symbol << " /// ";
            if (calculateScore(playersHand) > 21) {
                cout << "Bust! You lose." << endl;
                return;
            }
        } else {
            break;
        }
    }

    while (calculateScore(dealersHand) < 17) { 
        dealersHand.push_back(drawCard());
        cout << "Dealer has pulled: " << dealersHand[dealersHand.size() - 1].rank << " of " << dealersHand[dealersHand.size() - 1].symbol << " /// ";
    }

    cout << "Dealer's hand: ";
    for (int i = 0; i < dealersHand.size(); i++) {
        cout << dealersHand[i].rank << " of " << dealersHand[i].symbol << " /// ";
    }
    cout << "(Score: " << calculateScore(dealersHand) << ")" << endl;

    // Determine winner
    int playersScore = calculateScore(playersHand);
    int dealersScore = calculateScore(dealersHand);

    if (dealersScore > 21 || playersScore > dealersScore) {
        cout << "You win!" << endl;
    } else if (playersScore < dealersScore) {
        cout << "Dealer wins." << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    playAgain();
}

int main() {
    srand(time(0)); 
    play(); 
    return 0;
}
