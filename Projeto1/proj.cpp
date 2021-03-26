/**
 * Ficheiro: proj.cpp
 * Realizado por: David Belchior (95550) e Diogo Santos (95562)
 * Instituto Superior Tecnico - LEIC-A - Analise e Sintese de Algoritmos
 * Para compilar: g++ -std=c++11 -O3 -Wall proj.cpp -lm
*/

#include <iostream>
#include <vector>
#include <queue>

#define WHITE 1
#define GREY 0
#define BLACK -1

using namespace std;

typedef struct{
    int colour = WHITE;
    vector<int> adj;
} vertex;

vector<vertex> graph;
vector<vector<int>> graph_trans;

void readInput(){
    /**
     * Reads input from stdin and inicializes graph and graph_trans
    */
    int n, m;
    if (scanf("%d %d", &n, &m) < 0)
        exit(EXIT_FAILURE);
    if (n < 2 || m < 0){
        cout << "Input invalido. Tente de novo!" << endl;
        exit(EXIT_FAILURE);
    }

    graph = vector<vertex>(n);
    graph_trans = vector<vector<int>>(n, vector<int>());
    
    int u, v;
    for (int i = 0; i < m; ++i){
        if (scanf("%d %d", &u, &v) < 0)
            exit(EXIT_FAILURE);
        graph[u-1].adj.push_back(v-1);
        graph_trans[v-1].push_back(u-1);
    }
}

void printGraph(){
    /**
     * Prints graph
    */
    cout << "Graph:" << endl;
    for(unsigned int i = 0; i < graph.size(); ++i){
        cout << i+1 << " -> ";
        for(unsigned int j = 0; j < graph[i].adj.size(); ++j){
            cout << graph[i].adj[j]+1 << " ";
        }
        cout << endl;
    }
}

void printTransGraph(){
    /**
     * Prints graph_trans
    */
    cout << "Transposed graph:" << endl;
    for (unsigned int i = 0; i < graph_trans.size(); ++i){
        cout << i+1 << " -> ";
        for (unsigned int j = 0; j < graph_trans[i].size(); ++j){
            cout << graph_trans[i][j]+1 << " ";
        }
        cout << endl;
    }
}

vector<int> findSources(){
    /**
     * Finds all sources of graph_trans
    */
    vector<int> res = vector<int>();
    for (unsigned int i = 0; i < graph_trans.size(); ++i)
        if (graph_trans[i].size() == 0)
            res.push_back(i);
    return res;
}

void printSources(vector<int> sources){
    /**
     * Prints sources
    */
    cout << "Sources: ";
    for (unsigned int i = 0; i < sources.size(); ++i)
        cout << sources[i] + 1 << " ";
    cout << endl;
}

//Para cada vertice no grafo, iniciar um conjunto de BFS que esgotem todos os vertices
        //Para cada BFS feita, se o numero de arvores for menor que o minimo atual, substituir esse valor
        //e a profundidade da maior arvore encontrada (usar uma variavel que guarde a profundidade maxima)
        //Ao acabar o conjunto de BFS, repaintGraph() e passar para o proximo vertice inicial
int executeBFS(int source){
    /**
     * Executes BFS and returns number of vertex visited
    */
    for (unsigned int i = 0; i < graph.size(); ++i)
        graph[i].colour = WHITE;

    graph[source].colour = GREY;

    queue<int> q = queue<int>();
    q.push(source);

    int u, index, visited = 0;

    while (!q.empty()){
        u = q.front();
        q.pop();
        for (unsigned int i = 0; i < graph[u].adj.size(); ++i){
            index = graph[u].adj[i];
            if (graph[index].colour == WHITE){
                graph[index].colour = GREY;
                visited++;
                q.push(index);
            }
        }
        graph[u].colour = BLACK;
    }
    return visited;
}

int main(){

    readInput();
    //printGraph();
    //printTransGraph();
    int visited, max = 0;
    vector<int> sources = findSources();
    //printSources(sources);

    for (unsigned int i = 0; i < sources.size(); ++i)
        if ((visited = executeBFS(sources[i])) > max)
            max = visited;

    cout << sources.size() << " " << max << endl;
    exit(EXIT_SUCCESS);
}