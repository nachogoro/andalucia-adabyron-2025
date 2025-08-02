# Introducción a la solución

Dado un sistema de tres flotas en el espacio tridimensional, cada una con
posición inicial $(x, y, z)$ y velocidad inicial $(0, 0, 0)$, se desea
encontrar el número de días necesarios para que el sistema regrese a su estado
original (misma posición y velocidad).

Cada día, el sistema se actualiza en dos fases:

1. **Actualización de velocidades**:
   - Por cada par de flotas $(i, j)$ y por cada eje $(x, y, z)$:
     - Si $p_i < p_j$, entonces $v_i \mathrel{+}= 1$ y $v_j \mathrel{-}= 1$.
     - Si $p_i > p_j$, entonces $v_i \mathrel{-}= 1$ y $v_j \mathrel{+}= 1$.
     - Si $p_i = p_j$, no se modifica la velocidad.

2. **Actualización de posiciones**:
   - Para cada flota $i$, en cada eje:
     - $p_i \mathrel{+}= v_i$.

El proceso continúa hasta que las posiciones y velocidades sean exactamente las
mismas que al comienzo. El objetivo es calcular en cuántos días ocurre eso.

Las tres componentes ($x$, $y$, $z$) **se actualizan de forma completamente
independiente**. Esto permite simular cada eje por separado.

Sea $T_x$ el número de días necesarios para que las posiciones y velocidades en
el eje $x$ vuelvan al estado inicial. Análogamente $T_y$ y $T_z$.

La respuesta final es el mínimo común múltiplo de dichos periodos:

$$
T = \operatorname{mcm}(T_x, \operatorname{mcm}(T_y, T_z))
$$

## Simulación de un eje

La simulación por eje consiste en:

- Inicializar posiciones $p = [p_1, p_2, p_3]$ y velocidades $v = [0, 0, 0]$.
- En cada día:
  - Aplicar la regla de actualización de velocidades entre pares $(0,1)$, $(0,2)$ y $(1,2)$.
  - Sumar las velocidades a las posiciones.
- Repetir hasta que se cumpla:
  $$
  p = p_{\text{inicial}} \quad \text{y} \quad v = [0, 0, 0]
  $$

---

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [H.cpp](src/H.cpp) | :x:          |

