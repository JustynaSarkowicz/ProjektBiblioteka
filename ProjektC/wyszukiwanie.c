#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"
#include"odczytywanie.h"

/*
  Funkcja "wyszukaj" s³u¿y do wyszukiwania i wyœwietlania ksi¹¿ek zgodnych z podanym s³owem kluczowym.
  1. Otwiera plik bazy danych w trybie odczytu binarnego ("rb"). Jeœli operacja siê nie powiedzie, zwraca b³¹d.
  2. Inicjalizuje zmienne pomocnicze: found - licznik znalezionych ksi¹¿ek, num - numer pozycji na liœcie.
  3. Wczytuje s³owo kluczowe od u¿ytkownika.
  4. Wyœwietla nag³ówek tabeli z informacjami o ksi¹¿kach.
  5. W pêtli while odczytuje kolejne struktury z pliku i sprawdza, czy zawieraj¹ podane s³owo kluczowe.
	 - Jeœli tytu³ / rodzaj ksi¹¿ki zawiera s³owo kluczowe, wyœwietla jej informacje.
	 - Aby sprawdziæ czy któryœ z autorów zawiera s³owo kluczowe, wykorzystywana jest dodatkowa funkcja
	   znalezieni_autorzy
  6. Zamyka plik bazy danych.
  7. Jeœli nie znaleziono ¿adnej ksi¹¿ki, wyœwietla odpowiedni komunikat.
 */

int znalezieni_autorzy(const struct Ksiazka* ksiazka, const char* key) {
	for (int i = 0; i < ksiazka[i].liczba_autorow; ++i) {
		if (strstr(ksiazka[i].autorzy[i], key) != NULL) {
			return 1;
		}
	}
	return 0;
}

void wyszukaj(const char* nazwa, struct Ksiazka* nowa) {
	int found = 0, num = 1, i = 0;
	char key[50];

	FILE* fp;
	if (fopen_s(&fp, nazwa, "rb") != 0) {
		perror("Blad\n");
		return;
	}

	printf("Podaj slowo kluczowe w tytule ('Alicja w Krainie Czarow' - klucz: Krainie ), nazwisko autora lub gatunek: ");
	fseek(stdin, 0, SEEK_END);
	fgets(key, sizeof(key), stdin);
	key[strcspn(key, "\n")] = '\0';

	printf("\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|%-8s |%-45s| %-65s| %-15s| %-15s| %-15s| %-20s|\n", "Numer", "Tytul", "Autor(rzy)", "Rok wydania", "Okladka", "Liczba stron", "Rodzaj");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	while (fread(nowa, sizeof(struct Ksiazka), 1, fp) > 0) {
		if (strstr(nowa[i].tytul, key) != NULL
			|| strstr(nowa[i].rodzaj, key) != NULL
			|| znalezieni_autorzy(nowa, key)) {
			printf("  %-8d %-45s ", num, nowa[i].tytul);
			char autorzy_string[200] = "";
			memset(autorzy_string, 0, sizeof(autorzy_string));
			for (int j = 0; j < nowa[i].liczba_autorow; ++j) {
				strcat_s(autorzy_string, 200, nowa[i].autorzy[j]);
				strcat_s(autorzy_string, 200, ", ");
			}
			printf("%-70s", autorzy_string);
			printf(" %-15d  %-15s  %-15d  %-20s ", nowa[i].rok_wydania, nowa[i].okladka, nowa[i].liczba_stron, nowa[i].rodzaj);
			printf("\n");
			found++;
		}
		i++;
		num++;
	}

	if (found == 0) {
		printf("\n\t\t\tNie znaleziono ksiazki.\n");
	}

	fclose(fp);
}
