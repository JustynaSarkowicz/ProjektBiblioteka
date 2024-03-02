/* Projekt zaliczeniowy
Programowanie komputerow 
Informatyka I Ekonometria
I rok, stacjonarnie
Amelia Madej, Justyna Sarkowicz, Weronika Duda


Projekt 1. Baza ksi��ek w domowej biblioteczce(3 osoby).Projekt powinien obejmowa� nast�puj�c� funkcjonalno��: 
zapis ksi��ek do bazy i odczyt ksi��ek z bazy(baza ma by� przechowywana w pliku binarnym, 
nale�y utworzy� przyk�adow� baz� ksi��ek zawieraj�c� co najmniej 20 pozycji do testowania aplikacji),
dodawanie nowych ksi��ek(tytu�, lista autor�w, rok wydania, typ ok�adki(mi�kka, twarda), liczba stron, rodzaj
ksi��ki(fantastyka, dramat, komedia, itp.), wyszukiwanie ksi��ek(po nazwisku autora, wed�ug s�owa
kluczowego w tytule, itp.), usuwanie ksi��ek z bazy(operacja usuwania powinna wymaga� potwierdzenia),
sortowanie ksi��ek(po autorze, po tytule).Ksi��ki maj� by� wypisywane na konsol� w formie tabelki. */

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
//nowa: wska�nik na tablic� struktur, do kt�rej zostan� zapisane odczytane dane

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