#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"rede.h"

/*

Arquivo que contém todos os elementos da interface do usuário
    Feed Inicial (apenas com as pestagens dos perfis que o usuário segue)
    Feed Geral (todos os posts que não foram feitos pelo usuário)
    Meus Posts
    Ações de follow/unfollow, Postar, Ver infos próprias, resetar feed atual

*/

void user_feed(char *UserNick, FILE *fdin, char **dysplay_nicks, int *dysplay_n_posts);
void user_general_feed(char *UserNick, FILE *fdin, char **dysplay_nicks, int *dysplay_n_posts);
void user_posts(char *UserNick, FILE *fdin, int *dysplay_flow_posts, int *dysplay_n_posts);

void IsCommandValid_user_feed(char *comando);
void IsCommandValid_user_posts(char *comando);

int following_verif(char *UserNick, char *login);

void new_post(char *UserNick);

void UserInformations(char *UserName, char *UserNick);
int HowManyPosts(char *UserNick);
int HowManyFollowers(char *UserName, char *UserNick);
int WhoIFollow(char *UserNick);

void follow(char *UserNick, char *login);
void unfollow(char *UserNick, char *login);
void remove_post(int post_flow, FILE *fdin);




void user_interface(char *comando, char *UserName, char *UserNick) {

    char feed = 'f', **dysplay_nicks;
    int *dysplay_n_posts, n_posts, following, *dysplay_flow_posts;


    FILE *fdin = fopen("posts.txt" , "r");              // Abre o arquivo dos posts
    if(fdin == NULL) {                                  // Verifica se o arquivo foi aberto com sucesso
        printf("ERRO!"); exit(0);
    }

    dysplay_n_posts = &n_posts;                         // Variavel que diz quantos posts estão na tela
    dysplay_nicks = malloc(5 * sizeof(char*));
    for(int i = 0; i < 5; i++) {
        dysplay_nicks[i] = malloc(30 * sizeof(char));
    }                                                   // Vetor de strings que diz os autores dos 5 posts de feed em tela
    dysplay_flow_posts = malloc(5 * sizeof(int));       // Vetor que diz onde no arquivo estão os 5 meus posts em tela


    while(*comando != '9') {                            // Mantém no loop enquanto o usuário inserir o comando de log off

        switch (feed) {                                 // Abre o feed de acordo com a escolha do usuário
            case ('f'):                                 // Feed (Inicial)
                user_feed(UserNick, fdin, dysplay_nicks, dysplay_n_posts);
                break;
            case ('g'):                                 // Feed Geral
                user_general_feed(UserNick, fdin, dysplay_nicks, dysplay_n_posts);
                break;
            case ('p'):                                 // Minhas postagens
                user_posts(UserNick, fdin, dysplay_flow_posts, dysplay_n_posts);
                break;
        }

        printf("|\n|   >>  ");
        fgets(comando, 5, stdin);                       // Recebe o comando do usuário

        if(feed == 'p') {
            IsCommandValid_user_posts(comando);
        } else {
            IsCommandValid_user_feed(comando);
        }                                               // Verifica resposta de acordo com o feed atual em tela


        switch (*comando) {                             // Dado o comando, a função correta pe chamada pelo switch

            case ('i'):                                 // Comando para voltar ao inicio do feed
                rewind(fdin);
                break;

            case('1'):
            case('2'):
            case('3'):
            case('4'):
            case('5'):                                  // Se o comando é 1, 2, 3, 4 ou 5

                if(*dysplay_n_posts >= ((int)(*comando) - 48) && (feed == 'f' || feed == 'g')) {
                                                        // Se existia o post na tela de um dos feeds

                    following = following_verif(UserNick, dysplay_nicks[((int)(*comando) - 48)-1]);

                    if(following == 1) {                // Se o autor do post já é seguido, é dado unfollow
                        unfollow(UserNick, dysplay_nicks[((int)(*comando) - 48) - 1]);
                    }

                    if(following == 0) {                // Se o autor do post n é seguido, é dado follow
                        follow(UserNick, dysplay_nicks[((int)(*comando) - 48) - 1]);
                    }

                    feed = 'f';                         // É retornado após a ação para o feed inicial

                } else if(*dysplay_n_posts >= ((int)(*comando) - 48) && feed == 'p') {
                                                        // Se existia o post na tela de meus posts, o post é apagado
                    remove_post(dysplay_flow_posts[((int)(*comando) - 48) - 1], fdin);

                } else {                                // Se o post não existia na tela, é dado um aviso de comando invalido
                    printf("|   Comando inválido. ENTER para continuar.\n");
                    getchar();
                }

                rewind(fdin);                           // Arquivo de posts reiniciado
                break;

            case ('6'):                                 // Comando para toggle entre Feed (inicial) e Feed Geral
                rewind(fdin);
                if(feed != 'f') {
                    feed = 'f';
                } else {
                    if(feed == 'f') {
                        feed = 'g';
                    }
                }
                break;

            case ('7'):                                 // Comando para ver as infos de perfil
                UserInformations(UserName, UserNick);
                rewind(fdin);
                break;

            case('8'):                                  // Comando para ir para minhas postagens
                rewind(fdin);
                feed = 'p';
                break;

            case('0'):                                  // Comando para fazer nova postagem
                fclose(fdin);
                new_post(UserNick);
                fdin = fopen("posts.txt" , "r");
                feed = 'p';
                break;

            default:
                break;
        }
    }

    *comando = '0';
    fclose(fdin); free(dysplay_nicks);
}



