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

#ifndef NAVIGATION_HH
#define NAVIGATION_HH

#include <PlayerStageControl/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <PlayerStageControl/player/baseplayer.hh>
#include <PlayerStageControl/player/device/basedevices.hh>

class Navigation {
public:
    Navigation(Player *player, Laser *laser);

    // Path planning
    float getDirection(const Position &destination, bool avoidObstacles);

    // Velocity control
//    float getLinearSpeed();
//    float getAngularSpeed();
private:
    // Player access
    Player *_player;

    // Laser access
    Laser *_laser;

    // NavAlg
    NavigationAlgorithm *_navAlg;
};

#endif // NAVIGATION_HH
