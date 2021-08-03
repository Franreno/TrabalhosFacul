#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede.h"

void RemoveFunction(char *UserName, char *UserNick);
void RemoveUser(char *UserName, char *UserNick, char *LoginToRemove);
void RemoveUserFollowing(char *UserName, char *UserNick, char *LoginToRemove);
void DisplayUsuarios();
void Informations();
int NumberOfUsers();
int NumberOfPosts();
void IsCommandValid_ADM(char *comando);
int ANNIHILATE();
int MostFollowers();

// display da interface do adm
void adm_interface(char *comando, char *UserName, char *UserNick) {


    while(*comando != '9') {

        PainelADM();
        printf("|\n|   >>  ");
        fgets(comando, 5, stdin);                           // Ação inicial do adm
        IsCommandValid_ADM(comando);

        switch (*comando)
        {
        case ('1'):
            DisplayUsuarios();                              // Mostra quem sao os usuarios
            break;
        
        case('2'):
            RemoveFunction(UserName, UserNick);             // Remove um usuario
            break;
        case('3'):
            Informations();
            break;
        case('4'):
            ANNIHILATE();
            break;
        default:
            break;

        }    
    }
    *comando = '0';
}


/*
    FUNCAO RemoveFunction() e RemoveUser:
    Escolhe o usuario a ser removido
    O arquivo em follow_data dos usuarios tambem eh removido; 
    O arquivo "Users.txt" eh reescrito porem sem o nome e login do usuario a ser removido
    Eh criado um arquivo temporario para armazenar os nomes e logins dos OUTROS usuarios
    Depois disso o arquivo "Users.txt" eh apagado e o arquivo temporario eh nomeado para "Users.txt"
*/


void RemoveFunction(char *UserName, char *UserNick) {
    FILE *fdin;
    fdin = fopen("Users.txt" , "r");

    if(fdin == NULL) {
        printf("erro\n"); exit(EXIT_SUCCESS);
    }

    char *LoginToRemove;
    LoginToRemove = (char *) malloc(30*sizeof(char));


    printf("| Digite o Usuario a ser removido: ");
    fgets(LoginToRemove , 30 , stdin);
    for(int i=0; *(LoginToRemove+i) != '\0'; i++) {
        if( *(LoginToRemove+i) == '\n' ) {
            *(LoginToRemove+i) = '\0';
        }
    }


    while( fscanf(fdin, "%[^\n]\n" , UserName) != EOF) {
        fscanf(fdin , "%s\n" , UserNick);
        

        int found = strcmp(UserNick , LoginToRemove);

        if(found == 0) {
            RemoveUser(UserName , UserNick, LoginToRemove);
            printf("\33[H\33[2J");
            printf("|--T&T--------------------------------------------------------------------------\n");
            printf("| USUARIO %s REMOVIDO COM SUCESSO!                           ENTER-Voltar |\n" , LoginToRemove);
            printf("|-------------------------------------------------------------------------------\n");
            getchar();
            break;
        }

        //se chegar no final do arquivo
        if( feof(fdin) && found != 0) {
            PainelADM();
            printf("\033[1;31m");
            printf("| Usuario nao encontrado\n");
            printf("\033[0m");
            printf("| Digite o Usuario a ser removido: ");
            fgets(LoginToRemove , 30 , stdin);
            rewind(fdin);
        }

    }

    fclose(fdin); free(LoginToRemove);

}



