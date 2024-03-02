#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"odczytywanie.h"

/*
  Funkcja "odczyt" s³u¿y do odczytywania danych z bazy danych i wyœwietlania ich w formie listy.
  1. Otwiera plik bazy danych w trybie odczytu binarnego ("rb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
  2. Inicjalizuje zmienne pomocnicze: i - indeks aktualnej ksi¹¿ki, num - numer pozycji na liœcie.
  3. Wyœwietla nag³ówek tabeli z informacjami o ksi¹¿kach.
  4. W pêtli while odczytuje kolejne struktury z pliku i wyœwietla ich dane.
     - Wyœwietla numer pozycji, tytu³, autorów, rok wydania, rodzaj ok³adki, liczbê stron i gatunek ksi¹¿ki.
     - Tworzy ³añcuch znakowy "autorzy_string" zawieraj¹cy imiona i nazwiska autorów, oddzielone przecinkami.
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