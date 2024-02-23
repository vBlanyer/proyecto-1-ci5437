#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <string.h>
#include "priority_queue.hpp"

#define MAX_LINE_LENGTH 999

using namespace std;

// Funcion protitipo
int a_start(state_t *init, unsigned (*heuristic)(state_t));

int main(int argc, char **argv)
{
      char str[MAX_LINE_LENGTH + 1];
      char test[50];
      ssize_t nchars;
      state_t state, child;
      int d, ruleid;
      ruleid_iterator_t iter;

      loadPDB();

      // // MODIFICAR ESTA PARTE PARA INTRODUCIR EL NOMBRE DEL TEST
      // printf("Ingrese el nombre del archivo de prueba: ");
      // if (fgets(test, sizeof test, stdin) == NULL)
      // {
      //       printf("Error: Introduzca el nombre del archivo.\n");
      //       return 0;
      // }

      // // Elimina el salto de línea al final de la cadena (si existe)
      // if (test[strlen(test) - 1] == '\n')
      // {
      //       test[strlen(test) - 1] = '\0';
      // }

      // string direccion = "../benchmarks/";
      // direccion.append(test);
      ifstream infile("benchmarks/topspin_12_4.d=005");
      if (!infile.is_open())
      {
            cerr << "Error al abrir el archivo." << endl;
            return 1;
      }


      string line;
      int count = 0;
      while (getline(infile, line))
      {
            count++;

            // Convertir el string a array char para convertir a estado
            for (size_t i = 0; i < line.length(); ++i)
            {
                  str[i] = line[i];
            }

            // CONVERT THE STRING TO A STATE
            nchars = read_state(str, &state);
            if (nchars <= 0)
            {
                  printf("Error: invalid state entered.\n");
                  return 0;
            }

            a_start(&state, *heuristic);
      }

      if (count == 0)
      {
            printf("Error: Empty file benchmarks.\n");
      }

      infile.close(); // Cierra el archivo

      return 0;
}

int a_start(state_t *init, unsigned (*heuristic)(state_t))
{
      // variables para el estado y su iteracion
      state_t state, child;
      int g, ruleid;
      ruleid_iterator_t iter;

      PriorityQueue<state_t> q;           // La prioridad respecto a la funcion de costo
      state_map_t *map = new_state_map(); // Almacena los pesos de movimientos

      q.Add(0, 0, *init);          // Inicializacion de cola con el estado inicial con funcion de costo 0
      state_map_add(map, init, 0); // Inicializacion con peso del estado incial 0

      while (!q.Empty() )
      {
            g = q.CurrentPriority();

            cout << g << endl;

            state = q.Top();
            q.Pop();
            // printf("The state you entered is: ");
            // print_state(stdout, &state);
            // printf("\n");

            const int *old_d = state_map_get(map, &state);
            // assert(g != NULL);

            if (old_d == NULL || g < *old_d || !compare_states(&state, init)) {
                  state_map_add(map, &state, g);
      

                  if (is_goal(&state))
                  { // Si el estado es el objetivo entonces retornamos el valor de la funcion de costo
                  cout << "aqui";
                        return g;
                  }

                  init_fwd_iter(&iter, &state);
                  while ((ruleid = next_ruleid(&iter)) >= 0)
                  {
                        apply_fwd_rule(ruleid, &state, &child);

                        int child_g = g + get_fwd_rule_cost(ruleid);
                        int child_h = heuristic(child);

                        if (child_h < INT_MAX)
                        {
                              q.Add(child_g + child_h, child_g, child);
                        }
                  }
            }
      }
      printf("finalizo\n");
      return 0; // No hay camino
}
