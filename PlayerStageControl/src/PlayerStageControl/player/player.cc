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

#include "player.hh"
#include <iostream>
#include <PlayerStageControl/player/behavior/behavior.hh>
#include <PlayerStageControl/player/navigation/navigation.hh>
#include <PlayerStageControl/player/device/devices.hh>

Player::Player(const char *host, int port) {
    // Create player
    _client = playerc_client_create(NULL, host, port);

    // Create devices
    _odometer = new Odometer(_client);
    _laser = new Laser(_client);
    _gripper = new Gripper(_client);
    _blobfinder = new BlobFinder(_client);

    // Create navigation
    _nav = new Navigation(this, _laser);

    // Initialization
    _behavior = NULL;
    _lError = 0.10;
    _aError = Utils::toRadians(5);
    _maxLSpeed = 1.2;
    _maxASpeed = Utils::toRadians(100);
}

Player::~Player() {
    // Delete sensors
    delete _odometer;
    delete _laser;
    delete _gripper;
    delete _blobfinder;

    // Delete navigation
    delete _nav;

    // Destroy playerc client
    playerc_client_destroy(_client);
}

bool Player::connect() {
    return (playerc_client_connect(_client)==0);
}

bool Player::disconnect() {
    return (playerc_client_disconnect(_client)==0);
}

Position Player::position() const {
    // Get from odometer
    return _odometer->getPosition();
}

float Player::orientation() const {
    // Get from odometer
    return _odometer->getOrientation();
}

void Player::printError() {
    std::cout << "ERROR: " << playerc_error_str() << "\n";
}

float Player::getLinearSpeed(float distError) {
    float kp = 2.0;
    float speed = kp*distError;

    float signal = speed/fabs(speed);
    return (speed>_maxLSpeed? signal*_maxLSpeed : speed);
}

float Player::getAngularSpeed(float angError) {
    // Fix high angle
    if(angError > Utils::pi())
        angError -= Utils::twoPi();
    if(angError < -Utils::pi())
        angError += Utils::twoPi();

    float kp = 1.5;
    float speed = kp*angError;

    float signal = speed/fabs(speed);
    return (fabs(speed)>_maxASpeed? signal*_maxASpeed : speed);
}

void Player::update() {
    // Read
    playerc_client_read(_client);
}

void Player::initialization() {
    // Connect sensors
    _odometer->connect();
    _laser->connect();
    _gripper->connect();
    _blobfinder->connect();

    // Update first time
    update();
}

void Player::loop() {
    // Update data
    this->update();

    // Run behavior
    if(_behavior!=NULL)
        _behavior->run();
}

void Player::finalization() {
    // Send idle
    idle();

    // Disconnect sensors
    _odometer->disconnect();
    _laser->disconnect();
    _gripper->disconnect();
    _blobfinder->disconnect();
}

bool Player::isAtPosition(const Position &pos) {
    return (Utils::distance(position(), pos) <= _lError);
}

bool Player::isLookingTo(const Position &pos) {
    float targetAngle = Utils::getAngle(position(), pos);
    float angDiff = Utils::angleDiff(orientation(), targetAngle);
    return (fabs(angDiff) <= _aError);
}

void Player::setBehavior(Behavior *behavior) {
    _behavior = behavior;
    _behavior->initialize(this);
}

void Player::goTo(const Position &destination, bool avoidObstacles) {
    goToLookTo(destination, Position(), avoidObstacles);
}

void Player::goToLookTo(const Position &destination, const Position &posToLook, bool avoidObstacles) {

    // Calc dist error
    float distError = Utils::distance(destination, position());

    // setSpeed
    if(isAtPosition(destination)==false) {
        float targetAngle = _nav->getDirection(destination, avoidObstacles);
        float angError = targetAngle - orientation();

        float speedX = getLinearSpeed(distError);
        float speedA = getAngularSpeed(angError);

        setSpeed(speedX, 0.0, speedA);

    } else if(posToLook.isUnknown()==false && isLookingTo(posToLook)==false) {
        float targetAngle = Utils::getAngle(position(), posToLook);
        float angError = targetAngle - orientation();

        float speedA = getAngularSpeed(angError);
        setSpeed(0.0, 0.0, speedA);

    } else {
        idle();
    }
}

void Player::lookTo(const Position &posToLook, bool avoidObstacles) {
    goToLookTo(position(), posToLook, avoidObstacles);
}

void Player::idle() {
    setSpeed(0.0, 0.0, 0.0);
}

void Player::setSpeed(float x, float y, float theta) {
    _odometer->setSpeed(x, y, theta);
}
