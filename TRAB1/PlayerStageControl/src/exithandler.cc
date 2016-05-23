/***
 * SCC0712 - Programação de Robôs Móveis
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autores: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
 *          Luiz Felipe Machado Votto     (luizvotto@gmail.com)        - nUSP 8504006
 *          Nuno Bernardes Barcellos      (nunobarcellos@gmail.com)    - nUSP 8955132
 *
 * This file is part of PlayerStageControl project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "exithandler.hh"
#include <stdlib.h>
#include <iostream>
#include <signal.h>

sem_t ExitHandler::_sem;
int ExitHandler::_counter = 0;
bool ExitHandler::_finished = 0;

void ExitHandler::setup() {
    // Initialize semaphore
    sem_init(&_sem, 0, 0);

    // Setup CTRL+C hook
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = ExitHandler::run;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

void ExitHandler::wait() {
    // Avoid calling two times
    if(_finished)
        return;
    else
        _finished = true;

    // Wait for semaphore release
    sem_wait(&_sem);

    // Destroy semaphore
    sem_destroy(&_sem);
}

void ExitHandler::run(int s) {
    ExitHandler::_counter++;

    switch(ExitHandler::_counter) {
        case 1: {
            std::cout << "\n[EXIT HANDLER] Closing PlayerStageControl...\n";

            // Release semaphore
            sem_post(&_sem);
        } break;

        default:
        case 2: {
            std::cout << "\n[EXIT HANDLER] Halting PlayerStageControl...\n";
            exit(EXIT_FAILURE);
        } break;
    }
}
