#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
using namespace std;

// ============================================================
// PATRON FACTORY METHOD (creacional) - Productos
// Producto es la clase abstracta que crean las fabricas.
// Cada categoria es una clase hija con su propio dato y su
// propio stock minimo.
// ============================================================

class Producto {
protected:
    int codigo;
    string nombre;
    double precio;
    int stock;
    int stockMinimo;

public:
    Producto(int codigo, string nombre, double precio, int stock, int stockMinimo)
        : codigo(codigo), nombre(nombre), precio(precio),
          stock(stock), stockMinimo(stockMinimo) {}

    virtual ~Producto() {}

    int getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }
    int getStockMinimo() const { return stockMinimo; }

    void descontarStock(int cantidad) { stock -= cantidad; }
    bool stockBajo() const { return stock < stockMinimo; }

    // Metodos abstractos: cada categoria los implementa a su manera
    virtual string categoria() const = 0;
    virtual string detalle() const = 0;
};

// Producto concreto: camisas, conjuntos, sacos, medias
class Ropa : public Producto {
    string talla;
public:
    static const int STOCK_MINIMO = 5;
    Ropa(int codigo, string nombre, double precio, int stock, string talla)
        : Producto(codigo, nombre, precio, stock, STOCK_MINIMO), talla(talla) {}
    string categoria() const override { return "Ropa"; }
    string detalle() const override { return "Talla " + talla; }
};

// Producto concreto: gorras, bolsos, canguros, billeteras
class Accesorio : public Producto {
    string material;
public:
    static const int STOCK_MINIMO = 4;
    Accesorio(int codigo, string nombre, double precio, int stock, string material)
        : Producto(codigo, nombre, precio, stock, STOCK_MINIMO), material(material) {}
    string categoria() const override { return "Accesorio"; }
    string detalle() const override { return material; }
};

// Producto concreto: relojes
class Reloj : public Producto {
    int garantiaMeses;
public:
    static const int STOCK_MINIMO = 2;
    Reloj(int codigo, string nombre, double precio, int stock, int garantiaMeses)
        : Producto(codigo, nombre, precio, stock, STOCK_MINIMO), garantiaMeses(garantiaMeses) {}
    string categoria() const override { return "Reloj"; }
    string detalle() const override { return "Garantia " + to_string(garantiaMeses) + " meses"; }
};

// Producto concreto: colonias
class Colonia : public Producto {
    int mililitros;
public:
    static const int STOCK_MINIMO = 3;
    Colonia(int codigo, string nombre, double precio, int stock, int mililitros)
        : Producto(codigo, nombre, precio, stock, STOCK_MINIMO), mililitros(mililitros) {}
    string categoria() const override { return "Colonia"; }
    string detalle() const override { return to_string(mililitros) + " ml"; }
};

#endif
