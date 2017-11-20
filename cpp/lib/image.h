// Copyright 2017 Michael Bao. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file. The SIFT algorithm is
// patented and its use for commercial applications must be licensed.
// See the LICENSE file for details.
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

namespace sift
{

/*! \brief An exception class that gets thrown by the Image class during IO operations.
 *
 */
class ImageIOException: public std::runtime_error
{
public:
    explicit ImageIOException(const std::string& err):
        std::runtime_error(err)
    {}
    virtual ~ImageIOException() throw() {}
    const char* what() const throw() override;
};

/*! \brief Called 'Image' but in effect is can represent any 3D floating point data.
 *
 *  Stores a tensor of size (width, height, channels). Provides functionality to load in an image
 *  OpenImageIO.
 */
class Image
{
public:
    /*! Creates an empty image that has zero pixels in it.
     */
    Image();

    Image(const Image& other) = default;
    Image& operator=(const Image& other) = default;

    Image(Image&& other) = default;
    Image& operator=(Image&& other) = default;

    /*! Allocates memory for an image that is of size (width, height) the specified
     *  number of channels.
     *  @param[in] width Width of the image.
     *  @param[in] height Height of the image.
     *  @param[in] channels Number of image color channels.
     */
    Image(const int width, const int height, const int channels);

    /*! Resizes the buffer to contain the specified amount of data.
     *  @param[in] width Width of the image.
     *  @param[in] height Height of the image.
     *  @param[in] channels Number of image color channels.
     */
    void resizeImage(const int width, const int height, const int channels);

    /*! Loads an image from the given filename.
     *  @param[in] fname The filename to load an image from. Must be a format that
     *                   OpenImageIO supports.
     */
    void loadFromFile(const std::string& fname);

    /*! Saves the stored image to the given filename.
     * @param[in] fname The filename to save the image to. Must be a format that
     *                  OpenImageIO support.
     */
    void saveToFile(const std::string& fname) const;

    /*! Checks for equality in size and data between the two images.
     * @param[in] rhs Other image to compare to.
     * @return True if all members are equivalent. False otherwise.
     */
    bool operator==(const Image& rhs) const;

    /*! Checks for inequality in size and data between the two images.
     * @param[in] rhs Other image to compare to.
     * @return True if all members are different. False otherwise.
     */
    bool operator!=(const Image& rhs) const;

    /*! Retrieves width of image.
     * @return Width of the image in pixels.
     */
    int getWidth() const { return _width; }

    /*! Retrieves height of image.
     * @return Height of the image in pixels.
     */
    int getHeight() const { return _height; }

    /*! Retrieves the number of channels.
     * @return Number of color channels.
     */
    int getChannels() const { return _channels; }

    /*! Retrieves the size of the data buffer.
     * @return Size of the data buffer in bytes.
     */
    size_t getBufferSize() const { return _data.size(); }

    /*! Retrieves data from the stored data.
     * @param x The column of the image to query.
     * @param y The row of the image to query.
     * @param channel Which color channel to query.
     * @return The element in the _data member indexed by x, y, and channel.
     */
    float getColor(int x, int y, int channel) const;

    /*! Sets data into the underlying buffer.
     * @param[in] value The value to set in the buffer.
     * @param[in] x The column of the image to set.
     * @param[in] y The row of the image to set.
     * @param[in] channel Which color channel to set.
     */
    void setColor(float value, int x, int y, int channel);

    /*! Retrieves data from the stored data but casted to a byte. Conversion is done by
     *  multiplying by 255 and clamping to be between 0 and 255.
     * @param[in] x The column of the image to query.
     * @param[in] y The row of the image to query.
     * @param[in] channel Which color channel to query.
     * @return The element in the _data member indexed by x, y, and channel casted.
     */
    unsigned char getCastedColor(int x, int y, int channel) const;

protected:

    /*! Retrieves the appropriate idex into the buffer.
     * @param x The column of the image to query.
     * @param y The row of the image to query.
     * @param channel Which color channel to query.
     * @return The sequential index into the buffer to for (x, y, channel).
     */
    int getBufferIndex(int x, int y, int channel) const;

private:
    std::vector<float> _data; 
    int _width;
    int _height;
    int _channels;
};

inline const char* ImageIOException::what() const throw()
{
    std::ostringstream buff;
    buff << "[ImageIO]: " << std::runtime_error::what();
    return buff.str().c_str();
}

inline bool Image::operator!=(const Image& rhs) const
{
    return !(*this == rhs);
}

inline int Image::getBufferIndex(int x, int y, int channel) const
{
    return channel + x * _channels + y * _channels * _width;
}

inline float Image::getColor(int x, int y, int channel) const
{
    // Clamp at the edge.
    x = std::min(std::max(x, 0), getWidth());
    y = std::min(std::max(y, 0), getHeight());
    return _data[getBufferIndex(x, y, channel)];
}

inline void Image::setColor(float value, int x, int y, int channel)
{
    _data[getBufferIndex(x, y, channel)] = value;
}

inline unsigned char Image::getCastedColor(int x, int y, int channel) const
{
    const float data = std::min(std::max(255.f * getColor(x, y, channel), 0.0f), 255.0f);
    return static_cast<unsigned char>(data);
}

/*! Performs a naive resample of the image.
 *  @param[in] image Image to resample.
 *  @param[in] fx Gets every fx columns.
 *  @param[in] fy Gets every fy rows.
 *  @return The resampled image.
 */
Image resampleImage(const Image& image, float fx, float fy);
void resampleImageInPlace(Image* image, float fx, float fy);

}
