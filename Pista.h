//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_PISTA_H
#define TRAFFICJAM_PISTA_H

#include "strucs/linkedqueue.h"
#include "Veiculo.h"

//! Clase Pista
/*!
 * Classe "template" para as classes PistaEntrada e PistaSaida,
 * ela simula uma linkedQueue com infos extra que remetem a pistas.
 */
class Pista : private LinkedQueue<Veiculo*> {
public:
    Pista(std::size_t speed, std::size_t max_size);
    ~Pista();

    void clear();
    virtual void enqueue(Veiculo* data);
    Veiculo* dequeue();
    Veiculo* front() const;
    Veiculo* back() const;

    std::size_t route_time();

    char type() const;
    char* name() const;
    std::size_t speed() const;
    std::size_t size() const;
    std::size_t cars_on_the_road() const;
    std::size_t max_size() const;
    std::size_t input_counter() const;
    std::size_t output_counter() const;

    bool empty() const;
    bool full(const Veiculo* data) const;

protected:
    char _type{'b'};
    char* _name{(char*)"base\0"};
    std::size_t _speed,
    _size{0u},
    _max_size,
    _input_counter{0u},  //! contador de veiculos que entraram no sumidouro
    _output_counter{0u};  //! contador de veiculos que entraram no sumidouro
};

//! Construtor
/*!
 * inicializa a fila encadeada e seta speed e max_size.
 * @param speed
 * @param max_size
 */
Pista::Pista(std::size_t speed, std::size_t max_size) :
        LinkedQueue<Veiculo*>::LinkedQueue(),
        _speed{speed},
        _max_size{max_size}
{}

//! Destrutor
/*! Nada alocado dinamicamente
 */
Pista::~Pista() {
    LinkedQueue<Veiculo*>::clear();
}

//! Limpa Pista
/*! remove todos os veiculos da pista
 */
void Pista::clear() {
    LinkedQueue<Veiculo*>::clear();
}

//! Adiciona Veiculo
/*!
 * Insere um veiculo na fila que representa a pista, no final.
 * @param data
 */
void Pista::enqueue(Veiculo* data) {
    if (full(data))
        throw std::out_of_range("Pista Cheia!");

    LinkedQueue<Veiculo*>::enqueue(data);
    _input_counter++;
    _size += data->size();
}

//! Remove veiculo
/*!
 * Remove o primeiro veiculo da fila que representa a pista
 * @return veiculo removido
 */
Veiculo* Pista::dequeue() {
    Veiculo* toremove = LinkedQueue<Veiculo*>::dequeue();
    _output_counter++;
    return toremove;
}

//! Primeiro da fila
/*!
 * @return primeiro da fila
 */
Veiculo* Pista::front() const {
    return LinkedQueue<Veiculo*>::front();
}

//! Ultimo da fila
Veiculo* Pista::back() const {
    return LinkedQueue<Veiculo*>::back();
}

//! Tempo de rota
/*! retorna o tempo estimado em rota,
 *  baseado no tamanho máximo da pista e Velocidade.
 *  @return std::size_t tempoemrota
 */
std::size_t Pista::route_time() {
    return (std::size_t) _max_size/(_speed/3.6);  //< km/h => m/s
}

//! Tipo da pita
/*! Retorna o tipo da pista:
 *    - 'b' : base
 *    - 'a' : aferente / PistaEntrada
 *    - 'e' : eferente / PistaSaida
 *    @return char -> contendo tipo da pista
 */
char Pista::type() const {
    return _type;
}

//! Tamanho atual
/*! Retorna o tamanho atual da pista.
 * @return size
 */
std::size_t Pista::size() const {
    return _size;
}

//! Contador de entradas
/*! Retorna a quantidade de entradas que ocorreram
 *  @return input_counter
 */
std::size_t Pista::input_counter() const {
    return _input_counter;
}

//! Contador de saídas
/*! Retorna a quantidade de saídas que ocorreram
 @return output_counter
 */
std::size_t Pista::output_counter() const {
    return _output_counter;
}

//! Veiculos na pista
/*! Retorna a quantidade de carros que se encontram na estrada.
 *  @return std::size_t numero de veiculos
 */
std::size_t Pista::cars_on_the_road() const {
    return LinkedQueue<Veiculo*>::size();
}

//! Tamanho máximo
std::size_t Pista::max_size() const {
    return _max_size;
}


//! Pista vazia
bool Pista::empty() const {
    return _size == 0u;
}

//! Pista cheia
/*!
 * Verifica, contando o tamanho do veiculo que deseja acessar a pista,
 * se ela esta cheia (permite ou nao a inserçao)
 * @param data -> veiculo que deseja acessar
 * @return bool
 */
bool Pista::full(const Veiculo* data) const {
    return max_size() < data->size()+size();
}


//! O nome da pista
char* Pista::name() const {
    return _name;
}

//! Velocidade da pista
std::size_t Pista::speed() const {
    return _speed;
}



#endif //TRAFFICJAM_PISTA_H
