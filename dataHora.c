#include "funcs.h"

/**
 * Funcao que retorna os dias de cada mes
 * @return array com os dias de cada mes
 */
int* DiasMes() {
    static int DIAS_MES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return DIAS_MES;
}

/**
 * Funcao que verifica se uma data e hora sao validas
 * @param data data a verificar
 * @param hora hora a verificar
 * @return 1 se for valida, 0 se nao for
 */
int dataValida(Data data, Hora hora) {
    if (data.dia < 1 || data.dia > 31 || data.mes < 1 || data.mes > 12 ||
        data.ano < 1 || hora.hora < 0 || hora.hora > 23 || hora.minuto < 0 ||
        hora.minuto > 59) {
        return 0;
    }

    if (data.dia > DiasMes()[data.mes - 1]) {
        return 0;
    }
    return 1;
}

/**
 * Funcao que verifica se uma data e hora sao recentes comparando com outra
 * @param dataAntinga data antiga
 * @param horaAntiga hora antiga
 * @param dataNova data nova
 * @param horaNova hora nova
 * @return 1 se for recente, 0 se nao for
 */
int dataEhRecente(Data dataAntinga, Hora horaAntiga, Data dataNova,
                  Hora horaNova) {
    if (dataNova.ano < dataAntinga.ano) {
        return 0;
    }
    if (dataNova.ano == dataAntinga.ano) {
        if (dataNova.mes < dataAntinga.mes) {
            return 0;
        }
        if (dataNova.mes == dataAntinga.mes) {
            if (dataNova.dia < dataAntinga.dia) {
                return 0;
            }
            if (dataNova.dia == dataAntinga.dia) {
                if (horaNova.hora < horaAntiga.hora) {
                    return 0;
                }
                if (horaNova.hora == horaAntiga.hora) {
                    if (horaNova.minuto < horaAntiga.minuto) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

/**
 * Funcao que converte uma data e hora em minutos
 * @param data data a converter
 * @param hora hora a converter
 * @return minutos
 */
int converterMinutos(Data data, Hora hora) {
    int minutos;
    int horas;
    int dias;
    int mes;
    int anos;
    int* dias_mes = DiasMes();

    anos = data.ano;
    mes = data.mes;
    dias = data.dia;
    horas = hora.hora;
    minutos = hora.minuto;

    dias += (anos - 1) * 365;

    for (int i = 1; i < mes; i++) {
        dias += dias_mes[i - 1];
    }

    minutos += (dias * 24 * 60) + (horas * 60);
    return minutos;
}

/**
 * Funcao que calcula a diferenca entre duas datas e horas em minutos
 * @param data1 data 1
 * @param hora1 hora 1
 * @param data2 data 2
 * @param hora2 hora 2
 * @return diferenca em minutos
 */
int diferencaDataHora(Data data1, Hora hora1, Data data2, Hora hora2) {
    return abs(converterMinutos(data2, hora2) - converterMinutos(data1, hora1));
}

/**
 * Funcao que verifica se duas datas sao iguais
 * @param data1 data 1
 * @param data2 data 2
 * @return 1 se forem iguais, 0 se nao forem
 */
int datasIguas(Data data1, Data data2) {
    if (data1.ano == data2.ano && data1.mes == data2.mes &&
        data1.dia == data2.dia)
        return 1;
    return 0;
}