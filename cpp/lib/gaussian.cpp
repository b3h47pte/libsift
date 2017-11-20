// Copyright 2017 Michael Bao. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file. The SIFT algorithm is
// patented and its use for commercial applications must be licensed.
// See the LICENSE file for details.
#include "gaussian.h"
#include <cassert>

namespace sift
{

Gaussian2D::Gaussian2D(const std::shared_ptr<Image>& img):
    _filter(img)
{}

Gaussian2D create2DGaussian(const float stddev)
{
    std::shared_ptr<Image> filter(new Image);

    Gaussian2D gaussian(filter);
    return gaussian;
}

Image convolveGaussian2D(const Gaussian2D& gaussian, const Image& image)
{
    Image retImage(image);
    convolveGaussian2DInPlace(gaussian, &retImage);
    return retImage;
}

void convolveGaussian2DInPlace(const Gaussian2D& gaussian, Image* image)
{
    assert(image != nullptr);
}

DoGScaleSpacePyramid::DoGScaleSpacePyramid(const Image& image, int octaves, float stddev):
    _octaves(octaves), _stddev(stddev)
{
    initialize(image);
}

void DoGScaleSpacePyramid::initialize(const Image& image)
{
    Gaussian2D gaussian = create2DGaussian(_stddev);

    // Between each octave, the image shrinks in size by a factor of 2
    // and the std dev of the effective applied Gaussian doubles.
    // Assume we are given a Gaussian with stddev s, G(s), and an image I(x, y).
    // Convolve and get G(s) * I(x, y) which is the image convolved with a 
    // Gaussian with stddev s.
    // Note that if we do G(s) * G(s) * I(x,y), then we get an image convolved
    // with a Gaussian with stddev sqrt(2) * s.
    // Applying again gets G(s) * G(sqrt(2) * s) * I(x, y) which is effectively
    // applying a Gaussian with sqrt(3) s and so on and so forth.
    // The next iteration will result in a Gaussian with twice the std dev (the 4th application).
    // As specified in [Lowe 2004], this image is used to resample for the next octave.

    Image nextOctaveImage(image);
    Image prevScaleImage;
    Image currScaleImage;

    for (int o = 0; o < _octaves; ++o) {
        for (int s = 0; s < 5; ++s) {
            if (s == 0) {
                currScaleImage = convolveGaussian2D(gaussian, nextOctaveImage);
            } else {
                currScaleImage = convolveGaussian2D(gaussian, prevScaleImage);
            }

            if (s == 4)  {
                nextOctaveImage = currScaleImage;

                // Uses the algorithm in Section 3 in [Lowe 2004] where we take
                // every other pixel in each row and column.
                resampleImageInPlace(&nextOctaveImage, 2, 2);
            }
            prevScaleImage = std::move(currScaleImage);
        }
    }
}

}
