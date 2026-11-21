#ifndef CREADORES_H
#define CREADORES_H
#include "producto.h"
#include "utilidades.h"

// ============================================================
// PATRON FACTORY METHOD (creacional) - Creadores
// Corrige el antipatron #1 de la v0: el switch por tipo de
// producto en registrarGorra() (lineas 96-104).
//
// CreadorProducto declara el metodo fabrica crearProducto().
// Cada creador concreto decide que clase de Producto crea.
// Para una categoria nueva se agregan dos clases (el producto
// y su creador) sin modificar ninguna clase existente.
// ============================================================

class CreadorProducto {
public:
    virtual ~CreadorProducto() {}
    virtual string nombreCategoria() const = 0;
    // Metodo fabrica (Factory Method)
    virtual Producto* crearProducto(int codigo, string nombre, double precio, int stock) = 0;
};

class CreadorRopa : public CreadorProducto {
public:
    string nombreCategoria() const override { return "Ropa (camisas, conjuntos, sacos, medias)"; }
    Producto* crearProducto(int codigo, string nombre, double precio, int stock) override {
        string talla = leerTexto("Talla (S, M, L, XL): ");
        return new Ropa(codigo, nombre, precio, stock, talla);
    }
};

class CreadorAccesorio : public CreadorProducto {
public:
    string nombreCategoria() const override { return "Accesorio (gorras, bolsos, canguros, billeteras)"; }
    Producto* crearProducto(int codigo, string nombre, double precio, int stock) override {
        string material = leerTexto("Material: ");
        return new Accesorio(codigo, nombre, precio, stock, material);
    }
};

class CreadorReloj : public CreadorProducto {
public:
    string nombreCategoria() const override { return "Reloj"; }
    Producto* crearProducto(int codigo, string nombre, double precio, int stock) override {
        int garantia = leerNumero<int>("Garantia (meses): ");
        return new Reloj(codigo, nombre, precio, stock, garantia);
    }
};

class CreadorColonia : public CreadorProducto {
public:
    string nombreCategoria() const override { return "Colonia"; }
    Producto* crearProducto(int codigo, string nombre, double precio, int stock) override {
        int mililitros = leerNumero<int>("Mililitros: ");
        return new Colonia(codigo, nombre, precio, stock, mililitros);
    }
};

#endif
