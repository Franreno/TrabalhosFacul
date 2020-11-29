#include "qwirkle.h"

// Copiei e colei ela aqui, pq o tabuleiro meio q depende dela...kkkk
char *printTab(int valor, char *pecaTab) {

    memset(pecaTab , 0 ,sizeof(char));

    switch(valor)
    {

        case (0):
            strcat(pecaTab ," ");
            break;


        case (11):

            strcat(pecaTab, azul);
            strcat(pecaTab, "◆");
            strcat(pecaTab, color_reset);
            break;

        case (12):

            strcat(pecaTab, branco);
            strcat(pecaTab, "◆");
            strcat(pecaTab, color_reset);
            break;

        case (13):

            strcat(pecaTab, laranja);
            strcat(pecaTab, "◆");
            strcat(pecaTab, color_reset);
            break;

        case (14):

            strcat(pecaTab, roxo);
            strcat(pecaTab, "◆");
            strcat(pecaTab, color_reset);
            break;

        case (15):
            strcat(pecaTab, vermelho);
            strcat(pecaTab, "◆");
            strcat(pecaTab, color_reset);
            break;

        case (16):
            strcat(pecaTab, verde);
            strcat(pecaTab, "◆");
            strcat(pecaTab, color_reset);
            break;

        case (21):
            strcat(pecaTab, azul);
            strcat(pecaTab, "◼");
            strcat(pecaTab, color_reset);
            break;

        case (22):
            strcat(pecaTab, branco);
            strcat(pecaTab, "◼");
            strcat(pecaTab, color_reset);
            break;

        case (23):
            strcat(pecaTab, laranja);
            strcat(pecaTab, "◼");
            strcat(pecaTab, color_reset);
            break;

        case (24):
            strcat(pecaTab, roxo);
            strcat(pecaTab, "◼");
            strcat(pecaTab, color_reset);
            break;

        case (25):
            strcat(pecaTab, vermelho);
            strcat(pecaTab, "◼");
            strcat(pecaTab, color_reset);
            break;

        case (26):
            strcat(pecaTab, verde);
            strcat(pecaTab, "◼");
            strcat(pecaTab, color_reset);
            break;

        case (31):
            strcat(pecaTab, azul);
            strcat(pecaTab, "●");
            strcat(pecaTab, color_reset);
            break;

        case (32):
            strcat(pecaTab, branco);
            strcat(pecaTab, "●");
            strcat(pecaTab, color_reset);
            break;

        case (33):
            strcat(pecaTab, laranja);
            strcat(pecaTab, "●");
            strcat(pecaTab, color_reset);
            break;

        case (34):
            strcat(pecaTab, roxo);
            strcat(pecaTab, "●");
            strcat(pecaTab, color_reset);
            break;

        case (35):
            strcat(pecaTab, vermelho);
            strcat(pecaTab, "●");
            strcat(pecaTab, color_reset);
            break;

        case (36):
            strcat(pecaTab, verde);
            strcat(pecaTab, "●");
            strcat(pecaTab, color_reset);
            break;

        case (41):
            strcat(pecaTab, azul);
            strcat(pecaTab, "★");
            strcat(pecaTab, color_reset);
            break;

        case (42):
            strcat(pecaTab, branco);
            strcat(pecaTab, "★");
            strcat(pecaTab, color_reset);
            break;

        case (43):
            strcat(pecaTab, laranja);
            strcat(pecaTab, "★");
            strcat(pecaTab, color_reset);
            break;

        case (44):
            strcat(pecaTab, roxo);
            strcat(pecaTab, "★");
            strcat(pecaTab, color_reset);
            break;

        case (45):
            strcat(pecaTab, vermelho);
            strcat(pecaTab, "★");
            strcat(pecaTab, color_reset);
            break;

        case (46):
            strcat(pecaTab, verde);
            strcat(pecaTab, "★");
            strcat(pecaTab, color_reset);
            break;

        case (51):
            strcat(pecaTab, azul);
            strcat(pecaTab, "✚");
            strcat(pecaTab, color_reset);
            break;

        case (52):
            strcat(pecaTab, branco);
            strcat(pecaTab, "✚");
            strcat(pecaTab, color_reset);
            break;

        case (53):
            strcat(pecaTab, laranja);
            strcat(pecaTab, "✚");
            strcat(pecaTab, color_reset);
            break;

        case (54):
            strcat(pecaTab, roxo);
            strcat(pecaTab, "✚");
            strcat(pecaTab, color_reset);
            break;

        case (55):
            strcat(pecaTab, vermelho);
            strcat(pecaTab, "✚");
            strcat(pecaTab, color_reset);
            break;

        case (56):
            strcat(pecaTab, verde);
            strcat(pecaTab, "✚");
            strcat(pecaTab, color_reset);
            break;

        case (61):
            strcat(pecaTab, azul);
            strcat(pecaTab, "✸");
            strcat(pecaTab, color_reset);
            break;

        case (62):
            strcat(pecaTab, branco);
            strcat(pecaTab, "✸");
            strcat(pecaTab, color_reset);
            break;

        case (63):
            strcat(pecaTab, laranja);
            strcat(pecaTab, "✸");
            strcat(pecaTab, color_reset);
            break;

        case (64):
            strcat(pecaTab, roxo);
            strcat(pecaTab, "✸");
            strcat(pecaTab, color_reset);
            break;

        case (65):
            strcat(pecaTab, vermelho);
            strcat(pecaTab, "✸");
            strcat(pecaTab, color_reset);
            break;

        case (66):
            strcat(pecaTab, verde);
            strcat(pecaTab, "✸");
            strcat(pecaTab, color_reset);
            break;

        case (-1):
            strcat(pecaTab, "  ");
            break;

        default:
            strcat(pecaTab, "Err");
            break;

    }

    return pecaTab;
}
