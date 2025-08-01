# Introducción a la solución

Podemos resolver el problema de forma recursiva. Llamando $m(x, y)$ a los
cristales obtenidos al pasar por la casilla $(x, y)$, y definiendo la ganancia
posible desde la posición inicial $(0, 0)$ hasta la celda $(x,y)$ como $g(x,y)$:
- **Caso base:** si $(x,y) = (0,0)$, entonces $g(x,y) = m(0,0)$.
- **Caso general:** si $(x,y) \neq (0,0)$, entonces
$g(x,y) = m(x,y) + \max(g(x,y-1), g(x-1,y), g(x-1,y-1))$.

Es decir, si conocemos la ganancia máxima acumulada hasta la casilla derecha,
superior y en diagonal superior-derecha a una casilla dada $c$, podemos
encontrar la ganancia máxima posible hasta $c$ tomando la mayor de ellas y
añadiéndole los cristales obtenidos al pasar por $c$.

Puesto que muchos de estos valores habrá que calcularlos varias veces con una
implementación recursiva naïf, utilizamos memoización. Resolvemos el problema
por tanto mediante programación dinámica:

- Establecemos una matriz bidimensional $g$ de dimensiones $N \times M$, en la
  que $g[i][j]$ representa la ganancia máxima acumulada desde el origen
$(0,0)$ hasta la casilla $(i, j)$.
- Rellenamos $g$ fila a fila, de izquierda a derecha, empezando por el origen.
    - La primera fila sólo puede utilizar valores de su izquierda
      ($g[x][0] = m(x,0) + g[x-1][0]$).
    - La primera columna sólo puede utilizar valores de la casilla superior
      ($g[0][y] = m(0,y) + g[0][y-1]$).
    - El resto de columnas utilizarán la fórmula
      $g[i][j] = m(i,j) + \max(g[i][j-1], g[i-1][j], g[i-1][j-1])$.
Si rellenamos $g$ en el orden propuesto, todos los valores necesarios para
determinar $g(i,j)$ estarán disponibles cuando necesitamos determinarlo.

Finalmente, el valor buscado es $g[N-1][M-1]$ (la ganancia máxima acumulada
desde el origen hasta la casilla inferior derecha).


# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [J.cpp](src/J.cpp) | :x:          |

