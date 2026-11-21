#ifndef TIENDA_H
#define TIENDA_H

#include <vector>
#include "producto.h"
#include "creadores.h"
#include "pagos.h"
#include "precio.h"
#include "utilidades.h"

struct ItemVenta {
    Producto* producto;
    int cantidad;
    double subtotal;
};

struct Venta {
    int numero;
    vector<ItemVenta> items;
    string formaPago;
    double subtotal;
    double total;
};

// La tienda coordina el flujo. Ya no crea productos con un switch
// (Factory Method), no decide pagos con if/else (Strategy) y no
// calcula el total en un solo metodo (Decorator).
class Tienda {
    vector<Producto*> inventario;
    vector<Venta> ventas;
    vector<CreadorProducto*> creadores;   // Factory Method
    vector<EstrategiaPago*> pagos;        // Strategy
    int contadorVentas = 1;

    Producto* buscarProducto(int codigo) {
        for (Producto* p : inventario)
            if (p->getCodigo() == codigo) return p;
        return nullptr;
    }

public:
    ~Tienda() {
        for (Producto* p : inventario) delete p;
        for (CreadorProducto* c : creadores) delete c;
        for (EstrategiaPago* e : pagos) delete e;
    }

    void agregarCreador(CreadorProducto* creador) { creadores.push_back(creador); }
    void agregarPago(EstrategiaPago* pago) { pagos.push_back(pago); }
    void agregarProducto(Producto* producto) { inventario.push_back(producto); }

    // F1 - Registrar producto (usa Factory Method)
    void registrarProducto() {
        cout << "\n--- REGISTRAR PRODUCTO ---\n";
        int codigo = leerNumero<int>("Codigo: ");
        if (buscarProducto(codigo) != nullptr) {
            cout << "Ya existe un producto con ese codigo.\n";
            return;
        }
        string nombre = leerTexto("Nombre: ");
        double precio = leerNumero<double>("Precio: ");
        int stock = leerNumero<int>("Stock: ");

        cout << "Categoria:\n";
        for (int i = 0; i < (int)creadores.size(); i++)
            cout << "  " << i + 1 << ". " << creadores[i]->nombreCategoria() << "\n";
        int opcion = leerNumero<int>("Opcion: ");
        if (opcion < 1 || opcion > (int)creadores.size()) {
            cout << "Categoria no valida.\n";
            return;
        }

        // El creador elegido decide que clase de producto se crea
        Producto* nuevo = creadores[opcion - 1]->crearProducto(codigo, nombre, precio, stock);
        inventario.push_back(nuevo);
        cout << "Producto registrado: " << nuevo->categoria() << ".\n";
    }

    // F2 - Consultar inventario
    void consultarInventario() {
        cout << "\n--- INVENTARIO ---\n";
        if (inventario.empty()) {
            cout << "No hay productos registrados.\n";
            return;
        }
        cout << left << setw(8) << "Codigo" << setw(24) << "Nombre" << setw(11) << "Categoria"
             << setw(20) << "Detalle" << setw(10) << "Precio" << "Stock\n";
        for (Producto* p : inventario) {
            cout << left << setw(8) << p->getCodigo() << setw(24) << p->getNombre()
                 << setw(11) << p->categoria() << setw(20) << p->detalle()
                 << setw(10) << dinero(p->getPrecio()) << p->getStock() << "\n";
        }
    }

    // F3, F4 y F5 - Registrar venta (usa los tres patrones)
    void registrarVenta() {
        if (inventario.empty()) {
            cout << "\nNo hay productos para vender.\n";
            return;
        }
        Venta v;
        v.numero = contadorVentas;
        v.subtotal = 0;
        string otra = "s";

        cout << "\n--- REGISTRAR VENTA #" << v.numero << " ---\n";
        while (otra == "s" || otra == "S") {
            consultarInventario();
            int codigo = leerNumero<int>("\nCodigo del producto: ");
            Producto* p = buscarProducto(codigo);

            if (p == nullptr) {
                cout << "Codigo no encontrado.\n";
            } else {
                int cantidad = leerNumero<int>("Cantidad: ");
                if (cantidad <= 0 || cantidad > p->getStock()) {
                    cout << "Cantidad no valida o stock insuficiente.\n";
                } else {
                    ItemVenta item = {p, cantidad, p->getPrecio() * cantidad};
                    v.items.push_back(item);
                    v.subtotal += item.subtotal;

                    p->descontarStock(cantidad);   // F5
                    if (p->stockBajo())
                        cout << "*** ALERTA: '" << p->getNombre() << "' quedo con "
                             << p->getStock() << " unidades ***\n";
                }
            }
            otra = leerTexto("Agregar otro producto? (s/n): ");
        }

        if (v.items.empty()) {
            cout << "Venta cancelada (sin productos).\n";
            return;
        }

        // Strategy: el menu de pago se arma con las estrategias registradas
        cout << "\nForma de pago:\n";
        for (int i = 0; i < (int)pagos.size(); i++)
            cout << "  " << i + 1 << ". " << pagos[i]->nombre() << "\n";
        int opPago = leerNumero<int>("Opcion: ");
        while (opPago < 1 || opPago > (int)pagos.size())
            opPago = leerNumero<int>("Opcion no valida. Elija otra: ");
        EstrategiaPago* estrategia = pagos[opPago - 1];
        v.formaPago = estrategia->nombre();

        // Decorator: el total se arma capa por capa (F4)
        Precio* precio = new PrecioBase(v.subtotal);
        precio = new ConDescuentoPago(precio, estrategia);
        precio = new ConPromocion(precio, v.subtotal);
        precio = new ConIVA(precio);

        cout << "\n" << precio->detalle();
        v.total = precio->calcular();
        cout << "TOTAL A PAGAR: " << dinero(v.total) << "\n";
        delete precio;   // borra toda la cadena de decoradores

        ventas.push_back(v);
        contadorVentas++;
        cout << "Venta registrada.\n";
    }

    // F6 - Reporte de ventas
    void reporteVentas() {
        cout << "\n--- REPORTE DE VENTAS ---\n";
        if (ventas.empty()) {
            cout << "No se han realizado ventas.\n";
            return;
        }
        double totalVendido = 0;
        for (const Venta& v : ventas) {
            cout << "\nVenta #" << v.numero << " (" << v.formaPago << ")\n";
            for (const ItemVenta& it : v.items)
                cout << "   " << it.cantidad << " x " << it.producto->getNombre()
                     << " = " << dinero(it.subtotal) << "\n";
            cout << "   Total venta: " << dinero(v.total) << "\n";
            totalVendido += v.total;
        }
        cout << "\nTOTAL VENDIDO: " << dinero(totalVendido) << "\n";
    }
};

#endif
