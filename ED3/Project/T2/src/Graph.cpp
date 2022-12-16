/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "Graph.h"

/**
 * @brief Retorna o numero de vertices presente no grafo.
 */
int Graph::getnVertices()
{
    return nVertices;
}

/**
 * @brief Retorna o map contendo os dados do grafo.
 */
map<string, vector<GraphNode>> Graph::getAdjList()
{
    return graph;
}

/**
 * @brief Funcao de criacao do grafo. 
 * Abre um arquivo binario e le os registros dele para a criacao do grafo.
 * 
 * @param fileName string que contem o nome do arquivo.
 */
bool Graph::createGraph(string fileName)
{
    this->nVertices = 0;
    this->nArestas = 0;
    REGISTRO r;
    CABECALHO c;

    // Abre o arquivo.
    FILE *bin;
    bin = fopen(fileName.c_str(), "rb");
    if (bin == NULL)
    {
        cout << "Falha na execução da funcionalidade." << endl;
        return false;
    }

    // Pega o tamanho do arquivo.
    long fileSize = getFileSize(bin);

    // Le o cabecalho do arquivo.
    readCabecalho(&c, bin);

    // Le registro por registro do arquivo.
    while (ftell(bin) != fileSize)
    {
        if (!readSingleRegister(&r, bin))
        {
            fseek(bin, r.tamanhoRegistro, SEEK_CUR);
            continue;
        }

        // Pegar a prox estacao
        REGISTRO proxEstacao;
        if (r.codProxEstacao != -1)
        {
            procuraEstacao(r.codProxEstacao, &proxEstacao, bin);
            // Adicionar no grafo como vizinho deste registro.
            this->addAresta(r.nomeEstacao, r.distProxEstacao, r.nomeLinha, proxEstacao.nomeEstacao);
            free(proxEstacao.nomeEstacao);
            free(proxEstacao.nomeLinha);
            this->nArestas++;
        }

        REGISTRO estacaoIntegrante;
        if (r.codEstIntegra != -1)
        {
            procuraEstacao(r.codEstIntegra, &estacaoIntegrante, bin);
            // Comparar os valores encontrados
            // Se r.nomeEstacao == estacaoIntegrante.nomeEstacao nao pode inserir.
            if (strcmp(r.nomeEstacao, estacaoIntegrante.nomeEstacao) != 0)
            {
                // Pode inserir
                // Inserir estacaoIntegrante.nomeEstacao, 0, "Integracao"
                this->addAresta(r.nomeEstacao, 0, "Integracao", estacaoIntegrante.nomeEstacao);
                this->nArestas++;
            }

            free(estacaoIntegrante.nomeEstacao);
            free(estacaoIntegrante.nomeLinha);
        }

        if (r.codProxEstacao == -1 && r.codEstIntegra == -1)
            this->addFolha(r.nomeEstacao);

        free(r.nomeEstacao);
        free(r.nomeLinha);
        this->nVertices++;
    }

    fclose(bin);
    return true;
}

/**
 * @brief Adiciona um nodulo no grafo que nao possui arestas adjacentes para frente. (Grafo direcionado)
 * 
 * @param nomeEstacao_Origem nome do node que sera inserido no grafo.
 */
void Graph::addFolha(string nomeEstacao_Origem)
{
    this->graph[nomeEstacao_Origem] = vector<GraphNode>(1, GraphNode());
}

/**
 * @brief Adiciona uma aresta no grafo. 
 * u: (nomeEstacao_Origem, distancia_Origem, nomeLinha_Origem).
 * v: (nomeEstacao_Destino).
 * 
 * @param nomeEstacao_Origem Node que sera usado como Key no map.
 * @param distancia_Origem Distancia entre as estacoes.
 * @param nomeLinha_Origem Nome da linha pra adicionar no node.
 * @param nomeEstacao_Destino Nome do node de destino.
 */
void Graph::addAresta(string nomeEstacao_Origem, int distancia_Origem, string nomeLinha_Origem, string nomeEstacao_Destino)
{
    // Verificar se o u ja existe no map.
    auto it = this->graph.find(nomeEstacao_Origem);
    if (it != this->graph.end())
    {
        // Se encontrou no grafo tem que inserir um novo GraphNode.
        // Verificar se no vector de GraphNodes ja existe a estacao v->nomeEstacao
        // Se existir adicionar o nome da linha no vector de nomeLinhas.
        addNewDataAtKey(&it->second, nomeEstacao_Destino, distancia_Origem, nomeLinha_Origem);
    }
    else
    {
        // Caso contrario basta adicionar a nova estacao no mapa.
        this->graph[nomeEstacao_Origem] = vector<GraphNode>(1, GraphNode(nomeEstacao_Destino, distancia_Origem, nomeLinha_Origem));
    }
}

