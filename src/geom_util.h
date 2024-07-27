#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <algorithm>

#include "geometry.h"
#include "point.h"
#include "vector.h"

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

Matf4 RotateAboutX(float radians);
Matf4 RotateAboutY(float radians);
Matf4 RotateAboutZ(float radians);

shared_ptr<Mesh> loadGeoFile(const char *file);

shared_ptr<Mesh> objLoader(const char *file);