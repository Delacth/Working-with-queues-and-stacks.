


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "pizzaria.h"


//* ESTRUTURA PIZZA 
//* ESTRUTURA LISTA PIZZA
typedef struct pizza_teste{
    int codigo;
    char nome[50];
    char morada[50];
    char telefone[20];
    int preco;
    struct pizza_teste *prox;
} pizza;

//* ESTRUTURA FILA PIZZA DELIVERY
typedef struct fila_pedido{
    pizza *ini;
    pizza *fim;
} pedido_Fila;

//* ESTRUTURA LISTA PARA PIZZAS NORMAIS
typedef struct pizza_teste_normal{
    int codigo;
    int quantidade;
    int preco;
    char nome[50];

    struct pizza_teste_normal *prox;
}pizza_teste_Normal;


//* ESTRUTURA LISTA PEDIDO NORMAL

typedef struct pedidos_normal {
    int codigo;
    int quantidade;
    char nome[50];
    int preco;

    struct pedidos_normal *prox;
} pedidos_Normal;

//*  ESTRUTURA FILA PEDIDO NORMAL
typedef struct fila_pedido_normal{
    pedidos_Normal *ini;
    pedidos_Normal *fim;
} fila_pedido_Normal;


//* ESTRUTURA PEDIDO DELIVERY
typedef struct pedido_delivery  {
    int codigo;
    char telefone[20];
    int quantidade;
    char morada[50];
    char nome[50];
    int preco;
    struct pedido_delivery *prox;
} pedido_Delivery;

//* ESTRUTURA FILA PEDIDO DELIVERY
typedef struct pedido{
    pedido_Delivery *ini;
    pedido_Delivery *fim;
} pedidos;

//* ESTRUTURA PILHA PEDIDO DELIVERY
typedef struct registro_de_entregas {
    pizza *topo;
}registro_de_Entregas;


//* PEDIDO NORMAL



//* FUNÇÃO PARA ADICIONAR UM PEDIDD A LISTA PIZZA_TESTE_NORMAR
pizza_teste_Normal* adicionar_pedido_pizza_teste_normal(pizza_teste_Normal *lista, int codigo, int quantidade, char *nome, int preco) {
    pizza_teste_Normal *novo_pedido = (pizza_teste_Normal*)malloc(sizeof(pizza_teste_Normal));
    if (novo_pedido != NULL) {
        novo_pedido->codigo = codigo;
        novo_pedido->preco = preco;
        novo_pedido->quantidade = quantidade;
        strcpy(novo_pedido->nome, nome);
        novo_pedido->prox = lista;
        
        lista = novo_pedido;
    } else {
        printf("Erro ao alocar memória para o novo pedido.\n");
    }
    return lista;
}


//* FUNÇÃO PARA VERIFICAR SE HÁ PEDIDOS NA LISTA PIZZA TESTE COM O MESMO NOME
int verificar_pedido_pizza_teste_normal(pizza_teste_Normal *lista, char *nome) {
    pizza_teste_Normal *atual = lista;
    while (atual != NULL) {
        if (strcasecmp(atual->nome, nome) == 0) {
            return 1; 
        }
        atual = atual->prox;
    }
    return 0; 
}

//* FUNÇÃO PARA INICIALIZAR A FILA PARA PEDIDOS NORMAIS
fila_pedido_Normal* abrir_pedidos(fila_pedido_Normal *fila) {
    if (fila != NULL) {
        fila->ini = NULL;
        fila->fim = NULL;
    } else {
        printf("Erro: nÃ£o foi possí­vel abrir a fila de pedidos.\n");
    }
    return fila;
}

//* VERIFICAR SE FILA PEDIDOS NORMAIS ESTÁ VAZIA
int esta_vazia(fila_pedido_Normal *fila) {
    return (fila->ini == NULL);
}

