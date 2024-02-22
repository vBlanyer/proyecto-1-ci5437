#ifndef _MANHATTAN_PUZZLE_15_HPP
#define _MANHATTAN_PUZZLE_15_HPP

#include <iostream>

unsigned manhattan(const state_t state) {
      unsigned h;
      
      printf("The state you entered is: ");
      print_state(stdout, &state);
      printf("\n");

      for (int i = 0; i < 16; i++) {
            if (state.vars[i] != 0) { // Ignorar la pieza blanca
                  int fila_actual = i / 4; 
                  int columna_actual = i % 4; 

                  int fila_objetivo = (state.vars[i]) / 4;
                  int columna_objetivo = (state.vars[i]) % 4;




                  // Calcula la distancia Manhattan
                  printf("Costo de %d: %d\n", state.vars[i], std::abs(fila_actual - fila_objetivo) + std::abs(columna_actual - columna_objetivo));
                  h += std::abs(fila_actual - fila_objetivo) + std::abs(columna_actual - columna_objetivo);

            }
      }
      printf("Finalizado\n");
      return h;
}

#endif // _PRIORITY_QUEUE_HPP