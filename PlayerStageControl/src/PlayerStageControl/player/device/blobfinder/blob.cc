#include "blob.hh"

Blob::Blob(playerc_blobfinder_blob_t blob) {
    _id = blob.id;
    _color = blob.color;
    _area = blob.area;
    _centroid.set(blob.x,blob.y);
    _range = blob.range;
}

int Blob::getColor() {
    return _color;
}

int Blob::getArea() {
    return  _area;
}

Position Blob::getCentroid() {
    return _centroid;
}

float Blob::getRange() {
    return _range;
}
