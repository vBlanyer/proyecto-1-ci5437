#ifndef _MANHATTAN_PUZZLE_15_HPP
#define _MANHATTAN_PUZZLE_15_HPP

#include <iostream>

unsigned manhattan(const state_t state) {
      unsigned h;

      for (int i = 0; i < 16; i++) {
            if (state.vars[i] != 0) { // Ignorar la pieza blanca
                  int fila_objetivo = i / 4; 
                  int columna_objetivo = i % 4; 

                  int fila_actual = (state.vars[i] - 1) / 4;
                  int columna_actual = (state.vars[i] - 1) % 4;

                  // Calcula la distancia Manhattan
                  h += std::abs(columna_actual - fila_actual) + std::abs(columna_actual - fila_actual);
            }
      }

      return h;
}

#endif // _PRIORITY_QUEUE_HPP