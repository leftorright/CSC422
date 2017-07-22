//
// Clement.cpp
// Finds a minimum dominating set of a graph.
// TO RUN: ./a.out <verbosity>  <  <input file>  >  <output file>
//
// Created by Stephanie Clement on 2017-07-13.
//

#include <stdio.h>
#include <stdlib.h>
#define NMAX 2187
#define DEG_MAX 16
#define DEBUG 0

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
};

/* print_vector()
 *
 * prints the contents of an array
 * input: size - number of elements in the array
 *        dom - an integer array
 */
void print_vector(int size, int *dom) {
    if (size == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d ", dom[i]);
    }
    printf("]\n");
}
/*
 * get_next_int()
 * reads the next integer from stdin
 * input:  num - int ptr
 * output: 1 if successfully read in an integer
 *         0 otherwise
 */
int get_next_int(int *num, int graph_num)
{
    int ret = scanf("%d", num);
    if (ret == 1) {
        return 1;
    }
    else if (ret == EOF) {
#if DEBUG
        printf("Normal termination occurred. %d graphs read in\n", graph_num-1);
#endif
    } else {
        printf("Error reading in graph %d\n", graph_num);
    }
    return 0;
}
/*
 * initialize_min_dom_set()
 * initializes the data structures needed for determining a minimum dominating set of the input graph.
 * input: graph - graph_s ptr for storing graph/dominating set information
 */
void initialize_min_dom_set(graph_s *graph)
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

/* array_copy()
 * copies an array from src into output
 * input: src - input array
 *        output - output array
 *        size - number of integers to copy
 */
void array_copy(int *src, int *output, int size)
{
    for (int i = 0; i < size; i++) {
        output[i] = src[i];
    }
}
/*
 * color_blue()
 * labels vertex u as not part of the dominating set
 * decrements the number of choices for dominating vertex u and its neighbours.
 * If it does not make sense to color vertex u blue (i.e vertex u or one of its neighbours can't be dominated
 * if vertex u is colored blue) then num_choice is not decremented and the function returns 0.
 * input: G - graph_s ptr
 *        u - vertex u to be colored blue
 * output: 1 - if vertex u is colored blue
 *         0 - if vertex u should not be colored blue
 */
int color_blue(graph_s *G, int u)
{
    //check if we should color vertex blue
    if (G->num_choice[u] == 1) {
        return 0;
    }
    for (int i = 0; i < G->degree[u]; i++){
        int v = G->G[u][i];
        if (G->num_choice[v] == 1) {
            return 0;
        }
    }
    // color blue
    for (int i = 0; i < G->degree[u]; i++){
        int v = G->G[u][i];
        G->num_choice[v]--;
    }
    G->num_choice[u]--;
    return 1;
}
/*
 * uncolor_blue()
 * removes vertex u from the set of vertices not in the dominating set.
 * increments the number of choices for dominating vertex u and its neighbours after changing
 * "color" of vertex u from blue to red
 * input: G - graph_s ptr
 *        u - vertex colored red
 */
void uncolor_blue(graph_s *G, int u)
{
    G->num_choice[u]++;
    for (int i = 0; i < G->degree[u]; i++){
        int v = G->G[u][i];
        G->num_choice[v]++;
    }
}
/* inc_num_dominated()
 * updates the number of times vertices are dominated after vertex u is "colored red"
 * (added to the dominating set)
 * input: G - graph_s ptr
 *        u - vertex removed from dominating set
 */
void inc_num_dominated(graph_s *G, int u)
{
    G->num_dominated[u]++;
    for (int i = 0; i < G->degree[u]; i++)
    {
        int v = G->G[u][i];
        G->num_dominated[v]++;
    }
}

/*
 * update_n_dominated()
 * updates the number of dominated vertices in the graph after vertex u is "colored red"
 * input: G - graph_s ptr
 *        u - vertex that was "colored red" (added to dominating set)
 */
void update_n_dominated(graph_s *G, int u)
{
    for (int i = 0; i < G->size; i++){
        if (G->dom[i] == u){
            return;
        }
    }
    for (int i = 0; i < G->degree[u]; i++) {
        if (G->num_dominated[G->G[u][i]] == 0) {
            G->n_dominated++;
        }
    }
    if (G->num_dominated[u] == 0) {
        G->n_dominated++;
    }
}
/*
 * update_dom()
 * updates dominating set to add vertex u
 * input: G - graph_s ptr
 *        u - vertex added to the dominating set
 */
void update_dom(graph_s *G, int u)
{
    G->dom[G->size] = u;
    G->size++;
}

/*
 * color_red()
 * adds vertex u to the dominating set
 * input: G - graph_s ptr of graph
 *        u - vertex number added to dominating set
 */
void color_red(graph_s *G, int u) {
    update_n_dominated(G, u);
    inc_num_dominated(G, u);
    update_dom(G, u);
}
/*
 * color_white()
 * restores data structures.
 * Required for "coloring a vertex u white"
 * updates data structures so that a vertex u is no longer colored "red"
 * input: G - graph_s pointer
 *        u - vertex to be updated
 */
