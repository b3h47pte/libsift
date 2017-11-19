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

TEST_CASE("Image input output equivalence", "[imageio]") {
    sift::Image image, cmpImage;
    bfs::path tmpPath = bfs::unique_path();
    std::string tmpStr = tmpPath.native();
    std::string outFname = tmpStr + ".png";

    SECTION("redsquare.png") {
        image.loadFromFile("data/redsquare.png");
    }

    SECTION("hedgehog.tiff") {
        image.loadFromFile("data/hedgehog.tiff");
    }

    SECTION("league.jpg") {
        image.loadFromFile("data/league.jpg");
    }

    SECTION("anime.bmp") {
        image.loadFromFile("data/anime.bmp");
    }

    image.saveToFile(outFname);
    cmpImage.loadFromFile(outFname);
    REQUIRE(image == cmpImage);
    bfs::remove(bfs::path(outFname));
}
