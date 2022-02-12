#include <iostream>
using namespace std;

/*
    making a pathfinding algorithm
    gCost = distance from start to current node
    hCost = distance from current node to end
    fCost = gCost + hCost
 */

// ' ' is empty space, 'a' is starting point, 'b' is ending point, '0' is wall
// for now we fill all the tile with ' '
char StaticMap[10][10] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'b', '0', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', '0', '0', '0', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'a', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

// make node object
class node
{
#define normalNode 0
#define startNode 1
#define endNode 2

public:
    int position[2];
    int nodeType;
    int gCost, hCost, fCost;
    node *startingNode;
    node *finishNode;
    node *parent;
    bool evaluated = false;

    int calculateGCost()
    {
        // later we will use this function to calculate gCost
    }
    int calculateHCost()
    {
        // later we will use this function to calculate hCost
    }

    node(int x, int y, int nodeType, node *parent = NULL)
    {
        position[0] = x;
        position[1] = y;
        this->nodeType = nodeType;

        switch (nodeType)
        {
        case normalNode:
            this->parent = parent;
            gCost = calculateGCost();
            hCost = calculateHCost();
            fCost = gCost + hCost;
            finishNode = parent->finishNode;
            break;
            
        case startNode:
            this->parent = NULL;
            gCost = 0;
            hCost = calculateHCost();
            fCost = gCost + hCost;
            break;

        case endNode:
            this->parent = NULL;
            gCost = 0;
            hCost = 0;
            fCost = 0;
            break;
        }
    }
};

int main()
{
    cout << "Hello world!";
    return 0;
}