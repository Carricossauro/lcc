/**
@file listas.h
Definição das listas ligadas usadas na heurística
*/

#ifndef PROJETO_LA_LISTAS_H
#define PROJETO_LA_LISTAS_H

/**
\brief Definição da lista ligada genérica
*/
typedef struct nodo {
    /** Apontador para um valor genérico*/
    void *valor;
    /** Apontador para o próximo elemento da lista*/
    struct nodo *proximo;
} /** Lista */ NODO, /** Apontador para um lista */ *LISTA;

/**
\brief Função que cria um lista ligada
@returns Apontador para a lista ligada
*/
LISTA criar_lista();

/**
\brief Função que insere um valor à cabeça
@param l Lista ligada
@param valor Valor a ser adicionado
@returns Apontador para a lista ligada
 */
LISTA insere_cabeca(LISTA l, void *valor);

/**
\brief Função que devolve a cabeça da lista
@param l Lista ligada
@returns Valor guardado na cabeça
*/
void *devolve_cabeca(LISTA l);

/**
\brief Função que devolve o próximo valor da lista
@param l Lista ligada
@returns Lista que começa no elemento seguinte da lista dada
 */
LISTA proximo(LISTA l);

/**
\brief Função que remove a cabeça da lista
@param L Lista ligada
@returns Cauda da lista ligada
 */
LISTA remove_cabeca(LISTA L);

/**
\brief Função que verifica se a lista está vazia
@param L Lista ligada
@returns 1 - Lista está vazia |n 0 - Lista não está vazia
 */
int lista_esta_vazia(LISTA L);

#endif //PROJETO_LA_LISTAS_H