void IsCommandValid_user_feed(char *comando) {
    int tam = 0;
    for(int i=0; *(comando+i) != '\n'; i++) {           // Analiza tamanho da string em *comando
        tam++;
    }

    if(tam > 1) {                                       // Tamanho máximo do comando deve ser 1
        printf("|\n|   Comando invalido\n|   Digite novamente:\n|   >>");
        fgets(comando, 5, stdin);
        IsCommandValid_user_feed(comando);
    }
    else {

        if(*comando != '1' && *comando != '2' && *comando != '3' && *comando != '4' && *comando != '5' && *comando != '6' && *comando != '7' && *comando != '8' && *comando != '9' && *comando != '0' && *comando != 'i' && tam != 0) {
                                                        // Comando precisa estar entre os comandos do menu de feed
            printf("|\n|   Comando invalido\n|   Digite novamente:\n|   >>");
            fgets(comando, 5, stdin);
            IsCommandValid_user_feed(comando);
        }

    }
}



void IsCommandValid_user_posts(char *comando) {
    int tam = 0; //tamanho da string
    for(int i=0; *(comando+i) != '\n'; i++) {           // Analiza tamanho da string em *comando
        tam++;
    }

    if(tam > 1) {                                       // Tamanho máximo do comando deve ser 1
        printf("|\n|   Comando invalido\n|   Digite novamente:\n|   >>");
        fgets(comando, 5, stdin);
        IsCommandValid_user_posts(comando);
    }
    else {

        if(*comando != '1' && *comando != '2' && *comando != '3' && *comando != '4' && *comando != '5' && *comando != '6' && *comando != '7' && *comando != '9' && *comando != '0' && *comando != 'i' && tam != 0) {
                                                        // Comando precisa estar entre os comandos do menu de feed
            printf("|\n|   Comando invalido\n|   Digite novamente:\n|   >>");
            fgets(comando, 5, stdin);
            IsCommandValid_user_posts(comando);
        }

    }
}



