#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void criar_tabela(char *);
void free_tabela(int **, int);
int graph_density(int **, int);
void graph_maxdegree(int **, int);
void all_edges(char *, int **, int, int);

int main(int argc, char** argv) {

    if (argc < 1) {
        exit(0);
    }
    criar_tabela(argv[1]);

    return 1;
}

void criar_tabela(char *filename) {
    int **tabela;
    int V = 0, i = 0, j = 0;
    int D = 0;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(0);
    }

    if (fscanf(fp, "%d ", &V) != 1) {
        exit(0);
    }

    /* Alocaçao dinamica do array 2D */
    tabela = (int **) malloc(sizeof(int *) * V);
    if (tabela == NULL) {
        exit(0);
    }
    for (i = 0; i < V; i++) {
        tabela[i] = (int *) malloc(sizeof(int) * V);
        if (tabela[i] == NULL) {
            exit(0);
        }
    }

    while (!feof(fp)) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (fscanf(fp, "%d ", &tabela[i][j]) != 1) {
                    exit(0);
                }
            }
        }
    }

    /* PRINTS DEBUG */
    printf("%d\n", V);
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            printf("%d ", tabela[i][j]);
        }
        printf("\n");
    }
    /* Impressoes no terminal de dados do grafo */
    D = graph_density(tabela, V);
    graph_maxdegree(tabela, V);
    all_edges(filename, tabela, V, D);

    free_tabela(tabela, V);

    fclose(fp);
}

void all_edges(char *filename, int **tabela, int V, int D) {
    char *aux, *str_out;
    FILE *fp;
    int i, j;

    /* Tratar do nome do ficheiro out */
    aux = strtok(filename, ".");

    str_out = (char *) malloc(strlen(aux) + 6);
    strcpy(str_out, aux);
    strcat(str_out, ".edge");

    /* Criar ficheiro e colocar os dados out la */

    fp = fopen(str_out, "w");
    fprintf(fp, "%d %d\n", V, D);

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (tabela[i][j] != 0) {
                fprintf(fp, "%d %d %d\n", i, j, tabela[i][j]);
                tabela[j][i] = 0;
            }
        }
    }

    free(str_out);
    fclose(fp);
}

void free_tabela(int **tabela, int V) {
    int i = 0;
    for (i = 0; i < V; i++) {
        free(tabela[i]);
    }
    free(tabela);
}

int graph_density(int **tabela, int V) {
    int i, j, edges = 0;

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (tabela[i][j] != 0) {
                edges++;
            }
        }
    }
    printf("Densidade:\t%f\n", (double) edges / V);
    return edges / 2;
}

void graph_maxdegree(int **tabela, int V) {
    int i, j, degree = 0, max = 0;

    for (i = 0; i < V; i++, degree = 0) {
        for (j = 0; j < V; j++) {
            if (tabela[i][j] != 0) {
                degree++;
            }
        }
        if (max < degree) {
            max = degree;
        }
    }
    printf("Grau maximo:\t%d\n", max);
}