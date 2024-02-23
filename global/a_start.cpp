#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <string.h>
#include <time.h>
#include "priority_queue.hpp"
#include <vector>
#include <stdbool.h>

#define MAX_LINE_LENGTH 999

using namespace std;

int64_t nodes_expanded;

// Funcion protitipo
int a_start(state_t *init, unsigned (*heuristic)(state_t));

int main(int argc, char **argv)
{
      char str[MAX_LINE_LENGTH + 1];
      char test[50];
      ssize_t nchars;
      float runTime;
      state_t state, child;
      int d, ruleid;
      ruleid_iterator_t iter;
      clock_t startTime, endTime, timeSpan;

      loadPDB();

      // MODIFICAR ESTA PARTE PARA INTRODUCIR EL NOMBRE DEL TEST
      printf("Ingrese el nombre del archivo de prueba: ");
      if (fgets(test, sizeof test, stdin) == NULL)
      {
            printf("Error: Introduzca el nombre del archivo.\n");
            return 0;
      }

      // Elimina el salto de línea al final de la cadena (si existe)
      if (test[strlen(test) - 1] == '\n')
      {
            test[strlen(test) - 1] = '\0';
      }

      string direccion = "benchmarks/";
      direccion.append(test);
      ifstream infile(direccion);
      if (!infile.is_open())
      {
            cerr << "Error al abrir el archivo. " << direccion << endl;
            return 1;
      }

      printf("<id> : <instance> : \t\t  <# generated nodes> <final-value> <time-in-secs>\n");
      printf("----------------------------------------------------------------------------------\n");

      string line;
      int id = 0;
      while (getline(infile, line))
      {
            id++;

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

            startTime = clock();
            nodes_expanded = 0;
            d = 0;
            d = a_start(&state, *heuristic);

            endTime = clock();

            timeSpan = endTime - startTime;

            runTime = timeSpan / (double)CLOCKS_PER_SEC;
            if (d < 0)
            {
                  printf("%s  \t  False  \t  %f  \t  %ld  \t\t  %d\n", line.c_str(), runTime, nodes_expanded, d);
            }
            else
            {
                  printf("%-5d: ", id);
                  print_state(stdout, &state);
                  printf("\t %-20ld %-10d %-10f\n", nodes_expanded, d, runTime);
            }
      }

      if (id == 0)
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

      while (!q.Empty())
      {
            g = q.CurrentPriority();

            state = q.Top();
            q.Pop();

            int *old_d = state_map_get(map, &state);
            ++nodes_expanded;

            if (old_d == NULL || g < *old_d || !compare_states(&state, init))
            {
                  state_map_add(map, &state, g);

                  if (is_goal(&state))
                  {
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
      return -1; // No hay camino
}
