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

#include "odometer.hh"

Odometer::Odometer(playerc_client_t *client) {
    _odometer = playerc_position2d_create(client, 0);
}

Odometer::~Odometer() {
    playerc_position2d_destroy(_odometer);
}

Position Odometer::getPosition() {
    return Position(_odometer->px, _odometer->py);
}

float Odometer::getOrientation() {
    return _odometer->pa;
}

void Odometer::setSpeed(float x, float y, float theta) {
    playerc_position2d_set_cmd_vel(_odometer, x, y, theta, 1);
}

bool Odometer::connect() {
    return (playerc_position2d_subscribe(_odometer, PLAYERC_OPEN_MODE)==0);
}

bool Odometer::disconnect() {
    return (playerc_position2d_unsubscribe(_odometer)==0);
}
