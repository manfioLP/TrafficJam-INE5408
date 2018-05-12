//! COPYRIGHT @LeopoldoManfio #2018
#ifndef TRAFFICJAM_VEICULO_H
#define TRAFFICJAM_VEICULO_H


#include <cstdint>
#include <stdlib.h>

class Veiculo {
public:
    Veiculo();
    ~Veiculo();

    std::size_t size() const;
    std::size_t direction() const;
    void direction(std::size_t direction);

private:
    std::size_t size_;
    std::size_t direction_{0u}; //! Direçao que o carro esta indo (0, 1, 2, 3)
};

//! Construtor PaDRAO
/*!
 * Construtor padrao, onde se define um tamanho do veiculo,
 * que e um valor entre 2 e 6 metros + 2 metros na traseira + 1 na frente
 */
std::size_t Veiculo::Veiculo() {
    double temp = ((double) rand()/(RAND_MAX));
    size_ = (std::size_t) temp*5 + 3;
}

//! Destrutor padrão
/*  Nada alocado dinamicamente.
 */
Veiculo::~Veiculo() {}

std::size_t Veiculo::size() const {
    return size_;
}

std::size_t Veiculo::direction() const {
    return direction_;
}

void Veiculo::direction(std::size_t direction) {
    direction_ = direction;
}

#endif //TRAFFICJAM_VEICULO_H
