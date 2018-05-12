//! COPYRIGHT @LeopoldoManfio #2018

#ifndef TRAFFICJAM_SYSTEM_H
#define TRAFFICJAM_SYSTEM_H

#include "Semaforo.h"
#include "Evento.h"
#include "PistaSaida.h"

#define DEBUG false

class System {
public:
    System(std::size_t execution_time, std::size_t semaphore_time);
    ~System();

    void init();
    void run();
    void result();

private:
    std::size_t _execution_time,  //! Tempo de execução
            _semaphore_time,  //! Tempo de troca de sinal
            _global_clock{0u},  //! Relógio
            _input_counter{0u},  //! Contador de entrada
            _output_counter{0u},  //! Contador de saída
            _semaphore_counter{0u},  //! Contador troca de sinal
            _exchange_counter{0u};  //! Contador troca de pista

    ArrayList<PistaEntrada*> _entry_roads{8u};  //! Estradas aferentes
    ArrayList<PistaSaida*> _exit_roads{6u};  //! Estradas eferentes

    LinkedList<Evento>* _events;  //! Eventos
    Semaforo* _semaphore; //! Semáforo
};

//! Construtor padrão
/*! Atribuindo os valores bases para o funcionamento do sistema.
 *  @param execution_time Tempo de execução
 *  @param semaphore_time Tempo de uma sinaleira
 */
System::System(std::size_t execution_time, std::size_t semaphore_time):
        _execution_time{execution_time},
        _semaphore_time{semaphore_time}
{
    _events = new LinkedList<Evento>();
}

//! Destrutor
/*! Deleta o sistema
 */
System::~System() {
    delete _events;
    delete _semaphore;
}

//! Inícia todas as estradas e eventos iniciais
/*! Executa uma série e passos antes de rodar o sistema.
 */
void System::init() {

    // Criando as ruas
    // Aferentes
    PistaEntrada* N1_S = new PistaEntrada((char*)"N1_S\0", 60, 500, 20, 5, 80, 10, 10);
    PistaEntrada* S1_N = new PistaEntrada((char*)"S1_N\0", 60, 500, 30, 7, 10, 10, 80);
    PistaEntrada* O1_L = new PistaEntrada((char*)"O1_L\0", 80, 2000, 10, 2, 10, 80, 10);
    PistaEntrada* L1_O = new PistaEntrada((char*)"L1_O\0", 30, 400, 10, 2, 30, 30, 40);
    PistaEntrada* N2_S = new PistaEntrada((char*)"N2_S\0", 40, 500, 20, 5, 40, 30, 30);
    PistaEntrada* S2_N = new PistaEntrada((char*)"S2_N\0", 40, 500, 60, 15, 30, 30, 40);
    // Centrais
    PistaEntrada* C1_L = new PistaEntrada((char*)"C1_L\0", 60, 300, 0, 0, 30, 40, 30);
    PistaEntrada* C1_O = new PistaEntrada((char*)"C1_O\0", 60, 300, 0, 0, 30, 40, 30);
    // Eferente
    PistaSaida* N1_N = new PistaSaida((char*)"N1_N\0", 60, 500);
    PistaSaida* N2_N = new PistaSaida((char*)"N2_N\0", 40, 500);
    PistaSaida* O1_O = new PistaSaida((char*)"O1_O\0", 80, 2000);
    PistaSaida* L1_L = new PistaSaida((char*)"L1_L\0", 60, 500);
    PistaSaida* S1_S = new PistaSaida((char*)"S1_S\0", 60, 500);
    PistaSaida* S2_S = new PistaSaida((char*)"S2_S\0", 40, 500);

    // Interligando os cruzamentos: (left, front, right)
    N1_S->crossroads(C1_L, S1_S, O1_O);
    S1_N->crossroads(O1_O, N1_N, C1_L);
    O1_L->crossroads(N1_N, C1_L, S1_S);
    L1_O->crossroads(S2_S, C1_O, N2_N);
    N2_S->crossroads(L1_L, S2_S, C1_O);
    S2_N->crossroads(C1_O, N2_N, L1_L);
    C1_L->crossroads(N2_N, L1_L, S2_S);
    C1_O->crossroads(S1_S, O1_O, N1_N);

    _entry_roads.push_back(N1_S);
    _entry_roads.push_back(S1_N);
    _entry_roads.push_back(O1_L);
    _entry_roads.push_back(L1_O);
    _entry_roads.push_back(N2_S);
    _entry_roads.push_back(S2_N);
    _entry_roads.push_back(C1_L);
    _entry_roads.push_back(C1_O);

    _exit_roads.push_back(N1_N);
    _exit_roads.push_back(N2_N);
    _exit_roads.push_back(O1_O);
    _exit_roads.push_back(L1_L);
    _exit_roads.push_back(S1_S);
    _exit_roads.push_back(S2_S);

    // Inputs iniciais
    for (auto i = 0u; i<6; ++i) {
        std::size_t event_time = _global_clock + _entry_roads[i]->input_frequency();
        Evento input('i', event_time, _entry_roads[i]);
        _events->insert_sorted(input);
    }

    // Primeiro evento de troca de semáforo
    _semaphore = new Semaforo(_semaphore_time, _entry_roads);
    std::size_t event_time = _global_clock + _semaphore_time;
    Evento semaphore('s', event_time, _semaphore);
    _events->insert_sorted(semaphore);
}

