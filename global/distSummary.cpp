/*
This program computes the distance to goal (i.e. the cost of the least-cost path to the goal)
of every state from which the goal can be reached.
It does this by executing Dijkstra's algorithm backwards from the goal.
It prints on stdout the number of states at each distance from goal and, if a filename is
provided as a command line argument, it prints the state_map it builds to that file.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <vector>
#include "priority_queue.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {


    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)

    // add goal states
    first_goal_state(&state, &d);
    do {
        state_map_add(map, &state, 0);
        open.Add(0, 0, state);
    } while( next_goal_state(&state, &d) );

    int n;

    for(int i = 0; i < 7; i++) {
        n = state.vars[0];
    }

    cout << n << endl;

    print_state(stdout, &state);

    return 0;
}

