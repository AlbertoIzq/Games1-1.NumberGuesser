/*
___Description___
Create a program called number guesser.
There will be a secret number that is set at the start of the program without any user input.
The secret number should be picked from certain range.
The range of the number should be output to the player.
The player should be prompted to enter his guess.
The prompt should show how many guesses the player has left.
The player will then enter his guess.
If the guess is too high then the game will output that the guess was too high.
If the guess is too low then the game will output that the guess was too low.
The player only has a certain number of guesses.
The number of guesses should be based on the range of the secret number.
Any wrong guess will decrement the number of guesses left.
The game ends by saying what the secret number was regardless of if the player guessed the right number.
When the game is over, the player should be prompted if the would like to play again.
If yes then the secret number should change.
Any input errors by the player should have proper handling.

___How to solve it?___
We need a variable that stores the secret number
range: 0 - 100
We need a variable that stores the number of guesses the player has left
We need a variable that will store the player's guess
Number of guesses will be the log base 2 of the upper range - eg. log2(100) ~ 6.64 -> 7
How do we change the secret number?

do {
    Play the game
} while (want to play again?)

-Play the game:
1. Set the secret number - set it a known value for now
2. Set the number of guesses -> ceil(log2(100))

do {
    3. Prompt the user to make a guess (output the number of guesses left)
    4. Get the guess from the player
    5. Check to see if the guess is equal to the secret number
        5a. If the guess is not equal to the secret number then
            5a1. Decrement the number of guesses left
            5a2. Check to see if the guess was higher or lower than the secret number
                5a2a. If it was higher - print that the guess was too high
                5a2b. If it was lower - print that the guess was too low
} (while the game is not over)

Display the result - tell the player if the got it or not

___Functions___

Play the game -> playGame()
Want to play again -> wantToPlayAgain()
Get the guess from the player -> getGuess()

The game is not over -> isGameOver()

Number of guesses left == 0 ||  player's guess == secret number

Display result -> displayResult()

if (the player got it) {
    print that they got it and print the secret number
} else {
    print that they didn't get it and print the secret number
}
*/

#include <iostream>
#include <cstdlib> // required for rand()
#include <ctime> // required for time()
#include <sstream> // required for inputValidator
#include <vector> // required for specific input validator

using std::cin;
using std::cout;
using std::endl;

void playGame();
bool wantToPlayAgain();
int getGuess(const int&);

bool isGameOver(const int&, const int&, const int&);
void displayResult(const int&, const int&);

template <typename T>
T inputValidator();

template <typename T>
T inputValidatorSpecific(const std::vector<T>&);

int main()
{
    const std::string headline{ "Release date: 28/02/2020\nAuthor: Albertroll\nCopyright-All rights reserved" };
    cout << headline << endl << endl;
    cout << "Welcome to this stupid Number Guesser game!" << endl << endl;
    srand(static_cast<unsigned>(time(NULL)));
    do {
        playGame();
    } while (wantToPlayAgain());

    return 0;
}

void playGame() {
    const int UPPER_BOUND{ 100 };
    int secret_number = rand() % UPPER_BOUND + 1;
    const int NUMBER_GUESSES_MAX = static_cast<int>(ceil(log2(100)));
    int number_guesses_left{ NUMBER_GUESSES_MAX };
    int guess_player{ 0 };
    do {
        guess_player = getGuess(number_guesses_left);
        if (guess_player != secret_number) {
            number_guesses_left--;
            if (guess_player > secret_number) {
                cout << "Your shitty guess was too high..." << endl;
            }
            else if (guess_player < secret_number) {
                cout << "Your shitty guess was too low..." << endl;
            }
        }
        cout << endl;
    } while (!isGameOver(guess_player, secret_number, number_guesses_left));
    displayResult(guess_player, secret_number);
    cout << endl;
}

bool wantToPlayAgain() {
    cout << "Do you feel like playing this mind-blowing game? (y/n): ";
    char user_answer = inputValidatorSpecific<char>(std::vector<char>{'y', 'n'});
    user_answer = tolower(user_answer);
    bool play_again{ false };
    if (user_answer == 'y') {
        play_again = true;
    }
    return play_again;
}

int getGuess(const int& number_guesses_left) {
    int guess_player{ 0 };
    cout << "Guess the fucking number from 1 to 100 (" << number_guesses_left << " guesses left): ";
    guess_player = inputValidator<int>();
    return guess_player;
}

/*int getGuess(const int& number_guesses_left) { // Teacher's implementation
    const int IGNORE_CHARS = 256;
    int guess_player{ 0 };
    bool failure{ false };
    do {
        failure = false;
        cout << "Guess the fucking number from 1 to 100 (" << number_guesses_left << " guesses left): ";
        cin >> guess_player;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            cout << "Incorrect input, please try again: ";
            failure = true;
        }
    } while (failure);
    return guess_player;
}*/

bool isGameOver(const int& guess_player, const int& secret_number, const int& number_guesses_left) {
    return guess_player == secret_number || number_guesses_left == 0;
}

void displayResult(const int& guess_player, const int& secret_number) {
    if (guess_player == secret_number) {
        cout << "You got it, damn it!";
    }
    else {
        cout << "You stupid, fuck off!";
    }
    cout << " The secret number was " << secret_number << endl;
}

template <typename T>
T inputValidator() {
    T value{};
    std::string user_entry;
    bool done{ false };
    do {
        std::cin >> user_entry;
        std::istringstream iss{ user_entry };
        if (iss >> value) {
            done = true;
        }
        else {
            std::cout << "Incorrect input, please try again: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
        }
    } while (!done);
    return value;
}

template <typename T>
T inputValidatorSpecific(const std::vector<T>& v) {
    bool done{ false };
    T value{};
    do {
        value = inputValidator<T>();
        for (T element : v) {
            if (value == element) {
                done = true;
                break;
            }
        }
        if (!done) {
            std::cout << "Incorrect input, please try again: ";
        }
    } while (!done);
    return value;
}