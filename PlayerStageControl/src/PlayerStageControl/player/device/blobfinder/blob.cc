#include "blob.hh"

Blob::Blob() {
    _id = 0;
    _color = Colors::UNDEFINED;
    _area = 0;
    _centroid.setUnknown();
    _range = 0;
}

Blob::Blob(playerc_blobfinder_blob_t blob) {
    _id = blob.id;
    _color = blob.color;
    _area = blob.area;
    _centroid.set(blob.x,blob.y);
    _range = blob.range;
}

Colors::Color Blob::getColor() {
    return Colors::rgb2color(_color);
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
