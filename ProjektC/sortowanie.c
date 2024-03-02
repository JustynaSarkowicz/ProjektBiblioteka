#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"odczytywanie.h"

/*
  Funkcja "sortuj_rosnaco" s³u¿y do sortowania ksi¹¿ek w pliku bazy danych w kolejnoœci rosn¹cej.
  1. Otwiera plik bazy danych w trybie odczytu binarnego ("rb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
  2. Pobiera rozmiar pliku i oblicza liczbê struktur w pliku.
  3. Odczytuje struktury z pliku i zapisuje je w tablicy.
  4. Zamyka plik bazy danych.
  5. Wyœwietla menu wyboru opcji sortowania.
  6. W zale¿noœci od wybranej opcji sortuje tablicê struktur.
	 - Opcja 1: Sortowanie po tytule
	 - Opcja 2: Sortowanie po autorze
	 - Jeœli wybrana opcja jest niepoprawna, zwraca b³¹d.
  7. Zapisuje je do pliku.
  8. Zamyka plik bazy danych.
 */

void sortuj_rosnaco(const char* nazwa, struct Ksiazka* nowa)
{
	int num = 1, opcja, rozmiar = sizeof(struct Ksiazka);;

	FILE* fp;
	if (fopen_s(&fp, nazwa, "rb") != 0) {
		perror("Blad\n");
		return;
	}
	fseek(fp, 0, SEEK_END);

	int n = ftell(fp) / rozmiar;

	rewind(fp);

	for (int i = 0; i < n; ++i) {
		fread(&nowa[i], rozmiar, 1, fp);
	}

	fclose(fp);

	printf("\nWybierz opcje sortowania:\n");
	printf("1. Sortuj po tytule\n");
	printf("2. Sortuj po autorze\n");
	printf("Wybierz opcje: ");
	scanf_s("%d", &opcja);

	switch (opcja) {
	case 1:
		// Sortowanie po tytule
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (strcmp(nowa[i].tytul, nowa[j].tytul) > 0) {
					struct Ksiazka temp = nowa[i];
					nowa[i] = nowa[j];
					nowa[j] = temp;
				}
			}
		}
		printf("Posortowano ksiazki po tytule rosnaco.\n");
		break;

	case 2:
		// Sortowanie po autorze
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (strcmp(nowa[i].autorzy[0], nowa[j].autorzy[0]) > 0) {
					struct Ksiazka temp = nowa[i];
					nowa[i] = nowa[j];
					nowa[j] = temp;
				}
			}
		}
		printf("Posortowano ksiazki po autorze rosnaco.\n");
		break;

	default:
		printf("Niepoprawna opcja sortowania.\n");
		return;
	}

	if (fopen_s(&fp, nazwa, "wb") != 0) {
		perror("Blad\n");
		return;
	}

	for (int i = 0; i < n; ++i) {
		fwrite(&nowa[i], sizeof(struct Ksiazka), 1, fp);
	}
	fclose(fp);
}

void sortuj_malejaco(const char* nazwa, struct Ksiazka* nowa)
{
	int num = 1, rozmiar = sizeof(struct Ksiazka);


	FILE* fp;
	if (fopen_s(&fp, nazwa, "rb") != 0) {
		perror("Blad\n");
		return;
	}
	fseek(fp, 0, SEEK_END);

	int n = ftell(fp) / rozmiar;
	rewind(fp);
	for (int i = 0; i < n; ++i) {
		fread(&nowa[i], rozmiar, 1, fp);
	}
	fclose(fp);
	printf("\nWybierz opcje sortowania:\n");
	printf("1. Sortuj po tytule\n");
	printf("2. Sortuj po autorze\n");
	printf("Wybierz opcje: ");
	int opcja;
	scanf_s("%d", &opcja);

	switch (opcja) {
	case 1:
		// Sortowanie po tytule
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (strcmp(nowa[i].tytul, nowa[j].tytul) < 0) {
					struct Ksiazka temp = nowa[i];
					nowa[i] = nowa[j];
					nowa[j] = temp;
				}
			}
		}
		printf("Posortowane ksiazki po tytule malejaco.\n");
		break;

	case 2:
		// Sortowanie po autorze
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (strcmp(nowa[i].autorzy[0], nowa[j].autorzy[0]) < 0) {
					struct Ksiazka temp = nowa[i];
					nowa[i] = nowa[j];
					nowa[j] = temp;
				}
			}
		}
		printf("Posortowano ksiazki po autorze malejaco.\n");
		break;

	default:
		printf("Niepoprawna opcja sortowania.\n");
		return;
	}

	if (fopen_s(&fp, nazwa, "wb") != 0) {
		perror("Blad\n");
		return;
	}

	for (int i = 0; i < n; ++i) {
		fwrite(&nowa[i], sizeof(struct Ksiazka), 1, fp);
	}
	fclose(fp);
}
