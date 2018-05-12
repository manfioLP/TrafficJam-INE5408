//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_SEMAFORO_H
#define TRAFFICJAM_SEMAFORO_H

#include <cstdint>
#include <stdlib.h>
#include "./strucs/arraylist.h"
#include "PistaEntrada.h"


//! Clase Semaforo
/*!
 * Esta classe eh a responsavel pelo controle das pistas, ou seja,
 * ele impede que o veiculos se movimentem caso o mesmo esteja fechado.
 */
class Semaforo {
public:
    Semaforo(std::size_t tempo_semaforo, ArrayList<PistaEntrada*>& roads);
    ~Semaforo();

    std::size_t time() const;
    void changeOpenRoad();
    bool open(const PistaEntrada* road) const;

private:
    ArrayList<PistaEntrada*>& _roads;  //! guarda as pistas possiveis que um veiculo pode convergir no semaforo
    std::size_t _semaforo{0u},  //! para controlar a conversao de pista
    _time ;
    PistaEntrada *_S1, *_S2;  //! Semaforos do primeiro e segundo cruzamento, respectivamente
};

//! Construtor Padrao
/*!
 * seta atributos passados
 * @param tempo_semaforo
 * @param roads
 */
Semaforo::Semaforo(std::size_t tempo_semaforo, ArrayList<PistaEntrada *> &roads):
_time{tempo_semaforo},
_roads{roads},
_S1{roads[0]},
_S2{roads[3]}
{}

//! Destrutor
/*! Nada alocado dinamicamente
 */
Semaforo::~Semaforo() {}

//! Tempo para troca de sinal
/*!
 * Tempo para a troca do sinal
 * @return std::size_t tempo para trocar o sinal
 */
std::size_t Semaforo::time() const {
    return _time;
}

//! Troca de sinal
/*!
 * Checa qual pista precisa trocar o sinal e troca
 */
void Semaforo::changeOpenRoad() {
    _semaforo =(_semaforo+1) %4;
    _S1 = _roads[_semaforo];
    _S1 = _roads[_semaforo+3];
}

//! Sinal do semaforo
/*!
 * Verifica se uma determinada pista esta com o seu sinal aberto
 * @param PistaEntrada* road -> ponteiro da pista que se deseja verificar
 * @return bool
 */
bool Semaforo::open(const PistaEntrada* road) const {
    return _S1 == road || _S2 == road;
}


#endif //TRAFFICJAM_SEMAFORO_H
