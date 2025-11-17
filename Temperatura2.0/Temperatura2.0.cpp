//Przeliczanie temperatur upgrade 1

#include <iostream>
#include <stdlib.h> 
using namespace std;
#include "headerFile.h"

void menu() {
    cout << "1 - przelicz Fahr -> Celsius\n";
    cout << "2 - przelicz Fahr -> Kelwin\n";
    cout << "3 - przelicz Celsius -> Fahr\n";
    cout << "4 - przelicz Celsius -> Kelwin\n";
    cout << "5 - przelicz Kelwin -> Celsius\n";
    cout << "6 - przelicz Kelwin -> Fahr\n";
    cout << "7 - zakoncz dzialanie programu\n";
    cout << "8 - pokaz historie przeliczen\n";
}

void enter() {
    cout << "\nNacisnij enter zeby kontynuowac";
    cin.ignore();
    cin.get();
}

void save(double previous, char unitP, double next, char unitN) {
    if (counter + 1 >= 100) {
        counter = 0;
    }
    history[counter] = previous;
    unit[counter] = unitP;
    history[counter + 1] = next;
    unit[counter + 1] = unitN;
    counter += 2;
}

void show() {
    if (counter == 0) {
        cout << "Historia pusta\n";
        return;
    }

    for (int i = 0; i < counter; i += 2) {
        int nr = (i / 2) + 1;
        cout << "<" << nr << "> "
            << history[i] << unit[i]
            << " = "
            << history[i + 1] << unit[i + 1] << endl;
    }
}




float check(float temp, char stopnie) {
    switch (stopnie) {
    case 'K':
        if (temp < 0.0f)
            return -999.0f;
        break;
    case 'C':
        if (temp < -273.15f)
            return -999.0f;
        break;
    case 'F':
        if (temp < -459.67f)
            return -999.0f;
        break;
    }
    return temp;
}

float takeF() {
    float F;
    cout << "Podaj temperature w stopniach F: ";
    cin >> F;
    return F;
}

float takeC() {
    float C;
    cout << "Podaj temperature w stopniach C: ";
    cin >> C;
    return C;
}

float takeK() {
    float K;
    cout << "Podaj temperature w stopniach K: ";
    cin >> K;
    return K;
}

float FtoC(float F) { return (F - 32.0f) * 5.0f / 9.0f; }
float FtoK(float F) { return (F + 459.67f) * 5.0f / 9.0f; }
float CtoF(float C) { return C * 9.0f / 5.0f + 32.0f; }
float CtoK(float C) { return C + 273.15f; }
float KtoC(float K) { return K - 273.15f; }
float KtoF(float K) { return K * 9.0f / 5.0f - 459.67f; }







int main() {
    int choice;
    float temp, wynik;

    while (true) {
        system("cls");
        menu();
        cout << "Wybierz opcje: ";
        cin >> choice;

        if (choice == 7) {
            return 0;
        }

        if (choice == 8) {
            show();
            enter();
            continue;
        }

        switch (choice) {
        case 1:
            temp = takeF();
            temp = check(temp, 'F');
            if (temp == -999.0f) {
                cout << "Nie ma takiej temperatury\n";
                enter();
                break;
            }
            wynik = FtoC(temp);
            cout << temp << " F = " << wynik << " C\n";
            save(temp, 'F', wynik, 'C');
            enter();
            break;

        case 2:
            temp = takeF();
            temp = check(temp, 'F');
            if (temp == -999.0f) {
                cout << "Nie ma takiej temperatury\n";
                enter();
                break;
            }
            wynik = FtoK(temp);
            cout << temp << " F = " << wynik << " K\n";
            save(temp, 'F', wynik, 'K');
            enter();
            break;

        case 3:
            temp = takeC();
            temp = check(temp, 'C');
            if (temp == -999.0f) {
                cout << "Nie ma takiej temperatury\n";
                enter();
                break;
            }
            wynik = CtoF(temp);
            cout << temp << " C = " << wynik << " F\n";
            save(temp, 'C', wynik, 'F');
            enter();
            break;

        case 4:
            temp = takeC();
            temp = check(temp, 'C');
            if (temp == -999.0f) {
                cout << "Nie ma takiej temperatury\n";
                enter();
                break;
            }
            wynik = CtoK(temp);
            cout << temp << " C = " << wynik << " K\n";
            save(temp, 'C', wynik, 'K');
            enter();
            break;

        case 5:
            temp = takeK();
            temp = check(temp, 'K');
            if (temp == -999.0f) {
                cout << "Nie ma takiej temperatury\n";
                enter();
                break;
            }
            wynik = KtoC(temp);
            cout << temp << " K = " << wynik << " C\n";
            save(temp, 'K', wynik, 'C');
            enter();
            break;

        case 6:
            temp = takeK();
            temp = check(temp, 'K');
            if (temp == -999.0f) {
                cout << "Nie ma takiej temperatury\n";
                enter();
                break;
            }
            wynik = KtoF(temp);
            cout << temp << " K = " << wynik << " F\n";
            save(temp, 'K', wynik, 'F');
            enter();
            break;

        default:
            return 0;
        }
    }
}
