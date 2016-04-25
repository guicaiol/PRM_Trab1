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

#include "thread.hh"

Thread::Thread() {
    _running = false;
    _enabled = true;
}

Thread::~Thread() {

}

void Thread::start() {
    if(_running)
        return;
    else {
        _running = true;
        _enabled = true;
        _thread = std::thread(&Thread::run, this);
    }
}

void Thread::run() {
    initialization();
    while(_running) {
        if(_enabled)
            loop();
//        msleep(15);
    }
    finalization();
}

void Thread::stop() {
    if(_running)
        _running = false;
}

void Thread::wait() {
    if(_thread.joinable())
        _thread.join();
}

void Thread::msleep(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
