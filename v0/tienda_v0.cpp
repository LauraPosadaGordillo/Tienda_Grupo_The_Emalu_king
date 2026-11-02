#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

struct Gorra {
    int codigo;
    string nombre;
    double precio;
    int stock;
    string tipo;
    int stockMinimo;
};

struct ItemVenta {
    string nombre;
    int cantidad;
    double subtotal;
};

struct Venta {
    int numero;
    vector<ItemVenta> items;
    string formaPago;
    double total;
};

int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Debe escribir un numero entero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double leerDecimal(string mensaje) {
    double valor;
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

string leerTexto(string mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);
    return texto;
}

void pausa() {
    cout << "\nPresione ENTER para continuar...";
    string linea;
    getline(cin, linea);
}

class Tienda {
public:
    vector<Gorra> inventario;
    vector<Venta> ventas;
    int contadorVentas = 1;

    int buscarGorra(int codigo) {
        for (int i = 0; i < (int)inventario.size(); i++)
            if (inventario[i].codigo == codigo) return i;
        return -1;
    }

    void registrarGorra() {
        Gorra g;
        cout << "\n--- REGISTRAR GORRA ---\n";
        g.codigo = leerEntero("Codigo: ");
        if (buscarGorra(g.codigo) != -1) {
            cout << "Ya existe una gorra con ese codigo.\n";
            return;
        }
        g.nombre = leerTexto("Nombre: ");
        g.precio = leerDecimal("Precio: ");
        g.stock = leerEntero("Stock: ");
        int opcionTipo = leerEntero("Tipo (1. Plana  2. Curva  3. Trucker): ");

        switch (opcionTipo) {
            case 1:  g.tipo = "Plana";   g.stockMinimo = 5; break;
            case 2:  g.tipo = "Curva";   g.stockMinimo = 3; break;
            case 3:  g.tipo = "Trucker"; g.stockMinimo = 4; break;
            default:
                cout << "Tipo no valido. Se registra como Curva.\n";
                g.tipo = "Curva";
                g.stockMinimo = 3;
        }
        inventario.push_back(g);
        cout << "Gorra registrada correctamente.\n";
    }

    void consultarInventario() {
        cout << "\n--- INVENTARIO ---\n";
        if (inventario.empty()) {
            cout << "No hay gorras registradas.\n";
            return;
        }
        cout << left << setw(8) << "Codigo" << setw(22) << "Nombre"
             << setw(10) << "Tipo" << setw(12) << "Precio" << "Stock\n";
        for (int i = 0; i < (int)inventario.size(); i++) {
            Gorra g = inventario[i];
            cout << left << setw(8) << g.codigo << setw(22) << g.nombre
                 << setw(10) << g.tipo << "$" << setw(11) << fixed
                 << setprecision(0) << g.precio << g.stock << "\n";
        }
    }

    double aplicarDescuentoEImpuesto(double subtotal, string formaPago) {
        double total = subtotal;

        if (formaPago == "Efectivo") {
            total -= total * 0.10;
            cout << "Descuento por efectivo: 10%\n";
        } else if (formaPago == "Tarjeta") {
            total += total * 0.05;
            cout << "Recargo por tarjeta: 5%\n";
        } else if (formaPago == "Nequi") {
            total -= total * 0.05;
            cout << "Descuento por Nequi: 5%\n";
        } else {
            cout << "Sin descuento.\n";
        }

        if (subtotal > 200000) {
            total -= 10000;
            cout << "Promocion: -$10000 por compra mayor a $200000\n";
        }

        double iva = total * 0.19;
        cout << "IVA (19%): $" << fixed << setprecision(0) << iva << "\n";
        return total + iva;
    }

