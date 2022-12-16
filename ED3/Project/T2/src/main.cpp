/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <iostream>
#include "Graph.h"
#include "algmachine.h"

using namespace std;

int main()
{
    // Comando que define a funcao a ser utilizada
    int cmd;
    cin >> cmd;

    // Strings auxiliares
    string fileName;
    string trash;
    char eAux[200];
    char sAux[200];

    // Strings de entrada das funcoes ja convertidas
    char nomeEstacaoOrigem[200];
    string e;
    string s;
    string buff;

    // Objetos que serviram como suporte para algoritmos e o grafo no qual eles serao operados
    algMachine *alg;
    Graph g;
    
    // Hub para chamar as funcoes
    switch (cmd)
    {
    case 7:
        // Cria e exibe o grafico de acordo com a funcionalidade 7
        getline(cin >> ws, fileName);
        g.createGraph(fileName);
        cout << g.toString();
        break;

    case 8:
        // Descarata os caracterizadores de entradas e manipulada as entradas da forma string
        // da maneira adequada, chamando a funcionalidade 8
        cin >> fileName;
        alg = new algMachine(fileName);
        cin >> buff;
        scan_quote_string(eAux);
        e = eAux;
        cin >> buff;
        scan_quote_string(sAux);
        s = sAux;
        alg->dijkstra(e, s);
        break;

    case 9:
        // Descarta os caracterizadores de entrada e aplica o DFS no arquivo especificado
        cin >> fileName;
        alg = new algMachine(fileName);
        cin >> buff;
        scan_quote_string(nomeEstacaoOrigem);
        alg->CycleDFS(nomeEstacaoOrigem);
        break;

    case 10:
        // Descarta os caracterizadores de entrada e aplica o algoritmo de Prim no arquivo especificado
        cin >> fileName;
        alg = new algMachine(fileName);
        cin >> buff;
        scan_quote_string(sAux);
        s = sAux;
        alg->prim(s);
        break;

    case 11:
        // Descarta os caracterizadores de entrada e encontra dos os caminhos possiveis do vertice e ao vertice s
        cin >> fileName;
        alg = new algMachine(fileName);
        cin >> buff;
        scan_quote_string(eAux);
        e = eAux;
        cin >> buff;

        scan_quote_string(sAux);
        s = sAux;

        alg->DFSEveryPathFromUToV( e, s );

        break;

    default:
        break;
    }

    return 0;
}
