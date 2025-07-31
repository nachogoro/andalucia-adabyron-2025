# Introducción a la solución
En una ronda con $n$ participantes se realizarán $\frac{n}{2}$ combates, y por
cada combate habrá un ganador.

Si $n$ es impar, habrá $n+1$ participantes.

Podemos simplemente utilizar un bucle en el que calculamos el número de
combates de cada ronda, y lo añadimos a un acumulador. El bucle terminará
cuando sólo quede un único participante, que no requerirá ningún combate.


# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [A.cpp](src/A.cpp) | :x: |