//* FUNÇÃO PARA ADICIONAR UMA PIZZA NA NOSSA FILA 
fila_pedido_Normal* fazer_pedidos(fila_pedido_Normal *fila, int codigo, int quantidade, char *nome, int preco) {
    pedidos_Normal *novo_pedido = (pedidos_Normal*) malloc(sizeof(pedidos_Normal));

    if (!novo_pedido) {
        printf("Erro ao alocar memÃ³ria para o novo pedido.\n");
        return NULL;
    }

    novo_pedido->preco = preco;
    novo_pedido->codigo = codigo;
    novo_pedido->quantidade = quantidade;
    strcpy(novo_pedido->nome, nome);
    novo_pedido->prox = NULL;

    if (esta_vazia(fila)) {
        fila->ini = novo_pedido;
        fila->fim = novo_pedido;
    } else {
        fila->fim->prox = novo_pedido;
        fila->fim = novo_pedido;
    }

    printf("Pedido adicionado.\n");
    return fila;
}

//* VERIFICAR AS PIZZAS NA NOSSA FILA
void alistar_pedido_Normal(fila_pedido_Normal *fila) {
    if (esta_vazia(fila)) {
        printf("A lista de pedidos estÃ¡ vazia.\n");
    } else {
        pedidos_Normal *auxiliar = fila->ini;
        while (auxiliar != NULL) {
            printf("CÃ³digo: %d, Quantidade: %d, Nome: %s\n", auxiliar->codigo, auxiliar->quantidade, auxiliar->nome);
            auxiliar = auxiliar->prox;
        }
    }
}

//* FUNÇÃO PARA ENTREGAR A PIZZA AO CLIENTE
void entregar_pedidos(fila_pedido_Normal *fila) {
    if (esta_vazia(fila)) {
        printf("A lista de pedidos está vazia.\n");
        return;
    }
    pedidos_Normal *auxiliar = fila->ini;
    fila->ini = fila->ini->prox;
    free(auxiliar);

    if (fila->ini == NULL) {
        fila->fim = NULL;
    }
}

//*  REMOÇÃO DE ESPAÇOS NOS NOMES E MORADAS DIGITADOS PELO USER
void remover_espacos_extras(char *str) {
    int i, j;
    for (i = 0; str[i] != '\0'; ++i) {
        while ((str[i] == ' ' && str[i + 1] == ' ') || (str[i] == '\t' && str[i + 1] == '\t')) {
            for (j = i; str[j] != '\0'; ++j) {
                str[j] = str[j + 1];
            }
            str[j] = '\0';
        }
    }
}

//* VERIFICAR O NÚMERO DE TELEFONE
int verificar_Numero(char *numero){
    //* COMPRIMENTO DO NÚMERO
    if (strlen(numero) != 10){
        printf("Número inválido!");
        return 0;      
    }

    //* VERIFICAR SE OS DÍGITOS SÃO DE 0-9
    for (int count = 0; count < 9; count++) {
        if (!isdigit(numero[count]))
            return 0;
    }
    
    //* VERIFICAR SE O PRIMEIRO DÍGITO É 9
        if (numero[0] != '9'){
          return 0;      
        }

        //* VERIFICAR SE O NÚMERO É VÁLIDO 
        if(numero[1] == 6 || numero[1] == 7 || numero[1] ==8 ){
            return 0;
        }
        return 1;
        
}