void RemoveUser(char *UserName, char *UserNick, char *LoginToRemove) {

    //imprimir no arquivo delete os outros nomes e logins menos os que foram encontrados.
    FILE *fdin, *ftemp, *ftemp2, *fposts;

    fdin = fopen("Users.txt" , "r");
    fposts = fopen("posts.txt" , "r");
    ftemp = fopen("delete.txt" , "w");
    ftemp2 = fopen("delete2.txt" , "w");

    if(fdin == NULL || fposts == NULL || ftemp == NULL || ftemp2 == NULL) {
        printf("| Erro ao abrir arquivos, encerrando.."); exit(EXIT_SUCCESS);
    }


    char *EscreveNome, *EscreveUser, *path, *tempost1, *tempost2, *tempost3;
    EscreveNome = (char *) malloc(30*sizeof(char));
    EscreveUser = (char *) malloc(50*sizeof(char));
    path = (char *) malloc(60*sizeof(char));
    tempost1 = (char *) malloc(50*sizeof(char));
    tempost2 = (char *) malloc(30*sizeof(char));
    tempost3 = (char *) malloc(129*sizeof(char));

    memset(path , 0 , sizeof(path));
    strcat(path , "follow_data/"); strcat(path, LoginToRemove); strcat(path, ".txt");

    //reescrever o arquivo "Users.txt"
    while( fscanf(fdin, "%[^\n]\n", EscreveNome) != EOF ) {
        fscanf(fdin , "%s\n" , EscreveUser);

        int found = strcmp(EscreveUser, LoginToRemove);
        if(found != 0) {
            fprintf(ftemp, "%s\n" , EscreveNome);
            fprintf(ftemp, "%s\n" , EscreveUser);
        } 
    }


    // reescrever o arquivo "posts.txt"
    while( fscanf(fposts, "%[^\n]\n" , tempost1) != EOF ) {
        fscanf(fposts, "%[^\n]\n" , tempost2);
        fscanf(fposts, "%[^\n]\n" , tempost3);

        int found = strcmp(tempost2 , LoginToRemove);
        if(found != 0) {
            fprintf(ftemp2 , "%s\n" , tempost1);
            fprintf(ftemp2 , "%s\n" , tempost2);
            fprintf(ftemp2 , "%s\n" , tempost3);

        }
    }

    RemoveUserFollowing(UserName , UserNick, LoginToRemove);
    remove(path);
    remove("Users.txt");
    remove("posts.txt");
    rename("delete.txt" , "Users.txt");
    rename("delete2.txt" , "posts.txt");


    fclose(fdin); fclose(ftemp); fclose(fposts); fclose(ftemp2); free(EscreveNome); free(EscreveUser); free(path); free(tempost3); free(tempost2); free(tempost1);
}




/*
    FUNCAO RemoveUserFollowing():
    Nessa funcao eh removido o usuario requisitado pelo adm que seja encontrado dentro dos arquivos de follow_data/
    Assim, foi necessario usar um ponteiro duplo para que todos os arquivos sejam lidos corretamente e verificado dentro
    de cada um dele se o usuario em questao realmente existe.
*/

void RemoveUserFollowing(char *UserName, char *UserNick, char *LoginToRemove) {

    // fazer um array de ponteiro para a quantidade de arquivos presentes no dir "follow_data"
    // conhecer o numero de usuarios na rede ja que todo usuario possui um arquivo para quem segue

    int number_of_users = NumberOfUsers();
    char *EscreveNome, *EscreveUser;
    EscreveNome = (char *) malloc(30*sizeof(char));
    EscreveUser = (char *) malloc(50*sizeof(char));

    FILE **pfollow, *ftemp;
    pfollow = (FILE **) malloc(number_of_users*sizeof(FILE *));
    
    //abrir o arquivos de usuarios para "pegar" dele os nomes dos usuarios
    FILE *fdin = fopen("Users.txt" , "r");
    if(fdin == NULL) {
        printf("erro\n"); exit(0);
    }
    
    char *PathToUserNick = (char *) malloc(60*sizeof(char));
    memset(PathToUserNick, 0, sizeof(char));
    int i=0;

    /*primeiro while serve pra pegar o Login (UserNick) do aquivo Users.txt*/
    while( fscanf(fdin , "%[^\n]\n" , UserName) != EOF && i<number_of_users) {
        fscanf(fdin , "%[^\n]\n" , UserNick);
        int found1 = strcmp(UserNick, LoginToRemove);

        if(found1 != 0) {
            strcat(PathToUserNick , "follow_data/"); strcat(PathToUserNick , UserNick); strcat(PathToUserNick , ".txt");
            

            *(pfollow+i) = fopen( PathToUserNick ,  "r");
            if ( *(pfollow+i) == NULL ) {
                printf("| nao foi possivel abrir o arquivo\n"); 
                exit(0);
            }

            ftemp = fopen("follow_data/tempost.txt" , "w");

            // abri o arquivo que foi pego no Users.txt 
            // agora preciso escrever nele todos os outros logins que existem menos aquele que sera removido
            while( fscanf( *(pfollow+i) , "%[^\n]\n" ,  EscreveUser) != EOF) {
                int found = strcmp(EscreveUser , LoginToRemove);

                if(found != 0) {
                    fprintf( ftemp , "%s\n" , EscreveUser );    //escrever os usuarios que sao seguidos
                }
            }
            
            char *path = (char *) malloc(60*sizeof(char));
            memset(path, 0, sizeof(char));
            strcat(path , "follow_data/"); strcat(path , UserNick); strcat(path , ".txt");
            remove(path);
            rename("follow_data/tempost.txt" , path);

            memset(PathToUserNick, 0, sizeof(char));

            fclose(ftemp); fclose( *(pfollow+i) ); free(path);
        }

        i++;
    }

    fclose(fdin); free(PathToUserNick); free(pfollow);
}