    void registrarVenta() {
        if (inventario.empty()) {
            cout << "\nNo hay gorras para vender.\n";
            return;
        }
        Venta v;
        v.numero = contadorVentas;
        double subtotal = 0;
        string otra = "s";

        cout << "\n--- REGISTRAR VENTA #" << v.numero << " ---\n";
        while (otra == "s" || otra == "S") {
            consultarInventario();
            int codigo = leerEntero("\nCodigo de la gorra: ");
            int pos = buscarGorra(codigo);

            if (pos == -1) {
                cout << "Codigo no encontrado.\n";
            } else {
                int cantidad = leerEntero("Cantidad: ");
                if (cantidad <= 0 || cantidad > inventario[pos].stock) {
                    cout << "Cantidad no valida o stock insuficiente.\n";
                } else {
                    ItemVenta item;
                    item.nombre = inventario[pos].nombre;
                    item.cantidad = cantidad;
                    item.subtotal = inventario[pos].precio * cantidad;
                    v.items.push_back(item);
                    subtotal += item.subtotal;

                    inventario[pos].stock -= cantidad;

                    if (inventario[pos].stock < inventario[pos].stockMinimo)
                        cout << "*** ALERTA: '" << inventario[pos].nombre
                             << "' quedo con " << inventario[pos].stock
                             << " unidades ***\n";
                }
            }
            otra = leerTexto("Agregar otra gorra? (s/n): ");
        }

        if (v.items.empty()) {
            cout << "Venta cancelada (sin productos).\n";
            return;
        }

        int opPago = leerEntero("\nForma de pago (1. Efectivo  2. Tarjeta  3. Nequi): ");
        if (opPago == 1)      v.formaPago = "Efectivo";
        else if (opPago == 2) v.formaPago = "Tarjeta";
        else if (opPago == 3) v.formaPago = "Nequi";
        else                  v.formaPago = "Otro";

        cout << "\nSubtotal: $" << fixed << setprecision(0) << subtotal << "\n";
        v.total = aplicarDescuentoEImpuesto(subtotal, v.formaPago);
        cout << "TOTAL A PAGAR: $" << v.total << "\n";

        ventas.push_back(v);
        contadorVentas++;
        cout << "Venta registrada.\n";
    }

    void reporteVentas() {
        cout << "\n--- REPORTE DE VENTAS ---\n";
        if (ventas.empty()) {
            cout << "No se han realizado ventas.\n";
            return;
        }
        double totalVendido = 0;
        for (int i = 0; i < (int)ventas.size(); i++) {
            cout << "\nVenta #" << ventas[i].numero << " (" << ventas[i].formaPago << ")\n";
            for (int j = 0; j < (int)ventas[i].items.size(); j++) {
                ItemVenta it = ventas[i].items[j];
                cout << "   " << it.cantidad << " x " << it.nombre << " = $"
                     << fixed << setprecision(0) << it.subtotal << "\n";
            }
            cout << "   Total venta: $" << ventas[i].total << "\n";
            totalVendido += ventas[i].total;
        }
        cout << "\nTOTAL VENDIDO: $" << totalVendido << "\n";
    }

    void cargarDatosIniciales() {
        inventario.push_back({101, "New Era Yankees", 120000, 10, "Plana", 5});
        inventario.push_back({102, "Nike Classic", 85000, 6, "Curva", 3});
        inventario.push_back({103, "Trucker Malla Negra", 45000, 8, "Trucker", 4});
        inventario.push_back({104, "Adidas Basica", 60000, 4, "Curva", 3});
    }
};

Tienda tienda;

int main() {
    tienda.cargarDatosIniciales();
    int opcion;
    do {
        cout << "\n====== TIENDA DE GORRAS ======\n";
        cout << "1. Registrar gorra\n";
        cout << "2. Consultar inventario\n";
        cout << "3. Registrar venta\n";
        cout << "4. Reporte de ventas\n";
        cout << "0. Salir\n";
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: tienda.registrarGorra(); pausa(); break;
            case 2: tienda.consultarInventario(); pausa(); break;
            case 3: tienda.registrarVenta(); pausa(); break;
            case 4: tienda.reporteVentas(); pausa(); break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);
    return 0;
}
