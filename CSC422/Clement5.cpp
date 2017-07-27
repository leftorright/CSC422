//
// Created by Stephanie Clement on 2017-07-25.
//
#include <stdio.h>
#include <stdlib.h>

#define NMAX 121

struct graph_t {
    int graph_permutations[968][121];
    int n;
    int group_order;
};

int getNextInt(int *num_p)
{
    int ret = scanf("%d", num_p);
    if (ret == 0 || ret == EOF)
    {
        return 0;
    }

    return 1;
}

void read_graph_permutations(graph_t *graph_permutations)
{
    getNextInt(&graph_permutations->n);
    getNextInt(&graph_permutations->group_order);


    for (int i = 0; i < graph_permutations->group_order; i++)
    {
        for (int j = 0; j < graph_permutations->n; j++)
        {
            getNextInt(&graph_permutations->graph_permutations[i][j]);
        }
    }
}

int read_dominating_set(int dominating_set[], int *n)
{
    getNextInt(n);
    int ret;
    for (int i = 0; i < *n; i++) {
        ret = getNextInt(&dominating_set[i]);
        if (ret == 0) {
            return 0;
        }
    }
    return 1;
}
void initialize_bit_array(int arr[], int size, int src[], int n, int empty)
{
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
    if (!empty) {
        for (int i = 0; i < n; i++) {
            arr[src[i]] = 1;
        }
    }
}
void copy_bit_array(int arr[], int src[], int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] = src[i];
    }
}
/*
 * a < b = -1
 * a = b = 0
 * a > b = +1
 */
int compare(int n, int a[], int b[])
{
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            continue;
        }
        if (a[i] < b[i]) {
            // then b is smaller
            return 1;
        }
        if (a[i] > b[i]) {
            return -1;
        }
    }
    return 0;
}
void print_auto_group(int dom[], int n, int automorphism_group_order)
{
    printf("%3d %3d ", automorphism_group_order, n);

    for (int i = 0; i < n; i++) {
        printf("%3d ", dom[i]);
    }
    printf("\n");
}
void get_dom_set(int dom[], int ret_dom[], int n)
{
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (dom[i] == 1) {
            ret_dom[index] = i;
            index++;
        }
    }
}
void get_automorphism_group_order(graph_t *graph_permutations, int dom[], int n)
{
    // create 'bit' arrays for dominating set
    int dom_bit_array[graph_permutations->n];
    initialize_bit_array(dom_bit_array, graph_permutations->n, dom, n, 0);
    int min_dom[graph_permutations->n];
    copy_bit_array(min_dom, dom_bit_array, graph_permutations->n);
    int current_dom[graph_permutations->n];
    int automorphism_counter = 0;

    // check which automorphism map dom set to itself
    for (int i = 0; i < graph_permutations->group_order; i++) {
        initialize_bit_array(current_dom, graph_permutations->n, dom, 0, 1);
        int check = 1;
        for (int j = 0; j < n; j++) {
            current_dom[graph_permutations->graph_permutations[i][dom[j]]] = 1;
            if (dom_bit_array[graph_permutations->graph_permutations[i][dom[j]]] == 0) {
               check = 0;
            }
        }
        if (check == 1) {
            automorphism_counter++;
        } else {
            int ret = compare(graph_permutations->n, min_dom, current_dom);
            if (ret == 1) {
                copy_bit_array(min_dom, current_dom,graph_permutations->n);
            }
        }
    }
    int dom_set[n];
    get_dom_set(min_dom, dom_set, graph_permutations->n);
    print_auto_group(dom_set, n, automorphism_counter);

}
int main()
{
    graph_t graph_permutations;
    int dominating_set[NMAX];
    read_graph_permutations(&graph_permutations);
    int n;
    while(read_dominating_set(dominating_set, &n)) {
        get_automorphism_group_order(&graph_permutations, dominating_set, n);
    }
}