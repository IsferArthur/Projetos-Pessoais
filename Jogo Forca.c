#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void desenha_forca(int erros)
{
    printf("\n  _______ \n");
    printf(" |/      | \n");

    if (erros == 0)
    {
        printf(" |         \n");
        printf(" |         \n");
        printf(" |         \n");
        printf(" |         \n");
    }
    else if (erros == 1)
    {
        printf(" |      ( ) \n");
        printf(" |         \n");
        printf(" |         \n");
        printf(" |         \n");
    }
    else if (erros == 2)
    {
        printf(" |      ( ) \n");
        printf(" |       | \n");
        printf(" |       | \n");
        printf(" |         \n");
    }
    else if (erros == 3)
    {
        printf(" |      ( ) \n");
        printf(" |      \\| \n");
        printf(" |       | \n");
        printf(" |         \n");
    }
    else if (erros == 4)
    {
        printf(" |      ( ) \n");
        printf(" |      \\|/ \n");
        printf(" |       | \n");
        printf(" |         \n");
    }
    else if (erros == 5)
    {
        printf(" |      ( ) \n");
        printf(" |      \\|/ \n");
        printf(" |       | \n");
        printf(" |      /  \n");
    }
    else if (erros == 6)
    {
        printf(" |      ( ) \n");
        printf(" |      \\|/ \n");
        printf(" |       | \n");
        printf(" |      / \\ \n");
    }

    printf(" | \n");
    printf("_|___ \n\n");
}

int ja_digitada(char letra, char letras_usadas[], int total_usadas)
{
    for (int i = 0; i < total_usadas; i++)
    {
        if (letras_usadas[i] == letra)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{

    char cat1[][20] = {"BRASIL", "ARGENTINA", "CHILE", "COLOMBIA", "URUGUAI", "PERU", "EQUADOR", "VENEZUELA", "BOLIVIA", "PARAGUAI"};
    char cat2[][20] = {"LUKE", "LEIA", "YODA", "VADER", "CHEWBACCA", "ANAKIN", "PADME", "PALPATINE", "KYLO", "REY"};
    char cat3[][20] = {"FLAMENGO", "PALMEIRAS", "SANTOS", "GREMIO", "CRUZEIRO", "VASCO", "CORINTHIANS", "CORITIBA", "BOTAFOGO", "FLUMINENSE"};
    // Coritiba maior do paraná!!

    int opcao_categoria;
    char palavra_secreta[20];

    srand(time(NULL));

    printf("========================================\n");
    printf("        BEM-VINDO AO JOGO DA FORCA      \n");
    printf("========================================\n");
    printf("Escolha uma categoria para jogar:\n");
    printf("1 - Paises da America do Sul\n");
    printf("2 - Personagens de Star Wars\n");
    printf("3 - Times de Futebol da Serie A \n");
    printf("Escolha (1-3): ");

    do
    {
        scanf("%d", &opcao_categoria);
        if (opcao_categoria < 1 || opcao_categoria > 3)
        {
            printf("Opcao invalida! Digite 1, 2 ou 3: ");
        }
    } while (opcao_categoria < 1 || opcao_categoria > 3);

    // Sorteia de 0 a 9
    int indice_sorteio = rand() % 10;

    // Copia a palavra sorteada para a variável 'palavra_secreta'
    if (opcao_categoria == 1)
        strcpy(palavra_secreta, cat1[indice_sorteio]);
    else if (opcao_categoria == 2)
        strcpy(palavra_secreta, cat2[indice_sorteio]);
    else if (opcao_categoria == 3)
        strcpy(palavra_secreta, cat3[indice_sorteio]);

    int tamanho_palavra = strlen(palavra_secreta);
    int vidas = 6;
    int erros = 0;

    char letras_certas[26] = {0};
    char letras_erradas[26] = {0};
    int qtd_certas = 0;
    int qtd_erradas = 0;

    int ganhou = 0;

    while (vidas > 0 && ganhou == 0)
    {
        printf("\n========================================\n");
        desenha_forca(erros);
        printf("Vidas restantes: %d\n", vidas);

        printf("Letras erradas: ");
        for (int i = 0; i < qtd_erradas; i++)
        {
            printf("%c ", letras_erradas[i]);
        }
        printf("\n");

        printf("Palavra: ");
        ganhou = 1;
        for (int i = 0; i < tamanho_palavra; i++)
        {
            if (ja_digitada(palavra_secreta[i], letras_certas, qtd_certas))
            {
                printf("%c ", palavra_secreta[i]);
            }
            else
            {
                printf("_ ");
                ganhou = 0;
            }
        }
        printf("\n");

        if (ganhou)
            break;

        char palpite;
        printf("\nDigite uma letra: ");

        scanf(" %c", &palpite);
        palpite = toupper(palpite);

        if (palpite < 'A' || palpite > 'Z')
        {
            printf("Por favor, digite apenas letras do alfabeto!\n");
            continue;
        }

        if (ja_digitada(palpite, letras_certas, qtd_certas) || ja_digitada(palpite, letras_erradas, qtd_erradas))
        {
            printf("\n=> ATENCAO: Voce ja tentou a letra '%c'. Tente outra!\n", palpite);
            continue;
        }

        int acertou = 0;
        for (int i = 0; i < tamanho_palavra; i++)
        {
            if (palavra_secreta[i] == palpite)
            {
                acertou = 1;
                break;
            }
        }

        if (acertou)
        {
            printf("\n=> BOA! A letra '%c' existe na palavra!\n", palpite);
            letras_certas[qtd_certas] = palpite;
            qtd_certas++;
        }
        else
        {
            printf("\n=> QUE PENA! A letra '%c' nao existe na palavra.\n", palpite);
            letras_erradas[qtd_erradas] = palpite;
            qtd_erradas++;
            erros++;
            vidas--;
        }
    }

    printf("\n========================================\n");
    desenha_forca(erros);
    if (ganhou)
    {
        printf(" PARABENS! Voce adivinhou a palavra: %s \n", palavra_secreta);
    }
    else
    {
        printf(" GAME OVER! \n");
        printf("A palavra secreta era: %s\n", palavra_secreta);
    }
    printf("========================================\n");

    return 0;
}