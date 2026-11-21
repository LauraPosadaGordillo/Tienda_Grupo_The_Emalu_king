INFORME DE ANTIPATRONES - VERSIÓN 0
Archivo revisado: v0/tienda_v0.cpp (etiqueta entrega-s1, 264 líneas).
La versión 0 cumple las funciones F1 a F6, pero la hicimos sin aplicar ningún patrón. Para encontrar los problemas nos preguntamos en cada parte del código: si queremos agregar algo nuevo, ¿tenemos que modificar código que ya funciona? Cuando la respuesta fue sí, lo anotamos como problema de diseño.

RESUMEN
#	Problema	Líneas	Se corrige en la v1 con
1	switch por tipo de producto	96-104	Factory Method
2	if/else por forma de pago	128-139 y 198-201	Strategy
3	Descuento, promoción e IVA en un solo método	125-149	Decorator
4	Números mágicos	97-99, 129, 132, 135, 141-142, 146	Decorator y Strategy
5	Clase Dios	71-238	En parte
6	Alerta de stock dentro de la venta	183-186	No se corrige en esta entrega
7	Variable global	240	Se elimina en la v1 (variable local en main)
8	Código duplicado	30-42 y 44-56	Se corrige en la v1 con una función template

SWITCH POR TIPO DE PRODUCTO (líneas 96-104)
En registrarGorra() hay un switch que decide si la gorra es Plana, Curva o Trucker y le pone su stock mínimo.
El problema es que ahora la tienda va a vender también bolsos, medias, canguros, camisas, colonias, billeteras, relojes, conjuntos y sacos. Con este código, cada producto nuevo nos obliga a abrir registrarGorra() y agregar otro case. Además todos los productos usan el mismo struct Gorra, entonces no hay dónde guardar datos propios como la talla de una camisa o la garantía de un reloj.

IF/ELSE POR FORMA DE PAGO (líneas 128-139 y 198-201)
En aplicarDescuentoEImpuesto() se compara el texto "Efectivo", "Tarjeta" o "Nequi" con una cadena de if/else para saber qué descuento aplicar. Y en registrarVenta() se repite la misma lista para el menú de pago.
Si queremos agregar otra forma de pago, por ejemplo Daviplata, toca cambiar dos métodos distintos. Y si escribimos mal el nombre en uno de los dos, el descuento no se aplica y el compilador no nos avisa.

DESCUENTO, PROMOCIÓN E IVA EN UN SOLO MÉTODO (líneas 125-149)
aplicarDescuentoEImpuesto() hace todo en un orden fijo: primero el descuento por forma de pago, después la promoción de $10.000 y al final el IVA del 19%.
No se puede agregar, quitar ni cambiar el orden de un cargo sin reescribir el método completo. Si el dueño quiere una promoción nueva, como un 2x1 en medias, el método se llenaría de más condiciones.

NÚMEROS MÁGICOS
Hay valores escritos directamente en el código sin ningún nombre que diga qué son:
Líneas 97-99: stock mínimo 5, 3 y 4
Línea 129: 0.10 (descuento en efectivo)
Líneas 132 y 135: 0.05 (recargo con tarjeta y descuento con Nequi)
Líneas 141-142: 200000 y 10000 (promoción)
Línea 146: 0.19 (IVA)
Si cambia el IVA o la promoción, hay que buscar el número a mano dentro del código, y se corre el riesgo de cambiar otro número igual que significa otra cosa.

CLASE DIOS (líneas 71-238)
La clase Tienda hace todo: guarda el inventario y las ventas, registra productos, muestra el inventario, vende, calcula descuentos e impuestos, imprime alertas y saca el reporte.
Cualquier cambio en cualquier función termina tocando la misma clase, lo que la hace difícil de probar y de repartir entre los integrantes. En la v1 los patrones sacan de Tienda la creación de productos, las formas de pago y el cálculo del total, pero Tienda sigue organizando el flujo, por eso decimos que se corrige solo en parte.

ALERTA DE STOCK DENTRO DE LA VENTA (líneas 183-186)
Después de descontar el stock, la misma función registrarVenta() imprime la alerta con cout.
Si quisiéramos avisar de otra forma (al proveedor, por correo o en un archivo) habría que modificar la venta. Esto se corregiría con Observer, pero como patrón de comportamiento escogimos Strategy, así que lo dejamos anotado y no lo corregimos en esta entrega.

VARIABLE GLOBAL (línea 240)
Tienda tienda; está declarada como variable global, entonces cualquier parte del programa puede modificar todos los datos. Se podría convertir en Singleton, pero el Singleton también se considera muchas veces un antipatrón porque sigue siendo una variable global, así que no lo aplicamos. En la versión 1 lo resolvimos sin patrón: la tienda se declara como variable local dentro de main() (v1/main.cpp) y se pasa a las funciones que la necesitan.

CÓDIGO DUPLICADO (líneas 30-42 y 44-56)
leerEntero() y leerDecimal() son prácticamente iguales, solo cambia el tipo de dato. Si hay que arreglar algo, toca hacerlo en las dos. Esto se arregla con una función template, que no es un patrón de diseño. En la versión 1 las dos funciones se reemplazaron por una sola, leerNumero<T>(), en v1/utilidades.h.

ERRORES ENCONTRADOS EN LA VERSIÓN 0
La versión 0 no se modifica después del Seguimiento 1. Si encontramos errores de funcionamiento los vamos a anotar aquí.
Por ahora ninguno.
