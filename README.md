# Tienda de Gorras y Accesorios — Proyecto final de Patrones de Software

Aplicación de consola en C++ para gestionar una **tienda de gorras y accesorios**: registro de productos, inventario, ventas con descuentos e IVA, control de stock y reporte de ventas.

Curso: Patrones de Software (código 74362) · Cotecnova · 2026-2
Docente: Felipe Gutiérrez Isaza

## Integrantes y roles

| Integrante | Rol |
|---|---|
| Alejandro De La Rosa | Responsable de diseño |
| Laura Posada | Responsable de código |
| Emmanuel Bonilla | Responsable de modelado |

## Tipo de tienda

- **Versión 0:** tienda de gorras con tres tipos de producto: **Plana**, **Curva** y **Trucker**.
- **Versión 1:** la tienda amplía su catálogo a **gorras y accesorios**, agrupados en cuatro categorías: **Ropa** (camisas, conjuntos, sacos, medias), **Accesorio** (gorras, bolsos, canguros, billeteras), **Reloj** y **Colonia**.

El detalle del cliente y las historias de usuario están en [`docs/01_ficha_cliente.md`](docs/01_ficha_cliente.md).

## Patrones aplicados (versión 1)

| Grupo | Patrón | Uso en la tienda |
|---|---|---|
| Creacional | Factory Method | Crear los productos según su categoría |
| Estructural | Decorator | Aplicar descuento por pago, promoción e IVA al total, capa por capa |
| Comportamiento | Strategy | Formas de pago intercambiables: efectivo, tarjeta y Nequi |

La justificación está en [`docs/03_justificacion_patrones.md`](docs/03_justificacion_patrones.md) y el análisis de la versión 0 en [`docs/02_antipatrones.md`](docs/02_antipatrones.md).

## Funciones

| # | Función |
|---|---|
| F1 | Registrar productos (código, nombre, precio, stock y tipo o categoría) |
| F2 | Consultar el inventario |
| F3 | Registrar una venta con varios productos y cantidades |
| F4 | Aplicar descuentos por forma de pago, promoción e IVA |
| F5 | Descontar el stock y avisar cuando queda por debajo del mínimo |
| F6 | Reporte de ventas y total vendido |

## Cómo compilar y ejecutar

### Versión 0 (sin patrones)

```bash
g++ -std=c++11 v0/tienda_v0.cpp -o tienda_v0
./tienda_v0
```

En Windows, el ejecutable se llama `tienda_v0.exe`. También se puede abrir `v0/tienda_v0.cpp` en ZinjaI o en Dev-C++ y ejecutarlo directamente.

La aplicación arranca con cuatro gorras de ejemplo para poder registrar ventas de inmediato.

### Versión 1 (con patrones)

```bash
g++ -std=c++11 v1/main.cpp -o tienda_v1
./tienda_v1
```

En ZinjaI o Dev-C++ basta con abrir y ejecutar `v1/main.cpp`; los archivos `.h` de la misma carpeta se incluyen solos.

La versión 1 arranca con seis productos de ejemplo, uno o dos por categoría. El archivo [`v1/salida_esperada.txt`](v1/salida_esperada.txt) muestra la ejecución completa del escenario de venta.

| Archivo | Contenido | Patrón |
|---|---|---|
| `v1/producto.h` | `Producto` y sus categorías: `Ropa`, `Accesorio`, `Reloj`, `Colonia` | Factory Method |
| `v1/creadores.h` | `CreadorProducto` y un creador por categoría | Factory Method |
| `v1/pagos.h` | `EstrategiaPago`: `PagoEfectivo`, `PagoTarjeta`, `PagoNequi` | Strategy |
| `v1/precio.h` | `Precio`, `PrecioBase` y los decoradores `ConDescuentoPago`, `ConPromocion`, `ConIVA` | Decorator |
| `v1/tienda.h` | La clase `Tienda` con las funciones F1 a F6 | Usa los tres |
| `v1/utilidades.h` | Lectura del teclado y formato de pesos | — |
| `v1/main.cpp` | Menú y registro de creadores y formas de pago | — |

## Estructura del repositorio

```
tienda_grupo_The_Emalu_King
├── README.md
├── .gitignore
├── docs/
│   ├── 01_ficha_cliente.md
│   ├── 02_antipatrones.md
│   ├── 03_justificacion_patrones.md
│   └── uml/
│       ├── clases_v0.png
│       ├── clases_v1.png
│       ├── secuencia_venta.png
│       └── comunicacion_venta.png
├── v0/
│   └── tienda_v0.cpp
└── v1/
    ├── main.cpp
    ├── tienda.h
    ├── producto.h
    ├── creadores.h
    ├── pagos.h
    ├── precio.h
    ├── utilidades.h
    └── salida_esperada.txt
```

## Entregas

| Entrega | Etiqueta |
|---|---|
| Seguimiento 1 · Análisis y versión 0 | `entrega-s1` |
| Seguimiento 2 · Diagnóstico y rediseño | `entrega-s2` |
| Seguimiento 3 · Versión 1 y modelado dinámico | `entrega-s3` |

## Herramientas utilizadas

- C++ (g++ / ZinjaI)
- Git y GitHub
- Mermaid y SVG para los diagramas UML
- Claude (asistente de IA) como apoyo en la construcción del código
