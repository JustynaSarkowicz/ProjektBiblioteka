#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"odczytywanie.h"

/*
  Funkcja "usun" s³u¿y do usuwania ksi¹¿ki z bazy danych.
  1. Otwiera plik bazy danych w trybie odczytu binarnego ("rb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
  2. Tworzy tymczasowy plik "temp.csv" w trybie zapisu binarnego ("wb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
  3. Pobiera tytu³ ksi¹¿ki do usuniêcia od u¿ytkownika.
  4. Przechodzi przez plik bazowy, odczytuje struktury i sprawdza, czy tytu³ jest zgodny.
     - Jeœli tytu³ jest zgodny, ustawia flagê "found" na 1.
     - Jeœli tytu³ nie jest zgodny, zapisuje strukturê do tymczasowego pliku.
  5. Zamyka pliki bazowy i tymczasowy.
  6. Jeœli flaga "found" jest ustawiona na 1:
     - Otwiera tymczasowy plik "temp.csv" w trybie odczytu binarnego ("rb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
     - Otwiera plik bazowy "baza.csv" w trybie zapisu binarnego ("wb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
     - Przechodzi przez tymczasowy plik, odczytuje struktury i zapisuje je do pliku bazowego.
     - Zamyka pliki bazowy i tymczasowy.
     - Wyœwietla komunikat o usuniêciu ksi¹¿ki.
  7. Jeœli flaga "found" jest ustawiona na 0, wyœwietla komunikat o nieznalezieniu ksi¹¿ki w bazie.
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
	tytul[strcspn(tytul, "\n")] = '\0'; // Usuniêcie znaku nowej linii z koñca wczytanego tytu³u

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