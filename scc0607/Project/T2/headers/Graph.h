#ifndef __GRAPH__
#define __GRAPH__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>

#include "utils.h"

using namespace std;

class GraphNode
{
private:
    // Nome da estacao desse vertice.
    string nomeEstacao;
    // Distancia, ou peso, da aresta desse vertice ate o vertice de origem.
    int distProxEstacao;
    // Vetor de nomes das linhas que esse vertice possui.
    vector<string> nomesLinhas;

public:
    GraphNode();
    GraphNode(string _nomeEstacao, int _dist, string nomeLinha);
    string getNomeEstacao();
    int getDistProxEstacao();
    vector<string> getNomesLinhas();
    void updateNomesLinhas(string newData);
    bool isEmpty();
    bool operator<(const GraphNode &__node);
    string toString();
};

class Graph
{
private:
    // Map que guarda os dados do grafo.
    map<string, vector<GraphNode>> graph;
    // Numero de vertices.
    int nVertices;
    // Numero de arestas.
    int nArestas;

public:
    int getnVertices();
    map<string, vector<GraphNode>> getAdjList();
    bool createGraph(string fileName);
    void addAresta(string nomeEstacao_Origem, int distancia_Origem, string nomeLinha_Origem, string nomeEstacao_Destino);
    void addFolha(string nomeEstacao_Origem);
    void addNewDataAtKey(vector<GraphNode> *nodes, string nomeEstacao, int distancia, string nomeLinha);
    map<string, vector<GraphNode>> getMap();
    void eraseNode(string nomeEstacao);
    int getNumVertices();
    int getNumArestas();
    string toString();
};

#endif
