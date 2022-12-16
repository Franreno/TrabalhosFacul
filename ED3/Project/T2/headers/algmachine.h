#ifndef __ALG__
#define __ALG__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <limits>
#include <stack>

#include <math.h>
#include <exception>


#include "utils.h"
#include "Graph.h"

using namespace std;

/**
 * @brief Classe que guarda um caminho de um vertice ate outro.
 */
class allPaths
{
public:
    // Numero de estacoes percorridas de u ate v.
    int numEstacoes;
    // Distancia percorrida de u ate v.
    int dist;
    // Caminho percorrido de u ate v.
    vector<string> path;
    allPaths(int __nEst, int __dist, vector<string> __path);
    string toString();
};

/**
 * @brief Classe que contem todos os algoritmos utilizados no trabalho.
 */
class algMachine
{
private:
    // Grafo construido a partir de um arquivo binario.
    Graph g;
    // Vetor de distancias.
    map<string, int> D;
    // Vetor de antecessores.
    map<string, string> ANT;
    // Vetor de vertices visitados.
    map<string, bool> visited;
    // Vetor de todos os caminhos possiveis de um vertice u ate v.
    vector<allPaths> pathsList;

public:
    algMachine(string fileName);
    void cleanAuxVectors();
    void reconstructAndPrint(string e, string s);
    void dijkstra(string s, string e);
    void CycleDFS(string nomeEstacaoOrigem);
    void CycleDFS_CheckInVectors(stack<string> *pilha, GraphNode *node, string topoPilha);
    void prim(string s);
    void DFSEveryPathFromUToV(string origin, string destination);
    void DFSRecursive(map<string, vector<GraphNode>> *graphMap, string nodeName, int nodeDist, string lastNodeName, string mainOrigin, string dest);
};

#endif
