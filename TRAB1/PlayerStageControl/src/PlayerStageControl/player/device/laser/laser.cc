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

#include "laser.hh"

Laser::Laser(playerc_client_t *client) {
    _laser = playerc_laser_create(client, 0);
}

Laser::~Laser() {
    playerc_laser_destroy(_laser);
}

float Laser::getRange(int beam) {
    if(beam >= _laser->scan_count)
        std::cout << "[ERROR] Laser::getRange(" << beam << "), accessing invalid beam!";

    return _laser->scan[beam][0];
}

float Laser::getBearing(int beam) {
    if(beam >= _laser->scan_count)
        std::cout << "[ERROR] Laser::getBearing(" << beam << "), accessing invalid beam!";

    return _laser->scan[beam][1];
}

float Laser::getRangeResolution() {
    return _laser->scan_res;
}

float Laser::getMaxRange() {
    return _laser->max_range;
}

float Laser::getScanStart() {
    return _laser->scan_start;
}

float Laser::getScanStop() {
    return _laser->scan_start + _laser->scan_count*getScanResolution();
}

float Laser::getScanResolution() {
    return _laser->scan_res;
}

int Laser::getScanCount() {
    return _laser->scan_count;

}

bool Laser::connect() {
    return (playerc_laser_subscribe(_laser, PLAYERC_OPEN_MODE));
}

bool Laser::disconnect() {
    return (playerc_laser_unsubscribe(_laser)==0);
}
