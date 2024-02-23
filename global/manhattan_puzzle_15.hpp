#ifndef _MANHATTAN_PUZZLE_15_HPP
#define _MANHATTAN_PUZZLE_15_HPP

#include <iostream>

unsigned manhattan(const state_t state) {
      unsigned h;

      for (int i = 0; i < 16; i++) {
            if (state.vars[i] != 0) { // Ignorar la pieza blanca
                  int fila_actual = i / 4; 
                  int columna_actual = i % 4; 

                  int fila_objetivo = (state.vars[i]) / 4;
                  int columna_objetivo = (state.vars[i]) % 4;

                  // Calcula la distancia Manhattan
                  h += std::abs(fila_actual - fila_objetivo) + std::abs(columna_actual - columna_objetivo);

            }
      }
      return h;
}

#endif // _PRIORITY_QUEUE_HPP