#include "funcs.h"

/**
 * Funcao que fatura um carro
 * @param dataEntrada data de entrada
 * @param horaEntrada hora de entrada
 * @param dataSaida data de saida
 * @param horaSaida hora de saida
 * @param valor15Min valor a pagar por 15 minutos
 * @param valor30Apos1Hora valor a pagar apos 1 hora
 * @param valorMaximoDia valor maximo a pagar por dia
 * @return valor a pagar
 */
float faturar(Data dataEntrada, Hora horaEntrada, Data dataSaida,
              Hora horaSaida, float valor15Min, float valor30Apos1Hora,
              float valorMaximoDia) {
    int minutos;
    int dias;
    float aux = 0;
    float valorPago = 0;

    minutos = diferencaDataHora(dataEntrada, horaEntrada, dataSaida, horaSaida);
    dias = minutos / 1440;
    minutos = minutos % 1440;

    if (minutos >= 60) {
        aux += 4 * valor15Min;
        minutos -= 60;

        if (minutos > 0) {
            aux += (minutos / 15) * valor30Apos1Hora;
            minutos = minutos % 15;

            if (minutos > 0) {
                aux += valor30Apos1Hora;
            }
        }

    } else {
        aux += (minutos / 15) * valor15Min;
        minutos = minutos % 15;

        if (minutos > 0) {
            aux += valor15Min;
        }
    }

    valorPago = (dias * valorMaximoDia) + MIN(valorMaximoDia, aux);

    return valorPago;
};

/**
 * Funcao que trata os erros de faturar sem data
 * @param parques lista de parques
 * @param nomeParque nome do parque
 * @return 1 se não houver erros, 0 se houver
 */
int tratarErrosFaturarSemData(NodeParque *parques, char *nomeParque) {
    NodeParque *aux = parques;
    int flag = 0;

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, nomeParque) == 0) {
            flag = 1;
            break;
        }
        aux = aux->next;
    }

    if (flag == 0) {
        printf("%s: no such parking.\n", nomeParque);
        return 0;
    }

    return 1;
};

/**
 * Funcao que trata os erros de faturar com data
 * @param parques lista de parques
 * @param nomeParque nome do parque
 * @param data data a faturar
 * @param ultimaData ultima data do sistema
 * @param ultimaHora ultima hora do sistema
 * @return 1 se não houver erros, 0 se houver
 */
int tratarErrosFaturarComData(NodeParque *parques, char *nomeParque, Data data,
                              Data ultimaData, Hora ultimaHora) {
    NodeParque *aux = parques;

    Hora horaAux = ultimaHora;  // hora que está sempre certa, só para usar a
                                // função dataValida

    int flag = 0;  // flag que avisa se o parque existe

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, nomeParque) == 0) {
            flag = 1;  // o parque existe
            break;
        }
        aux = aux->next;
    }

    if (flag == 0) {
        printf("%s: no such parking.\n", nomeParque);
        return 0;
    }

    if (dataValida(data, horaAux) == 0 ||
        dataEhRecente(data, horaAux, ultimaData, ultimaHora) == 0) {
        printf("invalid date.\n");

        return 0;
    }
    return 1;
};

/**
 * Funcao que fatura um parque
 * @param parque parque a faturar
 * @param nomeParque nome do parque a faturar
 */
void faturarParque(NodeParque *parque, char *nomeParque) {
    NodeParque *aux = parque;
    float valorTotalDia;
    Data dataAux;
    NodeTicket *auxTickets;

    auxTickets = aux->parque.tickets;
    if (auxTickets == NULL) {
        return;
    }

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, nomeParque) == 0) {
            auxTickets = aux->parque.tickets;
            dataAux = auxTickets->ticket.dataSaida;
            valorTotalDia = 0;

            while (auxTickets != NULL) {
                if (datasIguas(dataAux, auxTickets->ticket.dataSaida)) {
                    valorTotalDia += auxTickets->ticket.valorPago;
                } else {
                    printf("%02d-%02d-%04d %.02f\n", dataAux.dia, dataAux.mes,
                           dataAux.ano, valorTotalDia);
                    dataAux = auxTickets->ticket.dataSaida;
                    valorTotalDia = auxTickets->ticket.valorPago;
                }
                auxTickets = auxTickets->next;
            }
            printf("%02d-%02d-%04d %.02f\n", dataAux.dia, dataAux.mes,
                   dataAux.ano, valorTotalDia);
            break;
        }
        aux = aux->next;
    }
}

/**
 * Funcao que fatura um parque numa data especifica
 * @param parque parque a faturar
 * @param nomeParque nome do parque a faturar
 * @param data data a faturar
 */
void faturarParqueDataEspecifica(NodeParque *parque, char *nomeParque,
                                 Data data) {
    NodeParque *aux = parque;
    NodeTicket *auxTickets;

    while (aux != NULL) {
        if (strcmp(aux->parque.nome, nomeParque) == 0) {
            auxTickets = aux->parque.tickets;

            while (auxTickets != NULL) {
                if (datasIguas(data, auxTickets->ticket.dataSaida) == 1) {
                    printf("%s %02d:%02d %.02f\n", auxTickets->ticket.Matricula,
                           auxTickets->ticket.horaSaida.hora,
                           auxTickets->ticket.horaSaida.minuto,
                           auxTickets->ticket.valorPago);
                }
                auxTickets = auxTickets->next;
            }
            break;
        }
        aux = aux->next;
    }
}