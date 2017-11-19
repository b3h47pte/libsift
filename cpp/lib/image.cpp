// Copyright 2017 Michael Bao. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file. The SIFT algorithm is
// patented and its use for commercial applications must be licensed.
// See the LICENSE file for details.
#include "image.h"
#include <OpenImageIO/imageio.h>

namespace sift
{

Image::Image():
    _width(0), _height(0), _channels(0)
{
}

Image::Image(const int width, const int height, const int channels)
{
    resizeImage(width, height, channels);
}

void Image::resizeImage(const int width, const int height, const int channels)
{
    _width = width;
    _height = height;
    _channels = channels;
    _data.resize(_width * _height * _channels);
}

void Image::loadFromFile(const std::string& fname)
{
    OIIO::ImageInput* in = OIIO::ImageInput::open(fname);
    if (!in) {
        throw ImageIOException("Failed to load image from file: " + fname);
    }

    const OIIO::ImageSpec& spec = in->spec();
    resizeImage(spec.width, spec.height, spec.nchannels);
    in->read_image(OIIO::TypeDesc::UINT8, &_data[0]);
    in->close();
    OIIO::ImageInput::destroy(in);
}

void Image::saveToFile(const std::string& fname) const
{
    OIIO::ImageOutput* out = OIIO::ImageOutput::create(fname);
    if (!out) {
        throw ImageIOException("Failed to write image to file: " + fname);
    }

    OIIO::ImageSpec spec(_width, _height, _channels, OIIO::TypeDesc::UINT8);
    out->open(fname, spec);
    out->write_image(OIIO::TypeDesc::UINT8, _data.data());
    out->close();
    OIIO::ImageOutput::destroy(out);
}

bool Image::operator==(const Image& rhs) const
{
    if (_width != rhs._width) {
        return false;
    }

    if (_height != rhs._height) {
        return false;
    }

    if (_channels != rhs._channels) {
        return false;
    }
    assert(_data.size() == rhs._data.size());
    for (size_t i = 0; i < _data.size(); ++i) {
        if (_data[i] != rhs._data[i]) {
            return false;
        }
    }

    return true;
}

}