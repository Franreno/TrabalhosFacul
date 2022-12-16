/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "algmachine.h"

/**
 * @brief Construtor da classe algMachine. Cria um grafo a partir de um path para um arquivo.
 * 
 * @param fileName Nome do arquivo que sera utilizado para a construcao do grafo.
 */
algMachine::algMachine(string fileName)
{
    if (!g.createGraph(fileName))
        throw invalid_argument(fileName);
}

/**
 * @brief Seta os vetores Antecessores, distancia e visitados com os valores defaults.
 */
void algMachine::cleanAuxVectors()
{
    for (auto it : this->g.getAdjList())
    {
        this->ANT[it.first] = "\0";
        this->D[it.first] = INT32_MAX;
        this->visited[it.first] = false;
    }
}

/**
 * @brief Funcao para percorrer o caminho do vertice final ate o inicial e printar o caminho em ordem 
 * 
 * @param e key do vertice de inicio
 * @param s key do vertice final
 */
void algMachine::reconstructAndPrint(string e, string s)
{
    string inverter = e; //string auxiliar
    int statNum = 0; //contador de vertices
    stack<string> path;
    while (inverter != s)
    {
        statNum++;
        path.push(ANT[inverter]);//implementada uma pilha para organizacao do caminho
        inverter = ANT[inverter];
    }
    cout << "Numero de estacoes que serao percorridas: " << statNum << endl;
    cout << "Distancia que sera percorrida: " << D[e] << endl; //distancia acumulada do vertice de origem ao final
    while (!path.empty())
    {
        inverter = path.top();//desempilhand os vertices que compoe o caminho
        cout << inverter << ", ";
        path.pop();
    }
    cout << e << endl;
}

/**
 * @brief algoritmo de dijkstra simples
 * 
 * @param s key do vertice inicial
 * @param e key do vertice final
 */
void algMachine::dijkstra(string s, string e)
{
    cleanAuxVectors();
    map<string, vector<GraphNode>> AdjList = g.getAdjList();// Lista de adjacencias que sera manipulada

    string curNode; // Vertice atual
    string nextNode; // Proximo vertice

    int min;
    int curDist = 0;

    // Preenchimento dos vetores para a posicao inicial e criacao de uma flag
    D[s] = 0;
    curNode = s;
    visited[s] = true;
    bool flag = false;

    // No pior caso todo o grafo eh percorrido
    for (auto node = AdjList.begin(); node != AdjList.end(); node++)
    {
        // O objetivo foi atingido
        if (curNode == e)
        {
            flag = true;
            break;
        }

        // Determina a menor distancia de todos os vertices baseado em uma apromiximacao gulosa
        for (auto it : AdjList[curNode])
        {
            if (it.getDistProxEstacao() + curDist < D[it.getNomeEstacao()])
            {
                D[it.getNomeEstacao()] = curDist + it.getDistProxEstacao();
                ANT[it.getNomeEstacao()] = curNode;
            }
        }

        // Escolhe o vertice com menor distancia para ser o proximo vertice
        min = INT32_MAX;
        for (auto it : D)
        {
            if (it.second <= min && !visited[it.first])
            {
                if (it.second < min)
                {
                    min = it.second;
                    nextNode = it.first;
                }
                else if (it.first < nextNode)
                    nextNode = it.first;
            }
        }
        
        // Determina a distancia atual e faz o book-keeping necessario
        curDist = D[nextNode];
        visited[nextNode] = true;
        curNode = nextNode;
    }
    if (!flag)
        cout << "Não existe caminho entre as estações solicitadas." << endl;
    else
        reconstructAndPrint(e, s);

    cleanAuxVectors();
}

/**
 * @brief Coloca os valores de um node nos vetores de antecessores e distancia.
 * 
 * @param pilha Pilha utilizada no algoritmo para adicionar novos elementos para serem visitados.
 * @param node Referencia de um GraphNode cujos atributos serao adicionados nos vetores.
 * @param topoPilha Nome do elementos que esta no topo da Pilha.
 */
void algMachine::CycleDFS_CheckInVectors(stack<string> *pilha, GraphNode *node, string topoPilha)
{
    if (visited[node->getNomeEstacao()] && node->isEmpty())
        return;

    // Adicionar no topo da pilha
    pilha->push(node->getNomeEstacao());

    // Colocar o topoPilha como parente desses vertices.
    if (ANT[node->getNomeEstacao()] == "\0" || ANT[node->getNomeEstacao()] > topoPilha)
        ANT[node->getNomeEstacao()] = topoPilha;

    // E colocar a distancia do topoPilha nesses vertices.
    if (D[node->getNomeEstacao()] == INT32_MAX)
        D[node->getNomeEstacao()] = node->getDistProxEstacao();
}