void user_feed(char *UserNick, FILE *fdin, char **dysplay_nicks, int *dysplay_n_posts) {

    int user_post, controle = 0, following, not_print = 0;
    char *tempo, *login, *tweet, *tweet1, *tweet2;

    PainelFeedUsuario();                                // Chama o header do feed

    tempo = (char *) malloc(50*sizeof(char));           // String para armazenar temporariamente a hora da postagem
    login = (char *) malloc(30*sizeof(char));           // String para armazenar temporariamente o nick do autor
    tweet = (char *) malloc(129*sizeof(char));          // String para armazenar temporariamente o texto da postagem
    tweet1 = (char *) malloc(65*sizeof(char));
    tweet2 = (char *) malloc(64*sizeof(char));          // Strings para armazenar a string "quebrada" ao meio

    while( controle != 5 && fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {
                                                        // Mostra 5 posts por vez, ou ate nao ter mais nenhum post (EOF)

        memset(tweet, '\0', 129*sizeof(char));

        fscanf(fdin , "%[^\n]\n" , login);              // Escaneio o nick do autor
        fscanf(fdin , "%[^\n]\n" , tweet);              // Escaneio o tweet

        following = following_verif(UserNick, login);   // Verifico o usuário logado segue o autor


        while((strcmp(UserNick, login) == 0 || following != 1) && fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {
                                                        // Escaneia até que ele encontre um post não próprio de alguem que o usuário siga
            fscanf(fdin , "%[^\n]\n" , login);
            fscanf(fdin , "%[^\n]\n" , tweet);

            following = following_verif(UserNick, login);
        }

        if(strcmp(UserNick, login) == 0 || following != 1) {
            not_print = 1;
        }

        if(not_print == 0) {                            // Concerto de bug do ultimo post do arquivo

            memcpy(dysplay_nicks[controle], login, 30); // Salvo o login do usuário na lista de autores dos posts em tela

            memset(tweet1, '\0', 65*sizeof(char));
            memset(tweet2, '\0', 64*sizeof(char));

            memcpy(tweet1, tweet, 65);                  // Quebro o tweet em duas linhas
            memcpy(tweet2, tweet+65, 65);

            printf("|     @%s %s\n" , login, tempo);
            printf("| [%d] %s\n",controle+1, tweet1);
            if(strlen(tweet) > 65) {                    // Printo as duas apenas se a segunda string é usada para evitar lixo
                printf("|     %s\n" , tweet2);
            } else {
                printf("|\n");
            }
            controle++;
            printf("|-------------------------------------------------------------------------------\n");
        }

    }

    *dysplay_n_posts = controle;                        // Salvo numero de posts em tela para limitar os comandos possíveis

    if(controle < 5) {                                  // Imprimo a msg que os posts acabaram
        printf("|\n|   Hummm... Parece que não há mais postagens das pessoas que você segue... \n|   Entre no feed geral, conheça mais pessoas e as siga!\n|-------------------------------------------------------------------------------\n");
        controle++;
    }

    for(int i = 0; i < 5-controle; i++) {               // Printo as lacunas vazias
        printf("|\n|\n|\n|-------------------------------------------------------------------------------\n");
    }

    // OBS: "%[^\n]\n" significa que o fscanf le, inclusive espacos, ate encontrar um \n dai tem outro \n logo em seguida
    // pra ele descer de linha

    free(tempo); free(login); free(tweet);free(tweet1); free(tweet2);
}



int following_verif(char *UserNick, char *login) {

    char *UserFollowFile, *user;
    FILE *ffollow;
    int following;

    UserFollowFile = (char *) malloc(50 * sizeof(char));
    user = (char *) malloc(30 * sizeof(char));

    for(int i=0; i < 50; i++) {                         // Zera a string
        UserFollowFile[i] = '\0';
    }

    strcat(UserFollowFile, "follow_data/");
    strcat(UserFollowFile, UserNick);
    strcat(UserFollowFile, ".txt");                     // Monta a string para acessar o arquivo do usuário

    ffollow = fopen(UserFollowFile, "r");               // Abre o arquivo de pessoas q o usuário segue
    rewind(ffollow);

    following = 0;                                      // Pŕé-define a como "não segindo"

    while(fscanf(ffollow, "%[^\n]\n", user) != EOF) {
        if(strcmp(login, user) == 0) {                  // Se estiver sendo seguido
            following = 1;                              // Variável passa a valer 1
        }
    }
    free(user); fclose(ffollow); free(UserFollowFile);

    return following;
}



void user_general_feed(char *UserNick, FILE *fdin, char **dysplay_nicks, int *dysplay_n_posts) {
                                                        // Funcionamento analogo ao do user_feed

    int user_post, controle = 0;
    char *tempo, *login, *tweet, *tweet1, *tweet2;
    int not_print = 0;

    PainelFeedGeralUsuario();

    tempo = (char *) malloc(50*sizeof(char));
    login = (char *) malloc(30*sizeof(char));
    tweet = (char *) malloc(129*sizeof(char));
    tweet1 = (char *) malloc(65*sizeof(char));
    tweet2 = (char *) malloc(64*sizeof(char));

    //mostrar 5 posts por vez, ou ate nao ter mais nenhum post (EOF).
    while(controle != 5 && fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {

        memset(tweet, '\0', 129*sizeof(char));

        fscanf(fdin , "%[^\n]\n" , login);
        fscanf(fdin , "%[^\n]\n" , tweet);

        while(strcmp(UserNick, login) == 0 && fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {
            fscanf(fdin , "%[^\n]\n" , login);
            fscanf(fdin , "%[^\n]\n" , tweet);
        }

        if(strcmp(UserNick, login) == 0) {
            not_print = 1;
        }

        if(not_print == 0) {

            memcpy(dysplay_nicks[controle], login, 30);

            memset(tweet1, '\0', 65*sizeof(char));
            memset(tweet2, '\0', 64*sizeof(char));

            memcpy(tweet1, tweet, 65);
            memcpy(tweet2, tweet+65, 65);

            printf("|     @%s %s\n" , login, tempo);
            printf("| [%d] %s\n",controle+1, tweet1);
            if(strlen(tweet) > 65) {
                printf("|     %s\n" , tweet2);
            } else {
                printf("|\n");
            }
            controle++;
            printf("|-------------------------------------------------------------------------------\n");
        }

    }

    *dysplay_n_posts = controle;

    if(controle < 5) {
        printf("|\n|   Parece que não há mais postagens...\n|\n|-------------------------------------------------------------------------------\n");
        controle++;
    }

    for(int i = 0; i < 5-controle; i++) {
        printf("|\n|\n|\n|-------------------------------------------------------------------------------\n");
    }

    // OBS: "%[^\n]\n" significa que o fscanf le, inclusive espacos, ate encontrar um \n dai tem outro \n logo em seguida
    // pra ele descer de linha

    free(tempo); free(login); free(tweet);free(tweet1); free(tweet2);
}



void user_posts(char *UserNick, FILE *fdin, int *dysplay_flow_posts, int *dysplay_n_posts) {
                                                        // Funcionamento analogo ao do user_feed

    int user_post, controle = 0, temp_flow;
    char *tempo, *login, *tweet, *tweet1, *tweet2;
    int not_print = 0;

    PainelPostsUsuario();

    tempo = (char *) malloc(50*sizeof(char));
    login = (char *) malloc(30*sizeof(char));
    tweet = (char *) malloc(129*sizeof(char));
    tweet1 = (char *) malloc(65*sizeof(char));
    tweet2 = (char *) malloc(64*sizeof(char));

     temp_flow = ftell(fdin);                           // Salva a posição inicial do primeiro scan

    //mostrar 5 posts por vez, ou ate nao ter mais nenhum post (EOF).
    while(controle != 5 && fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {

        memset(tweet, '\0', 129*sizeof(char));

        dysplay_flow_posts[controle] = temp_flow;       // Coloca a posição salva como a posição do post printado

        fscanf(fdin , "%[^\n]\n" , login);
        fscanf(fdin , "%[^\n]\n" , tweet);

        temp_flow = ftell(fdin);                        // Salva a posição de um próximo scan, para se o scan feito não for printado

        while(strcmp(UserNick, login) != 0 && fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {

            dysplay_flow_posts[controle] = temp_flow;   // Se o scan for refeito, a posição é salva com o ultimo valor medido

            fscanf(fdin , "%[^\n]\n" , login);
            fscanf(fdin , "%[^\n]\n" , tweet);

            temp_flow = ftell(fdin);                    // Salva a posição de um próximo scan, para se o scan feito não for printado
        }

        if(strcmp(UserNick, login) != 0) {
            not_print = 1;
        }

        if(not_print == 0) {

            memset(tweet1, '\0', 65*sizeof(char));
            memset(tweet2, '\0', 64*sizeof(char));

            memcpy(tweet1, tweet, 65);
            memcpy(tweet2, tweet+65, 65);

            printf("|     @%s %s\n" , login, tempo);
            printf("| [%d] %s\n",controle+1, tweet1);
            if(strlen(tweet) > 65) {
                printf("|     %s\n" , tweet2);
            } else {
                printf("|\n");
            }
            controle++;
            printf("|-------------------------------------------------------------------------------\n");
        }

    }

    *dysplay_n_posts = controle;

    if(controle < 5) {
        printf("|\n|   Parece que suas postegens acabam por aqui...\n|\n|-------------------------------------------------------------------------------\n");
        controle++;
    }

    for(int i = 0; i < 5-controle; i++) {
        printf("|\n|\n|\n|-------------------------------------------------------------------------------\n");
    }

    // OBS: "%[^\n]\n" significa que o fscanf le, inclusive espacos, ate encontrar um \n dai tem outro \n logo em seguida
    // pra ele descer de linha

    free(tempo); free(login); free(tweet);free(tweet1); free(tweet2);
}



void follow(char *UserNick, char *login) {

    char *UserFollowFile;
    FILE *ffollow;

    UserFollowFile = (char *) malloc(50 * sizeof(char));

    for(int i=0; i < 50; i++) {
        UserFollowFile[i] = '\0';
    }

    strcat(UserFollowFile, "follow_data/");
    strcat(UserFollowFile, UserNick);
    strcat(UserFollowFile, ".txt");

    ffollow = fopen(UserFollowFile, "r+");              // Abre o arquivo de perfis que o usuario segue

    fseek(ffollow, 0, SEEK_END);

    fprintf(ffollow, "%s\n", login);                    // Adiciona autor do post selecionado à lista

    PainelFollow(login);

    fclose(ffollow); free(UserFollowFile);

}



void unfollow(char *UserNick, char *login) {

    char *UserFollowFile, *user;
    FILE *ffollow, *ftemp;
    printf("%s\n", login);

    UserFollowFile = (char *) malloc(50 * sizeof(char));
    user = (char *) malloc(30 * sizeof(char));

    for(int i=0; i < 50; i++) {
        UserFollowFile[i] = '\0';
    }

    strcat(UserFollowFile, "follow_data/");
    strcat(UserFollowFile, UserNick);
    strcat(UserFollowFile, ".txt");

    ffollow = fopen(UserFollowFile, "r+");              // Abre o arquivo de perfis que o usuario segue
    ftemp = fopen("posts_temp.txt", "r+");              // Abre o arquivo temporário

    while(fscanf(ffollow, "%[^\n]\n", user) != EOF) {   // Copia tudo no arquivo temporario
        if(strcmp(login, user) != 0) {                  // Menos o que é igual ao login que deseja ser retidado
            fprintf(ftemp, "%s\n", user);
        }
    }

    freopen(UserFollowFile, "w", ffollow);              // Reseta o arquivo princial
    rewind(ftemp);                                      // Rebubina o arquivo temporário

    while(fscanf(ftemp, "%[^\n]\n", user) != EOF) {     // Copia o que ta no temporario para o principal
        printf("%s\n", user);
        fprintf(ffollow, "%s\n", user);
    }

    freopen("posts_temp.txt", "w", ftemp);              // Reseta o arquivo temporário

    PainelUnfollow(login);

    fclose(ftemp); free(user); fclose(ffollow); free(UserFollowFile);

}



void new_post(char *UserNick) {

    PainelNovaPostagem();
    int tam = 0;

    FILE *fposts = fopen("posts.txt", "r+");
    FILE *ftempposts = fopen("posts_temp.txt", "r+");
    char *new_user_post, *temp_data;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    new_user_post = (char *) malloc(129 * sizeof(char));// Alocação da memoria para o texto do post
    temp_data = (char *) malloc(129 * sizeof(char));    // String temporaria

    while(fscanf(fposts, "%[^\n]\n" , temp_data) != EOF) {
        fprintf(ftempposts, "%s\n", temp_data);
    }                                                   // Realoca tudo do arquivo principal no arquivo temporário

    freopen("posts.txt", "w", fposts);                  // Limpa o arquivo de posts

    printf("|\n|   >> ");
    fgets(new_user_post, 129, stdin);                   // Colhe o novo post do usuário

    for(int i=0; *(new_user_post+i) != '\n'; i++) {     // Verifica o tamanho da string inserida
        tam++;
    }

    if(tam > 0) {                                       // Insere a string com tamanho não nulo
        fprintf(fposts, "%d-%02d-%02d %02d:%02d:%02d\n%s\n%s", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, UserNick, new_user_post);
    }

    rewind(ftempposts);
    while(fscanf(ftempposts, "%[^\n]\n", temp_data) != EOF) {
        fprintf(fposts, "%s\n", temp_data);
    }                                                   // Retorna todos os valores no temporario para o arquivo principal

    ftempposts = freopen("posts_temp.txt", "w", ftempposts);

    fclose(fposts); fclose(ftempposts); free(new_user_post); free(temp_data);

}



void UserInformations(char *UserName, char *UserNick) {
    //mostar na tela:: Nome, login, numero de posts, numero de seguidores

    PainelInfoUsuario();
    printf("|\n| Seu nome: %s" , UserName);
    printf("| Seu login: %s\n" , UserNick);
    printf("| Numero de posts: %d\n" , HowManyPosts(UserNick));
    printf("| Voce segue: ");
    WhoIFollow(UserNick);
    printf("\n| Seguidores: ");
    printf("\n| Numero de seguidores: %d\n" , HowManyFollowers(UserName, UserNick));
    getchar();
}


// dado um certo usuario, ver quantas vezes o nome desse usuario aparece no arquivo de posts e incrementar em um contador
// no final, retornar o valor desse contador pra ser impresso.

int HowManyPosts(char *UserNick) {

    FILE *fdin = fopen("posts.txt" , "r");
    if(fdin == NULL) {
        printf("| erro!!"); exit(0);
    }

    char *tempo, *login, *tweet;
    tempo = (char *) malloc(50*sizeof(char));
    login = (char *) malloc(30*sizeof(char));
    tweet = (char *) malloc(129*sizeof(char));


    int vezes = 0;
    int found;
    while(fscanf(fdin , "%[^\n]\n" , tempo) != EOF) {
        fscanf(fdin , "%[^\n]\n" , login);
        fscanf(fdin , "%[^\n]\n" , tweet);

        found = strcmp(login, UserNick);
        if(found == 0) {
            vezes++;
            found = -1;
        }

    }

    fclose(fdin); free(tempo); free(login); free(tweet);
    return vezes;
}


//funcao imprime o numero de seguidores q a pessoa tem e imprime quem sao
int HowManyFollowers(char *UserName, char *UserNick) {
    int number_of_users = NumberOfUsers();
    int followers = 0;

    char *login_data = (char *) malloc(30*sizeof(char));
    char *PathToUserNick = (char *) malloc(60*sizeof(char));
    char *EscreveUser = (char *) malloc(50*sizeof(char));
    char *UserNick_atual = (char *) malloc(30*sizeof(char));
    char *UserName_atual = (char *) malloc(50*sizeof(char));
    strcpy(login_data, UserNick);
    strcpy(UserNick_atual, UserNick);
    strcpy(UserName_atual, UserName);


    FILE **pfollow, *puser, *ptemp;
    pfollow = (FILE **) malloc(number_of_users*sizeof(FILE *));
    puser = fopen("Users.txt" , "r");

    memset(PathToUserNick, 0, sizeof(char));
    int controle = 0;

    while( fscanf(puser, "%[^\n]\n" , UserName_atual) != EOF && controle<number_of_users) {
        fscanf(puser , "%[^\n]\n" , UserNick_atual);

        int found1 = strcmp(UserNick_atual , login_data);


        if(found1 != 0) {

            strcat(PathToUserNick , "follow_data/"); strcat(PathToUserNick , UserNick_atual); strcat(PathToUserNick , ".txt");


            *(pfollow + controle) = fopen( PathToUserNick ,  "r");
            if ( *(pfollow + controle) == NULL ) {
                printf("| nao foi possivel abrir o arquivo\n");
                exit(0);
            }

            while( fscanf( *(pfollow+controle) , "%[^\n]\n" ,  EscreveUser) != EOF) {
                int found = strcmp(EscreveUser , login_data);
                if(found == 0) {
                    printf("%s.   " , UserNick_atual); //imprime quem sao os seguidores
                    followers++;
                }
            }

            memset(PathToUserNick, 0, sizeof(char));
            fclose( *(pfollow+controle) );
        }

        controle++;
    }

    fclose(puser); free(PathToUserNick); free(EscreveUser); free(login_data); free((pfollow)); free(UserNick_atual); free(UserName_atual);
    return followers;
}



int WhoIFollow(char *UserNick) {
    char *Path = (char *)malloc(60*sizeof(char));
    memset(Path , 0 , sizeof(char));
    char *EscreveUser = (char *) malloc(50*sizeof(char));
    strcat(Path , "follow_data/"); strcat(Path , UserNick); strcat(Path , ".txt");

    FILE *fdin = fopen(Path , "r");
    if(fdin == NULL) {
        printf("| erro desconhecido.."); return 0;
    }

    while( fscanf(fdin , "%[^\n]\n" , EscreveUser) != EOF ) {
        printf("%s.   " , EscreveUser);
    }

    fclose(fdin); free(Path); free(EscreveUser);
    return 0;
}



void remove_post(int post_flow, FILE *fdin) {

    int flow_now;
    char *time_aux, *nick_aux, *post_aux;
    FILE *ftemp;

    time_aux = (char *) malloc(50*sizeof(char));
    nick_aux = (char *) malloc(30*sizeof(char));
    post_aux = (char *) malloc(129*sizeof(char));

    ftemp = fopen("posts_temp.txt", "r+");
    rewind(fdin);

    flow_now = ftell(fdin);

    while(fscanf(fdin, "%[^\n]\n" , time_aux) != EOF) {
        fscanf(fdin, "%[^\n]\n" , nick_aux);
        fscanf(fdin, "%[^\n]\n" , post_aux);            // Escaneio as infos do arquivo de posts

        if(flow_now != post_flow) {
            fprintf(ftemp, "%s\n", time_aux);
            fprintf(ftemp, "%s\n", nick_aux);
            fprintf(ftemp, "%s\n", post_aux);           // Aloco no arquivo temporário todos os tweets menos o indicado na localização
        }

        flow_now = ftell(fdin);
    }

    rewind(ftemp);
    rewind(fdin);

    freopen("posts.txt", "w", fdin);                    // Reseto o arquivo principal e rebubino o temporário

    while(fscanf(ftemp, "%[^\n]\n" , time_aux) != EOF) {
        fscanf(ftemp, "%[^\n]\n" , nick_aux);
        fscanf(ftemp, "%[^\n]\n" , post_aux);

        fprintf(fdin, "%s\n", time_aux);
        fprintf(fdin, "%s\n", nick_aux);
        fprintf(fdin, "%s\n", post_aux);                // Realoco tudo do temporário no arquivo principal de posts

        flow_now = ftell(fdin);
    }

    freopen("posts_temp.txt", "w", ftemp);
    rewind(fdin);

    freopen("posts.txt", "r+", fdin);

    fclose(ftemp); free(time_aux); free(nick_aux); free(post_aux);
}
