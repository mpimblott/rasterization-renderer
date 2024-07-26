#pragma once

#include <memory>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "vector.h"
#include "point.h"
#include "geometry.h"

using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

Matf4 RotateAboutX(float radians);
Matf4 RotateAboutY(float radians);
Matf4 RotateAboutZ(float radians);

shared_ptr<Mesh> loadGeoFile(const char *file);