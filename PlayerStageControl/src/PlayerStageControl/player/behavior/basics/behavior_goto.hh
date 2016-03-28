/***
 * SCC0712 - Programação de Robôs Móveis
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autor: Guilherme Caixeta de Oliveira (gcaixetaoliveira@gmail.com) - nUSP 8504368
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

#ifndef BEHAVIOR_GOTO_HH
#define BEHAVIOR_GOTO_HH

#include <PlayerStageControl/player/behavior/behavior.hh>

class Behavior_GoTo : public Behavior {
public:
    Behavior_GoTo();

    void setDestination(const Position &position) { _destination = position; }
    void setPosToLook(const Position &position) { _posToLook = position; }
private:
    void run();

    // Parameters
    Position _destination;
    Position _posToLook;
};

#endif // BEHAVIOR_GOTO_HH
