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
| F1 | Registrar gorras (código, nombre, precio, stock y tipo) |
| F2 | Consultar el inventario |
| F3 | Registrar una venta con varias gorras y cantidades |
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
│       └── clases_v1.png
└── v0/
    └── tienda_v0.cpp
```

## Entregas

| Entrega | Etiqueta |
|---|---|
| Seguimiento 1 · Análisis y versión 0 | `entrega-s1` |
| Seguimiento 2 · Diagnóstico y rediseño | `entrega-s2` |

## Herramientas utilizadas

- C++ (g++ / ZinjaI)
- Git y GitHub
- Mermaid para el diagrama de clases
- Claude (asistente de IA) como apoyo en la construcción del código
