#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_LEN 1000
#define MAX_NICK 24
#define MAX_ANSWER 4

// Struktura reprezentuj¹ca pytanie
typedef struct Pytanie {
    char tresc[MAX_LEN];
    char odpowiedzi[MAX_ANSWER][MAX_LEN];
    int poprawna_odpowiedz;
    struct Pytanie* next;
} Pytanie;

// Struktura reprezentuj¹ca graczy
typedef struct Gracz {
    char nickname[20];
    double score;
    double multiplier;
    struct Gracz* next;
} Gracz;