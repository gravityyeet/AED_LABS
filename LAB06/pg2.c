#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"LinkedList.h"

struct Edge {
    int V, W, val;
};

void free_tabela(int **, int);
int compare_items(Item, Item);
void free_node(Item);


int main(int argc, char** argv) {
    int **tabela;
    int V = 0, E = 0, i = 0, j = 0;
    FILE *fp;
    Item node;
    LinkedList *head;
    LinkedList *l_node;
    int err = 0;
    Item teste;
    char *str_out, *aux;

    if (argc < 1) {
        exit(0);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(0);
    }

    if (fscanf(fp, "%d %d ", &V, &E) != 2) {
        exit(0);
    }

    /* Alocaçao dinamica do array 2D */
    tabela = (int **) malloc(sizeof(int *) * E);
    if (tabela == NULL) {
        exit(0);
    }
    for (i = 0; i < E; i++) {
        tabela[i] = (int *) malloc(sizeof(int) * 3);
        if (tabela[i] == NULL) {
            exit(0);
        }
    }

    while (!feof(fp)) {
        for (i = 0; i < E; i++) {
            for (j = 0; j < 3; j++) {
                if (fscanf(fp, "%d ", &tabela[i][j]) != 1) {
                    exit(0);
                }
            }
        }
    }
    fclose(fp);

    /* Passagem dos dados para uma lista */
    head = initLinkedList();
    node = (Item) calloc(2*E, sizeof(Item) + sizeof(struct Edge));

    for (i = 0, j = 0; i < E; i++) {
        node[j].V = tabela[i][0];
        node[j].W = tabela[i][1];
        node[j].val = tabela[i][2];
        head = insertSortedLinkedList(head, &node[j], compare_items, &err);
        j++;
        if (head == NULL)
            exit(0);

        node[j].V = tabela[i][1];
        node[j].W = tabela[i][0];
        node[j].val = tabela[i][2];
        head = insertSortedLinkedList(head, &node[j], compare_items, &err);
        j++;
        if (head == NULL)
            exit(0);
    }

    /* Print da lista de adjacencias */
    l_node = head;

    aux = strtok(argv[1], ".");

    str_out = (char *) malloc(strlen(aux) + 6);
    strcpy(str_out, aux);
    strcat(str_out, ".ladj");
    fp = fopen(str_out, "w");

    fprintf(fp, "%d\n", V);
    for (j = 0; j < V; j++) {
        if (l_node == NULL) {
            fprintf(fp, "-1\n");
            break;
        }

        while (((teste = getItemLinkedList(l_node))->V) == j) {
            fprintf(fp, "%d:%d ", teste->W, teste->val);
            l_node = getNextNodeLinkedList(l_node);
            if (l_node == NULL) break;
        }
        fprintf(fp, "-1\n");
    }

    /* PRINTS DEBUG 
    for (i = 0; i < E; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", tabela[i][j]);
        }
        printf("\n");
    }*/

    /* Free de tudo */
    free(str_out);
    free_tabela(tabela, E);
    free(node);
    freeLinkedList_Normal(head);
    fclose(fp);

    return 1;
}

void free_tabela(int **tabela, int E) {
    int i = 0;
    for (i = 0; i < E; i++) {
        free(tabela[i]);
    }
    free(tabela);
}

int compare_items(Item i1, Item i2) {
    if (i1->V < i2->V) {
        return -2;
    } else if (i1->V > i2->V) {
        return 2;
    } else {
        if (i1->W < i2->W) {
            return -2;
        } else if (i1->W > i2->W) {
            return 2;
        } else {
            return 0;
        }
    }
}