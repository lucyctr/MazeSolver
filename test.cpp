// Main test method that parses the maze from the file into a 2D vector 
// and runs a recursive maze solver to find the shortest path of maze


#include <iostream>
#include <fstream>
#include <sstream>
#include "maze.h"

using namespace std;



int main()
{
    
    vector<vector<MazeElement> > mazeElements;
    
    // Read in file
    ifstream infile("/Users/lucy/Documents/css342/maze");
    
    if (!infile) {
        cout << "Error" << endl;
    }
    
    string line;
    
    getline(infile, line);

    istringstream iss(line);
    
    
    Point src;
    Point dest;
    
    int sizeX = 0;
    int sizeY = 0;
    
    iss >> sizeX;
    iss >> sizeY;
    iss >> src.x;
    iss >> src.y;
    
    
    
    int currentX = 0;
    
    //Parse the file and build a 2D vector of MazeElements representing the maze
    while (getline(infile, line))
    {
        if(currentX < sizeX){
            vector <MazeElement> row;

            
            int currentY = 0;
            
            for (int i = 0; i < sizeY; i++){
                char c = line.data()[i];
                
                MazeElement el = MazeElement::getMazeElement(c);
                
                if(el.isDestination()){
                    dest.x = currentX;
                    dest.y = currentY;
                }
                
                row.push_back(el);
                currentY++;
            }
            
            mazeElements.push_back(row);
            
        }
        
        currentX++;
    }
    
    Maze maze(mazeElements, src, dest);
    vector<Point> path;
    
    if(maze.getShortestPath(path)){
        maze.printSolution(path);
    }
    else{
        cout<<"Solution doesn't exist"<<endl;
    }
    
    return 0;
}
