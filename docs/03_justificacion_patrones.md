# Justificación de los patrones — Versión 1

## Combinación elegida

| Grupo | Patrón | Antipatrón de la v0 que corrige |
|---|---|---|
| Creacional | **Factory Method** | #1 `switch` por tipo de producto (líneas 96–104) |
| Estructural | **Decorator** | #3 Descuento, promoción e IVA amontonados (líneas 125–149) y #4 números mágicos |
| Comportamiento | **Strategy** | #2 `if/else` por forma de pago (líneas 128–139 y 198–201) |

Combinación del equipo: **Factory Method + Decorator + Strategy**.

## Cambio de alcance en la v1

En la versión 1 la tienda pasa de vender solo gorras a vender **gorras y accesorios**. Los productos se agrupan en cuatro categorías:

| Categoría | Productos | Dato propio |
|---|---|---|
| Ropa | Camisas, conjuntos, sacos, medias | Talla |
| Accesorio | Gorras, bolsos, canguros, billeteras | Material |
| Reloj | Relojes | Garantía en meses |
| Colonia | Colonias | Mililitros |

Este cambio es la mejor prueba del problema #1: en la v0, cada categoría nueva habría obligado a modificar el `switch`.

## 1. Factory Method (creacional)

**Problema que corrige.** En la v0, `registrarGorra()` decide el tipo con un `switch` y todos los productos usan el mismo `struct Gorra`.

**Cómo se aplica.**

- `Producto` es una clase abstracta con los datos comunes (código, nombre, precio, stock, stock mínimo) y los métodos virtuales `categoria()` y `detalle()`.
- `Ropa`, `Accesorio`, `Reloj` y `Colonia` heredan de `Producto`. Cada una agrega su dato propio y define su stock mínimo.
- `CreadorProducto` es la clase abstracta con el **método fábrica** `crearProducto()`.
- `CreadorRopa`, `CreadorAccesorio`, `CreadorReloj` y `CreadorColonia` implementan `crearProducto()` y piden el dato propio de su categoría.
- `Tienda` guarda una lista de creadores y usa el que el usuario elige, sin saber qué clase concreta se crea.

**Qué se gana.** Una categoría nueva, por ejemplo calzado, se agrega con dos clases nuevas (`Calzado` y `CreadorCalzado`) y una línea que la registra en la tienda. No se modifica ninguna clase existente.

## 2. Strategy (comportamiento)

**Problema que corrige.** En la v0, la forma de pago es un texto que se compara con `if/else` en dos métodos distintos.

**Cómo se aplica.**

- `EstrategiaPago` es la interfaz, con `aplicar(monto)` y `nombre()`.
- `PagoEfectivo` (10 % de descuento), `PagoTarjeta` (5 % de recargo) y `PagoNequi` (5 % de descuento) la implementan.
- `Tienda` guarda la lista de estrategias y arma el menú de pago a partir de ella, así que el menú ya no tiene los nombres escritos a mano.

**Qué se gana.** Una forma de pago nueva, por ejemplo Daviplata, es una clase nueva que se agrega a la lista. No se toca ni el menú ni el cálculo.

## 3. Decorator (estructural)

**Problema que corrige.** En la v0, un solo método aplica en orden fijo el descuento, la promoción y el IVA, con los valores escritos como números sueltos.

**Cómo se aplica.**

- `Precio` es la interfaz del componente, con `calcular()` y `detalle()`.
- `PrecioBase` es el componente concreto: devuelve el subtotal de la venta.
- `DecoradorPrecio` es el decorador abstracto: guarda un `Precio*` y le delega el cálculo.
- `ConDescuentoPago`, `ConPromocion` y `ConIVA` son los decoradores concretos. Cada uno toma el resultado del precio que envuelve y le aplica su propio cargo. Los valores (19 %, $200.000, $10.000) quedan como constantes con nombre dentro de cada decorador.
- El total se arma envolviendo capa por capa:
  `ConIVA( ConPromocion( ConDescuentoPago( PrecioBase(subtotal), estrategia ) ) )`

**Qué se gana.** Una promoción nueva, por ejemplo un 2×1 en medias, es un decorador nuevo que se agrega a la cadena. Quitar o reordenar un cargo es cambiar cómo se envuelven las capas, sin reescribir el cálculo.

## Cómo se integran en el flujo de venta

Los tres patrones participan en **registrar una venta**, el flujo principal de la aplicación:

1. **Factory Method:** los productos que se venden fueron creados por los creadores. La venta trabaja con `Producto*`, sin saber si es ropa, un reloj o una colonia.
2. **Strategy:** al cobrar, el usuario escoge una `EstrategiaPago` de la lista.
3. **Decorator:** la venta arma la cadena de decoradores sobre el subtotal. El decorador `ConDescuentoPago` **recibe la estrategia elegida** y la usa para calcular su capa.

Los patrones comparten abstracciones y se pasan objetos entre sí: el subtotal sale de los `Producto` que creó la fábrica, y el objeto que produce Strategy es usado por Decorator.

**Qué pasaría si se retirara cada uno:**

| Si se retira… | Vuelve a aparecer |
|---|---|
| Factory Method | Un `switch` por categoría para crear productos (antipatrón #1) |
| Strategy | Un `if/else` por forma de pago dentro de `ConDescuentoPago` y del menú (antipatrón #2) |
| Decorator | Un método que aplica todos los cargos en orden fijo con números sueltos (antipatrones #3 y #4) |

## Cambio en vivo de la sustentación

Con este diseño, cada cambio que puede pedir el profesor se resuelve agregando una clase:

| Cambio pedido | Qué se agrega |
|---|---|
| Nuevo tipo de producto | Una clase hija de `Producto` y su `Creador` |
| Nueva forma de pago | Una clase que implementa `EstrategiaPago` |
| Nueva promoción o impuesto | Un decorador nuevo que hereda de `DecoradorPrecio` |
