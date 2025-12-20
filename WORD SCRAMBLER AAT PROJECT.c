#include <stdio.h>    // Standard input/output functions (printf, fgets, etc.)
#include <stdlib.h>   // Standard library (rand, srand, etc.)
#include <string.h>   // String handling functions (strcmp, strcpy, strlen, strcspn)
#include <time.h>     // Time functions (time for random seed)

#define MAX_WORD_LEN 100   // Maximum length allowed for a word
#define DICT_COUNT 25    // Number of words in the dictionary

// Built-in dictionary of words
static const char *dictionary[DICT_COUNT] = {
    "apple", "orange", "banana", "grape", "pear", "alpaca", "gorilla",
    "melon", "peach", "plum", "mango", "berry","horse",
    "cherry", "lemon", "lime", "kiwi", "papaya", "elephant", "lion", "tiger", "chemeleon", "monkey", "rabbit", "donkey"
};

// Function to scramble a word
// Takes the original word and randomly swaps letters to create a scrambled version
void scrambleWord(const char *word, char *scrambled) {
    strcpy(scrambled, word);          // Copy original word into scrambled buffer
    int len = strlen(scrambled);      // Find length of the word
    for (int i = 0; i < len; i++) {   // Loop through each character
        int j = rand() % len;         // Pick a random position
        char temp = scrambled[i];     // Swap current character with random one
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
    }
}

int main(void) {
    srand((unsigned)time(NULL));  // Seed random number generator with current time

    int score = 0;   // Initialize score to 0
    printf("Welcome to the Word Scramble Game!\n");
    printf("Type your guess (or 'exit' to quit).\n");

    // Main game loop (runs until user quits)
    while (1) {
        // Pick a random word from dictionary
        const char *original = dictionary[rand() % DICT_COUNT];
        char scrambled[MAX_WORD_LEN];
        scrambleWord(original, scrambled);   // Scramble the chosen word

        // Show scrambled word to user
        printf("\nScrambled word: %s\n", scrambled);

        // First attempt
        char guess[MAX_WORD_LEN];
        printf("Your guess: ");
        if (!fgets(guess, sizeof(guess), stdin)) break;   // Read user input
        guess[strcspn(guess, "\n")] = '\0';               // Remove newline character

        // Check if user wants to quit
        if (strcmp(guess, "exit") == 0 || strcmp(guess, "quit") == 0) {
            printf("Final score: %d\n", score);
            printf("Goodbye!\n");
            break;   // Exit the loop
        }

        // If first guess is correct
        if (strcmp(guess, original) == 0) {
            printf("Correct!\n");
            score++;   // Increase score
        } else {
            // Give another chance if first guess is wrong
            printf("Wrong! Try again.\n");
            printf("Your second guess: ");
            if (!fgets(guess, sizeof(guess), stdin)) break;
            guess[strcspn(guess, "\n")] = '\0';

            // Check again if user wants to quit
            if (strcmp(guess, "exit") == 0 || strcmp(guess, "quit") == 0) {
                printf("Final score: %d\n", score);
                printf("Goodbye!\n");
                break;
            }

            // If second guess is correct
            if (strcmp(guess, original) == 0) {
                printf("Correct!\n");
                score++;   // Increase score
            } else {
                // If both guesses are wrong
                printf("Still wrong. The word was: %s\n", original);
                if (score > 0) {   // Negative marking, but score cannot go below 0
                    score--;
                }
            }
        }

        // Show current score after each round
        printf("Current score: %d\n", score);
    }

    return 0;   // End of program
}

