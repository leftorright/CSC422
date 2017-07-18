//
// Created by Stephanie Clement on 2017-05-03.
//
#include <stdio.h>
#include <stdlib.h>

#define NMAX 2187
//If NMAX is not big enough, print an error message that explains that the user should increase NMAX and recompile.

/*
 * getNextInt()
 *
 * reads the next integer from standard input
 *
 * input:
 *   num_p: a pointer where the next integer from stdin will be stored
 *
 * output:
 *   returns 1 if successful, otherwise returns 0
 */
int getNextInt(int *num_p)
{
    int ret = scanf("%d", num_p);
    if (ret == 0 || ret == EOF)
    {
        return 0;
    }

    return 1;
}
/*
 * checkGraph()
 *
 * Checks if a graph is valid
 *
 * input:
 *   N: the number of vertices in the graph
 *  adjList_p: a 2d integer vector pointer storing the adj list of the graph
 *  error_msg: buffer to hold an error message (if checkGraph is unsuccessful)
 *
 * output:
 *  1 if successful, otherwise 0
 */
int checkGraph(int N,
               int adjList[NMAX][NMAX],
               char *error_msg)
{
    int ret = 1;
    // iterate through every vertex in the graph
    for (int i = 0; i < N; i++)
    {
        int degree = adjList[i][0];
        for (int j = 1; j <= degree; j++)
        {
            // check vertex is valid
            int vertexNum = adjList[i][j];
            if((vertexNum > N) || (vertexNum < 0)){
                sprintf(error_msg, "Error- Value %d in the graph is not in range [%d,%5d]\n", vertexNum, 0, N);
                ret = 0;
            }
            // check for duplicate edge
            for (int k = 1; k < j; k++)
            {
                if (adjList[i][j] == adjList[i][k]){
                    // duplicate edge found in graph
                    sprintf(error_msg, "duplicate edge found in graph: %d-%d\n", i, adjList[i][j]);
                    ret = 0;
                }
            }

            int found = 0;
            for (int k = 1; k <= adjList[vertexNum][0]; k++)
            {
                // check there is a corresponding edge vertexNum - i
                if (adjList[vertexNum][k] == i){
                    found = 1;
                }
            }
            if(!found) {
                sprintf(error_msg, "*** Error- adjacency matrix is not symmetric: "
                        "A[ %d][ %d] = %d, A[ %d][ %d] = %d", i, j, 1, j, i, 0);
                ret = 0;
            }
        }
    }
    return ret;
}

/*
 * createAdjList()
 * fills a 2-d array to represent a graph in adj list format
 *
 * input:
 *   N: the number of vertices in the graph
 *   adjList: an empty 2d integer vector pointer for storing the adj list
 *   error_msg: a buffer to hold an error message (if createAdjList unsuccessful)
 *
 * output:
 *   1 if successful, otherwise 0
 */
int createAdjList(int N,
                  int (*adjList_p)[NMAX][NMAX],
                  char *error_msg)
{
    for(int i = 0; i < N; i++) {
        // get the degree of vertex i
        int degree;
        if (!getNextInt(&degree)){
            printf("Error- Graph has fewer than N vertices\n");
            exit(0);
        }
        (*adjList_p)[i][0] = degree;
        if ((degree > N-1) || (degree < 0))
        {
            printf("Error- Vertex %d has %d vertices\n", i, degree);
            exit(0);
        }

        // add the neighbours to vertex i into the adj list
        int tmp;
        for (int j = 1; j <= degree; j++)
        {
            if(!getNextInt(&tmp)) {
                printf("Error- Graph has an invalid degree for vertex %d\n", i);
                exit(0);
            }
            (*adjList_p)[i][j] = tmp;
        }
    }
    if (!checkGraph(N, *adjList_p, error_msg)) {
        return 0;
    }
    return 1;
}

/*
 * printGraph()
 * prints the graph to standard output
 *
 * input:
 *   graph_p: a pointer to a 2d integer array containing the graph in adj list format
 *   graph_num: The i-th graph read in starting from 1
 *   N: the number of vertices in the graph
 *
 */

void printGraph(int (*graph_p)[NMAX][NMAX], int graph_num, int N){
    for(int i = 0; i < N; i++)
    {
        printf("%3d(%2d):", i, (*graph_p)[i][0]);
        for(int j = 1; j <= (*graph_p)[i][0]; j++)
        {
            printf("%4d", (*graph_p)[i][j]);
        }
        printf("\n");
    }
}
/*
 * printDominatingSet()
 * prints the dominating set to standard output
 *
 * input:
 *   vec_p: pointer to an array of integers
 *   k: number of vertices in the dominating set
 */

void printDominatingSet(int (*vec_p)[NMAX], int k){
    for(int i = 0; i < k; i++)
    {
        printf("%4d", (*vec_p)[i]);
    }
    printf("\n");
}

/*
 * getCertificate()
 *
 * reads in the certificate (dominating set) from stdin
 *
 * input:
 *   k: number of vertices in the dominating set (certificate)
 *   N: number of vertices in the graph
 *   array: pointer to an (empty) array of integers
 *   error_msg: buffer for storing an error message (if getCertificate fails)
 *
 * output:
 *   1 if successful otherwise 0
 */
