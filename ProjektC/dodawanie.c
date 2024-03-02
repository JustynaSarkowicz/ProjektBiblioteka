#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"
#include"odczytywanie.h"

/*
 Funkcja "dodaj" s³u¿y do dodawania nowych ksi¹¿ek do bazy danych.
 1. Tworzy tablicê struktur "nowa" o rozmiarze MAX_BOOKS, przechowuj¹c¹ informacje o nowych ksi¹¿kach.
 2. Otwiera plik bazy danych w trybie do³¹czania ("ab"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
 3. Rozpoczyna pêtlê do-while, która pozwala na dodawanie wielu ksi¹¿ek.
 4. W ka¿dym przebiegu pêtli pyta u¿ytkownika o jedna z atrybutow ksi¹¿ki i zapisuje go w odpowiednim polu struktury "nowa[i]".
    - Zapisuje strukturê "nowa[i]" do pliku bazy danych.
    - Pyta u¿ytkownika, czy chce dodaæ kolejn¹ pozycjê. Jeœli wybór to 0, koñczy pêtlê.
 5. Zamyka plik bazy danych.
 6. Wyœwietla informacjê o pomyœlnym dodaniu ksi¹¿ki.
 */


void dodaj(char* nazwa) {
	int i = 0, opcja;
	FILE* fp;
	if (fopen_s(&fp, nazwa, "ab") != 0) {
		perror("Blad");
		return;
	}

	else {
		do {
			printf("Podaj tytul: ");
			fseek(stdin, 0, SEEK_END);
			scanf_s("%[^\n]", nowa[i].tytul, (unsigned int)sizeof(nowa[i].tytul));

			int j = 0;
			int liczba_autorow = 0;

			printf("Podaj liczbe autorow: ");
			fseek(stdin, 0, SEEK_END);
			scanf_s("%d", &nowa[i].liczba_autorow);
			for (int j = 0; j < nowa[i].liczba_autorow; ++j) {
				printf("Podaj imie i nazwisko autora: ");
				fseek(stdin, 0, SEEK_END);
				scanf_s("%[^\n]", nowa[i].autorzy[j], (unsigned int)sizeof(nowa[i].autorzy[j]));
			}

			printf("Podaj rok wydania: ");
			fseek(stdin, 0, SEEK_END);
			scanf_s("%d", &nowa[i].rok_wydania);
			printf("Podaj rodzaj okladki (miekka/twarda): ");
			fseek(stdin, 0, SEEK_END);
			scanf_s("%[^\n]", nowa[i].okladka, (unsigned int)sizeof(nowa[i].okladka));
			printf("Podaj liczbe stron: ");
			scanf_s("%d", &nowa[i].liczba_stron);
			printf("Podaj gatunek ksiazki: ");
			fseek(stdin, 0, SEEK_END);
			scanf_s("%[^\n]", nowa[i].rodzaj, (unsigned int)sizeof(nowa[i].rodzaj));
			fwrite(&nowa[i], sizeof(struct Ksiazka), 1, fp);
			printf("Czy chcesz dodac kolejna pozycje? (1 - tak, 0 - nie): ");
			fseek(stdin, 0, SEEK_END);
			scanf_s("%d", &opcja);
			i++;
		} while (opcja != 0);
	}
	fclose(fp);
	printf("Ksiazka zostala dodana pomyslnie.\n");
}