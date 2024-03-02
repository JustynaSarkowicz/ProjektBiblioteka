#pragma once

#define MAX_BOOKS 40
#define MAX_AUTHORS 20
#define MAX_TITLE 50
#define MAX_AUTHOR_NAME 50
#define MAX_RODZAJ 50

struct Ksiazka {

	char tytul[MAX_TITLE];
	int liczba_autorow;
	char autorzy[MAX_AUTHORS][MAX_AUTHOR_NAME];
	int rok_wydania;
	char okladka[8];
	int liczba_stron;
	char rodzaj[MAX_RODZAJ];


}nowa[MAX_BOOKS];