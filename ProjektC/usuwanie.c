#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"odczytywanie.h"

/*
  Funkcja "usun" s�u�y do usuwania ksi��ki z bazy danych.
  1. Otwiera plik bazy danych w trybie odczytu binarnego ("rb"). Je�li operacja si� nie powiedzie, zwraca b��d.
  2. Tworzy tymczasowy plik "temp.csv" w trybie zapisu binarnego ("wb"). Je�li operacja si� nie powiedzie, zwraca b��d.
  3. Pobiera tytu� ksi��ki do usuni�cia od u�ytkownika.
  4. Przechodzi przez plik bazowy, odczytuje struktury i sprawdza, czy tytu� jest zgodny.
     - Je�li tytu� jest zgodny, ustawia flag� "found" na 1.
     - Je�li tytu� nie jest zgodny, zapisuje struktur� do tymczasowego pliku.
  5. Zamyka pliki bazowy i tymczasowy.
  6. Je�li flaga "found" jest ustawiona na 1:
     - Otwiera tymczasowy plik "temp.csv" w trybie odczytu binarnego ("rb"). Je�li operacja si� nie powiedzie, zwraca b��d.
     - Otwiera plik bazowy "baza.csv" w trybie zapisu binarnego ("wb"). Je�li operacja si� nie powiedzie, zwraca b��d.
     - Przechodzi przez tymczasowy plik, odczytuje struktury i zapisuje je do pliku bazowego.
     - Zamyka pliki bazowy i tymczasowy.
     - Wy�wietla komunikat o usuni�ciu ksi��ki.
  7. Je�li flaga "found" jest ustawiona na 0, wy�wietla komunikat o nieznalezieniu ksi��ki w bazie.
 */

void usun(char* nazwa, struct Ksiazka* nowa) {
	FILE* fp, * fp1;
	char tytul[200];
	int i = 0, potwierdzenie = 0;

	if (fopen_s(&fp, nazwa, "rb") != 0) {
		perror("Blad otwarcia pliku\n");
		return;
	}

	if (fopen_s(&fp1, "temp.csv", "wb")) {
		printf("Nie udalo sie utworzyc pliku tymczasowego.\n");
		fclose(fp);
		return;
	}

	printf("Wprowadz tytul ksiazki do usuniecia: ");
	fseek(stdin, 0, SEEK_END);
	fgets(tytul, sizeof(tytul), stdin);
	tytul[strcspn(tytul, "\n")] = '\0'; // Usuni�cie znaku nowej linii z ko�ca wczytanego tytu�u

	while (fread(&nowa[i], sizeof(struct Ksiazka), 1, fp)) {
		if (strcmp(nowa[i].tytul, tytul) == 0) {
			printf("Czy na pewno chcesz usunac ksiazke \"%s\"? (1 - tak, 0 - nie)\n", tytul);
			fseek(stdin, 0, SEEK_END);
			scanf_s("%d", &potwierdzenie);
			if (potwierdzenie == 1) {
				continue;
			}
		}
		else {
			fwrite(&nowa[i], sizeof(struct Ksiazka), 1, fp1);
		}
		++i;
	}

	fclose(fp);
	fclose(fp1);

	if (potwierdzenie == 1) {
		if (fopen_s(&fp1, "temp.csv", "rb")) {
			printf("Nie udalo sie otworzyc pliku tymczasowego.\n");
			return;
		}

		if (fopen_s(&fp, "baza.csv", "wb")) {
			printf("Nie udalo sie otworzyc pliku.\n");
			fclose(fp1);
			return;
		}

		while (fread(&nowa[i], sizeof(struct Ksiazka), 1, fp1)) {
			fwrite(&nowa[i], sizeof(struct Ksiazka), 1, fp);
		}

		fclose(fp);
		fclose(fp1);
		printf("Ksiazka zostala usunieta.\n");
	}
	else {
		printf("Nie znaleziono ksiazki w bazie.\n");
	}
}