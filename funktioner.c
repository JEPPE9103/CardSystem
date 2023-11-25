#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "safeinput.h"
#include "funktioner.h"

CARD* cards = NULL;
int numCards = 0;

void InitializeSystem() {
    cards = NULL;
    numCards = 0;
}

void CleanupSystem() {
    free(cards);
}

void OpenDoor() {
    printf("Opening the door...\n");
    printf("Currently the light is: green\n");
}


void ListAllCards() {
    printf("List of cards in the system:\n");
    for (int i = 0; i < numCards; i++) {
        printf("Card number: %s - Access: %s - Entry Date: %s\n", cards[i].cardId,
               cards[i].hasAccess ? "Granted" : "Denied", cards[i].entryDate);
    }
}

void AddRemoveAccess() {
    printf("Enter the card number: ");
    char cardId[20];
    GetInput(" ", cardId, sizeof(cardId));

    for (int i = 0; i < numCards; i++) {
        if (strcmp(cards[i].cardId, cardId) == 0) {
            printf("Card number %s found in the system.\n", cardId);
            int choice;
            GetInputInt("Enter 1 to grant access or 0 to deny access: ", &choice);
            if (choice == 1) {
                cards[i].hasAccess = 1;
                printf("Access granted for card %s.\n", cardId);
            } else if (choice == 0) {
                cards[i].hasAccess = 0;
                printf("Access denied for card %s.\n", cardId);
            } else {
                printf("Invalid choice. Access status remains unchanged.\n");
            }
            return;
        }
    }

    printf("Card number %s not found in the system.\n", cardId);
    printf("Adding the card to the system...\n");

    numCards++;
    cards = realloc(cards, numCards * sizeof(CARD));
    if (cards == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    strcpy(cards[numCards - 1].cardId, cardId);
    GetInputInt("Enter 1 to grant access or 0 to deny access: ", &cards[numCards - 1].hasAccess);

    GetInput("Enter entry date: ", cards[numCards - 1].entryDate, sizeof(cards[numCards - 1].entryDate));

    printf("Card number %s has been added to the system.\n", cardId);
}

void FakeTestScanCard() {
    printf("Enter the card number: ");
    char cardId[20];
    GetInput(" ", cardId, sizeof(cardId));

    int found = 0;

    for (int i = 0; i < numCards; i++) {
        if (strcmp(cards[i].cardId, cardId) == 0) {
            printf("Card number %s found in the system.\n", cardId);
            if (cards[i].hasAccess) {
                printf("Access granted. Green light.\n");
                OpenDoor();
            } else {
                printf("Access denied. Red light.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Card number %s not found in the system.\n", cardId);
    }
}

void AdminMenu() {
    while (1) {
        printf("Admin menu\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in the system\n");
        printf("3. Add/Remove access\n");
        printf("4. Exit\n");
        printf("5. Fake Test Scan Card\n");
        int sel;
        GetInputInt("Enter your choice: ", &sel);

        switch (sel) {
            case 1:
                OpenDoor();
                break;
            case 2:
                ListAllCards();
                break;
            case 3:
                AddRemoveAccess();
                break;
            case 4:
                CleanupSystem();
                printf("Exiting...\n");
                exit(0);
            case 5:
                FakeTestScanCard();
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}