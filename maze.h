// maze.h file with MazeElement and Maze class

#ifndef x_Array
#define x_Array

#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

struct Point
{
    int x;
    int y;
};

class MazeElement {
    private:
        bool isWall;
        bool isDest;
    
        char depiction;
    
    public:
        // Constructor
        MazeElement(bool isWall, bool isDest, char depiction);
    
        bool canVisit();
        bool isDestination();
        char getDepiction();
    
    //Helper method to create MazeElements from a character
    static MazeElement getMazeElement(char c){
        if(c=='#'){
            return MazeElement(true, false, c);
        } else if(c=='o'){
            return MazeElement(false, true, c);
        } else{
            return MazeElement(false, false, c);
        }
    }
};


class Maze {
    
    private:
    
    // 2d Vector of MazeElement that represents maze
    vector<vector<MazeElement> > mazeVector;
    // Keeps track of all cells visited within maze and distance from source in order to find shortest path
    vector<vector<int> > visited;
        
    Point src;
    Point dest;
   

    
    // Methods to check is point in vector is valid index
    bool canVisit(Point p);
    bool canVisit(vector<Point> path, Point p);
    
    // A recursive function to solve the maze
    bool mazeSolver(Point p, int distance);
    
    
    
    public:
    
    
    // Constructor
    Maze(vector<vector<MazeElement> > mazeVector, Point src, Point dest);
    
    
    bool getShortestPath(vector<Point> &path);
    
    // A function to print maze overlayed with path calculated from visited matrix
    void printSolution(const vector<Point> &path);
    
};


#endif
