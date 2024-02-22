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

      while(!q.Empty()) {

            d = q.CurrentPriority();

            cout << d << endl;

            state = q.Top();
            q.Pop();
  
            const int *g = state_map_get(map, &state);
            //assert(g != NULL);

            if(*g < d) continue;

            if(is_goal(&state)) { // Si el estado es el objetivo entonces retornamos el valor de la funcion de costo
                  return d;
            }

            init_fwd_iter(&iter, &state);
            while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
                  apply_fwd_rule(ruleid, &state, &child);

                  if(heuristic(child) < INT_MAX) {
                        q.Add(*g+get_fwd_rule_cost(ruleid)+heuristic(child), *g+get_fwd_rule_cost(ruleid)+heuristic(child), child); 
                        state_map_add(map, &child, *g+get_fwd_rule_cost(ruleid));
                  }
                  const int child_d = d + get_fwd_rule_cost(ruleid);
            }
      }           
      return 0; // No hay camino
}


#endif // _PRIORITY_QUEUE_HPP