//! Inícia todas as estradas e eventos iniciais
/*! Executa uma série e passos antes de rodar o sistema.
 */
void System::run() {

    while (_global_clock < _execution_time) {
        auto events_made = 0;

        int i = 0;  // Incrementa caso não consiga realizar um evento
        Evento current_event = _events->at(i);
        while (current_event.time() <= _global_clock) {

            switch (current_event.type()) {

                // Evento de saída
                case 's': {
                    _semaphore->changeOpenRoad();
                    ++_semaphore_counter;

                    _events->pop(i);

                    auto event_time = _global_clock + _semaphore_time;
                    Evento semaphore('s', event_time, _semaphore);
                    _events->insert_sorted(semaphore);

                    events_made++;
                    break;
                }

                    // Evento de saída
                case 'o': {
                    PistaSaida* road = (PistaSaida*) current_event.source();
                    delete road->dequeue();
                    ++_output_counter;

                    _events->pop(i);
                    events_made++;
                    break;
                }

                    // Evento de entrada
                case 'i': {
                    events_made++;
                    Veiculo* new_vehicle = new Veiculo();
                    PistaEntrada* road = (PistaEntrada*) current_event.source();

                    try {
                        road->enqueue(new_vehicle);
                        ++_input_counter;

                        // Elimina evento completado
                        _events->pop(i);

                        auto event_time = _global_clock + road->;
                        Evento change('c', event_time, road);
                        _events->insert_sorted(change);

                        event_time = current_event.time() + road->route_time();
                        Evento input('i', event_time, road);
                        _events->insert_sorted(input);

                    } catch(std::out_of_range error) {
                        delete new_vehicle;
                        if (DEBUG)
                            printf("Entrada falhou: Rua: %s engarrafada.\n",
                                   road->name());
                        ++i;
                    }
                    break;
                }

                    // Evento de troca de pista
                case 'c': {
                    events_made++;
                    PistaEntrada* road = (PistaEntrada*) current_event.source();
                    if (!_semaphore->open(road)) {
                        ++i;
                        break;
                    }

                    Veiculo* first_vehicle = road->front();
                    auto direction = first_vehicle->direction();
                    Pista* temp = (Pista*) road->crossroads(direction);

                    if (temp->type() == 'a') {
                        PistaEntrada* aferente = (PistaEntrada*) road->crossroads(direction);
                        try {
                            aferente->enqueue(first_vehicle);
                            road->dequeue();
                            ++_exchange_counter;

                            // Elimina evento completado
                            _events->pop(i);

                            auto event_time = _global_clock + aferente->route_time();
                            Evento change('c', event_time, aferente);
                            _events->insert_sorted(change);

                            // Soma o tempo de saída do carro
                            ++_global_clock;

                        } catch(std::out_of_range error) {
                            if (DEBUG)
                                printf("Troca de %s para %s falhou.\n",
                                       road->name(), aferente->name());
                            ++i;
                        }
                    } else {
                        PistaSaida* eferente = (PistaSaida*) road->crossroads(direction);
                        try {
                            eferente->enqueue(first_vehicle);
                            road->dequeue();
                            ++_exchange_counter;

                            // Elimina evento completado
                            _events->pop(i);

                            auto event_time = _global_clock + eferente->route_time();
                            Evento out('o', event_time, eferente);
                            _events->insert_sorted(out);

                            // Soma o tempo de saída do carro
                            ++_global_clock;

                        } catch(std::out_of_range error) {
                            if (DEBUG)
                                printf("Troca de %s para %s falhou.\n",
                                       road->name(), eferente->name());
                            ++i;
                        }
                    }
                    break;
                }

                default: {
                    break;
                }
            }
            current_event = _events->at(i);
        }

        ++_global_clock;
        if (events_made == 0)
            _global_clock = current_event.time();
    }
}

void System::result() {
    std::size_t inside_roads = 0;
    for (auto i = 0; i < _entry_roads.size(); ++i)
        inside_roads += _entry_roads[i]->cars_on_the_road();
    for (auto i = 0; i < _exit_roads.size(); ++i)
        inside_roads += _exit_roads[i]->cars_on_the_road();

    printf("\nResultados gerais:\n");
    printf("Operação             |  Quant.\n");
    printf("Entrada de veículos  |  %lu\n", _input_counter);
    printf("Veículos nas ruas    |  %lu\n", inside_roads);
    printf("Saída de  veíulos    |  %lu\n", _output_counter);
    printf("Troca de pista       |  %lu\n", _exchange_counter);
    printf("Troca de semáforo    |  %lu\n", _semaphore_counter);
    printf("Eventos restantes    |  %lu\n", _events->size());
    printf("\nIntegridade do sistema\n");
    printf("Entrada - veículos nas ruas = saída:\n%lu - %lu = %lu\n",
           _input_counter, inside_roads, _input_counter-inside_roads);
    printf("Eventos restantes - 6 in - 1 sem = veículos nas ruas:\n%lu - 6 - 1 = %lu\n",
           _events->size(), _events->size()-7);
}
#endif //TRAFFICJAM_SYSTEM_H
