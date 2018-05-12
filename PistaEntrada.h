//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_PISTAENTRADA_H
#define TRAFFICJAM_PISTAENTRADA_H


#include "./Veiculo.h"
#include "./strucs/arraylist.h"
#include "./Pista.h"

//! Classe PistaEntrada
/*!
 * Esta classe e uma Pista mais sofisticada (extende Pista), possui caracteristicas especiais
 * para podermos tratar de pistas que recebem carros no semaforo.
 */
class PistaEntrada : public Pista {
public:
    PistaEntrada(char* name, std::size_t speed, std::size_t max_size, std::size_t average,
                 std::size_t interval, std::size_t prob_left, std::size_t prob_front, std::size_t prob_right);
    ~PistaEntrada();

    void crossroads(void *left, void *front, void *right);
    void* crossroads(std::size_t index);

    virtual void enqueue(Veiculo* data);

    std::size_t directionProb();
    std::size_t input_frequency();

private:
    std::size_t _average,  //! intervalo de tempo de entrada de carros
            _interval,  //! menor valor do intervalo
            _prob_left, _prob_front, _prob_right;  //! probabilidade de virar a esquerda/seguir reto/virar direita.
    ArrayList<void*> _crossroads{3u};  //! destinos possiveis
};

//! Construtor Padrao
/*!
 * Default constructor
 * @param name
 * @param speed
 * @param max_size
 * @param average
 * @param interval
 * @param prob_left
 * @param prob_front
 * @param prob_right
 */
PistaEntrada::PistaEntrada(char *name, std::size_t speed, std::size_t max_size, std::size_t average,
                           std::size_t interval, std::size_t prob_left, std::size_t prob_front,
                           std::size_t prob_right) :
Pista::Pista(speed, max_size),
_average{average},
_interval{interval},
_prob_front{prob_front},
_prob_left{prob_left},
_prob_right{prob_right}
{
    Pista::_name = name;
    Pista::_type = 'a';
}

//! Destrutor
/*! apenas chama o metodo clear de Pista();
 */
PistaEntrada::~PistaEntrada(){
    Pista::clear();
}

//! Get Pista pelo destino
/*!
 * Retorna a pista de destino baseado na direçao convergida:
 *  - 0 -> esquerda
 *  - 1 -> frente
 *  - 2 -> direita
 * @param index
 * @return pista de destino
 */
void* PistaEntrada::crossroads(std::size_t index) {
    return _crossroads[index];
}

//! Seta Cruzamentos
/*!
 * Faz a conexao das pistas com possiveis destinos,
 * setando as posiçoes do ponteiro de crossroads para:
 *  - 0 : esquerda
 *  - 1 : frente
 *  - 2 : direita
 * @param left void pointer to road on left
 * @param front void pointer to road in front
 * @param right void pointer to road on right
 */
void PistaEntrada::crossroads(void *left, void *front, void *right) {
    _crossroads.insert(left, 0u);
    _crossroads.insert(front, 1u);
    _crossroads.insert(right, 2u);
}

//! Enfileira Veiculo na fila (OVERWRITE)
/*!
 * Insere um veiculo na ultima posiçao da fila que representa a pista,
 * decidindo pra onde ele vai virar usando o metodo directionProb().
 * @param data ponteiro do veiculo que deseja atravessar o semaforo
 */
void PistaEntrada::enqueue(Veiculo* data) {
    if (Pista::full(data))
        throw std::out_of_range("A pista desejada se encontra cheia!");

    data->direction(directionProb());
    Pista::enqueue(data);
}

//! Get direçao destino provavel
/*!
 * Gera o destino provavel de entrada baseado na probabilidade da pista,
 * Se a probabilidade calculada for menor que a probabilidade de virar a esquerda, entao ele vira a esquerda.
 * Se a probabilidade calculada - probabilidade de virar a esquerda for menor que a de seguir retor, ele segue reto,
 * Caso a probabilidade calculada - probabilidade de virar a direita for menor que 1 (ultimo caso), ele vira a direita.
 * @return direçao de destino usando size_t
 */
std::size_t PistaEntrada::directionProb() {
    std::size_t prob = (std::size_t) rand()%100;
    if (prob < _prob_left)
        return 0u;
    else if (prob - _prob_left < _prob_front)
        return 1u;
    else
        return 2u;
}

//! get Frequencia de entrada
/*!
 * Calcula um tempo (calculado em std::size_t ) aleatorio para as entradas de carro na estrada
 * @return std:size_t -> tempo de entrada dos veiculos
 */
std::size_t PistaEntrada::input_frequency() {
    double temp = ((double) rand() / (RAND_MAX));
    return (std::size_t) temp * (2 * _interval+1) + _average - _interval;
}



#endif //TRAFFICJAM_PISTAENTRADA_H
