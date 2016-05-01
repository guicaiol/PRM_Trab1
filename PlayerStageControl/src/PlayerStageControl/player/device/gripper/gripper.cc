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

#include "gripper.hh"

Gripper::Gripper(playerc_client_t *client) {
    _gripper = playerc_gripper_create(client, 0);
}

Gripper::~Gripper() {
    playerc_gripper_destroy(_gripper);
}

Gripper::GripperState Gripper::state() {
    return (GripperState)_gripper->state;
}

bool Gripper::isAvailable() {
    return (_gripper->state!=GripperState::UNAVAILABLE);

}

void Gripper::open() {
    playerc_gripper_open_cmd(_gripper);
}

void Gripper::close() {
    playerc_gripper_close_cmd(_gripper);
}

bool Gripper::connect() {
    return (playerc_gripper_subscribe(_gripper, PLAYERC_OPEN_MODE));
}

bool Gripper::disconnect() {
    return (playerc_gripper_unsubscribe(_gripper)==0);
}
