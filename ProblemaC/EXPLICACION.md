# Introducción a la solución

La clave para resolver este problema es modelar el sistema de iluminación como
un grafo bipartito.

Cada vez que colocamos un farol en **modo horizontal**, este ilumina toda una
sección contigua de una fila (deteniéndose al encontrar una pared `X`), y de
forma análoga, un farol en **modo vertical** ilumina una sección contigua de
una columna.

Por tanto, podemos considerar cada sección horizontal y cada sección vertical
sin paredes como **nodos** de un grafo. Si un puesto de estudio (`T`) se
encuentra en la intersección de un segmento horizontal y uno vertical, puede
ser iluminado desde ambos, y por tanto se modela como una **arista** entre
dichos nodos.

La solución busca colocar el **mínimo número de faroles** necesario para
iluminar todos los puestos de estudio. Esto equivale a encontrar el **mínimo
conjunto de nodos** que cubre todas las aristas del grafo bipartito. Gracias al
**teorema de Kőnig**, en grafos bipartitos, este conjunto mínimo tiene el mismo
tamaño que un **emparejamiento máximo**.

## Modelado

- Recorremos la matriz para identificar *segmentos horizontales* y
  *verticales*. Cada grupo contiguo de celdas que no contiene paredes (`X`)
se considera un segmento y se le asigna un identificador único.
- Para cada celda que contiene una `T`, buscamos el identificador de su
  segmento horizontal $h$ y vertical $v$, y añadimos una arista entre
ellos en el grafo bipartito.

Es importante destacar que:
- Un puesto de estudio que se encuentre en una sección de solo una celda (por
  ejemplo, una `T` que está sola en su fila o columna) también se considera
una intersección válida, ya que igualmente se le asignan identificadores de
segmento horizontales y verticales. Esto asegura que ningún `T` quede sin
cubrir. Por ejemplo, un pasillo como `XOTOX` tendrá un único identificador
horizontal (para la secuencia horizontal `OTO`) y tres identificadores
verticales (uno para `O`, otro para `T` y otro para `O`). El horizontal
intersecta con el vertical de `T` y por tanto existe una arista entre ellos,
meintras que los otros dos identificadores verticales no tienen ninguna arista
incidente.
- Es posible (por simplicidad) asignar identificadores a segmentos que no
  contienen ninguna `T` (por ejemplo, pasillos vacíos o los dos identificadores
verticales del ejemplo del punto anterior). Estos segmentos no afectan al
algoritmo, ya que no tienen aristas que conecten con ellos.

## Resolución

Usamos un algoritmo estándar de emparejamiento máximo (como DFS o
Hopcroft-Karp) para encontrar el conjunto máximo de aristas disjuntas del
grafo. Esto nos da el número mínimo de faroles necesarios para iluminar todos
los `T`.

El algoritmo es eficiente, ya que cada celda se visita una vez durante
construcción y dos veces durante la segmentación; el emparejamiento del grafo
resultante puede resolverse en tiempo cercano a lineal en grafos bipartitos
dispersos.

## Algoritmo de emparejamiento máximo en grafos bipartitos

Un grafo bipartito es un grafo en el que los nodos pueden dividirse en dos
conjuntos disjuntos $U$ y $V$, y todas las aristas conectan un nodo de
$U$ con uno de $V$. En el problema de la biblioteca de Renatia, por
ejemplo, $U$ representa los segmentos horizontales y $V$ los segmentos
verticales, y se añade una arista entre un nodo de $U$ y uno de $V$ si
existe un puesto de estudio (`T`) en la intersección correspondiente.

El emparejamiento máximo en un grafo bipartito consiste en seleccionar el mayor
número posible de aristas tal que ningún nodo esté en más de una de ellas. En
otras palabras, se trata de emparejar tantos nodos como sea posible sin
repetirlos. El teorema de Kőnig garantiza que, en grafos bipartitos, el tamaño
del emparejamiento máximo es igual al tamaño del conjunto mínimo de nodos
necesarios para cubrir todas las aristas.

## Idea general del algoritmo

El algoritmo que se usa habitualmente para encontrar un emparejamiento máximo
en grafos bipartitos se basa en la búsqueda de **caminos aumentantes**.

Un camino aumentante es un camino que:

- comienza en un nodo libre del conjunto $U$,
- alterna aristas que **no están en el emparejamiento actual** con aristas que
  **sí lo están**,
- y termina en un nodo libre del conjunto $V$.

Al invertir el estado de las aristas a lo largo de ese camino (es decir, se
eliminan las aristas del emparejamiento y se añaden las que no lo estaban), se
obtiene un emparejamiento de tamaño mayor.

El algoritmo repite este proceso mientras sea posible encontrar caminos
aumentantes. Una vez que ya no hay ninguno, el emparejamiento actual es máximo.

## Estructura del procedimiento

1. **Inicialización**:  
   Se parte de un emparejamiento vacío. Cada nodo de $V$ está inicialmente
libre (no emparejado).

2. **Búsqueda en anchura (BFS)**:  
   Se realiza una búsqueda en anchura desde todos los nodos libres del conjunto
$U$. El objetivo es calcular, para cada nodo, la distancia mínima hasta un nodo
libre de $V$, siguiendo aristas válidas para formar caminos aumentantes.  
   Si no se alcanza ningún nodo libre en $V$, significa que no existen caminos
aumentantes y el algoritmo puede detenerse.

3. **Búsqueda en profundidad (DFS)**:  
   A continuación, para cada nodo libre de $U$, se intenta encontrar un camino
aumentante usando DFS, respetando los niveles obtenidos en la BFS anterior
(para evitar ciclos y mantener caminos mínimos). Si se encuentra un camino
aumentante, se actualiza el emparejamiento: se emparejan los nodos
correspondientes y se incrementa el contador total.

4. **Repetición**:  
   Se repite el proceso BFS + DFS hasta que la búsqueda en anchura no encuentre
más caminos aumentantes.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [C.cpp](src/C.cpp) | :x:          |

