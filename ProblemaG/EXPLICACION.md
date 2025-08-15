# Introducción a la solución

Una solución ingenua con ventana deslizante sería demasiado ineficiente: si
tenemos una cadena de $n$ nucleótidos y queremos analizar todas las
subsecuencias de longitudes en el rango $[K_{\text{min}}, K_{\text{max}}]$,
necesitaríamos comprobar $n \cdot (K_{\text{max}} - K_{\text{min}} + 1)$
ventanas distintas.

Para optimizar esto, podemos construir una estructura de suma prefija. Sea $s$
la cadena de entrada, y construyamos un vector $p$ tal que:

```math
p[i] = (\text{numA}, \text{numC}, \text{numG}, \text{numT})
```

donde cada componente indica cuántas veces ha aparecido cada nucleótido en el
prefijo $s[0, i]$. Esto nos permite calcular el recuento de nucleótidos en
cualquier subcadena $s[i, j]$ en tiempo constante, simplemente restando
$p[j] - p[i] + s[i]$.

Luego, para cada posición $i$ en la cadena, queremos contar cuántas
subsecuencias de longitud entre $K_{\text{min}}$ y $K_{\text{max}}$ que
empiezan en $i$ cumplen las condiciones impuestas:

- Contienen **al menos** $N$ nucleótidos de tipo G **y** C.
- Contienen **estrictamente menos de** $M$ nucleótidos de tipo A **y** T.

Esto se puede reinterpretar como una ventana deslizante cuyo extremo derecho
$j$ varía en el rango $[i + K_{\text{min}}, \min(i + K_{\text{max}}, L)]$.

En dicho rango de posibles $j$, podemos hacer dos búsquedas binarias:

1. **Primera posición `f` donde se han acumulado al menos $N$ nucleótidos G y
   C** (sólo a partir de ahí son válidas las subcadenas).
2. **Última posición `t` donde se no se han acumulado más de $M$ nucleótidos A
   y T** (a partir de ahí dejan de ser válidas las subcadenas).

El número de subcadenas válidas que empiezan en $i$ es entonces $\max(0, t - f + 1)$.

Realizamos esto para cada $i$ de $0$ a $L - K_{\text{min}}$, y acumulamos el total.

Gracias a las búsquedas binarias sobre una ventana acotada, el coste total es 
$O(n \cdot \log(K_{\text{max}} - K_{\text{min}} + 1))$.


# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [G.cpp](src/G.cpp) | :x:          |

