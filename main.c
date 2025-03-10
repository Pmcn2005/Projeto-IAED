/**
 * @brief Ficheiro principal do projeto
 * @file main.c
 * @author Pedro Nunes ist1109368
 */

#include "main.h"

int main() {
    NodeParque *Parques = NULL;  ///< Lista de parques
    int numParques = 0;
    char *input;  ///< Input do utilizador
    char comando;
    char *nomeParqueAux;
    char *matriculaAux;
    int capacidadeAux;
    float valor15MinAux, valor30Apos1HoraAux, valorMaximoDiaAux;
    Parque parqueAux;
    Carro carroAux;
    Data dataAux, ultimaData = {1, 1, 1};
    Hora horaAux, ultimaHora = {1, 1};

    while (1) {
        input = (char *)malloc(BUFSIZ * sizeof(char));
        fgets(input, BUFSIZ, stdin);

        comando = input[0];

        switch (comando) {
            case 'q':
                free(input);
                freeListaParques(Parques);
                exit(0);

            case 'p':
                // caso o input seja "p\n" imprime todos os parques
                if (input[1] == '\n') {
                    imprimeParques(Parques);

                }

                // caso o nome do parque nao comece com aspas
                else if (input[2] != '"') {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));

                    sscanf(input, "%c %s %d %f %f %f", &comando, nomeParqueAux,
                           &capacidadeAux, &valor15MinAux, &valor30Apos1HoraAux,
                           &valorMaximoDiaAux);

                    parqueAux =
                        criarParque(nomeParqueAux, capacidadeAux, valor15MinAux,
                                    valor30Apos1HoraAux, valorMaximoDiaAux);

                    free(nomeParqueAux);

                    if (tratarErrosAdicionarParque(Parques, parqueAux,
                                                   numParques) == 1) {
                        adicionarParque(&Parques, parqueAux);
                        numParques++;
                    } else {
                        freeParque(parqueAux);
                    }

                }

                // caso o nome do parque comece com aspas
                else {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));

                    sscanf(input, "%c \"%[^\"]\" %d %f %f %f", &comando,
                           nomeParqueAux, &capacidadeAux, &valor15MinAux,
                           &valor30Apos1HoraAux, &valorMaximoDiaAux);

                    parqueAux =
                        criarParque(nomeParqueAux, capacidadeAux, valor15MinAux,
                                    valor30Apos1HoraAux, valorMaximoDiaAux);

                    free(nomeParqueAux);

                    if (tratarErrosAdicionarParque(Parques, parqueAux,
                                                   numParques) == 1) {
                        adicionarParque(&Parques, parqueAux);
                        numParques++;

                    } else {
                        freeParque(parqueAux);
                    }
                }

                break;

            case 'e':

                if (input[2] != '"') {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));
                    matriculaAux = (char *)malloc(10 * sizeof(char));

                    sscanf(input, "%c %s %s %d-%d-%d %d:%d", &comando,
                           nomeParqueAux, matriculaAux, &dataAux.dia,
                           &dataAux.mes, &dataAux.ano, &horaAux.hora,
                           &horaAux.minuto);

                    if (tratarErrosAdicionarCarro(
                            Parques, nomeParqueAux, matriculaAux, dataAux,
                            horaAux, ultimaData, ultimaHora) == 1) {
                        carroAux = criarCarro(matriculaAux, dataAux, horaAux);
                        adicionarCarro(&Parques, nomeParqueAux, carroAux);
                        ultimaData = dataAux;
                        ultimaHora = horaAux;
                    }
                    free(nomeParqueAux);
                    free(matriculaAux);

                } else {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));
                    matriculaAux = (char *)malloc(10 * sizeof(char));

                    sscanf(input, "%c \"%[^\"]\" %s %d-%d-%d %d:%d", &comando,
                           nomeParqueAux, matriculaAux, &dataAux.dia,
                           &dataAux.mes, &dataAux.ano, &horaAux.hora,
                           &horaAux.minuto);

                    if (tratarErrosAdicionarCarro(
                            Parques, nomeParqueAux, matriculaAux, dataAux,
                            horaAux, ultimaData, ultimaHora) == 1) {
                        carroAux = criarCarro(matriculaAux, dataAux, horaAux);
                        adicionarCarro(&Parques, nomeParqueAux, carroAux);
                        ultimaData = dataAux;
                        ultimaHora = horaAux;
                    }
                    free(nomeParqueAux);
                    free(matriculaAux);
                }

                break;
            case 's':
                if (input[2] != '"') {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));
                    matriculaAux = (char *)malloc(10 * sizeof(char));

                    sscanf(input, "%c %s %s %d-%d-%d %d:%d", &comando,
                           nomeParqueAux, matriculaAux, &dataAux.dia,
                           &dataAux.mes, &dataAux.ano, &horaAux.hora,
                           &horaAux.minuto);

                    if (tratarErrosRemoverCarro(Parques, nomeParqueAux,
                                                matriculaAux, dataAux, horaAux,
                                                ultimaData, ultimaHora) == 1) {
                        removerCarro(&Parques, nomeParqueAux, matriculaAux,
                                     dataAux, horaAux);
                        ultimaData = dataAux;
                        ultimaHora = horaAux;
                    }
                    free(nomeParqueAux);
                    free(matriculaAux);
                }

                else {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));
                    matriculaAux = (char *)malloc(10 * sizeof(char));

                    sscanf(input, "%c \"%[^\"]\" %s %d-%d-%d %d:%d", &comando,
                           nomeParqueAux, matriculaAux, &dataAux.dia,
                           &dataAux.mes, &dataAux.ano, &horaAux.hora,
                           &horaAux.minuto);
                    if (tratarErrosRemoverCarro(Parques, nomeParqueAux,
                                                matriculaAux, dataAux, horaAux,
                                                ultimaData, ultimaHora) == 1) {
                        removerCarro(&Parques, nomeParqueAux, matriculaAux,
                                     dataAux, horaAux);
                        ultimaData = dataAux;
                        ultimaHora = horaAux;
                    }
                    free(nomeParqueAux);
                    free(matriculaAux);
                }
                break;

            case 'v':

                matriculaAux = (char *)malloc(10 * sizeof(char));
                sscanf(input, "%c %s", &comando, matriculaAux);

                if (tratarErrosListarEntradasSaidas(Parques, matriculaAux) ==
                    1) {
                    listarEntradasSaidas(Parques, matriculaAux, numParques);
                }

                free(matriculaAux);

                break;

            case 'f':
                nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));

                if (input[2] != '"' &&
                    sscanf(input, "%c %s %d-%d-%d", &comando, nomeParqueAux,
                           &dataAux.dia, &dataAux.mes, &dataAux.ano) == 5) {
                    if (tratarErrosFaturarComData(Parques, nomeParqueAux,
                                                  dataAux, ultimaData,
                                                  ultimaHora) == 1) {
                        faturarParqueDataEspecifica(Parques, nomeParqueAux,
                                                    dataAux);
                    }
                }

                else if (input[2] == '"' &&
                         sscanf(input, "%c \"%[^\"]\" %d-%d-%d", &comando,
                                nomeParqueAux, &dataAux.dia, &dataAux.mes,
                                &dataAux.ano) == 5) {
                    if (tratarErrosFaturarComData(Parques, nomeParqueAux,
                                                  dataAux, ultimaData,
                                                  ultimaHora) == 1) {
                        faturarParqueDataEspecifica(Parques, nomeParqueAux,
                                                    dataAux);
                    }
                }

                else if (input[2] != '"' &&
                         sscanf(input, "%c %s", &comando, nomeParqueAux) == 2) {
                    if (tratarErrosFaturarSemData(Parques, nomeParqueAux) ==
                        1) {
                        faturarParque(Parques, nomeParqueAux);
                    }
                } else if (input[2] == '"' &&
                           sscanf(input, "%c \"%[^\"]\"", &comando,
                                  nomeParqueAux) == 2) {
                    if (tratarErrosFaturarSemData(Parques, nomeParqueAux) ==
                        1) {
                        faturarParque(Parques, nomeParqueAux);
                    }
                }

                free(nomeParqueAux);

                break;

            case 'r':
                if (input[2] != '"') {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));

                    sscanf(input, "%c %s", &comando, nomeParqueAux);

                    if (tratarErrosRemoverParque(Parques, nomeParqueAux) == 1) {
                        removerParque(&Parques, nomeParqueAux, numParques);
                        numParques--;
                    }

                }

                else {
                    nomeParqueAux = (char *)malloc(BUFSIZ * sizeof(char));

                    sscanf(input, "%c \"%[^\"]\" ", &comando, nomeParqueAux);
                    if (tratarErrosRemoverParque(Parques, nomeParqueAux) == 1) {
                        removerParque(&Parques, nomeParqueAux, numParques);
                        numParques--;
                    }
                }

                free(nomeParqueAux);

                break;

            default:
                break;
        }
        free(input);
    }

    return 0;
}
