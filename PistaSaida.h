//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_PISTASAIDA_H
#define TRAFFICJAM_PISTASAIDA_H

#include "./Pista.h"

//! Classe PistaSaida
/*!
 * Esta classe e uma classe Pista mais sofisticada (extende Pista),
 * ela possui caracteristicas especiais que a remete a uma pista da qual saem carros no semaforo.
 */
class PistaSaida : public Pista {
public:
    PistaSaida(char* name, std::size_t speed, std::size_t max_size);
    ~ExitRoad();

    virtual void enqueue(Veiculo* data);
};

//! Construtor
/*!
 * construtor padrao
 * @param name -> nome da pista
 * @param speed -> velocidade de trafego
 * @param max_size -> maximo tamanho (quantos metros de carro suporta)
 */
PistaSaida::PistaSaida(char *name, std::size_t speed, std::size_t max_size) :
Pista::Pista(speed, max_size)
{
    Pista::_name = name;
    Pista::_type = 'e';
}

//! Destrutor
/*! Apenas chama a funcao clear que herdou de Pista
 */
PistaSaida::~ExitRoad() {
    Pista::clear();
}

//! Enfileira carro na pistta
/*!
 * Esta funcao realiza a chamada da funcao herdade de pista, enqueue,
 * passando um ponteiro de veiculo como parametro
 * @param data -> veiculo a ser inserido na fila
 */
void PistaSaida::enqueue(Veiculo *data) {
    Pista::enqueue(data);
}

#endif //TRAFFICJAM_PISTASAIDA_H