//* FUNÇÃO PARA MOSTRAR O PREÇO 
int check_pizza(int opcao, int quantidade){
    //* OPÇÕES 
    char pizzas_Info[][20] = {"4 Queijos", "Continental", "Francesa", "Americana", "Mista", "Portuguesa"};
    int preco_pizza = 0;
    if (opcao == 1)
    {
        if(quantidade == 1){
        printf("\n %i Pizza de %s ficou no valor de %i KZ ", quantidade, pizzas_Info[opcao-1], 5000*quantidade);
        preco_pizza = 5000*quantidade;
        }else{
            printf("\n%i Pizzas de %s ficou no valor de %i KZ",quantidade, pizzas_Info[opcao-1], 5000*quantidade);
            preco_pizza = 5000*quantidade;
        }
    }else if(opcao == 2){
        if(opcao == 1){
        printf("\n%i Pizza de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 5000*quantidade);
        preco_pizza = 5000*quantidade;
        }else{
            printf("\n%i Pizzas de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 5000*quantidade);
            preco_pizza = 5000*quantidade;
        }
    } else if(opcao == 3){
        if(quantidade == 1){
        printf("\n%i Pizza de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 7500*quantidade);
        preco_pizza = 7500*quantidade;
        }else{
            printf("\n%i Pizzas de %s ficou no valor de %i KZ ", quantidade, pizzas_Info[opcao-1], 7500*quantidade);
            preco_pizza = 7500*quantidade;
        }
    }else if(opcao == 4){
        if(quantidade == 1){
        printf("\n%i Pizza de %s ficou no valor de %i KZ ", quantidade, pizzas_Info[opcao-1], 6000*quantidade);
        preco_pizza = 6000*quantidade;
        }else{
            printf("\n%i Pizzas de %s ficou no valor de %i KZ ", quantidade, pizzas_Info[opcao-1], 6000*quantidade);
            preco_pizza = 6000*quantidade;
        }
    }else if(opcao == 5){
        if(quantidade == 1){
        printf("\n%i Pizza de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 5500*quantidade);
            preco_pizza = 5500*quantidade;
        }else{
            printf("\n%i Pizzas de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 5500*quantidade);
            preco_pizza = 5500*quantidade;
        }
    }else if(opcao == 6){
         if(quantidade == 1){
        printf("\n%i Pizza de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 7000*quantidade);
        preco_pizza = 7000*quantidade;
        }else{
            printf("\n%i Pizzas de %s ficou no valor de %i KZ", quantidade, pizzas_Info[opcao-1], 7000*quantidade);
            preco_pizza = 7000*quantidade;
        }
    }

    return preco_pizza;
}






//* DELIVERY */

//* INICIALIZAR A FILA DELIVERY
 pedidos* abrir_pedidos_delivery(pedidos *fila) {
    if (fila != NULL) {
        fila->ini = NULL;
        fila->fim = NULL;
    } else {
        printf("Erro: não foi possível abrir a fila de pedidos delivery.\n");
    }
    return fila;
}

        //1
        //* VERIFICAR SE A FILA DELIVERY ESTÁ VAZIA
      int esta_vazia_delivery(pedidos *fila) {
            return (fila->ini == NULL);
        }

//* FUNÇÃO PARA ADICONAR UM PEDIDO A NOSSA FILA DELIVERY
pedidos* fazer_pedidos_delivery(pedidos *fila, int codigo, char* telefone, int quantidade, char *nome, char *morada, int preco) {
    pedido_Delivery *novo_pedido = (pedido_Delivery*) malloc(sizeof(pedido_Delivery));

    if (!novo_pedido) {
        printf("Erro ao alocar memória para o novo pedido.\n");
        return NULL;
    }

    novo_pedido->codigo = codigo;
    novo_pedido->preco = preco;
    strcpy(novo_pedido->telefone, telefone);
    novo_pedido->quantidade = quantidade;
    strcpy(novo_pedido->nome, nome);
    strcpy(novo_pedido->morada, morada);
    novo_pedido->prox = NULL;

    if (esta_vazia_delivery(fila)) {
        fila->ini = novo_pedido;
        fila->fim = novo_pedido;
    } else {
        fila->fim->prox = novo_pedido;
        fila->fim = novo_pedido;
    }

    printf("Pedido de delivery adicionado.\n");
    return fila;
}

//* FUNÇÃO PARA MOSTRAR OS PEDIDOS NA NOSSA FILA DELIVERY
void alistar_pedidos_delivery( pedidos *fila) {
    if (esta_vazia_delivery(fila)) {
        printf("A lista de pedidos delivery está vazia.\n");
    } else {
       pedido_Delivery *auxiliar = fila->ini;
        while (auxiliar != NULL) {
            printf("Código: %d, Telefone: %s, Quantidade: %d, Nome: %s, Morada: %s\n", auxiliar->codigo, auxiliar->telefone, auxiliar->quantidade, auxiliar->nome, auxiliar->morada);
            auxiliar = auxiliar->prox;
        }
    }
}

 //****************************************************Outra função pra iniciar ou criar a pilha*************************************/
registro_de_Entregas* preparar_caixas() {
    registro_de_Entregas *nova_caixa = (registro_de_Entregas*) malloc(sizeof(registro_de_Entregas));
    if (nova_caixa != NULL) {
        nova_caixa->topo = NULL;
    } else {
        printf("FALHA NA ALOCAÇÃO");
    }
    return nova_caixa;
}

//* FUNÇÃO PARA INICIALIZAR O PALETE_MOTO
pizza* preparar_pizzas() {
    return NULL;
}


//* FUNÇÃO PARA INSERIR O TIPO DE PIZZA NA LISTA
pizza* organizar_pizzas(pizza *lista, pedidos *fila) {
    pizza *nova_pizza = (pizza*) malloc(sizeof(pizza));
    if (nova_pizza != NULL) {
        nova_pizza->codigo = fila->ini->codigo;
        strcpy(nova_pizza->nome, fila->ini->nome);
        strcpy(nova_pizza->telefone, fila->ini->telefone);
        nova_pizza->prox = lista;
    } else {
        printf("ERRO DE ALOCAÇÃO");
    }
    return nova_pizza;
}

  //****************************************************Outra função para arrumar as pizzas nas caixas e colocar na pilha *************************************/
registro_de_Entregas* preparar_entrega(registro_de_Entregas *palete_moto, pizza* pizzas) {
    pizza *entrega = (pizza*) malloc(sizeof(pizza));
    if (entrega != NULL) {
        entrega->preco = pizzas->preco;
        entrega->codigo = pizzas->codigo;
        strcpy(entrega->nome, pizzas->nome);
        strcpy(entrega->telefone,pizzas->telefone);
        entrega->prox = palete_moto->topo;
        palete_moto->topo = entrega;
    } else {
        printf("Erro de Alocação");
    }
    return palete_moto;
}


//* MENU 
void mostrar_menu_pizzas() {
    printf("------------------------------------------- MENU -------------------------------------------\n\n");
    printf(" \n [1] Pizza 4 Queijos    \n Ingredientes: Tomates em Cubo, Mozzarela com Picante e Cebola \n Preço: 5000 kz \n");
    printf(" \n [2] Pizza Continental  \n Ingredientes: Atum, Nata, Queijo, Chourinço e Cebola \n Preço: 5000 kz \n");
    printf(" \n [3] Pizza Francesa     \n Ingredientes: Tomate, Queijo, Catupiry, Mozzarela, Linguiça \n Preço: 7500 Kz \n");
    printf(" \n [4] Pizza Americana    \n Ingredientes: Pasta de Tomate, Mussarela, Jamón, Peperoni \n Preço: 6000 Kz \n");
    printf(" \n [5] Pizza Mista        \n Ingredientes: Pasta de Tomate, Mussarela, Jamón, Peperoni, Chouriço e Ervas Finas \n Preço: 5500 Kz  \n"); 
    printf(" \n [6] Pizza Portuguesa   \n Ingredientes: Frango, Tomates, Mussarela, Catupiry, Azeitona Preta, Cebola e Orégano \n Preço: 7000 Kz \n");
    printf(" \n [0] Sair do Menu \n\n");
}

//* LIMPEZA DO BUFFER DEPOIS DE UM SCANF
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//* FUNÇÃO PARA VERIFICAR SE A ENTRADA NÃO TEM CARACTERES
int lerNumeroInteiro() {
    char entrada[100];
    int numero;
    char *pointer;

    while (1) {
        
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro ao ler entrada.\n");
            
        }

        
        //* CONVERTER A ENTRADA PARA UM NÚMERO INTEIRO
        numero = (int) strtol(entrada, &pointer, 10);

        
        //* VERIFICAR SE NÃO HOUVE ERRO NA CONVERSÃO
        if (pointer == entrada || *pointer != '\n') {
            printf("Entrada inválida. Por favor, digite apenas números inteiros.\n");
        } else {
            
            //* ENTRADA VÁLIDA
            break;
        }
    }
    return numero;
}


//* TELA INCIAL DO PROGRAMA
void tela_inicial() {
    int opcao = 0, opcao_Pizza =0, quantidade_Pizza=0, opcao_Pedido = 0, preco = 0;
    char nome_cliente_normal[50], nome_cliente_deli[50], morada[50], numero_Telefone[20];
     char nome_cliente[50], telefone_check[50];

    fila_pedido_Normal *fila_pedido = (fila_pedido_Normal*) malloc(sizeof(fila_pedido_Normal));
    pedidos *fila_delivery = (pedidos*) malloc(sizeof(pedidos));
    registro_de_Entregas *palete_moto = (registro_de_Entregas*) malloc(sizeof(registro_de_Entregas));

    fila_pedido = abrir_pedidos(fila_pedido);
    fila_delivery = abrir_pedidos_delivery(fila_delivery);
    palete_moto = preparar_caixas();
    pizza_teste_Normal *lista_pizza_teste_normal = NULL;
      

    do {
        //* MENU PRINCIPAL

        system("cls");
        printf("Seja bem-vindo à Pizzaria Clement!\n");
        printf("1. Fazer um pedido\n");
        printf("2. Receber uma Pizza Normal \n");
        printf("3. Delivery\n");
        printf("4. Sair do programa\n");
        
        //* MENU PRINCIPAL 

        do{
            printf("Escolha uma opção: ");
            opcao = lerNumeroInteiro();  
        }while(opcao<1 || opcao>5);
        

        
        

        switch (opcao) {
            case 1:
                system("cls");

                //* MENU DE OPÇÕES
                mostrar_menu_pizzas();

                //* NÚMERO DA OPÇÃO
                do{
                printf("Número de opção da Pizza: ");
                opcao_Pizza = lerNumeroInteiro();
                }while(opcao_Pizza > 5 || opcao_Pizza < 0);
                              
                if (opcao_Pizza == 0) {
                    system("cls");
                    break;
                }

                //* QUANTIDADE PEDIDA PELO USER
                do
                {
                  printf("\n Quantidade de Pizza que deseja: ");
                  quantidade_Pizza = lerNumeroInteiro();
                } while (quantidade_Pizza <= 0);
                             
                if (quantidade_Pizza == 0) {
                    system("cls");
                    break;
                } 

                //* MOSTRAR O PEDIDO E RETORNAR O PREÇO    
                preco = check_pizza(opcao_Pizza, quantidade_Pizza);
                printf("\nPedido feito com sucesso!");
                                
                //* TIPO DE ENTREGA OU CANCELAMENTO DO PEDIDO                
                printf("\n\n---- Entrega do Pedido ----\n");
                printf("[1] Delivery\n");
                printf("[2] Pedido Normal\n");
                printf("[3] Cancelar o Pedido\n");
                do {
                    printf(": ");
                    opcao_Pedido = lerNumeroInteiro();
                } while (opcao_Pedido < 1 || opcao_Pedido > 3);
                
                

                if (opcao_Pedido == 1) {

                //* INSERIR O NOME DO USUÁRIO SEM ERROS     
                do {
                    printf("\nDigite o seu Nome: ");     
                    fgets(nome_cliente_deli, sizeof(nome_cliente_deli), stdin);                              
                    
                    //* VERIFICAR SE A ENTRADA CONTÉM APENAS CARACTERES DE TEXTO
                    int valido = 1;
                    for (int i = 0; nome_cliente_deli[i] != '\0'; i++) {
                       if (!isalpha(nome_cliente_deli[i]) && nome_cliente_deli[i] != ' ' && nome_cliente_deli[i] != '\n') {
                            valido = 0;
                            break;
                        }
                    }
                    if (valido == 1) {
                        break;
                    }
                } while (1);  
                 nome_cliente_deli[strcspn(nome_cliente_deli, "\n")] = '\0'; //* REMOVER QUEBRA DE LINHA
              
                
                //* INSERIR A MORADA DO USUÁRIO
                printf("\nDigite a sua Morada: ");     
                fgets(morada, sizeof(morada), stdin); 
                morada[strcspn(morada, "\n")] = '\0'; //* REMOVER QUEBRA DE LINHA               
                                   
                //* INSERIR O NÚMERO DE TELEFONE
                do {
                    printf("\nDigite o seu número de telefone: ");     
                    fgets(numero_Telefone, sizeof(numero_Telefone), stdin);                             
                     if(verificar_Numero(numero_Telefone)){
                        break;
                     }                           
                } while (1); 
                numero_Telefone[strcspn(numero_Telefone, "\n")] = '\0'; //* REMOVER QUEBRA DE LINHA    

                //* ENVIAR OS DADOS PARA A FILA DELIVERY
                fazer_pedidos_delivery(fila_delivery, opcao_Pizza, numero_Telefone, quantidade_Pizza, nome_cliente_deli, morada, preco);
                printf("\nAguarde....");
                sleep(2);

                } else if (opcao_Pedido == 2) {

                    //* INSERIR O NOME DO USUÁRIO SEM ERROS 
                    do {
                    printf("\nDigite o seu Nome: ");    
                    fgets(nome_cliente_normal, sizeof(nome_cliente_normal), stdin);                            
                    
                    //* VERIFICAR SE A ENTRADA CONTÉM APENAS CARACTERES DE TEXTO
                    int valido = 1;
                    for (int i = 0; nome_cliente_normal[i] != '\0'; i++) {
                        if (!isalpha(nome_cliente_normal[i]) && nome_cliente_normal != ' ' && nome_cliente_normal[i] != '\n') {
                            valido = 0;
                            break;
                        }
                    }
                    if (valido == 1) {
                        break;
                    }
                } while (1); 
                //* ENVIAR OS DADOS A FILA DE PEDIDOS        
                  fazer_pedidos(fila_pedido, opcao_Pizza, quantidade_Pizza, nome_cliente_normal, preco);
                  printf("Aguarde....");
                  sleep(2);

                }else if(opcao_Pedido == 3){
                    printf("\n Cancelando o Pedido ...");
                    sleep(2);
                    break;
                }

                break;
            case 2:
                
           
           if (fila_pedido->ini != NULL) {
   
                    
            char nome_cliente[50];
            int preco_pizza_normal = 0;
            
            //* INSERIR O NOME DO USUÁRIO SEM ERROS 
            do {
                printf("Digite seu nome: ");
                fgets(nome_cliente, sizeof(nome_cliente), stdin);
            
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';//* REMOVER QUEBRA DE LINHA
                int valido = 1;
                for (int i = 0; nome_cliente[i] != '\0'; i++) {
                    if (!isalpha(nome_cliente[i]) && nome_cliente != ' ' && nome_cliente[i] != ' ') {
                        valido = 0;
                        break;
                    }
                }

                if (valido == 1) {
                    break;
                }
             } while (1);
            

    
            //* REMOVER O CARACTERE DA NOVA LINHA DO NOME PEDIDO SE EXISTIR
            char *posicao_quebra_linha = strchr(fila_pedido->ini->nome, '\n');
            if (posicao_quebra_linha != NULL) {
                *posicao_quebra_linha = '\0';
            }
            preco_pizza_normal = fila_pedido->ini->preco;

            //* VERIFICAR SE O NOME DIGITADO É EQUIVALENTE AO DO PEDIDO 
             if (strcmpi(fila_pedido->ini->nome, nome_cliente) == 0) {
                            
                                //* SE O NOME DIGITADO É EQUIVALENTE, RETIRAR O PRIMEIRO PEDIDO DA FILA E COLOCAR NA LISTA PIZZA_TESTE_NORMAL
                                pedidos_Normal *pedido_normal = fila_pedido->ini;
                                fila_pedido->ini = fila_pedido->ini->prox;
                                pedido_normal->prox = NULL;

                                //* ADICIONAR OS VALORES DA FILA A LISTA PARA SER ENTREGUE
                                lista_pizza_teste_normal = adicionar_pedido_pizza_teste_normal(lista_pizza_teste_normal, pedido_normal->codigo, pedido_normal->quantidade, pedido_normal->nome, pedido_normal->preco);

                                printf("Pedido entregue ao Cliente %s no valor de %d .\n",nome_cliente, preco_pizza_normal);
                                free(pedido_normal);
                                free(lista_pizza_teste_normal);
            }else {
                                
                                //* SE O NOME NÃO CONDIZ COM O PRIMEIRO PEDIDO DA FILA, ENVIA O PEDIDIO PARA A LISTA PIZZA TESTE
                                lista_pizza_teste_normal = adicionar_pedido_pizza_teste_normal(lista_pizza_teste_normal, fila_pedido->ini->codigo, fila_pedido->ini->quantidade, fila_pedido->ini->nome, fila_pedido->ini->preco);

                                
                                //*VERIFICAR SE O NOME ESTÁ NA LISTA PIZZA TESTE
                                if (verificar_pedido_pizza_teste_normal(lista_pizza_teste_normal, nome_cliente)) {
                                    
                                    //* SE O NOME ESTIVER NA LISTA, RETIRAR E LIBERAR A MEMORIA 
                                    pizza_teste_Normal *atual = lista_pizza_teste_normal;
                                    pizza_teste_Normal *anterior = NULL;
                                    preco_pizza_normal = atual->preco;
                                    while (atual != NULL) {
                                        if (strcmp(atual->nome, nome_cliente) == 0) {
                                            pizza_teste_Normal *remover = atual;

                                            if (anterior == NULL) {
                                                lista_pizza_teste_normal = atual->prox;
                                                free(remover);
                                                atual = lista_pizza_teste_normal;
                                            } else {
                                                anterior->prox = atual->prox;
                                                free(remover);
                                                atual = anterior->prox;
                                            }
                                        } else {
                                            anterior = atual;
                                            atual = atual->prox;
                                        }
                                    }
                                    printf("Pedido entregue ao Cliente %s no valor de %d .\n",nome_cliente, preco_pizza_normal);
                                    free(lista_pizza_teste_normal);
                                } else {
                                    printf("Não há reserva pronta com esse nome.\n");
                                }
                            }
                        } else {
                            printf("A há pedidos .\n");
                        }
                sleep(2);
                break;
            case 3:
               
              
                //* INSERIR O NOME DO USUÁRIO SEM ERROS               
                do {
                        printf("Digite seu nome: ");
                        fgets(nome_cliente, sizeof(nome_cliente), stdin);                            
                            
                            //* VERIFICAR SE A ENTRADA CONTÉM APENAS CARACTERES DE TEXTO
                            int valido = 1;
                            for (int i = 0; nome_cliente[i] != '\0'; i++) {
                                if (!isalpha(nome_cliente[i]) && nome_cliente[i] != ' ' && nome_cliente[i] != '\n') {
                                    valido = 0;
                                    break;
                                }
                            }
                            if (valido == 1) {
                                break;
                            }
                    } while (1); 

                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';//* REMOVER A QUEBRA DE LINHA E ESPAÇOS EXTRAS
                
                //* INSERIR O NÚMERO DE TELEFONE
                do {
                    printf("\nDigite o seu número de telefone: ");     
                    fgets(telefone_check, sizeof(telefone_check), stdin);                             
                     if(verificar_Numero(telefone_check)){
                        break;
                     }                           
                } while (1); 
                telefone_check[strcspn(telefone_check, "\n")] = '\0'; //* REMOVER QUEBRA DE LINHA    
        
                
                   

         //* VERIFICAR SE A FILA DE PEDIDOS DELIVERY ESTÁ VAZIA
          
  
            if (!esta_vazia_delivery(fila_delivery)) {  

            
                
                //* RETIRAR O PRIMEIRO PEDIDO DA FILA DE PEDIDOS DELIVERY
                pedido_Delivery *pedido = fila_delivery->ini;
                fila_delivery->ini = fila_delivery->ini->prox;

                
                //* ENVIAR A PIZZA PARA A ESTRUTURA PIZZA 
                pizza *nova_pizza = (pizza*)malloc(sizeof(pizza));
                if (nova_pizza == NULL) {
                    printf("Erro ao alocar memória para a pizza.\n");
                    break;
                }

                nova_pizza->codigo = pedido->codigo;
                nova_pizza->preco = pedido->preco;
                strcpy(nova_pizza->nome, pedido->nome);
                strcpy(nova_pizza->telefone, pedido->telefone);
                nova_pizza->prox = NULL;

                
                //* EMPILHAR ESSA PIZZA PARA ENTREGA
                palete_moto = preparar_entrega(palete_moto, nova_pizza);

                                                      
                //* PROCURAR NA PILHA DE ENTREGA SE EXISTE UMA PIZZA PARA ESSE CLIENTE
                pizza *atual_pizza = palete_moto->topo;
                pizza *anterior_pizza = NULL;

                //* REMOVER ESPAÇOS EXTRAS NO NOME DIGITADOS
                remover_espacos_extras(nome_cliente);
                char verifi_n[50], verifi_t[20];
                int verifi_p = atual_pizza->preco;
                
                //* REMOVER ESPAÇOS EXTRAS NO NOME DA PILHA
                remover_espacos_extras(atual_pizza->nome);
                strcpy(verifi_n, atual_pizza->nome);
                strcpy(verifi_t, atual_pizza->telefone);
                int check_pedido = 0;
                

                //* PROCURAR SE O VALOR DIGITADO EXISTE NA FILA
                while (atual_pizza != NULL) {
                    
                   //* VERIFICAR SE OS VALORES DIGITADOS SÃO IGUAIS AOS DA FILA     
                    if (strcmpi(atual_pizza->nome, nome_cliente) == 0 && strcmpi(atual_pizza->telefone, telefone_check) == 0) {
                        check_pedido = 1;
                        break;
                    } else {
                        anterior_pizza = atual_pizza;
                        atual_pizza = atual_pizza->prox;
                    }                    

                    
                   
                }

                    //* SE EXISTIR O NOME É RETIRADO DA PILHA
                    //* SENÃO NÃO EXISTE UM PEDIDO COM ESSE NOME
                    if(check_pedido ){
                        //* REMOVER O ELEMENTO ENCONTRADO
                        pizza *remover_pizza = atual_pizza;
                        if (anterior_pizza == NULL) {
                            palete_moto->topo = atual_pizza->prox;
                        } else {
                            anterior_pizza->prox = atual_pizza->prox;
                        }
                        free(remover_pizza);    
                        printf("O Pedido Foi entregue com sucesso ao Cliente %s no valor de %d KZ", verifi_n, verifi_p);
                    }else{
                        printf("\nNão há nenhuma reserva com esse nome.\n");     
                    }      
                

            } else {
                //* SE A FILA DE DELIVERY ESTIVER VAZIA
                //* VAI SE PROCURAR NA PILHA 
                pizza *atual_pizza = palete_moto->topo;
                pizza *anterior_pizza = NULL;

                if(atual_pizza == NULL){
                    printf("Não há nenhuma reserva!.\n");        
                }else{

                
                //* REMOVER ESPAÇOS EXTRAS NO NOME DIGITADOS
                remover_espacos_extras(nome_cliente);
                char verifi_n[50], verifi_t[20];
                //* REMOVER ESPAÇOS EXTRAS NO NOME DA PILHA
                remover_espacos_extras(atual_pizza->nome);
                strcpy(verifi_n, atual_pizza->nome);
                strcpy(verifi_t, atual_pizza->telefone);
                int verifi_p = atual_pizza->preco;

               int check_pedido = 0;
               //* PROCURAR SE O VALOR DIGITADO EXISTE NA PILHA
                while (atual_pizza != NULL) {
                    //* VERIFICAR SE OS VALORES DIGITADOS SÃO IGUAIS AOS DA FILA
                    if (strcmpi(atual_pizza->nome, nome_cliente) == 0 && strcmpi(atual_pizza->telefone, telefone_check) == 0) {
                        check_pedido = 1;
                        break;
                    } else {
                        anterior_pizza = atual_pizza;
                        atual_pizza = atual_pizza->prox;
                    }
                }

                //* SE EXISTIR O NOME É RETIRADO DA PILHA
                //* SENÃO NÃO EXISTE UM PEDIDO COM ESSE NOME
                 if (check_pedido) {
                    
                    //* REMOVER O ELEMENTO ENCONTRADO
                    pizza *remover_pizza = atual_pizza;
                    if (anterior_pizza == NULL) {
                        palete_moto->topo = atual_pizza->prox;
                    } else {
                        anterior_pizza->prox = atual_pizza->prox;
                    }
                    free(remover_pizza);
                    printf("\nO Pedido Foi entregue com sucesso ao Cliente %s no valor de %d Kz \n", nome_cliente, verifi_p);
                } else {
                    printf("\nNão há nenhuma reserva para o Cliente %s.\n", nome_cliente);
                }       
              }
                
                                
                

            }
            sleep(3);    

        break;


            case 4:
                system("cls");        
                printf("\nObrigado por adquir nossos produtos !\n");
                printf("\nVolte Sempre!");
                break;
            
            default:

                printf("\nOpção inválida. Tente novamente.\n\n");
                sleep(1);
                break;
        }
    } while (opcao != 4);

    free(fila_pedido);
    free(fila_delivery);
    free(palete_moto);
}