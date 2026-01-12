//Kalkulator temperatur
//Konsolowy przelicznik obslugujacy 3 skale, ma 6 typow konwersji, sprawdza czy temp jest fizycznie możliwa, zapisuje historie przeliczen i ja wyswietla, dziala w petli do wybrania odpowiedniej opcji, jest podzielony na plik glowny (logika programu) i naglowkowy (deklaracje funkcji i zmienne globalne)
#include <iostream>
#include <stdlib.h> 
#include <ctime>
using namespace std;
#include "headerFile.h"                                                 //dolaczanie pliku naglowkowego

//Funkcja pokazujaca menu
void menu() {
    cout << "1 - F -> C\n";
    cout << "2 - F -> K\n";
    cout << "3 - C -> F\n";
    cout << "4 - C -> K\n";
    cout << "5 - K -> C\n";
    cout << "6 - K -> F\n";
    cout << "7 - Pokaz historie (filtr)\n";
    cout << "8 - Usun wpis z historii\n";
    cout << "9 - Edytuj wpis z historii\n";
    cout << "10 - Losowe wypelnienie historii\n";
    cout << "-1 - Zakoncz program\n";
}

//Funkcja pauzujaca program do entera
void enter() {
    cout << "\nNacisnij enter zeby kontynuowac";
    cin.ignore();                                                       //czyszczenie buforu
    cin.get();                                                          //czekanie na enter
}

//Funkcja zapisujaca w historii
void save(double a, char ua, double b, char ub) {
    if (counter + 2 > MAX_HIS) {                                        //sprawdzenie czy jest miejsce w tablicach
        cout << "Historia jest pelna\n";
        return;
    }

    history[counter] = a;                                               //zapis temp poczatkowej
    unit[counter] = ua;

    history[counter + 1] = b;                                           //zapis wyniku
    unit[counter + 1] = ub;

    counter += 2;                                                       //przesuniecie licznika o 2
}

//Funkcja pokazujaca cala historie
void showhis() {
    if (counter == 0) {                                                 //jesli historia pusta
        cout << "Brak danych w historii\n";
        return;
    }

    for (int i = 0; i < counter; i += 2) {                              //wyswietlanie kolejnych par wartosci
        cout << (i / 2 + 1) << ". "
            << history[i] << unit[i]
            << " = "
            << history[i + 1] << unit[i + 1] << endl;
    }
}

//Funkcja pokazujaca historie z filtrem
void showhisfiltr() {
    int opt;
    cout << "1 - Tylko C -> inne\n";
    cout << "2 - Tylko F -> inne\n";
    cout << "3 - Tylko K -> inne\n";
    cout << "4 - Cala historia\n";
    cin >> opt;

    bool found = false;

    for (int i = 0; i < counter; i += 2) {

        if (opt == 4 ||
            (opt == 1 && unit[i] == 'C') ||
            (opt == 2 && unit[i] == 'F') ||
            (opt == 3 && unit[i] == 'K')) {

            cout << history[i] << unit[i]
                << " = "
                << history[i + 1] << unit[i + 1] << endl;

            found = true;
        }
    }

    if (!found)
        cout << "Brak danych\n";
}

//Funkcja usuwajaca wpis
void deletehis() {
    showhis();
    if (counter == 0) return;

    int n;
    cout << "Ktory wpis chcesz usunac? ";
    cin >> n;

    if (n < 1 || n > counter / 2) {
        cout << "Niepoprawny numer\n";
        return;
    }

    int idx = (n - 1) * 2;                                              //obliczanie indeksu w tablicy
    for (int i = idx + 2; i < counter; i++) {                           //przesuwanie danych
        history[i - 2] = history[i];
        unit[i - 2] = unit[i];
    }
    counter -= 2;
}

