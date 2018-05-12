//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_EVENTO_H
#define TRAFFICJAM_EVENTO_H

#include <cstdint>

class Evento {

public:
    Evento(char type, std::size_t, void* source);
    ~Evento();

    char type() const;
    std::size_t time() const;
    void* source() const;

    bool operator<(const Evento& otherEvent) const;
    bool operator==(const Evento& otherEvent) const;

protected:
    char _type;  //! representa o tipo do evento
    std::size_t _time{0u};  //! "Hora" que o evento foi executado
    void* _source;  //! Quem gerou o evento
};

//! Construtor
/*!
 * Construtor padrao, setando propriedades
 * @param type
 * @param time
 * @param source
 */
Evento::Evento(char type, std::size_t time, void *source) :
_type{type},
_time{time},
_source{source}
{}

//! Destrutor
/*!
 * Nada alocado dinamicamente
 */
Evento::~Evento() {}

//! Get tipo de evento gerado
/*!
 * Retorna o tipo do evento no seguinte esquema:
 *  - s -> evento de semaforo
 *  - i -> evento de entrada (in)
 *  - o -> evento de saida (out)
 *  - c -> evento de troca de pista (change)
 * @return char referente ao tipo de evento
 */
char Evento::type() const {
    return _type;
}

//! get Fonte
/*!
 * retorna a fonte do evento gerado
 * @return ponteiro nao especificado de fonte
 */
void* Evento::source() const {
    return _source;
}

//! get Hora
/*!
 * retorna a hora (tratada como std::size_t) que o evento foi gerado
 * @return std::size_t horario
 */
std::size_t Evento::time() const {
    return _time;
}

//! Sobrecarga do operador menor que ( < )
/*!
 * Compara dois eventos pelo seu tempo e retorna true ou false para this.time < otherevent.time
 * @param otherEvent
 * @return bool
 */
bool bool Evento::operator<(const Evento &otherEvent) const {
    return _time < otherEvent.time();
}

//! Sobrecarga do operador igual ( == )
/*!
 * Checa se dois eventos sao iguais baseados em seu endereço de memoria,
 * se for mesmo endereco, eles sao iguais e portanto retorna true, senao, false
 * @param otherEvent
 * @return bool
 */
bool Evento::operator==(const Evento& otherEvent) const {
    return this == &otherEvent;
}


#endif //TRAFFICJAM_EVENTO_H
