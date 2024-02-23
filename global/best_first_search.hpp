#ifndef _BEST_FIRST_SEARCH_HPP
#define _BEST_FIRST_SEARCH_HPP

#include <iostream>
#include "priority_queue.hpp"

using namespace std;

int best_first_search(state_t *init, unsigned (*heuristic) (state_t)) {
      // variables para el estado y su iteracion
      state_t state, child; 
      int d, ruleid;
      ruleid_iterator_t iter;

      PriorityQueue<state_t> q; // La prioridad respecto a la funcion de costo
      state_map_t *map = new_state_map(); // Almacena los pesos de movimientos 

      q.Add(0, 0, *init); // Inicializacion de cola con el estado inicial con funcion de costo 0
      state_map_add(map, init, 0); // Inicializacion con peso del estado incial 0

      int test = 5000000;
      while(!q.Empty() && test != 0) {
            test--;
            d = q.CurrentPriority();

            cout << d << endl;

            state = q.Top();
            q.Pop();
            printf("The state you entered is: ");
            print_state(stdout, &state);
            printf("\n");

            const int *g = state_map_get(map, &state);
            //assert(g != NULL);

            printf("valor de gasto %d y valor de f.c %d\n", *g, d);
            if(*g > d) continue;

            if(is_goal(&state)) { // Si el estado es el objetivo entonces retornamos el valor de la funcion de costo
                  return *g;
            }

            init_fwd_iter(&iter, &state);
            while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
                  apply_fwd_rule(ruleid, &state, &child);

                  int child_g = *g + get_fwd_rule_cost( ruleid );
                  int child_h = heuristic(child);

                  printf("The state you entered is: ");
                  print_state(stdout, &child);
                  printf("funcion de costo %d\n", child_g+child_h);

                  if(child_h < INT_MAX) {
                        q.Add(child_g+child_h, child_g, child); 
                        state_map_add(map, &child, child_g);
                  }
            }
      }
      printf("finalizo\n"); 
      return 0; // No hay camino
}


#endif // _PRIORITY_QUEUE_HPP