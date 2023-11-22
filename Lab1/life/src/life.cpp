/* this file is a simulation of the game of life,
   a simulation from generation to generation of living cells */
// vicny135
#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

// prints given grid to console
void gridToConsole(const Grid<char>&grid){
    for(int i = 0; i < grid.numRows(); i++){
        for(int j = 0; j < grid.numCols(); j++){
            cout << grid.get(i, j);
        }
        cout << "\n";
    }
}

// gets the amount of living cells surrounding a given cell
int getNrOfNeighbours(const Grid<char>&grid, int row, int col){
    int neighbour_count = 0;
    for(int i = row - 1; i < row + 2; i++){
        for(int j = col - 1; j < col + 2; j++){
            if(grid.inBounds(i,j) && !(row == i && col == j)){
                if(grid.get(i,j) == 'X'){
                    neighbour_count++;
                }
            }
        }
    }
    return neighbour_count;
}

// creates the next generation of the grid
Grid<char> nextGeneration(const Grid<char>&grid){
    // creates a new temporary grid with the same dimensions
    Grid<char>tempGrid(grid.numRows(), grid.numCols());
    int neighbours;

    for(int i = 0; i < grid.numRows(); i++){
        for(int j = 0; j < grid.numCols(); j++){
            neighbours = getNrOfNeighbours(grid, i,j);
            //based on the amount of neighbours, adds "-" or "X" to grid
            if(neighbours <= 1 || neighbours >= 4){
                tempGrid.set(i, j, '-');
            }
            if(neighbours == 2){
                tempGrid.set(i, j, grid.get(i,j));
            }
            if(neighbours == 3){
                tempGrid.set(i, j, 'X');
            }
        }
    }
    return tempGrid;
}

int main() {
    string nrRows, nrColumns, line, input;
    int rows, columns, i, j;
    cout << "Welcome to the TDDD86 Game of Life,\n"
            "a simulation of the lifecycle of a bacteria colony.\n"
            "Cells (X) live and die by the following rules:\n"
            "  - A cell with 1 or fewer neighbours dies.\n"
            "  - Locations with 2 neighbours remain stable.\n"
            "  - Locations with 3 neighbours will create life.\n"
            "  - A cell with 4 or more neighbours dies." << endl;
    cout << "Grid input file name: ";
    // gets the inputfile and takes out info of nr of rows and columns
    string file;
    cin >> file;
    ifstream inputfile(file);
    getline(inputfile, nrRows);
    getline(inputfile, nrColumns);
    rows = stoi(nrRows);
    columns = stoi(nrColumns);
    // creates grid based on supplied file
    Grid<char>grid(rows, columns);
    for(i = 0; i < rows; i++){
        getline(inputfile, line);
        j = 0;
        for(char c : line){
            grid.set(i, j, c);
            j++;
        }
    }
    inputfile.close();
    // clear console and print out starting grid to the console
    clearConsole();
    gridToConsole(grid);
    // runs the game
    while(true){
      cout << "a)nimate, t)ick, q)uit? ";
      cin >> input;
      // animate through entire game
      if(input == "a"){
          while(true){
          clearConsole();
          grid = nextGeneration(grid);
          gridToConsole(grid);
          pause(100);
          }
      }
      // tick to next generation
      if(input == "t"){
          clearConsole();
          grid = nextGeneration(grid);
          gridToConsole(grid);
      }
      // quit game
      if(input == "q"){
          clearConsole();
          break;
      }
    }
    cout << "Have a nice life!" << endl;
    return 0;
}
