/**
 * @brief Ficheiro que contem as declarações das funções
 * @file funcs.h
 * @author Pedro Nunes ist1109368
 */

#include "structures.h"

#ifndef _FUNCS_H_
#define _FUNCS_H_

/**
 * @brief Macro que retorna o minimo entre dois valores
 * @param X valor 1
 * @param Y valor 2
 * @return o minimo entre X e Y
 */
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// funcoes no "carros.c"
int matriculaValida(char *matricula);
int dataValida(Data data, Hora hora);
int dataEhRecente(Data dataAntinga, Hora horaAntiga, Data dataNova,
                  Hora horaNova);
int tratarErrosAdicionarCarro(NodeParque *Parques, char *nomeParque,
                              char *matricula, Data dataEntrada,
                              Hora horaEntrada, Data ultimaData,
                              Hora ultimaHora);
Carro criarCarro(char *matricula, Data dataEntrada, Hora horaEntrada);
NodeCarro *criarNodeCarro(Carro carro);
unsigned long hash(char *str, int size);
CarroHashTable *criarCarroHashTable(int size);
void adicionarCarro(NodeParque **parques, char *nomeParque, Carro carro);
int tratarErrosRemoverCarro(NodeParque *Parques, char *nomeParque,
                            char *matricula, Data dataEntrada, Hora horaEntrada,
                            Data ultimaData, Hora ultimaHora);
void removerCarro(NodeParque **parques, char *nomeParque, char *matricula,
                  Data data, Hora hora);
int tratarErrosListarEntradasSaidas(NodeParque *parques, char *matricula);
void listarEntradasSaidas(NodeParque *parques, char *matricula, int numParques);

// funcoes no "dataHora.c"
int *DiasMes();
int dataValida(Data data, Hora hora);
int dataEhRecente(Data dataAntinga, Hora horaAntiga, Data dataNova,
                  Hora horaNova);
int converterMinutos(Data data, Hora hora);
int diferencaDataHora(Data data1, Hora hora1, Data data2, Hora hora2);
int datasIguas(Data data1, Data data2);

// funcoes no "faturacao.c"
float faturar(Data dataEntrada, Hora horaEntrada, Data dataSaida,
              Hora horaSaida, float valor15Min, float valor30Apos1Hora,
              float valorMaximoDia);
int tratarErrosFaturarSemData(NodeParque *parques, char *nomeParque);
int tratarErrosFaturarComData(NodeParque *parques, char *nomeParqueAux,
                              Data data, Data ultimaData, Hora ultimaHora);
void faturarParque(NodeParque *parque, char *nomeParque);
void faturarParqueDataEspecifica(NodeParque *parque, char *nomeParque,
                                 Data data);

// funcões no "parques.c"
void imprimeParques(NodeParque *parques);
void imprimeNomeParques(char **nomes, int numParques);
Parque criarParque(char *nome, int capacidade, float valor15Min,
                   float valor30Apos1Hora, float valorMaximoDia);
NodeParque *criarNodeParque(Parque parque);
void adicionarParque(NodeParque **parques, Parque parque);
int tratarErrosAdicionarParque(NodeParque *parques, Parque parqueAux,
                               int numParques);
void freeParque(Parque parque);
void freeListaParques(NodeParque *parques);
char **obterNomeParques(NodeParque *parques, int numParques);
void trocarStr(char **str1, char **str2);
void ordenarNomesParques(char **nomes, int numParques);
int tratarErrosRemoverParque(NodeParque *parques, char *nomeParqueAux);
void removerParque(NodeParque **parques, char *nomeParqueAux, int numParques);

// funcoes no "tickets.c"
Ticket criarTicket(char *Matricula, Data dataSaida, Hora horaSaida,
                   float valorPago);
NodeTicket *criarNodeTicket(Ticket ticket);
void adicionarTicket(NodeTicket **tickets, Ticket ticket);

#endif