#ifndef PAGOS_H
#define PAGOS_H

#include <string>
using namespace std;

// ============================================================
// PATRON STRATEGY (comportamiento)
// Corrige el antipatron #2 de la v0: el if/else por forma de
// pago (lineas 128-139 y 198-201).
//
// EstrategiaPago es la interfaz. Cada forma de pago es una
// estrategia intercambiable. Para una forma de pago nueva se
// agrega una clase y se registra en main(), sin modificar
// la tienda ni el calculo del total.
// ============================================================

class EstrategiaPago {
public:
    virtual ~EstrategiaPago() {}
    virtual string nombre() const = 0;
    virtual string descripcion() const = 0;
    virtual double aplicar(double monto) const = 0;
};

class PagoEfectivo : public EstrategiaPago {
    static constexpr double DESCUENTO = 0.10;
public:
    string nombre() const override { return "Efectivo"; }
    string descripcion() const override { return "Descuento por efectivo (10%)"; }
    double aplicar(double monto) const override { return monto * (1 - DESCUENTO); }
};

class PagoTarjeta : public EstrategiaPago {
    static constexpr double RECARGO = 0.05;
public:
    string nombre() const override { return "Tarjeta"; }
    string descripcion() const override { return "Recargo por tarjeta (5%)"; }
    double aplicar(double monto) const override { return monto * (1 + RECARGO); }
};

class PagoNequi : public EstrategiaPago {
    static constexpr double DESCUENTO = 0.05;
public:
    string nombre() const override { return "Nequi"; }
    string descripcion() const override { return "Descuento por Nequi (5%)"; }
    double aplicar(double monto) const override { return monto * (1 - DESCUENTO); }
};

#endif