void color_white(graph_s *G, int u)
{
    // decrement num_dominated[v] - v neighbour of u and num_dominated[u]
    G->num_dominated[u]--;
    for (int i = 0; i < G->degree[u]; i++)
    {
        int v = G->G[u][i];
        G->num_dominated[v]--;
    }
    // check if neighbours num_dominated go to 0 and then decrease those and itself
    for (int i = 0; i < G->degree[u]; i++)
    {
        int v = G->G[u][i];
        if (G->num_dominated[v] == 0){
            G->n_dominated--;
        }
    }
    if (G->num_dominated[u] == 0) {
        G->n_dominated--;
    }
    // decrement size
    G->size--;
}
/*
 * min_dom_set()
 * Finds a minimum dominating set of a graph.
 * Input: G - graph_s pointer
 *        level - indicates the level of recursion
 */
void min_dom_set(int level, graph_s *G)
{
#if DEBUG
    printf("\n");
    printf("Level %3d: \n", level);
    printf("Dom set size:%d\n", G->size);
    printf("Dom: ");
    print_vector(G->size, G->dom);
    printf("Number of vertices dominated: %3d\n",
           G->n_dominated);
    printf("Number of choices per vertex:\n");
    print_vector(G->n, G->num_choice);
    printf("Number of times dominated:\n");
    print_vector(G->n, G->num_dominated);
#endif

    if (G->n_dominated == G->n || level == G->n) {
        if (G->size < G->min_size) {
            array_copy(G->dom, G->min_dom, G->size);
            G->min_size = G->size;
        }
        return;
    }
    int n_extra = (G->n - G->n_dominated + G->max_degree) / (G->max_degree + 1);
    if ((G->size + n_extra) >= G->min_size)
        return;

    // color vertex blue if ret is 0 then it doesn't make sense to color it blue, so
    // skip to coloring vertex red
    int ret = color_blue(G, level);
    if (ret) {
        min_dom_set(level + 1, G);
        uncolor_blue(G, level);
    }
    // color vertex red
    color_red(G, level);
    min_dom_set(level + 1, G);

    // color vertex white
    color_white(G, level);
    return;
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
        if (get_next_int(&i_degree, G->graph_num) && i_degree <= DEG_MAX ) {
            G->degree[i] = i_degree;
            if (i_degree > max_degree)
                max_degree = i_degree;
            for (int j = 0; j < i_degree; j++)
            {
                if(!get_next_int(&neighbour, G->graph_num)) {
                    printf("Error: graph:%d vertex:%d is missing neighbour in position:%d\n", G->graph_num, i, j);
                    exit(0);
                }

                G->G[i][j] = neighbour;
            }
        } else {
            printf("Error: vertex %d has invalid degree=%d\n", i, i_degree);
            exit(0);
        }
    }
    G->max_degree = max_degree;
    return 1;
}
/*
 * print_certificate()
 * given a graph it prints the dominating set certificate.
 * if verbose print:
 *      <number of vertices>
 *      <degree of vertex 0> <neighbour 1 of vertex 0> <neighbour 2 of vertex 0> ...
 *          ...
 *      <size of dominating set>
 *      <vertices of dominating set>
 *
 * input: G - graph_s pointer
 *        verbose - the verbosity of the output
 */
void print_certificate(graph_s *G, int verbose)
{
    if (!verbose) {
        printf("%5d %3d %3d\n", G->graph_num, G->n, G->min_size);
        fflush(stdout);
    } else {
        printf("%d\n", G->n);
        // print the graph in adj list format (with degree)
        for (int i = 0; i < G->n; i++) {
            printf("%d ", G->degree[i]);
            for (int j = 0; j < G->degree[i]; j++) {
                printf("%d ", G->G[i][j]);
            }
            printf("\n");
        }
        // print size of dominating set and dominating set vertices
        printf("\n%d\n", G->min_size);
        for (int i = 0; i < G->min_size; i++) {
            printf("%d ", G->min_dom[i]);
        }
        printf("\n\n");
        fflush(stdout);
    }
}
/* read_graph()
 *
 * read from stdin a graph in adj list format
 * input: graph - graph_s pointer
 *        verbose - the verbosity required for the output
 */
int read_graph(graph_s *graph, int graph_num)
{
    if (get_next_int(&graph->n, graph_num)) {
        graph->graph_num = graph_num;
        get_adj_list(graph);
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    int verbose = atoi(argv[1]);
    if (!(verbose == 0 || verbose == 1))
    {
        printf("Error: verbose flag must be set to 0 or 1.\n");
        return 0;
    }
    graph_s graph;
    int graph_num = 1;
    while (read_graph(&graph, graph_num)) {
        initialize_min_dom_set(&graph);
        min_dom_set(0, &graph);
        print_certificate(&graph, verbose);
        graph_num++;
    }

    return 0;
}