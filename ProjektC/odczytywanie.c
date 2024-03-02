#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"odczytywanie.h"

/*
  Funkcja "odczyt" s�u�y do odczytywania danych z bazy danych i wy�wietlania ich w formie listy.
  1. Otwiera plik bazy danych w trybie odczytu binarnego ("rb"). Je�li operacja si� nie powiedzie, zwraca b��d.
  2. Inicjalizuje zmienne pomocnicze: i - indeks aktualnej ksi��ki, num - numer pozycji na li�cie.
  3. Wy�wietla nag��wek tabeli z informacjami o ksi��kach.
  4. W p�tli while odczytuje kolejne struktury z pliku i wy�wietla ich dane.
     - Wy�wietla numer pozycji, tytu�, autor�w, rok wydania, rodzaj ok�adki, liczb� stron i gatunek ksi��ki.
     - Tworzy �a�cuch znakowy "autorzy_string" zawieraj�cy imiona i nazwiska autor�w, oddzielone przecinkami.
  5. Zamyka plik bazy danych.
 */

void odczyt(char* nazwa, struct Ksiazka* nowa) {
	FILE* fp;
	if (fopen_s(&fp, nazwa, "rb") != 0) {
		perror("Blad\n");
		return;
	}

	int i = 0, num = 1;

	printf("\n\n Lista wszystkich ksiazek: \n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|%-8s |%-45s| %-65s| %-15s| %-15s| %-15s| %-28s|\n", "Numer", "Tytul", "Autor(rzy)", "Rok wydania", "Okladka", "Liczba stron", "Rodzaj");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


	while (fread(&nowa[i], sizeof(struct Ksiazka), 1, fp) == 1) {
		printf("  %-8d %-45s ", num, nowa[i].tytul);
		char autor[30];
		char autorzy_string[200] = "";
		for (int j = 0; j < nowa[i].liczba_autorow; ++j) {
			sprintf_s(autor, 30, "%s", nowa[i].autorzy[j]);
			strcat_s(autorzy_string, 200, autor);
			strcat_s(autorzy_string, 200, ", ");
		}
		printf("%-67s", autorzy_string);
		printf(" %-15d  %-15s  %-15d  %-30s ", nowa[i].rok_wydania, nowa[i].okladka, nowa[i].liczba_stron, nowa[i].rodzaj);
		printf("\n");

		i++;
		num++;
	}
	fclose(fp);
}