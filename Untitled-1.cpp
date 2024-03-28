#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int manhattan(int x, int y, int goalx, int goaly)
{
    return abs(x - goalx) + abs(y - goaly);
}

struct node
{
    int x, y;
    int totalCost, previousCost, futureCost;
    int weight;
    node* previous;

    node(int weight, int x, int y, int previousCost, int futureCost, int totalCost, node* previous = nullptr)
        : weight(weight), x(x), y(y), previousCost(previousCost), futureCost(futureCost), totalCost(futureCost + previousCost), previous(previous) {}
};

int previousCostCalc(node* tempNode)
{
    if (tempNode->previous == nullptr)
    {
        //cout << " ||| if statement weight: " << tempNode->weight + 1 << "||| ";
        return tempNode->weight + 1; // If it's the starting node, return its weight
    }
    //cout << "--- made past if, weight then previous cost calc: " << tempNode->weight << " " << previousCostCalc(tempNode->previous) << "---";
    return 1 + tempNode->weight + previousCostCalc(tempNode->previous); // Add the weight of the current node and recursively calculate for the previous node
}

bool doesExist(const std::vector<node*>& vec, int y, int x) {
    // Loop through the vector to check if the node exists
    for (const auto& n : vec) {
        if (n->x == x && n->y == y) {
            return true; // Node exists
        }
    }
    return false; // Node doesn't exist
}


