#include <iostream>
using namespace std;

/*
    making a pathfinding algorithm
 */

// ' ' is empty space, 'a' is starting point, 'b' is ending point, '0' is wall
// for now we fill all the tile with ' '
#define map_size_x 10
#define map_size_y 10
char StaticMap[map_size_x][map_size_y] = {
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
#define emptyNode 0
#define normalNode 1
#define startNode 2
#define endNode 3
#define wallNode 4
/*
     the define bellow is only for arduino code, it is not needed for c++.
     uncomment it when this code is used for arduino
*/
// #define throw Serial.
// #define invalid_argument println
/*
    the define bellow is only for c++ code, it is not needed for arduino
    comment it when this code is used for arduino
*/
#define F

public:
    int position[2];
    int nodeType;
    /*
        gCost = distance from start to current node
        hCost = distance from current node to end
        fCost = gCost + hCost
    */
    int gCost, hCost, fCost;
    // the starting point basicly
    node *startingNode;
    // the finish point basicly
    node *finishNode;
    // the other node that generate this node
    node *parent;
    // is the node already generate the serounding node
    bool evaluated = false;

    int calculateGCost()
    {
        // later we will use this function to calculate gCost
        return 0; // for now we just return 0
    }
    int calculateHCost()
    {
        // later we will use this function to calculate hCost
        return 0; // for now we just return 0
    }

    // this is the constructor for the finish and start node
    node(int x, int y, int nodeType, node *theOtherEnd)
    {
        switch (nodeType)
        {
        case startNode:
            startingNode = this;
            finishNode = theOtherEnd;
            gCost = 0;
            // the hCost will be 0 because when creating the starting node, the finish node is not defined yet, the hcost will be calculated later
            hCost = 0;
            break;
        case endNode:
            finishNode = this;
            startingNode = theOtherEnd;
            hCost = 0;
            gCost = calculateGCost();
            break;
        default:
            throw invalid_argument(F("nodeType for this constructor must be either startNode or endNode!"));
            return;
            break;
        }

        position[0] = x;
        position[1] = y;
        this->nodeType = nodeType;
        this->parent = NULL;
    }
    node(int x, int y, int nodeType)
    {
        this->nodeType = nodeType;
        position[0] = x;
        position[1] = y;
    }
    node()
    {
        this->nodeType = emptyNode;
    }

    // this constructor is only for the normalNode
    node(int x, int y, node *parent = NULL)
    {
        if (nodeType != normalNode)
        {
            throw invalid_argument(F("nodeType for this constructor must be normalNode!"));
            return;
        }

        position[0] = x;
        position[1] = y;

        this->parent = parent;
        gCost = calculateGCost();
        hCost = calculateHCost();
        fCost = gCost + hCost;
        finishNode = parent->finishNode;
        startingNode = parent->startingNode;
    }
};

int main()
{
    // the node map
    node nodeMap[map_size_x][map_size_y];
    node *startingNode = NULL;
    // loop trough the static map then make the node map
    {
        int startingPosition[2];
        int finishPosition[2];
        for (int y = 0; y < map_size_y; y++)
        {
            for (int x = 0; x < map_size_y; x++)
            {
                switch (StaticMap[x][y])
                {
                case ' ':
                    nodeMap[x][y] = node(x, y, emptyNode);
                    break;
                case 'a':
                    startingPosition[0] = x;
                    startingPosition[1] = y;
                    break;
                case 'b':
                    finishPosition[0] = x;
                    finishPosition[1] = y;
                    break;
                case '0':
                    nodeMap[x][y] = node(x, y, wallNode);
                    break;
                default:
                    throw invalid_argument(F("the map must be filled with ' ' or 'a' or 'b' or '0'"));
                    return 0;
                    break;
                }
            }
        }
        // make the startinf node on the map
        nodeMap[startingPosition[0]][startingPosition[1]] = node(startingPosition[0], startingPosition[1], startNode, NULL);
        // assign the startingNode pointer to the starting node
        startingNode = &nodeMap[startingPosition[0]][startingPosition[1]];
        // make the finish node on the map
        nodeMap[finishPosition[0]][finishPosition[1]] = node(finishPosition[0], finishPosition[1], endNode, startingNode);
        // assign the finishNode pointer on the starting node property to the finish node
        startingNode->finishNode = &nodeMap[finishPosition[0]][finishPosition[1]];
        // finnaly calculate the hCost for the starting node
        startingNode->hCost = startingNode->calculateHCost();
    }
    // print out the node map, for debugging purpose
    for (int x = 0; x < map_size_x; x++)
    {
        for (int y = 0; y < map_size_y; y++)
        {
            string output;
            switch (nodeMap[x][y].nodeType)
            {
            case emptyNode:
                output = ".";
                break;
            case normalNode:
                output = '-';
                break;
            case startNode:
                output = 'a';
                break;
            case endNode:
                output = 'b';
                break;
            case wallNode:
                output = '0';
                break;
            }
            cout << output;
        }
        cout << endl;
    }
    // press enter to continue
    getchar();
    return 0;
}