/**
 * @brief Realiza uma busca em profundidade (DFS) no grafo para encontrar se existe um ciclo
 * para um vertice x. Se existir esse ciclo a funcao imprime o caminho que encontrou.
 * 
 * @param nomeEstacaoOrigem Nome do vertice de origem.
 */
void algMachine::CycleDFS(string nomeEstacaoOrigem)
{
    cleanAuxVectors();

    // Pega o grafo a partir do objeto Graph.
    map<string, vector<GraphNode>> graphMap = g.getAdjList();

    // Pilha utilizado para marcar os vertices que serao visitados.
    stack<string> pilha;

    vector<GraphNode> adjacentes = graphMap[nomeEstacaoOrigem];
    for (auto it = adjacentes.begin(); it != adjacentes.end(); it++)
        CycleDFS_CheckInVectors(&pilha, &(*it), nomeEstacaoOrigem);

    // Roda enquanto a pilha nao esta vazia.
    while (!pilha.empty())
    {
        // Pegar o conteudo da pilha
        string topoPilha = pilha.top();
        pilha.pop();

        // Se esse elemento ja foi visitado, nao ver os vizinhos dele e ir pro proximo elemento da pilha.
        if (visited[topoPilha])
            continue;

        // Visitei esse elemento.
        visited[topoPilha] = true;

        // Verificar se esse node eh o node nomeEstacaoOrigem.
        if (topoPilha == nomeEstacaoOrigem)
            break;

        // Visitar os proximos nodes
        adjacentes = graphMap[topoPilha];

        for (auto it = adjacentes.begin(); it != adjacentes.end(); it++)
            CycleDFS_CheckInVectors(&pilha, &(*it), topoPilha);
    }

    // Verificar se o antecessor do nomeEstacaoOrigem esta como 'nulo'
    if (ANT[nomeEstacaoOrigem] == "\0")
    {
        cout << "Nao existe um ciclo a partir da estacao de origem." << endl;
        return;
    }

    // Fazer o caminho reverso.
    vector<string> path = vector<string>(1, nomeEstacaoOrigem);
    string lastOne = ANT[nomeEstacaoOrigem];
    int maxDist = D[nomeEstacaoOrigem];
    int numDeEstacoesPercorridas = 1;
    while (lastOne != nomeEstacaoOrigem)
    {
        numDeEstacoesPercorridas++;
        path.insert(path.begin(), lastOne);
        maxDist += D[lastOne];
        lastOne = ANT[lastOne];
    }
    path.insert(path.begin(), nomeEstacaoOrigem);

    // Imprimir o caminho.
    cout << "Numero de estacoes que serao percorridas: " << numDeEstacoesPercorridas << endl;
    cout << "Distancia que sera percorrida: " << maxDist << endl;
    for (auto it = path.begin(); it != path.end(); it++)
    {
        cout << *it;
        if (it != path.end() - 1)
            cout << ", ";
    }
    cout << endl;
}

/**
 * @brief Implementacao do algoritmo de busca em profundidade de maneira recursiva. Utilizado para encontrar todos os
 * caminhos possiveis de um vertice `v` ate um vertice `u`.
 * 
 * @param graphMap Referencia ao map do grafo. Utilizado para pegar elementos diretamente do grafo.
 * @param nodeName Nome do atual vertice de analise.
 * @param nodeDist Valor da distancia entre o ultimo vertice analisado e o atual.
 * @param lastNodeName Nome do ultimo vertice que foi visitado.
 * @param mainOrigin Nome do vertice de origem (v).
 * @param dest Nome do vertice de destivo (u).
 */
