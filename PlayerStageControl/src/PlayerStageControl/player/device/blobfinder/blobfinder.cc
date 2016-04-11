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

#include "blobfinder.hh"


BlobFinder::BlobFinder(playerc_client_t *client) {
    _blobfinder = playerc_blobfinder_create(client, 0);
}

BlobFinder::~BlobFinder() {
    playerc_blobfinder_destroy(_blobfinder);
}

Blob BlobFinder::getBlob(int index){
    return Blob(_blobfinder->blobs[index]);
}

int BlobFinder::getNumBlobs() {
    return _blobfinder->blobs_count;
}

bool BlobFinder::connect() {
    return (playerc_blobfinder_subscribe(_blobfinder, PLAYERC_OPEN_MODE));
}

bool BlobFinder::disconnect() {
    return (playerc_blobfinder_unsubscribe(_blobfinder)==0);
}