int getCertificate(int k,
                   int N,
                   int (*array)[NMAX],
                   char *error_msg)
{
    int vertex;
    int ret = 1;
    for(int i = 0; i < k; i++)
    {
        if(!getNextInt(&vertex)){
            sprintf(error_msg, "Error- Value k=%d is invalid\n", k);
            return 0;
        }
        if((vertex >= N) || (vertex < 0))
        {
            sprintf(error_msg, "Error- Value %4d in the certificate is not in the range [0,%4d]",
                    vertex, N-1);
            ret = 0;
        }
        (*array)[i] = vertex;
    }
    return ret;
}

/*
 * isDominatingSet()
 * Check if a set of vertices is a dominating set for a particular graph
 *
 * input:
 *    N: the number of vertices in the graph
 *    graph: a pointer to a 2d vector of integers representing the adj list of a graph
 *    certificate: a  pointer to the vector of integers of the proposed dominating set
 *    error_msg: a buffer for writing an error message
 *    k is the dominating set size
 *
 * output:
 *   returns 1 if dominating set, otherwise returns 0
 */
int isDominatingSet( int N,
                     int (*graph)[NMAX][NMAX],
                     int (*certificate)[NMAX],
                     char *error_msg,
                     int k)
{
    // for each vertex in certificate mark a boolean array for itself and its neighbours
    int dominated_vertices[N];
    // initialize structure with zeros
    for (int i = 0; i < N; i++)
    {
        dominated_vertices[i] = 0;
    }

    for(int i = 0; i < k; i++)
    {
        // get vertex in certificate
        int vertex = (*certificate)[i];
        // mark it as dominated
        dominated_vertices[vertex] = 1;
        // the the degree of that vertex
        int degree = (*graph)[vertex][0];

        // for each of the edges of vertex i mark those neighbours as dominated
        for(int j = 1; j <= degree; j++)
        {
            int vertex1 = (*graph)[vertex][j];
            dominated_vertices[vertex1] = 1;
        }

        for (int j = 1; j < i; j++)
        {
            if((*certificate)[j] == (*certificate)[i])
            {
                sprintf(error_msg, "Error - duplicate vertex: %d in dominating set", (*certificate)[i]);
                return 0;
            }
        }
    }
    // if every vertex is marked return 1 else return 0
    for(int i = 0; i < N; i++)
    {
        if(dominated_vertices[i] == 0)
        {
            sprintf(error_msg, "Error- Vertex %4d is not dominated", i);
            return 0;
        }
    }

    return 1;
}

/*
 * writeOutput()
 * prints the results of checking the graph for a particular dominating set.
 *
 * input:
 *  isDominatingSet: code determining whether check was successful
 *                   and whether the set was a dominating set
 *  verbose: flag for style of output
 *  graph: pointer to a 2d array representing the graph
 *  certificate: pointer to an array representing the proposed dominating set
 *  graph_num: the i-th graph read (starting at 1)
 *  error_msg: error message buffer
 *  N: number of vertices in the graph
 *  k: number of vertices in the dominating set
 *
 */
void writeOutput( int isDominatingSet,
                  int verbose,
                  int (*graph)[NMAX][NMAX],
                  int (*certificate)[NMAX],
                  int graph_num,
                  char* error_msg,
                  int N,
                  int k)
{
    if(verbose) {
        printf("Graph %4d:\n", graph_num);
        printGraph(graph, graph_num, N);

        if (isDominatingSet == -1)
        {
            printf("%s\n", error_msg);
            printf("Graph %5d: BAD GRAPH\n", graph_num);
        } else if (isDominatingSet == 1)
        {
            printf("Proposed dominating set:\n");
            printDominatingSet(certificate, k);
            printf("Graph%5d: OK\n", graph_num);

        } else {
            printf("Proposed dominating set:\n");
            printDominatingSet(certificate, k);
            printf("%s\n", error_msg);
            printf("Graph %5d: BAD CERTIFICATE\n", graph_num);
        }
        printf("=============================\n");
    } else {
        printf("%5d", graph_num);
        int value;
        if (isDominatingSet == -1) {
            value = -1;
        } else if (isDominatingSet == 1)
        {
            value = 1;
        } else
        {
            value = 0;
        }
        printf("%3d\n", value);
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Error: wrong number of command lines arguments\n");
        return 0;
    }

    int verbose = atoi(argv[1]);
    if (!(verbose == 0 || verbose == 1))
    {
        printf("Error: verbose flag must be set to 0 or 1.\n");
        return 0;
    }

    int size_of_graph;
    int graph_count = 1;
    printf("1\n");
    fflush(stdout);
    /* while there are integers to be read in from stdin, create the adj list and check the dominating set */
    while(getNextInt(&size_of_graph)) {

        if (size_of_graph <= 0) {
            printf("Error: N = %d. Please set to an appropriate value\n", size_of_graph);
            return 0;
        }

        static int graph[NMAX][NMAX];
        int certificate[NMAX];
        char error_msg[255];
        int error_num;

        if (!createAdjList(size_of_graph, &graph, error_msg)) {
            /* Invalid graph print out results and quit */
            writeOutput(-1, verbose, &graph, &certificate, graph_count, error_msg, size_of_graph, 0);
            return 0;
        }

        int k;
        if (getNextInt(&k)) {
            /* check if the certificate represents a valid dominating set */
            if (!getCertificate(k, size_of_graph, &certificate, error_msg)) {
                error_num = -2;
            } else {
                error_num = isDominatingSet(size_of_graph, &graph, &certificate, error_msg, k);
            }
        }

        writeOutput(error_num, verbose, &graph, &certificate, graph_count, error_msg, size_of_graph, k);
        graph_count++;
    }
    return 0;
}