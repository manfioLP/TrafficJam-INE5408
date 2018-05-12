#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "System.h"

int main() {
    std::cout << "Hello, Profesor!" << std::endl;
    srand(time(NULL));
    std::size_t _execution_time=28800;  // 8h
    std::size_t _semaphore_time=30;     // 30s

    std::ifstream file;
    file.open("./config.txt");

    if (file.is_open()) {
        char line[200];
        file.getline(line, 200);
        while (line[0]=='#')
            file.getline(line, 200);
        file >> _execution_time >> _semaphore_time;
        file.close();

        std::cout << "Tempo de execução: " << _execution_time << "\n";
        std::cout << "Tempo de troca de semáforo: " << _semaphore_time << "\n";
    } else {
        std::cout << "Informe o tempo, em segundos, de execução da simulação: \n" << "> ";
        std::cin >> _execution_time;
        std::cout << "Informe o tempo, em segundos, que um semáforo ficará aberto: \n" << "> ";
        std::cin >> _semaphore_time;
    }

    System sys{_execution_time, _semaphore_time};
    sys.init();
    sys.run();
    sys.result();

    return 0;
}