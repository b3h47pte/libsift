// Copyright 2017 Michael Bao. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file. The SIFT algorithm is
// patented and its use for commercial applications must be licensed.
// See the LICENSE file for details.

#include "image.h"
#include <memory>

namespace sift
{

/*! A 2D Gaussian filter type.
 */
class Gaussian2D
{
public:
    explicit Gaussian2D(const std::shared_ptr<Image>& img);
private:
    std::shared_ptr<Image> _filter;
};

/*! Creates a 2D Gaussian operator that can be convolved with an image.
 *  @param[in] stddev The 'sigma' of the Gaussian function. 
 *  @return An 'Image' object that contains an appropriately sized 2D Gaussian operator.
 */
Gaussian2D create2DGaussian(const float stddev);

/*! Convolve a 2D Gaussian with an image while taking advantage of the fact that
 *  the kernel is separable.
 *  @param[in] gaussian The Gaussian to use for convolution.
 *  @param[in] image The image to convolve the Gaussian with.
 *  @return A new image that contains the convolved image data.
 */
Image convolveGaussian2D(const Gaussian2D& gaussian, const Image& image);

/*! Convolve a 2D Gaussian with an image while taking advantage of the fact that
 *  the kernel is separable.
 *  @param[in] gaussian The Gaussian to use for convolution.
 *  @param[in,out] image The image to convolve the Gaussian with. Result is stored in this image.
 */
void convolveGaussian2DInPlace(const Gaussian2D& gaussian, Image* image);

/*! The Difference of Gaussian (DoG) Scale Space Pyramid described in [Lowe 2004]
 *  in Section 3.
 */
class DoGScaleSpacePyramid
{
public:
    /*! Creates a DoG scale-space pyramid as described by [Lowe 2004].
     *  @param[in] image The original image to create the pyramid from.
     *  @param[in] octaves The number of octaves to use in the pyramid. 
     *                     If -1, computes the number of octaves automatically
     *                     from the size of the image.
     *  @param[in] stddev The initial std dev of the Gaussian at each octave.
     */
    DoGScaleSpacePyramid(const Image& image, int octaves = -1, float stddev = 1.6f);

    /*! Does the work in actually creating the pyramid given the stored number of octaves, and stddev.
     *  @param[in] The original image to create the pyramid from.
     */
    void initialize(const Image& image);

private:
    /*! Difference of Gaussian images. Indexed first by octave, then by scale space sample.
     */
    std::vector<std::vector<std::shared_ptr<Image> > > _dogs;

    int _octaves;
    float _stddev;
};

}
