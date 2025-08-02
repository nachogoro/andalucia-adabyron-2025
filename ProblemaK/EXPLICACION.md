# Introducción a la solución

Dado un conjunto de almacenes y un restaurante, hay que transportar todos los
ingredientes al restaurante, tal que:

1. El transporte conecta todos los nodos (almacenes + restaurante) con **el
   menor número de trayectos posible** (es decir, un árbol con $N$ aristas si
hay $N+1$ nodos).
2. La **mayor longitud de un trayecto** en esta red debe ser **la menor
   posible**.
3. La suma total de **satisfacción** de las conexiones elegidas (solo algunas
   tienen vistas, con un valor dado) debe ser **al menos $S$**.
4. Si no se puede alcanzar el nivel de satisfacción requerido con el número
   mínimo de trayectos, hay que imprimir `-1.00`.

## Modelado

- Cada nodo es un punto en el plano: el restaurante es el nodo `0`, y los
  almacenes son del `1` al `N`.
- Cada par de nodos tiene una distancia euclídea asociada.
- Solo algunas conexiones tienen satisfacción adicional por vistas, indicadas
  con su valor.

## Solución

Queremos un **árbol generador mínimo** (spanning tree) que:

- Conecte todos los nodos.
- Tenga *exactamente* $N$ aristas.
- El máximo peso de una arista (distancia euclídea $\text{dist}(a,b) =
  \sqrt{(X_a - X_b)^2 + (Y_a - Y_b)^2}$) sea el mínimo posible.
- Tenga una satisfacción total al menos $S$.

Haremos una **búsqueda binaria** sobre el valor máximo permitido de una arista
(la longitud máxima entre nodos), con un límite inferior de $0.0$ y superior de
$\sqrt{2} \cdot 10^4$, que continuará mientras la diferencia entre candidatos
sea mayor que $\epsilon = 10^-3$, para garantizar que el error sea menor que
$0.05$.

Para cada candidato:
1. Generamos un grafo solo con las aristas cuya distancia euclídea ≤ límite
   actual.
2. Ejecutamos un algoritmo de **Kruskal modificado** para encontrar un árbol de
   expansión:
    - Tomamos primero las aristas con mayor satisfacción (para cumplir el
      límite de satisfacción).
    - Mantenemos la suma total de satisfacción.
    - Si logramos conectar todos los nodos con exactamente $N$ aristas y el
      total de satisfacción ≥ $S$, este límite es factible.
3. La búsqueda binaria nos permite encontrar el mínimo posible valor del mayor
   trayecto.

### Búsqueda binaria

- Límite inferior: $0.0$
- Límite superior: la distancia máxima entre dos nodos del problema (≈ 14142 si
  el plano es de $[0,10^4] \times [0,10^4]$)
- Precisión: hasta dos decimales

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
|          |                        |

