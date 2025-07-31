# Introducción a la solución

Podemos modelar una expresión aritmética con operadores binarios (como `+`,
`-`, `*`, `/`) utilizando un **árbol binario**:
- Las **hojas** del árbol representan los números que queremos combinar.
- Los **nodos internos** representan operaciones que se aplican a los
  resultados de sus dos hijos.

Por ejemplo, la expresión `3 * (5 + 1)` puede representarse con el siguiente
árbol:

```
    *
   / \
  3   +
     / \
    5   1
```


Con esta estructura en mente, podemos calcular **todos los valores posibles**
que pueden obtenerse combinando $n$ números distintos mediante operaciones
binarias, de forma recursiva:

## Paso a paso

1. **Caso base:**  
   Si solo tenemos un número ($n = 1$), el único resultado posible es ese
número.

2. **Paso recursivo:**  
   Si $n > 1$, debemos:
   - **Partir el conjunto** en dos subconjuntos no vacíos y disjuntos.
   - **Calcular recursivamente** todos los valores posibles que pueden
     generarse con cada subconjunto.
   - **Combinar** los valores de ambos lados usando todas las operaciones
     posibles (`+`, `-`, `*`, `/`, etc.).

Este proceso nos permite construir todas las expresiones válidas (respetando el
orden de los operandos) y calcular sus resultados.

## Cómo hacer las particiones

Para generar todas las particiones posibles de un conjunto de $n$ números en
dos subconjuntos no vacíos, podemos usar una máscara binaria de $n$ bits.

Recorremos todas las máscaras entre $1$ y $2^{n-1} - 1$ (esto evita contar
particiones simétricas dos veces).

Por ejemplo, con $n = 3$ (números $[a, b, c]$), la máscara $010$ (en binario)
nos dice que:
- $b$ va en el primer subconjunto (bit 1).
- $a$ y $c$ van en el segundo subconjunto (bits 0).

Esto nos da una partición: $g_1 = [b]$, $g_2 = [a, c]$.

Gracias a la simetría del problema, no es necesario considerar también $[a, c],
[b]$ como una partición distinta.

## Consideración importante

Durante el cálculo es posible que aparezcan valores intermedios negativos o
fraccionarios.

Es importante no descartar estos resultados demasiado pronto, ya que
podrían ser necesarios para llegar a un valor final válido (por ejemplo, una
división seguida de una multiplicación puede producir un número entero aunque
los pasos intermedios no lo sean).

Por eso, el filtro "solo resultados enteros y positivos" deben aplicarse **solo
al final**, cuando ya se generaron todas las expresiones posibles.

# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
| [F.cpp](src/F.cpp) | :x:          |
| [F.py](src/F.py)   | :x:          |

