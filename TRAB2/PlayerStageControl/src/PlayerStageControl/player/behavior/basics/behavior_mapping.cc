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

#include "behavior_mapping.hh"
#include <PlayerStageControl/player/player.hh>
#include <PlayerStageControl/player/device/devices.hh>

#define RESOLUTION 0.025 // m
#define MAP_X_MIN -8.0
#define MAP_X_MAX  8.0
#define MAP_Y_MIN -8.0
#define MAP_Y_MAX  8.0

#define RGB_MAX 255

Behavior_Mapping::Behavior_Mapping() {
    _width = (MAP_X_MAX-MAP_X_MIN)/RESOLUTION;
    _height = (MAP_Y_MAX-MAP_Y_MIN)/RESOLUTION;

    // Create map
    _map.resize(_width);
    for(unsigned i=0; i<_map.size(); i++)
        _map[i].resize(_height, 0.5);

    // Create OpenCV image
    _image = cvCreateImage(cvSize(_width,_height), IPL_DEPTH_8U, 3);
    refreshView();
}

Behavior_Mapping::~Behavior_Mapping() {

}

void Behavior_Mapping::run() {
    // Player moviment
    player()->idle();

    // Reset view
//    resetView();

    // Player laser mapping
    Laser *laser = player()->laser();
    for(int i=0; i<laser->getScanCount(); i++) {
        const float range = laser->getRange(i);
        const float bearing = laser->getBearing(i);

        // Draw lines
        float globalAngle = player()->orientation() + bearing;
        Position relPos(range*cos(globalAngle), range*sin(globalAngle));
        Position pos(player()->position().x() + relPos.x(), player()->position().y() + relPos.y());
        mapLine(player()->position(), pos);

        // Point
        if(range < laser->getMaxRange()) {
            const int x = (pos.x()+MAP_X_MAX)/RESOLUTION;
            const int y = _height - (pos.y()+MAP_Y_MAX)/RESOLUTION;

            nunoMapPixel(x, y, -0.2);
//            drawPosition(pos, RGB_MAX, 0, 0);
        }

    }

    // Apply Alzheimer
    updateAlzheimer();

    // Update map to view
    updateMapToView();

    // Refresh
    refreshView();
}

void Behavior_Mapping::resetView() {
    cvSet(_image, cvScalar(0,0,0));
}

void Behavior_Mapping::refreshView() {
    cvNamedWindow("Behavior_Mapping", 1);
    cvShowImage("Behavior_Mapping", _image);
    cvWaitKey(50);
}

void Behavior_Mapping::updateAlzheimer() {
    for(int i=0; i<_width; i++) {
        for(int j=0; j<_height; j++) {
            nunoMapPixel(i, j, -0.005);
        }
    }
}

void Behavior_Mapping::updateMapToView() {
    for(int i=0; i<_width; i++) {
        for(int j=0; j<_height; j++) {
            float color = _map[i][j]*RGB_MAX;
            drawPixel(i, j, color, color, color);
        }
    }
}

void Behavior_Mapping::drawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if(x>=0 && y>=0 && x<=_width && y<=_height) {
        _image->imageData[3*((y*_width)+x)]   = b;
        _image->imageData[3*((y*_width)+x)+1] = g;
        _image->imageData[3*((y*_width)+x)+2] = r;
    }
}

void Behavior_Mapping::drawPosition(const Position &pos, unsigned char r,  unsigned char g, unsigned char b) {
    const int x = (pos.x()+MAP_X_MAX)/RESOLUTION;
    const int y = _height - (pos.y()+MAP_Y_MAX)/RESOLUTION;
    drawPixel(x, y, r, g, b);
}

void Behavior_Mapping::mapLine(const Position &p1, const Position &p2) {
    int x0 = (p1.x()+MAP_X_MAX)/RESOLUTION;
    int y0 = _height - (p1.y()+MAP_Y_MAX)/RESOLUTION;
    const int x1 = (p2.x()+MAP_X_MAX)/RESOLUTION;
    const int y1 = _height - (p2.y()+MAP_Y_MAX)/RESOLUTION;

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
//        drawPixel(x0, y0, RGB_MAX, RGB_MAX, RGB_MAX);
        nunoMapPixel(x0, y0, 0.1);

        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void Behavior_Mapping::nunoMapPixel(int x, int y, float inc) {
    if(x<0 || y<0 || x>=_width || y>=_width)
        return;

    _map[x][y] += inc;

    if(_map[x][y] > 1)
        _map[x][y] = 1;

    if(_map[x][y] < 0)
        _map[x][y] = 0;
}
