// C++ Example Ford Fulkerson Algorithm

/* Ford Fulkerson Algorithm:

    // 0. Initialize an adjacency matrix to represent our graph.
    // 1. Create the residual graph. (Same as the original graph.)
    // 2. Create an default parent vector for BFS to store the augmenting path.
    // 3. Keep calling BFS to check for an augmenting path (from the source to the sink...
    // 4. Find the max flow through the path we found.
    // 5. Update the residual capacities of the edges and reverse edges.
    // 6. Add this path's flow to our total max flow so far.

*/

// The example graph: https://www.srcmake.com/uploads/5/3/9/0/5390645/maxflow_1_orig.jpg

// See the picture here: https://www.srcmake.com/uploads/5/3/9/0/5390645/adjmatrix_1_orig.jpg


// -----------------------------------------------------------------

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector< vector<int> > FormAdjMatrix()
{

    // Our adjacency list.

    vector< vector<int> > adjMatrix;

            const int n = 6;

            // Initialize our matrix to all 0s.

    for(int i = 0; i < n; i++)
    {

        vector<int> row;
        adjMatrix.push_back(row);
        for(int j = 0; j < n; j++)
            {
            adjMatrix[i].push_back(0);
            }
        }

    // First number is the vertex, second is the edge capacity.

    adjMatrix[0][1] = 15;
    adjMatrix[0][2] = 12;
    adjMatrix[1][2] = 9;
    adjMatrix[1][3] = 11;
    adjMatrix[2][1] = 5;
    adjMatrix[2][4] = 13;
    adjMatrix[3][2] = 9;
    adjMatrix[3][5] = 25;
    adjMatrix[4][3] = 8;
    adjMatrix[4][5] = 6;

    // Our graph is now represented as an adjacency list.

    return adjMatrix;

}



// A special BFS version that returns true if there's a path from source to sink.

bool BFS(vector< vector<int> > &resAdjMatrix, int &source, int &sink, vector<int> &parent)
{
    // Create an array for all nodes we visited. Initialized to false.

    int n = resAdjMatrix.size();
    bool visited[n] = { false };

    // Create a queue to check each node.

    queue<int> q;

    // Push our source into the queue and mark it as visited. It has no parent.

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    // Keep visiting vertices.

    while(q.empty() == false)
        {
        int u = q.front();
        q.pop();

        // Check all of u's friends.

        for(int i = 0; i < n; i++)
            {
            int v = i;
            int capacity = resAdjMatrix[u][v];

            // We find a neighbor that hasn't been visited, and the capacity is bigger than 0.

            if(visited[v] == false && capacity > 0)
                {
                // Push the neighbor onto the queue, mark it's parent, and mark it as visited.

                q.push(v);
                parent[v] = u;
                visited[v] = true;
                }
            }
}

    // If the sink got visited, then we found a path to it.

    if(visited[sink] == true)
    {
return true;
      }

    return false;
}


// Use the Ford Fulkerson algorithm. Return the max flow.

int FordFulkerson(vector< vector<int> > &adjMatrix, int &source, int &sink)
{
    int maxflow = 0;

    // 1. Create the residual graph. (Same as the original graph.)

    vector< vector<int> > resAdjMatrix;
    int n = adjMatrix.size();
    for(int i = 0; i < n; i++)
        {
        vector<int> row;
        resAdjMatrix.push_back(row);
        for(int j = 0; j < adjMatrix[i].size(); j++)
            {
            resAdjMatrix[i].push_back(adjMatrix[i][j]);
            }
        }

    // 2. Create an empty parent array for BFS to store the augmenting path.

    vector<int> parent;
    for(int i = 0; i < n; i++)
        {
        parent.push_back(-1);
        }

    // 3. Keep calling BFS to check for an augmenting path (from the source to the sink...

    while(BFS(resAdjMatrix, source, sink, parent) == true)
        {
        // 4. Find the max flow through the path we just found.

        int pathflow = 10000007;

        // Go through the path we just found. Iterate through the path.
        int v = sink;
        while(v != source)
            {
            int u = parent[v]; // The parent.

            // Update the pathflow to this capacity if it's smaller
            int capacity = resAdjMatrix[u][v];
            pathflow = min(pathflow, capacity);

            // Setup for the next edge in the path.
            v = u;
            }

        // 5. Update the residual capacities of the edges and reverse edges.

        v = sink;
        while(v != source)
            {
            int u = parent[v]; // The parent.

            // Update the capacities.

            resAdjMatrix[u][v] -= pathflow;
            resAdjMatrix[v][u] += pathflow;

            // Setup for the next edge in the path.
            v = u;
            }

        // 6. Add this path's flow to our total max flow so far.
        maxflow += pathflow;
        }

    return maxflow;
}


int main()
{
    cout << "Program started.\n";

    // Create our adjacency list.

    vector< vector<int> > adjMatrix = FormAdjMatrix();

    // Call FordFulkerson to get the max flow from the source to the sink.

    int source = 0;
    int sink = 6;

    for(int i = 0; i < 6; i++)
        {
        for(int j = 0; j < 6; j++)
            {
            int source = i;
            int sink = j;

            if(i == j)
{
continue;
}

            cout << "The max flow from " << source << " to " << sink << " is: ";
            cout << FordFulkerson(adjMatrix, source, sink) << endl;
            }
        cout << endl;
        }


    cout << "Program ended.\n";

    return 0;
}
