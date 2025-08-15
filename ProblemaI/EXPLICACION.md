# Introducción a la solución
Dado un jardín con dos filas de flores y $M$ columnas, cada flor tiene un valor
de esplendor. Ada debe recolectar flores siguiendo estas dos reglas:

1. No puede recolectar dos flores consecutivas en la misma fila.
2. No puede recolectar dos flores que estén enfrentadas en la misma columna
   (es decir, no puede tomar ambas flores en una misma columna).

El objetivo es maximizar la cantidad total de esplendor recolectado cumpliendo ambas restricciones.

Podemos resolver este problema eficientemente con **programación dinámica**.
Observamos que para cada columna podemos tomar tres decisiones posibles:
- Tomar la flor de la fila superior.
- Tomar la flor de la fila inferior.
- No tomar ninguna flor.

Definimos dos vectores:

- `dp_top[i]`: el máximo esplendor que se puede recolectar tomando la flor de
  la fila superior en la columna $i$.
- `dp_bot[i]`: lo mismo, pero tomando la de la fila inferior.

## Casos base

- $dp_{\text{top}}[0] = \text{top}[0]$
- $dp_{\text{bot}}[0] = \text{bot}[0]$
  
Para la columna $i = 1$, la única opción válida es tomar la flor opuesta a la que se tomó en $i = 0$:

- $dp_{\text{top}}[1] = \text{bot}[0] + \text{top}[1]$
- $dp_{\text{bot}}[1] = \text{top}[0] + \text{bot}[1]$

## Transiciones dinámicas

A partir de $i = 2$ en adelante:

```math
\begin{align*}
    dp_{\text{top}}[i] &= \max(dp_{\text{bot}}[i-1],\ dp_{\text{bot}}[i-2]) + \text{top}[i] \\
    dp_{\text{bot}}[i] &= \max(dp_{\text{top}}[i-1],\ dp_{\text{top}}[i-2]) + \text{bot}[i]
\end{align*}
```

La idea es que para una columna concreta $i$, hay dos cuatro posibilidades:
1. Tomar la flor de la fila superior, si en la columna $i-1$ elegimos la
   fila inferior.
2. Tomar la flor de la fila superior, si en la columna $i-1$ no tomamos
   ninguna flor. Sólo tendría sentido no tomar ninguna flor en la columna
   $i-1$ si eso fuese incompatible con elegir la mejor opción en la columna
   $i-2$. Puesto que en la columna $i$ estamos tomando la flor de la fila
   superior, la mejor opción en $i-2$ debe ser la fila inferior (porque si la
   mejor opción de la columna $i-2$ fuese la fila superior, podríamos coger la
   fila inferior en $i-1$, que es el caso 1). Por lo tanto, esta opción se puede
   expresar como tomar la flor de la fila superior, si en la columna $i-2$
   tomamos la flor de la fila inferior.
3. Tomar la flor de la fila inferior, si en la columna anterior elegimos la
   fila superior.
4. Tomar la flor de la fila inferior, si en la columna $i-1$ no tomamos
   ninguna flor. Sólo tendría sentido no tomar ninguna flor en la columna
   $i-1$ si eso fuese incompatible con elegir la mejor opción en la columna
   $i-2$. Puesto que en la columna $i$ estamos tomando la flor de la fila
   inferior, la mejor opción en $i-2$ debe ser la fila superior (porque si la
   mejor opción de la columna $i-2$ fuese la fila inferior, podríamos coger la
   fila superior en $i-1$, que es el caso 3). Por lo tanto, esta opción se puede
   expresar como tomar la flor de la fila inferior, si en la columna $i-2$
   tomamos la flor de la fila superior.

## Resultado

El resultado final es el máximo entre las dos posibilidades en la última
columna:

$$
\max(dp_{\text{top}}[M-1],\ dp_{\text{bot}}[M-1])
$$

El coste es de $O(M)$ en tiempo y en espacio (aunque podemos reducir el coste
espacial a $O(1)$ si almacenásemos sólo las dos últimas columnas y no la tabla
entera).

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [I.cpp](src/I.cpp) | :x:          |