int main()
{
    vector<node*> queue;
    vector<node*> visited;

    char graph[20][20] = {
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        {'W', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'G', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', 'W', ' ', '5', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', '7', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', '2', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', 'W', ' ', '7', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', 'W', ' ', '7', ' ', ' ', ' ', 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', 'W', ' ', ' ', 'W', ' ', ' ', ' ', 'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', 'W', ' ', ' ', '3', 'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', '4', ' ', 'W', 'W', ' ', ' ', ' ', 'W', 'W', 'W', ' ', '1', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3', 'W', 'W', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', '4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', '3', 'W', 'W', 'W', ' ', ' ', 'W', 'W', 'W', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', '2', ' ', ' ', 'W', ' ', ' ', ' ', 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}
    };

    char finishedGraph[20][20] = {
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', 'W', ' ', '5', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', '7', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', '2', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', 'W', ' ', '7', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', 'W', ' ', '7', ' ', ' ', ' ', 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', 'W', ' ', ' ', 'W', ' ', ' ', ' ', 'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', 'W', ' ', ' ', '3', 'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', '4', ' ', 'W', 'W', ' ', ' ', ' ', 'W', 'W', 'W', ' ', '1', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3', 'W', 'W', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', '4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', '3', 'W', 'W', 'W', ' ', ' ', 'W', 'W', 'W', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', '2', ' ', ' ', 'W', ' ', ' ', ' ', 'W', 'W', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}
    };

    int startx, starty;
    int goalx, goaly;
    bool goalFound;
    //printing graph
    cout << "___________________________________________" << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << "| ";
        for (int j = 0; j < 20; j++)
        {
            cout << graph[i][j] << " ";

            if (graph[i][j] == 'S')
            {
                startx = j;
                starty = i;
            }
            if (graph[i][j] == 'G')
            {
                goalx = j;
                goaly = i;
            }
        }
        cout << "|" << endl;
    }
    cout << "___________________________________________" << endl;

    //new node for the start node and adding it to the queue
    node* start = new node(0, startx, starty, 0, manhattan(startx, starty, goalx, goaly), manhattan(startx, starty, goalx, goaly), nullptr);
    queue.push_back(start);

    /*first attempt
    //start of the main loop
    node* next;
    int nextCost;
    bool found = false;

    int tempIt = 0;
    while (tempIt < 100 && queue.size() > 0)
    {
        //cout << "queue/visited: " << queue.size() << "/" << visited.size() << endl;
        cout << "queue 1: |";
        next = nullptr; // added
        //finds the smallest value in the queue
        nextCost = queue[0]->totalCost;
        for (auto it = queue.begin(); it != queue.end(); ++it) 
        {
            node* currentNode = *it;
            if(currentNode->totalCost <= nextCost)
            {
                nextCost = currentNode->totalCost;
                next = currentNode;
            }
            
            //cout << "(" << currentNode->x << "," << currentNode->y << ")|";
            cout << "(" << currentNode->x << "," << currentNode->y << "), " << currentNode->previousCost << ", " << currentNode->futureCost << ", " << currentNode->totalCost << "|";
        }

        /*cout << endl << "visited: |";
        for (auto it = visited.begin(); it != visited.end(); ++it) 
        {
            node* currentNode = *it;
            cout << "(" << currentNode->x << "," << currentNode->y << ")|";
            
        }


        //puts the smallest value node into visited and removes from queue
        visited.push_back(next);
        for (auto it = queue.begin(); it != queue.end(); ) 
        {
            node* currentNode = *it;
            if (currentNode->x == next->x && currentNode->y == next->y)
            {
                it = queue.erase(it); // Erase the current element
                cout << endl << "erasing: " << currentNode->x << ", " << currentNode->y << endl;
            }
            else
            {
                ++it; // Move to the next element
            }
        }

        cout << endl << "queue 2: |";
        for (auto it = queue.begin(); it != queue.end(); ++it) 
        {
            node* currentNode = *it;
            if(currentNode->totalCost <= nextCost)
            {
                nextCost = currentNode->totalCost;
                next = currentNode;
            }
            
            //cout << "(" << currentNode->x << "," << currentNode->y << ")|";
            cout << "(" << currentNode->x << "," << currentNode->y << "), " << currentNode->previousCost << ", " << currentNode->futureCost << ", " << currentNode->totalCost << "|";
        }
 

        //checks and possibly adds the node to the queue
        node* temp;
        int nodeWeight = 0;

        // Check the node to the left
        if(next != nullptr && graph[next->y][next->x - 1] != 'W')
        {
            if (graph[next->y][next->x - 1] >= '1' && graph[next->y][next->x - 1] <= '9') 
            {
                nodeWeight = graph[next->y][next->x - 1] - '0';
            }
            else
            {
                nodeWeight = 0;
            }
            // Calculate total cost from current node to the adjacent node plus heuristic cost to goal
            int tempCost = previousCostCalc(next) + nodeWeight; // Cost from current node to adjacent node
            int heuristicCost = manhattan(next->x - 1, next->y, goalx, goaly); // Heuristic cost from adjacent node to goal
            int totalCost = tempCost + heuristicCost; // Total cost

            int adjacentX = next->x - 1;
            int adjacentY = next->y;

            temp = new node(nodeWeight, adjacentX, adjacentY, tempCost, heuristicCost, totalCost, next);

            
            if(doesExist(visited, next->y, next->x - 1))
            {
                //cout << "already been there";
            }
            else
            {
                queue.push_back(temp);
            }
        }

        // Check the node to the right
        if(next != nullptr && graph[next->y][next->x + 1] != 'W')
        {
            if (graph[next->y][next->x + 1] >= '1' && graph[next->y][next->x + 1] <= '9') 
            {
                nodeWeight = graph[next->y][next->x + 1] - '0';
            }
            else
            {
                nodeWeight = 0;
            }
            int tempCost = previousCostCalc(next) + nodeWeight; // Cost from current node to adjacent node
            int heuristicCost = manhattan(next->x + 1, next->y, goalx, goaly); // Heuristic cost from adjacent node to goal
            int totalCost = tempCost + heuristicCost; // Total cost

            int adjacentX = next->x + 1;
            int adjacentY = next->y;

            temp = new node(nodeWeight, adjacentX, adjacentY, tempCost, heuristicCost, totalCost, next);
            
            if(doesExist(visited, next->y, next->x + 1))
            {
                //cout << "already been there";
            }
            else
            {
                queue.push_back(temp);
            }
        }

        // Check the node above
        if(next != nullptr && graph[next->y - 1][next->x] != 'W')
        {
            if (graph[next->y - 1][next->x] >= '1' && graph[next->y - 1][next->x] <= '9') 
            {
                nodeWeight = graph[next->y - 1][next->x] - '0';
            }
            else
            {
                nodeWeight = 0;
            }
            int tempCost = previousCostCalc(next) + nodeWeight; // Cost from current node to adjacent node
            int heuristicCost = manhattan(next->x, next->y - 1, goalx, goaly); // Heuristic cost from adjacent node to goal
            int totalCost = tempCost + heuristicCost; // Total cost

            int adjacentX = next->x;
            int adjacentY = next->y - 1;

            temp = new node(nodeWeight, adjacentX, adjacentY, tempCost, heuristicCost, totalCost, next);
            
            if(doesExist(visited, next->y - 1, next->x))
            {
                //cout << "already been there";
            }
            else
            {
                queue.push_back(temp);
            }
        }

        // Check the node below
        if(next != nullptr && graph[next->y + 1][next->x] != 'W')
        {
            if (graph[next->y + 1][next->x] >= '1' && graph[next->y + 1][next->x] <= '9') 
            {
                nodeWeight = graph[next->y + 1][next->x] - '0';
            }
            else
            {
                nodeWeight = 0;
            }
            int tempCost = previousCostCalc(next) + nodeWeight; // Cost from current node to adjacent node
            int heuristicCost = manhattan(next->x, next->y + 1, goalx, goaly); // Heuristic cost from adjacent node to goal
            int totalCost = tempCost + heuristicCost; // Total cost

            int adjacentX = next->x;
            int adjacentY = next->y + 1;

            temp = new node(nodeWeight, adjacentX, adjacentY, tempCost, heuristicCost, totalCost, next);
            
            if(doesExist(visited, next->y + 1, next->x))
            {
                //cout << "already been there";
            }
            else
            {
                queue.push_back(temp);
            }
        }


        if (next != nullptr) 
        {
            cout << endl <<"(" << next->x << "," << next->y << "), " << endl << endl;
        }
        if(next != nullptr && next->x == goalx && next->y == goaly)
        {
            cout << "lets goooo";
            break;
        }

        tempIt++;
    }
    */
    int whileIt = 0;
    //while loop until goal is found or queue is empty
    while(!goalFound && queue.size() > 0 && whileIt != 100)
    {
        //check queue for node with least total cost
        node* smallestNode = queue[0];
        int smallestIndex = 0, tempIndex = 0;
        for (auto it = queue.begin(); it != queue.end(); ++it)
        {
            node* currentNode = *it;
            if(currentNode->totalCost < smallestNode->totalCost)
            {
                smallestNode = currentNode;
                smallestIndex = tempIndex;
            }
            tempIndex++;
        }

        //just for checking the visited vector
        for (auto it = visited.begin(); it != visited.end(); ++it)
        {
            node* currentNode = *it;
        }

        //remove that node out of the queue
        
        if (smallestIndex < queue.size())
        {
            queue.erase(queue.begin() + smallestIndex);
        } 
            

        //create each child node
        int childWeight = 0, childX, childY, childPastCost, childFutureCost, childTotalCost;
        for(int i = 0; i < 8; i++)
        {
            childWeight = 0;
            //top left corner
            if(i == 0)
            {
                childX = smallestNode->x - 1;
                childY = smallestNode->y - 1;
            }
            //top middle
            else if(i == 1)
            {
                childX = smallestNode->x - 1;
                childY = smallestNode->y;
            }
            //top right corner
            else if(i == 2)
            {
                childX = smallestNode->x - 1;
                childY = smallestNode->y + 1;
            }
            //middle right
            else if(i == 3)
            {
                childX = smallestNode->x;
                childY = smallestNode->y + 1;
            }
            //bottom right corner
            else if(i == 4)
            {
                childX = smallestNode->x + 1;
                childY = smallestNode->y + 1;
            }
            //bottom middle
            else if(i == 5)
            {
                childX = smallestNode->x + 1;
                childY = smallestNode->y;
            }
            //bottom left corner
            else if(i == 6)
            {
                childX = smallestNode->x + 1;
                childY = smallestNode->y - 1;
            }
            //middle left
            else if(i == 7)
            {
                childX = smallestNode->x;
                childY = smallestNode->y - 1;
            }

            if(graph[childY][childX] != 'W')
            {
                if(graph[childY][childX] >= '0' && graph[childY][childX] <= '9')
                {
                    childWeight =  graph[childY][childX] - '0';
                }

                //if child is the goal, stop
                if(childX == goalx && childY == goaly)
                {
                    goalFound = true;
                    cout << endl << endl << "Optimum path: (" << goalx << ", " << goaly << ") ";
                    while(smallestNode != nullptr)
                    {
                        finishedGraph[smallestNode->y][smallestNode->x] = 'X';
                        cout << "(" << smallestNode->x << ", " << smallestNode->y << ") ";
                        smallestNode = smallestNode->previous;
                    }
                    finishedGraph[starty][startx] = 'S';
                    finishedGraph[goaly][goalx] = 'G';
                    cout << endl << endl;
                    break;
                }

                //calculate g, h and f
                childPastCost = smallestNode->previousCost + 1 + childWeight;
                childFutureCost = manhattan(childX, childY, goalx, goaly);
                childTotalCost = childPastCost + childFutureCost;
                node* newChild = new node(childWeight, childX, childY, childPastCost, childFutureCost, childTotalCost, smallestNode);

                bool inQueue = false, inVisited = false;
                //if this child exists in the queue
                for (auto it = queue.begin(); it != queue.end(); ++it)
                {
                    node* currentNode = *it;
                    if(currentNode->x == childX && currentNode->y == childY)
                    {
                        //if it has larger f value than on the queue, stop (might have issues)
                        if(currentNode->totalCost <= childTotalCost)
                        {
                            inQueue = true;
                        }
                    }
                }

                //if this child exists on the visited list
                for (auto it = visited.begin(); it != visited.end(); ++it)
                {
                    node* currentNode = *it;
                    if(currentNode->x == childX && currentNode->y == childY)
                    {
                        //if child has higher f than one on visited, dont add it
                        if(currentNode->totalCost <= childTotalCost)
                        {
                            inVisited = true;
                        }
                    }
                }
                if(!inVisited && !inQueue)
                {
                    queue.push_back(newChild);
                }
            }
        }
        //add the node from the start to visited
        visited.push_back(smallestNode);

        if(queue.size() == 0)
        {
            cout << "queue is empty" << endl;
        }
        whileIt++;
    }

    //printing the finished graph
    cout << "___________________________________________" << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << "| ";
        for (int j = 0; j < 20; j++)
        {
            cout << finishedGraph[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "___________________________________________" << endl;

    return 0;
}

