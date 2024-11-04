#include <stdio.h>
#include<locale.h>

#define max_produtos 50

int main()
{   //deixar a linguagem em português
    setlocale(LC_ALL, "Portuguese");

    //Tela inicial

    printf("|--------------------------------------------\n"
    "|Bem-vindo(a) ao seu Sistema de Estoque     |\n"
    "|--------------------------------------------\n"
    "|O que deseja fazer?\n"
    "|1. Adicionar um novo produto\n"
    "|2. Consultar informações sobre um produto\n"
    "|3. Registrar a venda de um produto\n"
    "|4. Exibir um relatório geral\n"
    "|5. Apagar um produto\n"
    "|6. Sair\n|\n"
    "|Digite sua escolha: ");
//variaveis com suas respectivas funções
//valor de teste, valor temporario, for, quantidade de produtos a adicionar, valores temporarios, venda a ser registrada, contador, escolha.
    int found, temp, i, j, prod, novoCod, codProd, quantVend, espaco = 0, opc = 0;
   //Código do produto      //Quantidade do produto
    int cod[max_produtos], qtd[max_produtos];
    //Preço do produto
    double valor[max_produtos];
    //Loop infinito para facilitar o codigo
    while(1)
    {
        scanf("%d", &opc);
        printf("|\n");
        //Opção de sair
        if(opc == 6){
            printf("|--------------------------------------------\n"
            "|Obrigado por usar nosso sistema!\n"
            "|\n|--------------------------------------------\n");
            break;
            //Não deixar usar um número fora as opções dadas
        } else if(opc < 1 || opc > 6) {
            printf("|Número inválido, tente novamente");
            //função de adicionar o produto
        } else if(opc == 1) {
            printf("|--------------------------------------------\n"
            "|Tamanho do estoque: %d/%d\n", espaco, max_produtos);
            if (espaco == max_produtos) {
                printf("|Limite do estoque atingido!\n");
            } else {
                printf("|Quantos produtos quer adicionar?: ");
                scanf("%d", &prod);
                if (prod + espaco > max_produtos) {
                    printf("|Quantidade Inválida! Espaço insuficiente\n|", espaco);
                    //Não permitir o mesmo código para 2 produtos
                } else {
                    for(i = 0; i < prod; i++) {
                        printf("|-----------------------\n"
                        "|Produto %d:\n", i);
                        while (1) {
                                //Found facilita a checagem das condições
                            found = 0;
                            printf("|Digite o código do produto: ");
                            scanf("%d", &novoCod);
                            for (int j = 0; j < espaco; j++) {
                                if (cod[j] == novoCod) {
                                    found = 1;
                                    break;
                                }
                            }
                            if (found == 1) {
                                printf("|Código já existe. Digite um código diferente.\n");
                            } else {
                                cod[espaco] = novoCod;
                                break;
                            }
                        }
                        printf("|Digite o preço do produto: ");
                        scanf(" %lf", &valor[espaco]);
                        //Não permitir valor negativo ou 0
                        while(valor[espaco] <= 0) {
                                    printf("|Preço não pode ser negativo ou nulo\n");
                                    printf("|\n|Digite o preço do produto: ");
                                    scanf(" %lf", &valor[espaco]);
                                }
                        printf("|Digite a quantidade do produto: ");
                        scanf(" %d", &qtd[espaco]);
                        //Não permitir valor negativo ou 0
                        while(qtd[espaco] <= 0) {
                            printf("|Estoque não pode ser negativo ou nulo\n");
                            printf("|\n|Digite a quantidade do produto: ");
                            scanf(" %d", &qtd[espaco]);
                        }
                        espaco++;
                    }
                }
            }
            //Deixar a tela mais organizada
            printf("|\n|--------------------------------------------\n");
            //Função para ver os dados do produto
        } else if(opc == 2) {
            found = 0;
            printf("|--------------------------------------------\n"
            "|Digite o código do produto: ");
            scanf("%d", &codProd);

            for (i = 0; i < espaco; i++) {
                if (codProd == cod[i]) {
                    found = 1;
                    printf("|Preço: R$%.2lf\n|Quantidade: %d\n", valor[i], qtd[i]);
                }
            }
            if (found != 1) {
                printf("|Produto desconhecido/indisponível\n");
            }
            printf("|\n|--------------------------------------------\n");
            //Função para venda do produto
        } else if(opc == 3) {
            found = 0;
            printf("|--------------------------------------------\n"
            "|Informe o código do produto: ");
            scanf("%d", &codProd);

            for (i = 0; i < max_produtos; i++) {
                if (codProd == cod[i]) {
                    found = 1;
                    if (qtd[i] == 0)
                    {
                        printf("|Estoque Indisponível!\n");
                    } else {
                        printf("|Informe a quantidade: ");
                        scanf("%d", &quantVend);

                        if (quantVend > qtd[i]) {
                            printf("|Quantidade Indisponível! (%d)\n", qtd[i]);
                        } else {
                            qtd[i] -= quantVend;
                            printf("|Valor: R$%.2lf\n", quantVend*valor[i]);
                            break;
                        }
                    }
                }
            }
            if (found != 1) {
                printf("|Produto desconhecido/indisponível\n");
            }
            printf("|\n|--------------------------------------------\n");
            //Função de visualizar o estoque
        } else if(opc == 4) {
            printf("|--------------------------------------------\n");
            if (espaco == 0) {
                printf("|Estoque Vazio!\n");
            } else {
                for (i = 0; i < espaco; i++) {
                    printf("|-----------------------\n"
                    "|Produto %d:\n", i);
                    printf("|Código: %d\n|Valor: R$%.2lf\n|Quantidade: %d\n", cod[i], valor[i], qtd[i]);
                    printf("|\n");
                }
            }
            printf("|\n|--------------------------------------------\n");
            //Função extra de apagar um código
        } else if (opc == 5) {
            printf("|--------------------------------------------\n");
            found = 0;
            printf("|Informe o código do produto: ");
            scanf(" %d", &codProd);

            for (i = 0; i < espaco; i++) {
                if (cod[i] == codProd) {
                    found = 1;
                    temp = espaco;

                    for (j = i; j < temp - 1; j++) {
                        cod[j] = cod[j + 1];
                        qtd[j] = qtd[j + 1];
                        valor[j] = valor[j + 1];
                    }
                    espaco--;
                    cod[espaco] = 0;
                    qtd[espaco] = 0;
                    valor[espaco] = 0;
                    printf("|Produto apagado com sucesso!\n");
                    break;
                }
            }
            if (found != 1) {
                printf("|Produto desconhecido/indisponível\n");
            }
            printf("|\n|--------------------------------------------\n");
        }
        printf("|\n|Digite sua escolha: ");
    }

    return 0;
}