#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "best_first_search.hpp"
#include "manhattan_puzzle_15.hpp"
#include <string.h>

using namespace std;

int main(int argc, char **argv) {
      char str[1000];
      ssize_t nchars; 
      state_t state, child;   
      int d, ruleid;
      ruleid_iterator_t iter;


      // char str[256];
      // cout << "Please enter a state followed by ENTER: ";
      // if (fgets(str, sizeof(str), stdin) == nullptr) {
      //       cout << "Error: empty input line." << endl;
      // }

      std::ifstream infile("15_puzzle_100_instances_korf.txt"); // Cambia "mi_archivo.txt" al nombre de tu archivo

      if (!infile.is_open()) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return 1;
      }

      std::string firstLine;
      if (std::getline(infile, firstLine)) {
            std::cout << "Primera línea del archivo: " << firstLine << std::endl;
      } else {
            std::cerr << "El archivo está vacío." << std::endl;
      }

      for (size_t i = 0; i < firstLine.length(); ++i) {
            str[i] = firstLine[i];
      }

      // CONVERT THE STRING TO A STATE
      nchars = read_state(str, &state);
      if( nchars <= 0 ) {
            printf("Error: invalid state entered.\n");
            return 0; 
      }

      printf("The state you entered is: ");
      print_state(stdout, &state);
      printf("\n");


      cout << "costo: " + best_first_search(&state, *manhattan) << endl;

      infile.close(); // Cierra el archivo

      return 0;
}