/*
    FUNCAO DisplayUsuarios():
    Mostra os usuarios presentes nos arquivo "Users.txt".

*/

void DisplayUsuarios() {

    PainelADMUsuarios();

    //abrir o arquivo
    FILE *fdin;
    fdin = fopen("Users.txt" , "r");
    if(fdin == NULL) {
        printf("| NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
        exit(0);
    }

    //ler os nomes e usuarios e apresenta-los
    char *UserNome; char *UserLogin;
    UserNome = (char *) malloc(50*sizeof(char));
    UserLogin = (char *) malloc(30*sizeof(char));

    int contador = 1;
    while( (fgets(UserNome, 50, fdin) != NULL) ) {
        fscanf(fdin, "%s\n" , UserLogin);

        printf("|\n| Usuario %d:\n" , contador);
        contador++;
        printf("| %s" , UserNome);
        printf("| %s\n" , UserLogin);
    }
    getchar();

    free(UserLogin); free(UserNome);
    fclose(fdin);
}



// mostrar a quantidade de usuarios e a quantidade de posts
void Informations() {

    PainelADMInformations();

    // a cada 2 \n eh considerado um usuario
    printf("|\n| Quantidade de Usuarios: %d\n" , NumberOfUsers());

    // a cada 3 \n eh considerado um post
    printf("| Quantidade de Posts: %d\n" , NumberOfPosts());

    //imprimir a pessoa com mais seguidores e a quantidade de seguidores
    printf("| User com mais seguidores: "); MostFollowers();

    getchar();
}



int NumberOfUsers() {

    // calculo da quantidade de usuarios
    FILE *fdin;
    fdin = fopen("Users.txt" , "r");    //abre o arquivo somente para leitura

    if(fdin == NULL) {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
        exit(0);
    }

    int numero = 0;                     //variavel de quantidade de usuarios
    char *ch;
    ch = (char *) malloc(1*sizeof(char));


    /* a cada novo usuario um 2 '\n' sao acrescentados, portanto so eh necessario ler quantos '\n' existem no arquivo e dividir por 2*/
    while( ( *ch = fgetc(fdin) ) != EOF ) {
        if(*ch == '\n') {
            numero++;
        }
    }

    fclose(fdin);
    free(ch);
    return numero/2;
}



int NumberOfPosts() {

    FILE *fdin;

    // calculo da quantidade de posts
    fdin = fopen("posts.txt" , "r");

    if(fdin == NULL) {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
        exit(0);
    }

    int numero = 0;                     //variavel de quantidade de posts
    char *ch;
    ch = (char *) malloc(1*sizeof(char));


    while( ( *ch = fgetc(fdin) ) != EOF ) {
        if(*ch == '\n') {
            numero++;
        }
    }

    fclose(fdin);
    free(ch);
    return numero/3;

}


void IsCommandValid_ADM(char *comando) {
    int tam = 0; //tamanho da string
    for(int i=0; *(comando+i) != '\n'; i++) {
        tam++;
    }

    if(tam > 1) {
        PainelADM();
        printf("|\n|   Comando invalido\n|   Digite novamente:\n|   >>");
        fgets(comando, 5, stdin);
        IsCommandValid_ADM(comando);
    }
    else {

        if(*comando != '1' && *comando != '2' && *comando != '3' && *comando != '4' && *comando != '9') {
            PainelADM();
            printf("|\n|   Comando invalido\n|   Digite novamente:\n|   >>");
            fgets(comando, 5, stdin);
            IsCommandValid_ADM(comando);
        }

    }
}


int ANNIHILATE() {


    printf("| Apagar toda a rede nao tem volta! Se deseja continuar escreva: ADENILSO\n| >> ");
    char *Controle = (char *) malloc(15*sizeof(char));
    char adenilso[10] = {"ADENILSO"};
    fgets(Controle , 15 , stdin);
    for(int i=0; *(Controle+i) != '\0'; i++) {
        if( *(Controle+i) == '\n' ) {
            *(Controle+i) = '\0';
        }
    }
    int certeza = strcmp(adenilso , Controle);

    if(certeza != 0) {printf("|\n| Palavra incorreta, Cancelando...\n| Pressione ENTER"); getchar();  return 0;}
    else {

        int number_of_users = NumberOfUsers();
        FILE *fusers, *ftemp1, *ftemp2;
        char *EscreveNome, *EscreveUser, *path;
        EscreveNome = (char *) malloc(50*sizeof(char));
        EscreveUser = (char *) malloc(30*sizeof(char));
        path = (char *) malloc(100*sizeof(char));

        fusers = fopen("Users.txt" , "r"); if(fusers == NULL) {printf("| ERRO\n| Pressione ENTER"); getchar(); return 0;}

        while( fscanf(fusers , "%[^\n]\n" , EscreveNome) != EOF ) {
            fscanf(fusers , "%[^\n]\n" , EscreveUser);

            memset(path , 0 , sizeof(char));
            strcat(path , "follow_data/"); strcat(path , EscreveUser); strcat(path , ".txt");

            remove(path);
        }
        fclose(fusers);
        
        ftemp1 = fopen("temp1.txt" , "w");
        ftemp2 = fopen("temp2.txt" , "w");




        remove("Users.txt"); remove("posts.txt");
        rename("temp1.txt" , "Users.txt"); rename("temp2.txt" , "posts.txt");

        fclose(ftemp1); fclose(ftemp2); free(Controle); free(EscreveNome); free(EscreveUser); free(path);
    }

    printf("| REDE RESETADA\n| Pressione ENTER"); getchar();
    return 0;
}

int MostFollowers() {
    //ler arquivo por arquivo e guardar o tanto de \n que contem no arquivo
    //o que tiver mais sera a pessoa q tem mais seguidores

    //alocacao de variaveis e ponteiros
    int number_of_users = NumberOfUsers();
    FILE **pfollow;
    int *user_array;
    char *path, *EscreveNome, *EscreveUser, *ch, *most_followers;
    pfollow = (FILE  **) malloc(number_of_users*sizeof(FILE *));
    user_array = (int *) calloc(number_of_users , sizeof(int));
    path = (char *) malloc(60*sizeof(char));
    EscreveNome = (char *) malloc(50*sizeof(char));
    EscreveUser = (char *) malloc(30*sizeof(char));
    ch = (char *) malloc(1*sizeof(char));
    most_followers = (char *) malloc(30*sizeof(char));


    FILE *fusers = fopen("Users.txt" , "r"); if(fusers == NULL) {printf("ERRO#: Nao foi possivel abrir o arquivo"); getchar(); free(pfollow); free(EscreveUser); free(EscreveNome); free(path); free(ch); free(most_followers); free(user_array); return 0;}

    for(int i=0; i<number_of_users; i++) {
        *(user_array+i) = 0;
    }


    //abrindo todos os arquivos, um por vez, pra contar quantos '\n' ha dentro de cada arquivo
    //armazenando em um vetor de inteiros e vendo qual eh o maior deles
    //salvando o user da pessoa que tem mais seguidores e a quantidade de seguidores
    int controle = 0; int numero = 0; int biggest;
    while( fscanf(fusers , "%[^\n]\n" , EscreveNome) != EOF ) {
        fscanf(fusers, "%[^\n]\n" , EscreveUser);

        memset(path , 0 , sizeof(char));
        strcat(path , "follow_data/"); strcat(path , EscreveUser); strcat(path , ".txt");

        *(pfollow + controle) = fopen(path , "r"); if( *(pfollow+controle) == NULL ) {printf("ERRO#: Nao foi possivel abrir o arquivo: %s\n" , path); getchar(); fclose(fusers); free(pfollow); free(EscreveUser); free(EscreveNome); free(path); free(ch); free(most_followers); free(user_array); return 0;} 

        while( ( *ch = fgetc( *(pfollow+controle) ) ) != EOF ) {
            if(*ch == '\n') {
                numero++;
            }
        }

        //atribuindo o numero de pessoas pra tal lugar;
        *(user_array+controle) = numero;
        if(controle == 0) {
            biggest = *(user_array+controle);
            memset(most_followers , 0 ,sizeof(char));
            strcat(most_followers , EscreveUser);
        }


        //verificando no array se esse novo numero de seguidores eh maior que algum outro
        for(int i=0; i<number_of_users; i++) {
            if ( *(user_array + i) > biggest ) {
                biggest = *(user_array+i);
                memset(most_followers , 0 ,sizeof(char));
                strcat(most_followers , EscreveUser);
            }
        }


        fclose( *(pfollow+controle) );
        controle++;
        numero = 0;
    }

    //imprimir quem tem mais seguidores e quantos seguidores sao
    printf("%s ---- " , most_followers);
    printf("%d seguidores\n" , biggest);

    fclose(fusers); free(pfollow); free(EscreveUser); free(EscreveNome); free(path); free(ch); free(most_followers); free(user_array);
    return 0;
}