//Funkcja edytujaca wpis
void edithis() {
    showhis();
    if (counter == 0) return;

    int n;
    cout << "Ktory wpis chcesz edytowac? ";
    cin >> n;

    if (n < 1 || n > counter / 2) return;

    int idx = (n - 1) * 2;

    double val, res;
    char from, to;

    cout << "Nowa temperatura: ";
    cin >> val;

    cout << "Skala (C/F/K): ";
    cin >> from;

    cout << "Na co (C/F/K): ";
    cin >> to;

    if (from == 'C' && to == 'F') res = CtoF(val);                      //przeliczanie
    else if (from == 'C' && to == 'K') res = CtoK(val);
    else if (from == 'F' && to == 'C') res = FtoC(val);
    else if (from == 'F' && to == 'K') res = FtoK(val);
    else if (from == 'K' && to == 'C') res = KtoC(val);
    else if (from == 'K' && to == 'F') res = KtoF(val);
    else res = val;

    history[idx] = val;
    unit[idx] = from;
    history[idx + 1] = res;
    unit[idx + 1] = to;
}

//Funkcja losowego wypelniania
void random() {
    int n;
    cout << "Ile chcesz losowych wpisow? ";
    cin >> n;

    if (counter + n * 2 > MAX_HIS) {
        cout << "Za malo miejsca w historii\n";
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        char from = "CFK"[rand() % 3];
        int x = rand() % 1000;
        double temp = (double)x;

        char to;
        do {
            to = "CFK"[rand() % 3];
        } while (to == from);

        double res = temp;

        if (from == 'C' && to == 'F') res = CtoF(temp);
        if (from == 'C' && to == 'K') res = CtoK(temp);
        if (from == 'F' && to == 'C') res = FtoC(temp);
        if (from == 'F' && to == 'K') res = FtoK(temp);
        if (from == 'K' && to == 'C') res = KtoC(temp);
        if (from == 'K' && to == 'F') res = KtoF(temp);

        save(temp, from, res, to);
    }
}

//Funkcje przeliczajace temp
float FtoC(float F) { return (F - 32) * 5 / 9; }
float FtoK(float F) { return (F + 459.67f) * 5 / 9; }
float CtoF(float C) { return C * 9 / 5 + 32; }
float CtoK(float C) { return C + 273.15f; }
float KtoC(float K) { return K - 273.15f; }
float KtoF(float K) { return K * 9 / 5 - 459.67f; }

//Funkcja sprawdzajaca czy temp jest mozliwa
float check(float temp, char u) {
    if (u == 'C' && temp < -273.15f) return -999;
    if (u == 'F' && temp < -459.67f) return -999;
    if (u == 'K' && temp < 0) return -999;
    return temp;
}

//Funkcja main
int main() {
    int choice;                                                         //wybieranie opcji z menu
    double temp, result;                                                  

    while (true) {                                                      //petla nieskonczona do wybrania opcji 7
        system("cls");                                                  //czyszczenie ekranu
        menu();                                                         //pokazanie menu
        cin >> choice;

        if (choice == -1) break;                                        //koniec dzialania programu

        switch (choice) {                                               //opcje z menu
        case 1:
            cout << "Podaj F: ";
            cin >> temp;
            result = FtoC(temp);
            cout << temp << " F = " << result << " C\n";
            save(temp, 'F', result, 'C');
            break;

        case 2:
            cout << "Podaj F: ";
            cin >> temp;
            result = FtoK(temp);
            cout << temp << " F = " << result << " K\n";
            save(temp, 'F', result, 'K');
            break;

        case 3:
            cout << "Podaj C: ";
            cin >> temp;
            result = CtoF(temp);
            cout << temp << " C = " << result << " F\n";
            save(temp, 'C', result, 'F');
            break;

        case 4:
            cout << "Podaj C: ";
            cin >> temp;
            result = CtoK(temp);
            cout << temp << " C = " << result << " K\n";
            save(temp, 'C', result, 'K');
            break;

        case 5:
            cout << "Podaj K: ";
            cin >> temp;
            result = KtoC(temp);
            cout << temp << " K = " << result << " C\n";
            save(temp, 'K', result, 'C');
            break;

        case 6:
            cout << "Podaj K: ";
            cin >> temp;
            result = KtoF(temp);
            cout << temp << " K = " << result << " F\n";
            save(temp, 'K', result, 'F');
            break;

        case 7:
            showhisfiltr();
            break;

        case 8:
            deletehis();
            break;

        case 9:
            edithis();
            break;

        case 10:
            random();
            break;
        }

        enter();
    }

    return 0;
}
