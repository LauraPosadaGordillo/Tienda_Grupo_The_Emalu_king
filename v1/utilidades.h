#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

// Lee un numero y lo vuelve a pedir si el usuario escribe letras.
// Es una plantilla (template): sirve para int y para double, asi no se
// repite el mismo codigo dos veces como en la version 0.
template <typename T>
T leerNumero(string mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Debe escribir un numero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

inline string leerTexto(string mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);
    return texto;
}

inline void pausa() {
    cout << "\nPresione ENTER para continuar...";
    string linea;
    getline(cin, linea);
}

// Convierte un valor a texto con formato de pesos, por ejemplo $120000
inline string dinero(double valor) {
    ostringstream salida;
    salida << "$" << fixed << setprecision(0) << valor;
    return salida.str();
}

#endif
