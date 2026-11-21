// ============================================================
//  TIENDA DE GORRAS Y ACCESORIOS - Version 1 (con patrones)
//  Factory Method + Decorator + Strategy
//  Compilar: g++ -std=c++11 v1/main.cpp -o tienda_v1
// ============================================================
#include "tienda.h"

// Productos de ejemplo para no empezar con el inventario vacio
void cargarDatosIniciales(Tienda& tienda) {
    tienda.agregarProducto(new Accesorio(101, "Gorra New Era Yankees", 120000, 10, "Algodon"));
    tienda.agregarProducto(new Accesorio(102, "Canguro Nike", 75000, 5, "Poliester"));
    tienda.agregarProducto(new Ropa(201, "Camisa Oversize", 65000, 8, "M"));
    tienda.agregarProducto(new Ropa(202, "Medias Adidas x3", 30000, 6, "Unica"));
    tienda.agregarProducto(new Reloj(301, "Reloj Casio", 180000, 3, 12));
    tienda.agregarProducto(new Colonia(401, "Colonia Hugo Boss", 210000, 4, 100));
}

int main() {
    Tienda tienda;

    // Factory Method: se registra un creador por categoria.
    // Una categoria nueva = una clase nueva + una linea aqui.
    tienda.agregarCreador(new CreadorRopa());
    tienda.agregarCreador(new CreadorAccesorio());
    tienda.agregarCreador(new CreadorReloj());
    tienda.agregarCreador(new CreadorColonia());

    // Strategy: se registra cada forma de pago.
    // Una forma de pago nueva = una clase nueva + una linea aqui.
    tienda.agregarPago(new PagoEfectivo());
    tienda.agregarPago(new PagoTarjeta());
    tienda.agregarPago(new PagoNequi());

    cargarDatosIniciales(tienda);

    int opcion;
    do {
        cout << "\n=== TIENDA DE GORRAS Y ACCESORIOS ===\n";
        cout << "1. Registrar producto\n";
        cout << "2. Consultar inventario\n";
        cout << "3. Registrar venta\n";
        cout << "4. Reporte de ventas\n";
        cout << "0. Salir\n";
        opcion = leerNumero<int>("Opcion: ");

        switch (opcion) {
            case 1: tienda.registrarProducto(); pausa(); break;
            case 2: tienda.consultarInventario(); pausa(); break;
            case 3: tienda.registrarVenta(); pausa(); break;
            case 4: tienda.reporteVentas(); pausa(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);
    return 0;
}
