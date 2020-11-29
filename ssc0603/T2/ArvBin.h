
typedef struct node* ArvBin;

ArvBin* criaArvBin();
void liberaNode(struct node* no);
void liberaArvBin(ArvBin* raiz);

int insertBinaryTree(ArvBin* root, char dado[], int flag, char stdado[]);
int SearchNode(ArvBin* raiz, struct node* valor, int flag, char stdado[]);

int mostraArvBin(ArvBin *raiz);
int visitaArvBin(struct node* atual, int *total, int *saida);