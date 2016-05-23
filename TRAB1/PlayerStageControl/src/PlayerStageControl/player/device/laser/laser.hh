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

#ifndef LASER_HH
#define LASER_HH

#include <PlayerStageControl/player/device/device.hh>

class Laser : public Device {
public:
    Laser(playerc_client_t *client);
    ~Laser();

    // Gets
    float getRange(int beam);
    float getBearing(int beam);
    float getRangeResolution();
    float getMaxRange();
    float getScanStart();
    float getScanStop();
    float getScanResolution();
    int getScanCount();

private:
    playerc_laser_t *_laser;

    // Inheritance implementation (called by Player)
    friend class Player;
    bool connect();
    bool disconnect();
};

#endif // LASER_HH
