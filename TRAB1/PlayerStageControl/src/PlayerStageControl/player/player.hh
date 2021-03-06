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

#ifndef PLAYER_HH
#define PLAYER_HH

#include <libplayerc/playerc.h>
#include <PlayerStageControl/player/baseplayer.hh>
#include <PlayerStageControl/player/device/basedevices.hh>
#include <PlayerStageControl/utils/thread/thread.hh>
#include <PlayerStageControl/player/device/blobfinder/blob.hh>

class Player : public Thread {
public:
    Player(const char *host = "localhost", int port = 6665);
    ~Player();

    // Connection and execution
    bool connect();
    bool disconnect();

    // Devices access
    Gripper* gripper() { return _gripper; }
    BlobFinder* blobFinder() { return _blobfinder; }

    // Player position and orientation
    Position position() const;
    float orientation() const;

    // Position/orientation auxiliary
    bool isAtPosition(const Position &pos);
    bool isLookingTo(const Position &pos);
    bool isLookingTo(float angle);
    bool isLookingToBlob(const Blob &blob);

    // Max speeds
    void setMaxLSpeed(float maxLSpeed) { _maxLSpeed = maxLSpeed; }
    float maxLSpeed() const { return _maxLSpeed; }
    float maxASpeed() const { return _maxASpeed; }

    // Check stall
    void setCheckStall(bool enable) { _checkStall = enable; }

    // Behavior
    void setBehavior(Behavior *behavior);

    // Locomotion layer 1
    void goTo(const Position &destination, bool avoidObstacles);
    void goToLookTo(const Position &destination, const Position &posToLook, bool avoidObstacles);
    void lookTo(const Position &position, bool avoidObstacles);
    void lookTo(float angle);
    void idle();

    bool goToBlob(const Blob &blob);
    void lookToBlob(const Blob &blob);

    // Locomotion layer 0
    void setSpeed(float x, float y, float theta);

    // Debug
    void printError();
private:
    // Thread implementation
    void initialization();
    void loop();
    void finalization();

    // Playerc connection
    playerc_client_t *_client;

    // Behavior
    Behavior *_behavior;

    // Navigation
    Navigation *_nav;

    // Sensors
    Odometer *_odometer;
    Laser *_laser;
    Gripper *_gripper;
    BlobFinder *_blobfinder;

    // Errors
    float _lError;
    float _aError;

    // Max speeds
    float _maxLSpeed;
    float _maxASpeed;

    // Flags
    bool _checkStall;

    // Speed calc
    float getLinearSpeed(float distError);
    float getAngularSpeed(float angError);

    // Sensors
    void connectSensors();
    void disconnectSensors();

    // Internal
    void update();
};

#endif // PLAYER_HH
