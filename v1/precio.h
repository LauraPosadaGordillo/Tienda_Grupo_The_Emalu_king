#ifndef PRECIO_H
#define PRECIO_H

#include "pagos.h"
#include "utilidades.h"

// ============================================================
// PATRON DECORATOR (estructural)
// Corrige el antipatron #3 de la v0: descuento, promocion e IVA
// amontonados en aplicarDescuentoEImpuesto() (lineas 125-149),
// y los numeros magicos (#4), que ahora son constantes con nombre.
//
// Precio es el componente. PrecioBase es el subtotal.
// DecoradorPrecio envuelve otro Precio y cada decorador concreto
// le aplica su propio cargo. El total se arma capa por capa.
// ============================================================

// Componente (interfaz)
class Precio {
public:
    virtual ~Precio() {}
    virtual double calcular() const = 0;
    virtual string detalle() const = 0;
};

// Componente concreto: el subtotal de la venta
class PrecioBase : public Precio {
    double subtotal;
public:
    PrecioBase(double subtotal) : subtotal(subtotal) {}
    double calcular() const override { return subtotal; }
    string detalle() const override { return "Subtotal: " + dinero(subtotal) + "\n"; }
};

// Decorador abstracto: ES un Precio y TIENE un Precio envuelto
class DecoradorPrecio : public Precio {
protected:
    Precio* envuelto;
public:
    DecoradorPrecio(Precio* envuelto) : envuelto(envuelto) {}
    ~DecoradorPrecio() { delete envuelto; }
    double calcular() const override { return envuelto->calcular(); }
    string detalle() const override { return envuelto->detalle(); }
};

// Decorador concreto: aplica la forma de pago elegida.
// Aqui se conectan Decorator y Strategy.
class ConDescuentoPago : public DecoradorPrecio {
    const EstrategiaPago* estrategia;
public:
    ConDescuentoPago(Precio* envuelto, const EstrategiaPago* estrategia)
        : DecoradorPrecio(envuelto), estrategia(estrategia) {}
    double calcular() const override {
        return estrategia->aplicar(envuelto->calcular());
    }
    string detalle() const override {
        return envuelto->detalle() + estrategia->descripcion() + ": " + dinero(calcular()) + "\n";
    }
};

// Decorador concreto: promocion por compras grandes
class ConPromocion : public DecoradorPrecio {
    double subtotalOriginal;
    static constexpr double MINIMO = 200000;
    static constexpr double DESCUENTO = 10000;
public:
    ConPromocion(Precio* envuelto, double subtotalOriginal)
        : DecoradorPrecio(envuelto), subtotalOriginal(subtotalOriginal) {}
    bool aplica() const { return subtotalOriginal > MINIMO; }
    double calcular() const override {
        double valor = envuelto->calcular();
        return aplica() ? valor - DESCUENTO : valor;
    }
    string detalle() const override {
        if (!aplica()) return envuelto->detalle();
        return envuelto->detalle() + "Promocion compra mayor a " + dinero(MINIMO)
               + " (-" + dinero(DESCUENTO) + "): " + dinero(calcular()) + "\n";
    }
};

// Decorador concreto: IVA
class ConIVA : public DecoradorPrecio {
    static constexpr double TASA = 0.19;
public:
    ConIVA(Precio* envuelto) : DecoradorPrecio(envuelto) {}
    double calcular() const override {
        return envuelto->calcular() * (1 + TASA);
    }
    string detalle() const override {
        double iva = envuelto->calcular() * TASA;
        return envuelto->detalle() + "IVA (19%): " + dinero(iva) + "\n";
    }
};

#endif
