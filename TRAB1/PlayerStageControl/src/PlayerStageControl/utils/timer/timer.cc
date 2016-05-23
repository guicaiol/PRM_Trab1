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

#include "timer.hh"

Timer::Timer() {
    clock_gettime(CLOCK_REALTIME, &_time1);
    clock_gettime(CLOCK_REALTIME, &_time2);
}

void Timer::start() {
    clock_gettime(CLOCK_REALTIME, &_time1);
}

void Timer::stop() {
    clock_gettime(CLOCK_REALTIME, &_time2);
}

double Timer::timesec() {
    return timensec()/1E9;
}

double Timer::timemsec()   {
    return timensec()/1E6;
}

double Timer::timeusec()   {
    return timensec()/1E3;
}

double Timer::timensec()   {
    return (_time2.tv_sec*1E9 + _time2.tv_nsec) - (_time1.tv_sec*1E9 + _time1.tv_nsec);
}
