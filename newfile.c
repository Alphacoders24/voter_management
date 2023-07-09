#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Voter {
    char name[50];
    int age;
    int voted;
};
void registerVoter() {
    FILE *file = fopen("voters.txt", "a");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    struct Voter voter;
    printf("Enter voter name: ");
    fgets(voter.name, sizeof(voter.name), stdin);
    printf("Enter voter age: ");
    scanf("%d", &voter.age);
    voter.voted = 0;

    fprintf(file, "%s;%d;%d\n", voter.name, voter.age, voter.voted);

    fclose(file);

    printf("Voter registered successfully.\n");
}

int checkVoterExists(const char *name) {
    FILE *file = fopen("voters.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ";");
        if (strcmp(token, name) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void castVote() {
    char name[50];
    printf("Enter voter name: ");
    fgets(name, sizeof(name), stdin);

    if (checkVoterExists(name)) {
        FILE *file = fopen("voters.txt", "r+");
        if (file == NULL) {
            printf("Failed to open file.\n");
            return;
        }

        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char *token = strtok(line, ";");
            if (strcmp(token, name) == 0) {
                fseek(file, -1, SEEK_CUR);
                fputc('1', file);
                break;
            }
        }

        fclose(file);
        printf("Vote cast successfully.\n");
    } else {
        printf("Voter not found.\n");
    }
}

void displayResults() {
    FILE *file = fopen("voters.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    int totalVoters = 0;
    int totalVoted = 0;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        totalVoters++;
        char *token = strtok(line, ";");
        strtok(NULL, ";");
        int voted = atoi(strtok(NULL, ";"));
        if (voted == 1) {
            totalVoted++;
        }
    }

    fclose(file);

    printf("Total voters: %d\n", totalVoters);
    printf("Total voted: %d\n", totalVoted);
    printf("Total not voted: %d\n", totalVoters - totalVoted);
}

int main() {
    int choice;
    do {
        printf("\n");
        printf("1. Register voter\n");
        printf("2. Cast vote\n");
        printf("3. Display results\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                registerVoter();
                break;
            case 2:
                castVote();
                break;
            case 3:
                displayResults();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}