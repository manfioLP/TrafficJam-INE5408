cmake_minimum_required(VERSION 3.10)
project(TrafficJam)

set(CMAKE_CXX_STANDARD 11)

add_executable(TrafficJam main.cpp strucs/arraylist.h strucs/linkedlist.h strucs/linkedqueue.h Pista.h Veiculo.h PistaEntrada.h Semaforo.h PistaSaida.h Evento.h System.h)