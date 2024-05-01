 //* TAD: PIZZARIA

  //* ESTRUTURA PARA A PIZZA
  typedef struct pizza_teste pizza;
  typedef struct fila_pedido pedido_Fila;
 
 
 //* ESTRUTURA PARA A PIZZA E A FILA DE PIZZA
  typedef  struct pedidos_normal pedidos_Normal;
  typedef struct fila_pedido_normal fila_pedido_Normal;
 
 //* ESTRUTURA PARA A PIZZA DE DELIVERY
  typedef  struct pedido pedidos;
  typedef struct pedido_delivery  pedido_Delivery;
  typedef struct registro_de_entregas registro_de_Entregas;
 
 
 




 /*
 * FUNÇÃO PARA ABRIR OS PEDIDOS DAS PIZZAS
 */
 
   fila_pedido_Normal* abrir_pedidos(fila_pedido_Normal* fila);
 
 /*
 *FUNÇÃP PARA VERIFICAR SE A FILA ESTÃ VAZIA
 */
    int esta_vazia( fila_pedido_Normal* fila);
  /*

 * FUNÇÃO PARA FAZER OS PEDIDOS DAS PIZZAS
 */
    
    fila_pedido_Normal* fazer_pedidos(fila_pedido_Normal* fila, int codigo, int quantidade, char* nome, int preco);

   
 /*
 * FUNÇÃO PARA ALISTAR OS PEDIDOS DAS PIZZAS
 */
  void alistar_pedidos(fila_pedido_Normal* fila);
  
 /*
 * FUNÇÃO PARA ENTREGAR OS PEDIDOS DAS PIZZAS
 */
   void entregar_pedido_Normal(fila_pedido_Normal* fila);
   

  /*
   * FUNÇÃO PARA A INICIALIZAR OS PEDIDOS DELIVERY
 */
   pedidos* abrir_Pedidos();

  
  /*
  * FUNÇÃO PARA REGISTRAR O PEDIDO DELIVERY
 */
  pedidos* fazer_Pedidos(pedidos*fila,char*nome,int codigo,char* telefone,char*morada, int quantidade, int preco);

 //* VÊ   
 // int verificar_Pedidos(pedidos*fila);
  //void alistar_Pedidos(pedidos** fila);
 // int atender_Pedidos(pedidos*fila);
  
  /*
  * FUNÇÃO PARA INICIALIZAR A  "PALETE_MOTO"
 */
  pizza* preparar_pizzas();

  /*
  * FUNÇÃO PARA INSERIR O TIPO DE PIZZA NA LISTA
 */
  pizza*organizar_pizzas(pizza*lista,pedidos* fila);

  /*
  * FUNÇÃO PARA INSERIR O TIPO DE PIZZA NA LISTA
 */
  registro_de_Entregas* preparar_caixas();

  /*
  * FUNÇÃO PARA INSERIR VALORES DA LISTA PIZZA PARA A PILHA
 */
  registro_de_Entregas* preparar_entrega(registro_de_Entregas*palete_moto,pizza*pizzas);

/*
  * FUNÇÃO PARA REMOVER ESPAÇOS EXTRAS DE UMA STRING
*/  
void remover_espacos_extras(char *str);

/*
 * FUNÇÃO PARA VERIFICAR O NÚMERO DE TELEFONE
 */     
int verificar_Numero(char *numero);

/*
 * FUNÇÃO PARA MOSTTRAR A OPÇÃO E QUANTIDADE PEDIDA E RETORNARÁ UM PREÇO
 */
int check_pizza(int opcao, int quantidade);
 
 /*
 * FUNÇÃO PARA A TELA DO MENU
 */
 void tela_Inicial();
/*
 * LIMPEZA DE BUFFER DE MEMORIA
 */
 void limpar_buffer();
 
 /*
 * FUNÇÃO PARA MOSTRAR OS PEDIDOS NA NOSSA FILA DELIVERY
 */
 void alistar_pedidos_delivery( pedidos *fila);
 
/*
 * FUNÇÃO PARA VERIFICAR SE O VALOR DIGITADO É UM INTEIRO
 */ 
int lerNumeroInteiro();