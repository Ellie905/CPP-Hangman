/*
	Name: Dallas Roberts
	Date: 06/19/2020
	Project: Midterm Project - Hangman Console Game
*/
#include <ctime>
#include <iostream>
#include <string>

// Structures
struct Animals
{
	short numOfChars;
	std::string name;
};

struct Country
{
	short numOfChars;
	std::string name;
};

struct States
{
	short numOfChars;
	std::string name;
};

struct Word
{
	short numOfChars;
	std::string word;
};

// Functions
void startGame(bool&, Word);

int main()
{
	// Loop Condition Variable
	bool userWantsToClose = false;

	// Declarations
	const int SIZE = 10;
	Animals animals[SIZE] = { {5, "tiger"}, {4, "lion"}, {5, "koala"}, {8, "kangaroo"}, {6, "racoon"}, {8, "parakeet"}, {3, "cat"}, {7, "catfish"}, {7, "opossum"}, {5, "rhino"} };
	Country countries[SIZE] = { {6, "mexico"}, {5, "egypt"}, {6, "canada"}, {7, "germany"}, {7, "ireland"}, {6, "france"}, {8, "mongolia"}, {9, "indonesia"}, {9, "guatemala"}, {9, "venezuela"} };
	States states[SIZE] = { {4, "ohio"}, {7, "arizona"}, {5, "texas"}, {7, "wyoming"}, {10, "california"}, {9, "tennessee"}, {8, "illinois"}, {11, "connecticut"}, {7, "montana"}, {9, "louisiana"} };
	enum PlayerChoice { ANIMAL, COUNTRY, STATE, EXIT };

	// Seed Random Number Generation
	srand(static_cast<unsigned int>(time(NULL)));

	while (!userWantsToClose)
	{
		// Program Variables
		int input = 0;
		int randomWord = 0;
		PlayerChoice player;

		// Game Variables
		bool playerWon;
		Word hangmanWord;

		// RNG
		randomWord = (rand() % SIZE) + 1; // randomWord = 1 thru 10
		if (randomWord > SIZE) { randomWord = SIZE; } // Just in case

		// Console
		system("cls");
		std::cout << "C++ Hangman" << std::endl << std::endl;

		std::cout << "Pick a Subject:" << std::endl;
		std::cout << "0. Animals" << std::endl;
		std::cout << "1. Countries" << std::endl;
		std::cout << "2. States" << std::endl;
		std::cout << "3. Exit Program" << std::endl;
		std::cout << std::endl;

		std::cin >> input;
		// Convert to Enum, Input Validation
		if (input >= 0 && input < 4)
			player = static_cast<PlayerChoice>(input);
		else
		{
			std::cout << "Invalid Input" << std::endl;
			system("pause");
			continue;
		}

		// Launch the appropriate function overload based on player's choice
		switch (player)
		{
		case PlayerChoice::ANIMAL:
			hangmanWord.numOfChars = animals[randomWord].numOfChars;
			hangmanWord.word = animals[randomWord].name;
			break;
		case PlayerChoice::COUNTRY:
			hangmanWord.numOfChars = countries[randomWord].numOfChars;
			hangmanWord.word = countries[randomWord].name;
			break;
		case PlayerChoice::STATE:
			hangmanWord.numOfChars = states[randomWord].numOfChars;
			hangmanWord.word = states[randomWord].name;
			break;
		case PlayerChoice::EXIT:
			return 0;
			break;
		default:
			return 1;
		}

		// Start Game
		startGame(playerWon, hangmanWord);

		system("cls");

		if (playerWon)
		{
			std::cout << "You guessed the word correctly!" << std::endl;
			std::cout << "Word: " << hangmanWord.word << std::endl;
		}
		else
		{
			std::cout << "You lost" << std::endl;
			std::cout << "The word was: " << hangmanWord.word << std::endl;
		}

		std::cout << std::endl << "Would you like to play again?" << std::endl;
		std::cout << "0. Yes" << std::endl;
		std::cout << "1. No" << std::endl;
		std::cin >> userWantsToClose;

		// Pause so the player can read, then the loop reiterates
		system("pause");
	}
	return 1;
}

void startGame(bool& playerWon, Word word)
{
	// Variables
	char playerGuess;
	enum Difficulty { EASY, MEDIUM, HARD };
	Difficulty difficulty = EASY; // Default difficulty
	short input;
	short lives;
	std::string strWord;

	// Difficulty
	system("cls");
	std::cout << "Select Difficulty:" << std::endl;
	std::cout << "Easy = 10 lives, Medium = 5 lives, Hard = 3 lives" << std::endl;
	std::cout << "0. Easy" << std::endl;
	std::cout << "1. Medium" << std::endl;
	std::cout << "2. Hard" << std::endl;
	std::cin >> input;
	difficulty = static_cast<Difficulty>(input);

	switch (difficulty)
	{
	case Difficulty::MEDIUM:
		lives = 5;
		break;
	case Difficulty::HARD:
		lives = 3;
		break;
	default:
		lives = 10;
		break;
	}

	// Assign * chars to word
	for (int x = 0; x < word.numOfChars; x++)
		strWord.append("*");

	// Display, Input
	while (true)
	{
		// Check if player won before continuing with the loop
		int strWasUncovered = 0; // If strWasUncovered = word.numOfChars then the string has been uncovered by the player

		for (int x = 0; x < word.numOfChars; x++)
		{
			if (strWord[x] == word.word[x])
				strWasUncovered++;
		}

		if (strWasUncovered == word.numOfChars)
		{
			playerWon = true;
			break;
		}

		system("cls");
		std::cout << std::endl << "Lives: " << lives << std::endl;
		std::cout << "Word: " << std::endl;
		std::cout << strWord << std::endl;
		std::cout << std::endl;

		std::cout << "All letters are in lower case" << std::endl;
		std::cout << "Guess (One Character): " << std::endl;
		std::cin.ignore();
		std::cin >> playerGuess;
		std::cout << std::endl;

		bool playerGotOne = false; // if true, displays correct, otherwise incorrect

		// Compare playerGuess to each letter in word
		for (int x = 0; x < word.numOfChars; x++)
		{
			if (playerGuess == word.word[x])
			{
				// Replace each correct letter with *
				strWord[x] = word.word[x];
				playerGotOne = true;
			}
		}

		if (playerGotOne) // Player guessed a correct letter
			std::cout << "Correct Guess!" << std::endl;
		else
		{
			if (lives == 0) // Player lost the game
			{
				playerWon = false; // Jumps back to main(), main tells the player they lost
				break;
			}
			else // Player lost a live
			{
				lives--;
				std::cout << "Sorry, Maybe Next Time" << std::endl;
			}
		}
		system("pause");
	}

}