void algMachine::DFSRecursive(map<string, vector<GraphNode>> *graphMap, string nodeName, int nodeDist, string lastNodeName, string mainOrigin, string dest)
{

    // Marcar esse vetice como visitado e adicionar os valores do ultimo vertice nesse nodulo
    // nos vetores de antecessores e distancias.
    visited[nodeName] = true;
    ANT[nodeName] = lastNodeName;
    D[nodeName] = nodeDist;

    // Chegou no destino.
    if (nodeName == dest)
    {
        // Criar o caminho.
        vector<string> path = vector<string>(1, nodeName);

        string lastOne = ANT[nodeName];
        int numOfTimes = 1;
        int maxDist = D[nodeName];

        // Fazer o caminho reverso.
        while (lastOne != mainOrigin)
        {
            numOfTimes++;
            maxDist += D[lastOne];
            path.insert(path.begin(), lastOne);
            lastOne = ANT[lastOne];
        }
        path.insert(path.begin(), mainOrigin);

        // Adicionar no vetor de caminhos utilizando a classe allPaths.
        pathsList.insert(pathsList.begin(), allPaths(numOfTimes, maxDist, path));
    }
    else
    {
        // Ir para os vizinhos desse vertice.
        // Pegar os vizinhos desse vertice no grafo.
        vector<GraphNode> adjNode = graphMap->at(nodeName);

        // Percorrer por todos os vizinhos
        for (auto it = adjNode.begin(); it != adjNode.end(); it++)
        {
            // e se esse vertice nao estiver vazio e nao foi visitado fazer a analise nele.
            if (!visited[it->getNomeEstacao()] && !it->isEmpty())
                DFSRecursive(graphMap, it->getNomeEstacao(), it->getDistProxEstacao(), nodeName, mainOrigin, dest);
        }
    }

    // Limpando os vetores para pegar o proximo caminho.
    ANT[nodeName] = "\0";
    D[nodeName] = INT32_MAX;
    visited[nodeName] = false;
}

/**
 * @brief Aplica uma busca em profundidade recursiva para encontrar todos os caminhos
 * possiveis de um vertice de origem ate um vertice de destino.
 * 
 * @param origin Nome do vertice de origem.
 * @param destination Nome do vertice de destino.
 */
void algMachine::DFSEveryPathFromUToV(string origin, string destination)
{
    // Limpa os vetores auxiliares.
    cleanAuxVectors();

    // Pega da classe grafo o map de dados.
    map<string, vector<GraphNode>> graphMap = g.getAdjList();

    // Aplica o algoritmo recursivo.
    // Como esse eh o primeiro vertice analisado a sua distancia eh 0
    // e nao possui outra estacao atras dele, ou seja, o ultimo vertice visitado eh nulo ("\0").
    DFSRecursive(&graphMap, origin, 0, "\0", origin, destination);

    // Se o vetor de caminhos estiver vazio eh pq nao existe nenhum caminho entre u ate v.
    if (pathsList.empty())
    {
        cout << "Não existe caminho entre as estações solicitadas." << endl;
    }
    else
    {
        // Ordernar o vetor antes de imprimir.
        sort(pathsList.begin(), pathsList.end(), [](allPaths const &a, allPaths const &b)
             {
                 // Ordernar primeiramente pelo numero de estacoes percorridas.
                 if (a.numEstacoes < b.numEstacoes)
                     return true;
                 if (a.numEstacoes > b.numEstacoes)
                     return false;

                 // Se o numero de estacoes percorridas eh igual entao ordernar pelo vetor de caminhos.
                 if (a.path < b.path)
                     return true;
                 if (a.path > b.path)
                     return false;

                 return false;
             });

        // Imprime um caminho.
        for (auto it = pathsList.begin(); it != pathsList.end(); it++)
            cout << it->toString() << endl;
    }
}

/**
 * @brief Uma busca binaria simples, caso os vertices ja possuam arestas que sejam bivalentes
 * 
 * @param vect O vetor ordenado que sera manipulado
 * @param targ O parametro que esta sendo buscado
 * @param s Posicao de inicio da parcela analisada na iteracao
 * @param e Posicao de fim da parcela anaisada na iteracao
 */
static bool buscaBinaria(vector<GraphNode> vect, string targ, int s, int e)
{
    // Vetor vazio
    if (e == -1)
        return false;
    int mid = s + floor((e - s) / 2);
    
    // Objetivo alcancado
    if (vect[mid].getNomeEstacao() == targ)
        return true;
    
    // O alvo nao se encontra no vetor
    else if (e == s)
        return false;

    // Faz a divisao do vetor
    if (vect[mid].getNomeEstacao() > targ)
        return buscaBinaria(vect, targ, s, mid);
    else
        return buscaBinaria(vect, targ, mid + 1, e);
}

/**
 * @brief Converte o grafo para nao direcionado tornando todas as arestas bivalentes
 * 
 * @param AdjList Lista de adjacencias manipulavel
 * @param g Ponteiro para grafo
 */
static void convertAdjList(map<string, vector<GraphNode>> AdjList, Graph *g)
{
    string name;
    for (auto it : AdjList)
    {
        for (auto node : it.second)
        {
            // Vizinho estara vazio e sera desconsiderado.
            name = node.getNomeEstacao();
            if (node.isEmpty())
            {
                g->eraseNode(it.first);
                continue;
            }
            // Se a aresta ja nao e dupla sera dupicada
            if (!buscaBinaria(AdjList[name], it.first, 0, AdjList[name].size() - 1))
            {
                for (auto linha : node.getNomesLinhas())
                    g->addAresta(name, node.getDistProxEstacao(), linha, it.first);
            }
        }
    }
}

