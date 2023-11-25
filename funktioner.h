#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

typedef struct {
    char cardId[20];
    int hasAccess;
    char entryDate[20];
} CARD;

void InitializeSystem();
void CleanupSystem();
void OpenDoor();
void ListAllCards();
void AddRemoveAccess();
void FakeTestScanCard();
void AdminMenu();

#endif