// Copyright 2017 Michael Bao. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file. The SIFT algorithm is
// patented and its use for commercial applications must be licensed.
// See the LICENSE file for details.

#include <boost/filesystem.hpp>
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include <cstdio>
#include "image.h"
#include <iostream>

namespace bfs = boost::filesystem;

TEST_CASE("Image constructor and data allocation", "[imageio]") {
    sift::Image img;
    CHECK(img.getWidth() == 0);
    CHECK(img.getHeight() == 0);
    CHECK(img.getChannels() == 0);
    CHECK(img.getBufferSize() == 0);

    img.resizeImage(10, 20, 3);
    CHECK(img.getWidth() == 10);
    CHECK(img.getHeight() == 20);
    CHECK(img.getChannels() == 3);
    CHECK(img.getBufferSize() == 600);

    sift::Image img2(10, 20, 3);
    CHECK(img2.getWidth() == 10);
    CHECK(img2.getHeight() == 20);
    CHECK(img2.getChannels() == 3);
    CHECK(img2.getBufferSize() == 600);
}

TEST_CASE("Image read write equivalence", "[imageio]") {
    sift::Image image, cmpImage;
    bfs::path tmpPath = bfs::unique_path();
    std::string tmpStr = tmpPath.native();
    std::string outFname = tmpStr + ".png";

    SECTION("redsquare.png") {
        image.loadFromFile("../../data/redsquare.png");
    }

    SECTION("hedgehog.tiff") {
        image.loadFromFile("../../data/hedgehog.tiff");
    }

    SECTION("league.jpg") {
        image.loadFromFile("../../data/league.jpg");
    }

    SECTION("anime.bmp") {
        image.loadFromFile("../../data/anime.bmp");
    }

    image.saveToFile(outFname);
    cmpImage.loadFromFile(outFname);
    REQUIRE(image == cmpImage);
    bfs::remove(bfs::path(outFname));
}

TEST_CASE("Image read color correctness", "[imageio]") {
    sift::Image image;

    SECTION("redsquare.png") {
        image.loadFromFile("../../data/redsquare.png");
        CHECK(image.getColor(161, 158, 0) == 255);
        CHECK(image.getColor(161, 158, 1) == 0);
        CHECK(image.getColor(161, 158, 2) == 0);
    }
}

TEST_CASE("Image IO Failure", "[imageio]") {
    sift::Image image;
    REQUIRE_THROWS_AS(image.loadFromFile("THIS_SHOULD_FAIL.HELLO"), sift::ImageIOException);
    REQUIRE_THROWS_AS(image.loadFromFile(""), sift::ImageIOException);
}