/**
 * @brief Abordagem DS para print dos vertices
 * 
 * @param s Vertice de inicio
 * @param agm Arvore geradora minima do grafo
 */
static void organizeAndPrint(string s, map<string, vector<GraphNode>> agm)
{
    for (auto it : agm[s])
    {
        cout << s + ", " + it.getNomeEstacao() + ", " << it.getDistProxEstacao() << endl;
        if (it.getDistProxEstacao() != -1)
            organizeAndPrint(it.getNomeEstacao(), agm);
    }
}

/**
 * @brief Algoritmo de Prim
 * @param s Vertice de inicio
 */
void algMachine::prim(string s)
{
    cleanAuxVectors();

    // Instanciacao da arvore geradora minima e demais variaveis necessarias para book keeping
    map<string, vector<GraphNode>> AdjList = g.getAdjList();
    map<string, vector<GraphNode>> agm;
    int min;
    GraphNode nextNode;
    string lastNode;

    // Converte o grafo nativo para nao direcionado
    convertAdjList(AdjList, &g);

    // Inicializa os valores necessarios
    AdjList = g.getAdjList();
    visited[s] = true;
    lastNode = s;

    while (true)
    {
        min = INT32_MAX;
        // Percorre o conjunto de vertices visitados U
        for (auto it : visited)
        {
            if (it.second)
            {
                for (auto node : AdjList[it.first])
                {
                    // Checa para ver se o vertice (node) pertence ao conjunto de vertices nao visitados (V - U)
                    if (!visited[node.getNomeEstacao()])
                    {
                        // Determina o par de vertices que caracteriza uma aresta a partir dos criterios colocados
                        if (node.getDistProxEstacao() < min)
                        {
                            min = node.getDistProxEstacao();
                            nextNode = node;
                            lastNode = it.first;
                        }
                        // Empate de arestas
                        else if (node.getDistProxEstacao() == min)
                        {
                            // u1 < u2
                            if (it.first < lastNode)
                            {
                                lastNode = it.first;
                                nextNode = node;
                            }

                            // Empate de vertices pai
                            else if (it.first == lastNode)
                            {
                                // v1 < v2 
                                // Decidido pelos filhos
                                if (node.getNomeEstacao() < nextNode.getNomeEstacao())
                                {
                                    lastNode = it.first;
                                    nextNode = node;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Isso indica um retorno para um vertice visitado e caracteriza o fim do algoritmo
        if (visited[nextNode.getNomeEstacao()])
        {
            break;
        }

        // Inclui a aresta e consequentemente os vertices na AGM, inserindo uma nova chave caso
        // o vertice nao esteja presente posteriormente ou apenas inserindo e ordenando caso
        // ele ja exista neste contexto
        if (agm.find(lastNode) == agm.end())
        {
            agm.insert({lastNode, vector<GraphNode>(1, nextNode)});
        }
        else
        {
            agm[lastNode].insert(agm[lastNode].end(), nextNode);
            sort(agm[lastNode].begin(), agm[lastNode].end());
        }

        // Book keeping 
        visited[nextNode.getNomeEstacao()] = true;
        lastNode = nextNode.getNomeEstacao();
    }
    organizeAndPrint(s, agm);
}

/**
 * @brief Construtor da classe allPaths. Guarda um caminho entre o vertice u ate v.
 * 
 * @param __nEst Numero de estacoes percorridas.
 * @param __dist Distancia entre as estacoes percorridas.
 * @param __path Vetor com os nomes das estacoes percorridas.
 */
allPaths::allPaths(int __nEst, int __dist, vector<string> __path)
{
    this->numEstacoes = __nEst;
    this->dist = __dist;
    this->path = __path;
}

/**
 * @brief Cria uma string formatada da maneira que o exercicio pede para imprimir na tela.
 */
string allPaths::toString()
{
    string output = "Numero de estacoes que serao percorridas: ";
    output += to_string(this->numEstacoes) + "\n";

    output += "Distancia que sera percorrida: ";
    output += to_string(this->dist) + "\n";

    // Nome de cada caminho.
    for (auto it = this->path.begin(); it != this->path.end(); it++)
    {
        output += *it;
        output += (it != this->path.end() - 1) ? ", " : "";
    }
    output += "\n";

    return output;
}
