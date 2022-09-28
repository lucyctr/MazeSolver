// maze.cpp file that implements functions for the MazeElement and Maze class

#include "maze.h"

// MazeElement class constructor
MazeElement::MazeElement(bool isWall, bool isDest, char depiction) {
    this->isWall = isWall;
    this->isDest = isDest;
    this->depiction = depiction;
}

// Checks if element can be visited
bool MazeElement::canVisit(){
    return !isWall;
}

// Checks if element is destination
bool MazeElement::isDestination(){
    return isDest;
}

// Returns the char representation of the element
char MazeElement::getDepiction(){
    return depiction;
};



// Determines wether the element of the maze is within boundaries and can be visited
bool Maze::canVisit(Point p)
{
    // if (x, y outside maze) return false
    if (p.x >= 0 && p.x < mazeVector.size() && p.y >= 0 && p.y < mazeVector[0].size() && mazeVector[p.x][p.y].canVisit()){
        return true;
    }

    return false;
}

// Determines wether the element can be visited and is already part of the path
bool Maze::canVisit(vector<Point> path, Point p)
{
    if(!canVisit(p)){
        return false;
    }
    
    for(int i=0;i<path.size();i++){
        if(path[i].x == p.x && path[i].y==p.y){
            return false;
        }
    }
    return true;
}

// Recursive function to find the shortest maze path
bool Maze::mazeSolver(Point p, int distance)
{
    
    // Check if we reached the destination and decide if new distance is shorter than last path
    if (p.x == dest.x && p.y == dest.y && mazeVector[p.x][p.y].canVisit()) {
        if (distance < visited[dest.x][dest.y]){
            visited[dest.x][dest.y] = distance;
        }
        return true;
    }
  
    
    //If point in maze is visitable, explore new surrounding points in maze
    if (canVisit(p) == true) {
        if(distance < visited[p.x][p.y]){
            
               visited[p.x][p.y] = distance;
            // Move forward in x direction
            bool first = mazeSolver({p.x + 1, p.y}, distance+1);
            // Move down in y direction
            bool second = mazeSolver({p.x, p.y + 1}, distance+1);
            // move backwards in x direction
            bool third = mazeSolver({p.x - 1, p.y}, distance+1);
            // move upwards in y direction
            bool fourth = mazeSolver({p.x, p.y - 1}, distance+1);
            
            
            return (first || second || third || fourth);
                
    } else{
        //the path that took us to this cell is longer than the previous one, so we stop searching as it will not lead us to a shorter solution
        return false;
    }
}
return false;
}

// Returns array of points that identify the shortest path
bool Maze::getShortestPath(vector<Point> &path){
    
    //Initialize a maze to track visited cells
    //Initialize all non-wall cells to the largest possible number so that we know we have not visited it yet
    visited = vector<vector<int>>(mazeVector.size(), vector<int>(mazeVector[0].size(), INT_MAX));
    
    
    if (mazeSolver(src, 0) == false) {
        return false;
    }
    
    //Generates the path
    Point tmp = dest;
    
    while(tmp.x != src.x || tmp.y != src.y){
        
        int min = INT_MAX;
        Point p;
        
        if(canVisit(path, {tmp.x - 1, tmp.y}) && visited[tmp.x - 1][tmp.y] < min){
            min = visited[tmp.x - 1][tmp.y];
            p = {tmp.x - 1, tmp.y};
        }
        if(canVisit(path, {tmp.x + 1, tmp.y}) && visited[tmp.x + 1][tmp.y] < min){
            min = visited[tmp.x + 1][tmp.y];
            p = {tmp.x + 1, tmp.y};
        }
        if(canVisit(path, {tmp.x, tmp.y - 1}) && visited[tmp.x][tmp.y - 1] < min){
            min = visited[tmp.x][tmp.y - 1];
            p = {tmp.x, tmp.y - 1};
        }
        if(canVisit(path, {tmp.x, tmp.y + 1}) && visited[tmp.x][tmp.y + 1] < min){
            min = visited[tmp.x][tmp.y + 1];
            p = {tmp.x, tmp.y + 1};
        }
        
        path.push_back(p);
        tmp = p;
        
    }
 
    
    return true;
    
}

// Helper method to print out the shortest path
void Maze::printSolution(const vector<Point> &path)
{
   
    for (int i = 0; i < mazeVector.size(); i++) {
        for (int j = 0; j < mazeVector[i].size(); j++){
            if(mazeVector[i][j].isDestination() || !mazeVector[i][j].canVisit()){
                cout << mazeVector[i][j].getDepiction();
            }
            else{
                bool isPath = false;
                for(int k=0;k<path.size();k++){
                    if(path[k].x == i && path[k].y==j){
                        cout << ".";
                        isPath = true;
                        break;
                    }
                }
                
                if(!isPath){
                    cout << mazeVector[i][j].getDepiction();;
                }
            }
        }
            
       
        cout << endl;
    }
    cout << endl;
}

// Maze class constructor
Maze::Maze(vector<vector<MazeElement> > mazeVector, Point src, Point dest){
    this->mazeVector = mazeVector;
    this->src = src;
    this->dest = dest;
    
}
