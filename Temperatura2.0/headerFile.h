#pragma once														//zabezpieczenie przed wielokrotnym dodaniem
#include <iostream>
const int MAX_HIS = 6;												//max liczba elementow w his

//Funkcje przeliczajace temp
float FtoC(float F);
float FtoK(float F);
float CtoF(float C);
float CtoK(float C);
float KtoC(float K);
float KtoF(float K);

//Funkcja sprawdzajaca temp
float check(float temp, char stopnie);

//Funkcje menu
void menu();														//pokazanie menu
void enter();														//pauza do entera

//Funkcje historii
void save(double a, char ua, double b, char ub);					//zapisywanie do his
void showhis();														//pokazanie calej his
void showhisfiltr();												//his z filtrem
void deletehis();													//usuwanie
void edithis();														//edycja
void random();														//losowe wypelnienie

//Zmienne globalne
double history[MAX_HIS];											//tablica his
char unit[MAX_HIS];													//tablica jednostek
int counter = 0;													//licznik zajetych miejsc tablicy


