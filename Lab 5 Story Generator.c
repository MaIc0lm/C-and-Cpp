#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void askQuestions(char *name, int *age, char *color) {
    printf("What is your name? ");
    scanf("%s", name);

    printf("How old are you? ");
    scanf("%d", age);

    printf("What is your favorite color? ");
    scanf("%s", color);
}

char* getRandomEnding(char *name) {
    char *endings[] = {
        "%s bravely faced the dragon and defeated it, emerging victorious!",
        "%s turned and ran, narrowly escaping the dragon's fiery breath.",
        "%s fought valiantly, but unfortunately, the dragon was too powerful, and %s fell in defeat."
    };
    int numEndings = sizeof(endings) / sizeof(char *);
    int randomIndex = rand() % numEndings;

    int endingLength = strlen(endings[randomIndex]) + strlen(name) * 2 + 1;
    char *ending = (char *)malloc(endingLength);

    if (ending == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }

    snprintf(ending, endingLength, endings[randomIndex], name, name);
    return ending;
}

int main() {
    char name[100];
    int age;
    char color[20];

    srand(time(NULL));  // Seed for randomization

    askQuestions(name, &age, color);

    char *ending = getRandomEnding(name);

    printf("\nOnce upon a time, there was a brave adventurer named %s, who was %d years old.\n", name, age);
    printf("One fateful day, %s set out on a quest to battle a fearsome dragon.\n", name);
    printf("The dragon, with scales the color of %s, stood in the adventurer's path.\n", color);
    printf("%s\n", ending);

    // Free dynamically allocated memory
    free(ending);

    return 0;
}
