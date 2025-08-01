# Introducción a la solución

Para resolver el reparto de vales entre clientes de forma proporcional al
gasto, utilizamos una estrategia basada en un montículo de máximos (*priority
queue*). La idea es simular la asignación de los vales uno a uno, eligiendo en
cada paso al cliente con el mayor cociente hasta ahora.

Cada cliente puede recibir varios vales, por lo que su cociente se actualiza
cada vez que recibe uno nuevo. El valor de cada nuevo cociente para un cliente
se calcula dividiendo su gasto total entre la cantidad de vales que ha recibido
hasta ahora más uno.

Utilizamos un montículo para mantener los mejores candidatos a recibir el
siguiente vale. Cada entrada del montículo será una tupla con:
- El cociente actual (gasto dividido entre número de vales que tendría),
- El gasto original del cliente (para desempates),
- El identificador del cliente (índice en la entrada).

Para cada cliente $i$ se introduce inicialmente en el montículo la tupla:
```math
\left( \frac{v_i}{1}, v_i, i \right)
```
Es decir, su gasto dividido por 1 (aún no tiene vales), su gasto original y su
índice.

A continuación, por cada uno de los $n$ vales que haya que asignar repetimos el
siguiente proceso:
1. Extraer de la cima del montículo la tupla con el mayor cociente, y en caso
   de empate, el mayor gasto original $\left( \frac{v_j}{k}, v_j, j \right)$.
2. Asignar un vale al cliente correspondiente a dicha cima.
3. Insertar en el montículo el siguiente cociente de ese cliente:
```math
\left( \frac{v_j}{k+1}, v_j, j \right)
```

Al finalizar el proceso, habremos asignado a cada cliente los vales que merecía
según el criterio establecido en el enunciado.


# Soluciones

| Solución | Verificado con el juez |
| :------: | :--------------------: |
|[D.cpp](src/D.cpp) | :x:           |

