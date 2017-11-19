// Copyright 2017 Michael Bao. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file. The SIFT algorithm is
// patented and its use for commercial applications must be licensed.
// See the LICENSE file for details.
#include <exception>
#include <sstream>
#include <string>
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

/*! \brief Wrapper class around the functionality that OpenImageIO provides.
 *
 *  A simple image class that stores byte image data along with the size of the image.
 */
class Image
{
public:
    /*! Creates an empty image that has zero pixels in it.
     */
    Image();

    /*! Allocates memory for an image that is of size (width, height) the specified
     *  number of channels.
     *  @param[in] width Width of the image.
     *  @param[in] height Height of the image.
     *  @param[in] channels Number of image color channels.
     */
    Image(const int width, const int height, const int channels);

    /*! Resizes the image to contain the specified amount of data.
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

private:
    std::vector<unsigned char> _data; 
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

}
