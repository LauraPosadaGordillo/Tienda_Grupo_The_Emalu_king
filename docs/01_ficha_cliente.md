# Ficha del cliente

## Tipo de tienda

**Tienda de gorras y accesorios.** Un local pequeño que empezó vendiendo gorras de tres tipos (**planas**, **curvas** y **trucker**) y amplió su catálogo a accesorios y ropa. En la versión 1 los productos se agrupan en cuatro categorías:

| Categoría | Productos | Dato propio |
|---|---|---|
| Ropa | Camisas, conjuntos, sacos, medias | Talla |
| Accesorio | Gorras, bolsos, canguros, billeteras | Material |
| Reloj | Relojes | Garantía en meses |
| Colonia | Colonias | Mililitros |

## Necesidad que resuelve la aplicación

Hoy el dueño lleva el inventario y las ventas en un cuaderno. Eso le genera estos problemas:

- No sabe con certeza cuántas unidades le quedan de cada producto.
- Se le acaban los modelos que más se venden sin darse cuenta a tiempo.
- Calcula a mano los descuentos por forma de pago y el IVA, y a veces se equivoca.
- Al final del día le cuesta saber cuánto vendió.

La aplicación de consola registra los productos, controla el stock, calcula el total de cada venta con sus descuentos e impuestos, y muestra un reporte de lo vendido.

## Quiénes la usarán

| Usuario | Qué hace en la aplicación |
|---|---|
| **Administrador (dueño)** | Registra productos nuevos, revisa el inventario, recibe las alertas de stock bajo y consulta el reporte de ventas. |
| **Vendedor** | Consulta el inventario y registra las ventas de los clientes en la caja. |

## Reglas del negocio

- Cada producto tiene código, nombre, precio, stock, categoría y un dato propio de su categoría.
- En la versión 0 (solo gorras) el stock mínimo era Plana 5, Curva 3 y Trucker 4. En la versión 1 cada categoría tiene el suyo: Ropa 5, Accesorio 4, Colonia 3 y Reloj 2.
- Cada tipo tiene su propio stock mínimo: Plana 5, Curva 3 y Trucker 4.
- Formas de pago: **efectivo** (10 % de descuento), **tarjeta** (5 % de recargo) y **Nequi** (5 % de descuento).
- Promoción: las compras con subtotal mayor a $200.000 tienen $10.000 de descuento.
- A todas las ventas se les aplica el **IVA del 19 %**.

## Historias de usuario

| # | Historia de usuario | Función |
|---|---|---|
| HU1 | **Como** administrador **quiero** registrar un producto con su código, nombre, precio, stock y categoría **para** tenerlo disponible para la venta. | F1 |
| HU2 | **Como** vendedor **quiero** consultar el inventario con el precio y el stock de cada producto **para** saber qué puedo ofrecer al cliente. | F2 |
| HU3 | **Como** vendedor **quiero** registrar una venta con varios productos y sus cantidades **para** atender en una sola compra a un cliente que lleva más de un producto. | F3 |
| HU4 | **Como** vendedor **quiero** que el sistema aplique el descuento o recargo según la forma de pago **para** cobrar el valor correcto sin hacer cálculos a mano. | F4 |
| HU5 | **Como** administrador **quiero** que a cada venta se le sume el IVA y se aplique la promoción por compras grandes **para** cumplir con los impuestos y premiar a los clientes que compran más. | F4 |
| HU6 | **Como** administrador **quiero** que el stock se descuente automáticamente al vender **para** que el inventario siempre esté actualizado. | F5 |
| HU7 | **Como** administrador **quiero** recibir un aviso cuando un producto quede por debajo de su stock mínimo **para** pedirle más unidades al proveedor a tiempo. | F5 |
| HU8 | **Como** administrador **quiero** ver las ventas realizadas y el total vendido **para** conocer los ingresos del día. | F6 |
