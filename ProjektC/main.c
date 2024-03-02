/* Projekt zaliczeniowy
Programowanie komputerow 
Informatyka I Ekonometria
I rok, stacjonarnie
Amelia Madej, Justyna Sarkowicz, Weronika Duda


Projekt 1. Baza ksi¹¿ek w domowej biblioteczce(3 osoby).Projekt powinien obejmowaæ nastêpuj¹c¹ funkcjonalnoœæ: 
zapis ksi¹¿ek do bazy i odczyt ksi¹¿ek z bazy(baza ma byæ przechowywana w pliku binarnym, 
nale¿y utworzyæ przyk³adow¹ bazê ksi¹¿ek zawieraj¹c¹ co najmniej 20 pozycji do testowania aplikacji),
dodawanie nowych ksi¹¿ek(tytu³, lista autorów, rok wydania, typ ok³adki(miêkka, twarda), liczba stron, rodzaj
ksi¹¿ki(fantastyka, dramat, komedia, itp.), wyszukiwanie ksi¹¿ek(po nazwisku autora, wed³ug s³owa
kluczowego w tytule, itp.), usuwanie ksi¹¿ek z bazy(operacja usuwania powinna wymagaæ potwierdzenia),
sortowanie ksi¹¿ek(po autorze, po tytule).Ksi¹¿ki maj¹ byæ wypisywane na konsolê w formie tabelki. */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "dodawanie.h"
#include "odczytywanie.h"
#include "sortowanie.h"
#include "usuwanie.h"
#include "wyszukiwanie.h"
#include "Struktura.h"



//Zastosowane parametry funkcji:
//nazwa: nazwa pliku bazy danych
//nowa: wskaŸnik na tablicê struktur, do której zostan¹ zapisane odczytane dane

int main() {
	int wybor;
	char nazwa[20];


	printf("Aby wyswietlic testowa baze biblioteczki ksiazek nalezy jako nazwe pliku podac: \"baza.csv\"\n\n");
	printf("Podaj nazwe pliku binarnego: ");
	scanf_s("%s", nazwa, (unsigned int)sizeof(nazwa));
	do {
		printf("1. Dodaj ksiazke\n");
		printf("2. Odczytaj ksiazki z bazy danych\n");
		printf("3. Wyszukaj ksiazki z bazy danych\n");
		printf("4. Sortuj ksiazki rosnaco\n");
		printf("5. Sortuj ksiazki malejaco\n");
		printf("6. Usun ksiazke\n");
		printf("7. Zamknij program\n");
		printf("Wybierz program: ");
		scanf_s("%d", &wybor);

		switch (wybor) {
		case 1:
			dodaj(nazwa);
			break;
		case 2:
			odczyt(nazwa, nowa);
			break;
		case 3:
			wyszukaj(nazwa, nowa);
			break;
		case 4:
			sortuj_rosnaco(nazwa, nowa);
			odczyt(nazwa, nowa);
			break;
		case 5:
			sortuj_malejaco(nazwa, nowa);
			odczyt(nazwa, nowa);
			break;
		case 6:
			usun(nazwa, nowa);
			break;
		case 7:
			return;
		}	
		printf("\n\n");

	} while (wybor != 0);

	return 0;
}