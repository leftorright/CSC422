//
// Created by Stephanie Clement on 2017-07-13.
//

#include <stdio.h>
#include <stdlib.h>
#define NMAX 2187
#define DEG_MAX 16
#define DEBUG 1

struct graph_s {
    int n;
    int degree[NMAX]; /* max degree? */
    int max_degree;
    int G[NMAX][DEG_MAX];
    int graph_num;
    int n_dominated;
    int num_choice[NMAX];
    int num_dominated[NMAX];
    int size;
    int dom[NMAX];
    int min_size;
    int min_dom[NMAX];
    int verbose;
};
/* print_vector()
 *
 * prints the contents of an array
 * input: size - number of elements in the array
 *        dom - an array
 */
print_vector(int size, int *dom) {
    for (int i = 0; i < size; i++) {
        print("%d: %d", i, dom[i]);
    }
}
/* verbose=0    <graph num> <degree of vertices> <dominating set order>
 * printf("%5d %3d %3d\n", graph_i_degree, n, min);
 *
 * verbose=1    <degree of vertices>
 *              <degree of v> <neighbours of v>
 *              ...
 *              <k>
 *              < k integers representing vertices of dominating set>
 */

/* get_next_int()
 *
 * reads the next character from stdin
 * input: int ptr
 * output: 1 if successful, 0 otherwise
 */
int get_next_int(int *num)
{
    int ret = scanf("%d", num);
    if (ret == 0 || ret == EOF)
    {
        return 0;
    }
    return 1;
}
/* get_adj_list()
 *
 * reads in graph from standard input
 * input: G the graph to be read from stdin
 * output: 1 if successful
 */
int get_adj_list(graph_s *G)
{
    int max_degree = 0;
    for(int i = 0; i < G->n; i++) {
        int i_degree;
        int neighbour;

        if (get_next_int(&i_degree) && i_degree <= DEG_MAX ) {
            G->degree[i] = i_degree;
            if (i_degree > max_degree)
                max_degree = i_degree;
            for (int j = 1; j <= i_degree; j++)
            {
                if(!get_next_int(&neighbour)) {
                    printf("Error: graph:%d vertex:%d is missing neighbour in position:%d\n", G->graph_num, i, j);
                    exit(0);
                }

                G->G[i][j] = neighbour;
            }
        } else { 
            printf("Error: vertex %d has invalid degree=%d\n", i, i_degree);
            exit(0);
        }
        G->max_degree = max_degree;
        return 1;
    }
}
int initialize_BFS(graph_s *graph)
{
    for (int i=0; i < graph->n; i++){
        graph->num_choice[i] = graph->degree[i] + 1;
        graph->num_dominated[i] = 0;
        graph->min_dom[i] = i;
    }
    graph->n_dominated = 0;
    graph->size = 0;
    graph->min_size = graph->n;

}

void BFS(int level, graph_s *G)
{
#if DEBUG
    printf("Level %3d: ", level);
    print_vector(G->size, G->dom);
    printf("Number of vertices dominated: %3d\n",
           G->n_dominated);
    printf("Number of choices per vertex:\n");
    print_vector(G->n, G->num_choice);
    printf("Number of times dominated:\n");
    print_vector(G->n, G->num_dominated);
#endif

    for (int i = 0; i < G->n; i++) {
        if (G->num_choice[i] == 0)
            return;
    }
    int u = level;
    int n_extra = (G->n - G->n_dominated) / G->max_degree + 1; // XXX make this ceiling
    if ( (G->size + n_extra) >= G->min_size)
        return;

    G->num_choice[u]--;
    for (int i = 0; i < G->degree[u]; i++){
        int v = G->G[u][i];
        G->num_choice[v]--;
    }
}

/* read_graph()
 *
 * read from stdin a graph in adj list format
 * input: graph struct for to store graph info
 * output: 1 if successful, -1 otherwise
 */
int read_graph(graph_s *graph)
{
    graph->n = 0;
    graph->graph_num = 0;
    int *n = &graph->n;
    while (get_next_int(n)) {
        // check if i_degreeber of vertices in G is a valid i_degreeber
        if (*n <= 0 || *n > NMAX) {
            printf("Error: Invalid number of vertices: %d. Should be a value between 1 and 2187\n", n);
            return -1;
        }
        get_adj_list(graph);
    }
    return 1;
}

int main(int argc, char *argv[])
{
    graph_s graph;
    read_graph(&graph);
    initialize_BFS(&graph);
    BFS(0, &graph);
}