/**
 * @brief Adiciona um novo nodulo na lista de adjacencia, ou adiciona mais um nomeLinha no vector de linhas.
 * 
 * @param nodes Referencia da lista de adjacencia.
 * @param nomeEstacao Nome da estacao que sera inserido.
 * @param distancia Distancia entre as estacoes.
 * @param nomeLinha Nome da linha que sera inserida.
 */
void Graph::addNewDataAtKey(vector<GraphNode> *nodes, string nomeEstacao, int distancia, string nomeLinha)
{
    int flag = 0;
    // Procurar na lista de adjacencia uma estacao com o mesmo nome.
    for (auto it = nodes->begin(); it != nodes->end(); it++)
    {
        // Se encontrar adicionar uma nova linha na lista de linhas.
        // Adicionar o nome linha nesse node.
        if (it->getNomeEstacao() == nomeEstacao)
        {
            it->updateNomesLinhas(nomeLinha);
            flag = 1;
        }
    }

    // Se nao encontrou inserir novo node na lista de adjacencia.
    if (!flag)
    {
        nodes->push_back(GraphNode(nomeEstacao, distancia, nomeLinha));
        // Ordernar alfabeticamente por nome de estacao.
        sort(nodes->begin(), nodes->end());
    }
}

void Graph::eraseNode(string nomeEstacao)
{
    this->graph.erase(nomeEstacao);
}

/**
 * @brief Pega os nodes do grafo cria uma string com todo o seu conteudo.
 * 
 * @return string que contem o conteudo do grafo.
 */
string Graph::toString()
{
    string output = "";
    // Itera por cad node
    for (auto it = this->graph.begin(); it != this->graph.end(); it++)
    {
        // Adiciona o nome do node
        output += it->first;

        // Itera pela lista de adjacencia do node
        for (auto vecIt = it->second.begin(); vecIt != it->second.end(); vecIt++)
        {
            output += " ";
            // Pega a string do GraphNode
            output += vecIt->toString();
        }
        output += "\n";
    }

    return output;
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Cria um GraphNode vazio.
 * 
 */
GraphNode::GraphNode()
{
    this->nomeEstacao = "\0";
    this->distProxEstacao = -1;
    this->nomesLinhas = vector<string>(1, "\0");
}

/**
 * @brief Construtor do objeto GraphNode.
 * 
 * @param _nomeEstacao Nome da estacao do GraphNode.
 * @param _dist Peso da aresta desse node.
 * @param nomeLinha Nome da linha que conecta os nodes.
 */
GraphNode::GraphNode(string _nomeEstacao, int _dist, string nomeLinha)
{
    this->nomeEstacao = _nomeEstacao;
    this->distProxEstacao = _dist;
    this->nomesLinhas = vector<string>(1, nomeLinha);
}

/**
 * @return string O nome da estacao desse node.
 */
string GraphNode::getNomeEstacao()
{
    return this->nomeEstacao;
}

/**
 * @return int O peso da aresta desse node.
 */
int GraphNode::getDistProxEstacao()
{
    return this->distProxEstacao;
}

/**
 * @return vector<string> O vector de nome de linhas.
 */
vector<string> GraphNode::getNomesLinhas()
{
    return this->nomesLinhas;
}

/**
 * @brief Compara dois GraphNodes pelo nome da sua estacao.
 * 
 * @param __node O objeto GraphNode que sera comparado.
 */
bool GraphNode::operator<(const GraphNode &__node)
{
    return (this->nomeEstacao < __node.nomeEstacao);
}

/**
 * @brief Atualiza o vector de nome de linhas com um novo valor.
 * 
 * @param newData Novo valor que sera inserido no vector
 */
void GraphNode::updateNomesLinhas(string newData)
{
    this->nomesLinhas.push_back(newData);
    sort(this->nomesLinhas.begin(), this->nomesLinhas.end());
}

bool GraphNode::isEmpty()
{
    return this->nomeEstacao == "\0" && this->distProxEstacao == -1 && this->nomesLinhas[0] == "\0";
}

/**
 * @brief Cria uma string que contem os valores de um GraphNode.
 * 
 * @return string conteudo do node.
 */
string GraphNode::toString()
{
    string output = "";

    if (this->isEmpty())
        return output;

    output += this->nomeEstacao + " ";
    output += to_string(this->distProxEstacao) + " ";
    for (auto it = this->nomesLinhas.begin(); it != this->nomesLinhas.end(); it++)
    {
        output += *it;
        output += (it != this->nomesLinhas.end() - 1) ? " " : "";
    }

    return output;
}
