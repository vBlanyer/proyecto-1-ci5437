#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits.h>
#include <time.h>
#include <cassert>

using namespace std;

#define MAX_LINE_LENGTH 999 

int64_t nodes_expanded;



// Implementación de IDA*
int searchWithinBound(state_t *state, int g, unsigned bound, unsigned *nextBound) {
    unsigned f = g + heuristic(*state);
    if (f > bound) {
        *nextBound = f;
        return INT_MAX; // No alcanza el umbral
    }
    if (is_goal(state)) {
        return g; // Solución encontrada
    }

    unsigned t = UINT_MAX;
    state_t child;
    ruleid_iterator_t iter;
    int ruleid;

    // Inicializa el iterador de reglas hacia adelante
    init_fwd_iter(&iter, state);
    while ((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid, state, &child);
        ++nodes_expanded;

        unsigned tempBound = UINT_MAX;
        int temp = searchWithinBound(&child, g + get_fwd_rule_cost(ruleid), bound, &tempBound);
        if (temp != INT_MAX) {
            return temp; // Solución encontrada
        }
        t = min(t, tempBound);
    }
    *nextBound = t;
    return INT_MAX; // No se encontró solución en este nivel
}

int ida_star(state_t *init) {
    unsigned bound = heuristic(*init);
    while (true) {
        unsigned nextBound = UINT_MAX;
        nodes_expanded = 0;
        int result = searchWithinBound(init, 0, bound, &nextBound);
        if (result != INT_MAX) {
            return result; // Solución encontrada
        }
        if (nextBound == UINT_MAX) {
            break; // No hay más nodos para explorar
        }
        bound = nextBound;
    }
    return -1; // No se encontró solución
}



int main() {
    loadPDB();

    printf("Ingrese el nombre del archivo de prueba: ");
    char test[50];
    if (fgets(test, sizeof test, stdin) == NULL) {
        printf("Error: Introduzca el nombre del archivo.\n");
        return 0;
    }
    if (test[strlen(test) - 1] == '\n') {
        test[strlen(test) - 1] = '\0';
    }

    string path = "benchmarks/" + string(test);
    ifstream infile("benchmarks/" + string(test));

    if (!infile.is_open()) {
        cerr << "Error al abrir el archivo: " << path << endl;
        return 1;
    }

    printf("<id> : <instance> :               <# generated nodes> <final-value> <time-in-secs>\n");
    printf("----------------------------------------------------------------------------------\n");

    string line;
    state_t state;
    int id = 0;
    while (getline(infile, line)) {
        ++id;
        ssize_t nchars = read_state(line.c_str(), &state);
        if (nchars <= 0) {
            cerr << "Error: invalid state entered." << endl;
            continue;
        }

        clock_t startTime = clock();
        nodes_expanded = 0;
        int solution = ida_star(&state);
        clock_t endTime = clock();

        float runTime = static_cast<float>(endTime - startTime) / CLOCKS_PER_SEC;
        printf("%-5d: %s\t %-20ld %-10d %-10f\n", id, line.c_str(), nodes_expanded, solution, runTime);
    }

    infile.close();
    return 0;
}
