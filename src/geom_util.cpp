#include "geom_util.h"

Matf4 RotateAboutX(float radians) {
  Matf4 tmp = {{1, 0, 0, 0},
               {0, std::cos(radians), std::sin(radians), 0},
               {0, -1 * std::sin(radians), std::cos(radians), 0},
               {0, 0, 0, 1}};
  return tmp;
}

Matf4 RotateAboutY(float radians) {
  Matf4 tmp = {{std::cos(radians), 0, -1 * std::sin(radians), 0},
               {0, 1, 0, 0},
               {std::sin(radians), 0, std::cos(radians), 0},
               {0, 0, 0, 1}};
  return tmp;
}

Matf4 RotateAboutZ(float radians) {
  Matf4 tmp = {{std::cos(radians), std::sin(radians), 0, 0},
               {0, -1 * std::sin(radians), std::cos(radians), 0},
               {0, 0, 1, 0},
               {0, 0, 0, 1}};
  return tmp;
}

// shared_ptr<Mesh> loadGeoFile(const char *file) {
//   std::ifstream ifs;
//   try {
//     ifs.open(file);
//     if (ifs.fail()) throw;
//     std::stringstream ss;
//     ss << ifs.rdbuf();
//     size_t numFaces;
//     // >> shifts the internal pointer, stops at whitespace
//     ss >> numFaces;
//     std::cerr << "Mesh has " << numFaces << " faces " << std::endl;
//     size_t vertsIndexArraySize = numFaces * 3;

//     std::cerr << "Number of vertices (incl repeats): " << vertsIndexArraySize << std::endl;
//     // stores the vertex ordering data
//     unique_ptr<std::vector<size_t>> vertexOrderingIndices = make_unique<std::vector<size_t>>(vertsIndexArraySize);
//     uint32_t numUniqueVertices = 0;

//     // reading vertex index array
//     for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
//       ss >> (*vertexOrderingIndices)[i];
//       if ((*vertexOrderingIndices)[i] > numUniqueVertices)
//         numUniqueVertices = (*vertexOrderingIndices)[i];  // track the largest vertex index
//       std::cerr << (*vertexOrderingIndices)[i] << std::endl;
//     }
//     numUniqueVertices += 1;
//     std::cerr << "Max verts index " << numUniqueVertices << std::endl;

//     // reading vertices
//     unique_ptr<std::vector<Point3h>> vertices = make_unique<std::vector<Point3h>>(numUniqueVertices);
//     for (uint32_t i = 0; i < numUniqueVertices; i++) {
//       ss >> (*vertices)[i].x() >> (*vertices)[i].y() >> (*vertices)[i].z();
//       std::cerr << (*vertices)[i] << std::endl;
//     }

//     // reading normals
//     std::cerr << "Reading normals\n";
//     unique_ptr<std::vector<Point3h>> normals = make_unique<std::vector<Point3h>>(vertsIndexArraySize);
//     for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
//       ss >> (*normals)[i].x() >> (*normals)[i].y() >> (*normals)[i].z();
//       std::cerr << (*normals)[i] << std::endl;
//     }

//     // reading st coordinates
//     std::cerr << "Reading texture coordinates\n";
//     unique_ptr<std::vector<Vec<float, 2>>> textureCoordinates =
//         make_unique<std::vector<Vec<float, 2>>>(vertsIndexArraySize);
//     for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
//       ss >> (*textureCoordinates)[i][0] >> (*textureCoordinates)[i][1];
//       std::cerr << (*textureCoordinates)[i] << std::endl;
//     }

//     // read vertex colours
//     std::cerr << "Reading vertex colours\n";
//     unique_ptr<std::vector<Vec<float, 3>>> vertexColours = make_unique<std::vector<Vec<float,
//     3>>>(vertsIndexArraySize); for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
//       ss >> (*vertexColours)[i][0] >> (*vertexColours)[i][1] >> (*vertexColours)[i][2];
//       std::cerr << (*vertexColours)[i] << std::endl;
//     }

//     shared_ptr<Mesh> mesh_out =
//         make_shared<Mesh>(Mesh(vertsIndexArraySize, std::move(vertexOrderingIndices), std::move(vertices),
//                                std::move(normals), std::move(textureCoordinates), std::move(vertexColours)));

//     // reading colours
//     ifs.close();
//     return mesh_out;
//   } catch (...) {
//     ifs.close();
//     assert(false && "Error reading mesh file.");
//   }
// }

shared_ptr<Mesh> objLoader(const char *file) {
  std::ifstream ifs;
  try {
    // read the input line by line
    ifs.open(file);
    if (ifs.fail()) throw;
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string line;
    size_t nFaces = 0;
    unique_ptr<std::vector<Point3h>> vertices = make_unique<std::vector<Point3h>>();
    unique_ptr<std::vector<Point3h>> normals = make_unique<std::vector<Point3h>>();
    unique_ptr<std::vector<TextureCoord>> textureCoordinates = make_unique<std::vector<TextureCoord>>();
    unique_ptr<std::vector<ColourRGB>> vertexColours = make_unique<std::vector<ColourRGB>>();
    unique_ptr<std::vector<Triangle>> triangles = make_unique<std::vector<Triangle>>();

    while (std::getline(ss, line)) {
      std::stringstream lineStream(line);
      std::string type;
      lineStream >> type;
      size_t highestVertexIdx = 0;
      if (type == "#") {
        continue;
      } else if (type == "v") {
        // vertex positioning data -  these are repeated positions that may be shared among several faces of a mesh
        Point3h vertex;
        lineStream >> vertex.x() >> vertex.y() >> vertex.z();
        std::cerr << "v: " << vertex << std::endl;
        vertices->push_back(vertex);
      } else if (type == "f") {

        // face data
        nFaces++;
        std::string chunk;
        std::string vertexIndex;
        std::string colourIndex;
        size_t vertexCount = 0;

        std::array<size_t, 3> vertexIndices;
        std::array<size_t, 3> colourIndices;
        std::array<size_t, 3> normalIndices;
        std::array<size_t, 3> textureCoordIndices;

        while (lineStream >> chunk) {
          std::replace(chunk.begin(), chunk.end(), '/', ' ');
          std::stringstream vertexIndexStream(chunk);
          size_t vertexIndex;
          size_t colourIndex;
          vertexIndexStream >> vertexIndex >> colourIndex;
          vertexIndex--;
          colourIndex--;
          vertexIndices[vertexCount] = vertexIndex;
          colourIndices[vertexCount] = colourIndex;
          vertexCount++;
        }
        std::cerr << "building triangle" << std::endl;
        Triangle tri(vertexIndices, textureCoordIndices, normalIndices, colourIndices);
        triangles->push_back(tri);
        std::cerr << "f: " << tri << std::endl;
      } else if (type == "vc") {
        ColourRGB col;
        lineStream >> col[0] >> col[1] >> col[2];
        vertexColours->push_back(col);
      }
    }

    shared_ptr<Mesh> mesh_out =
        make_shared<Mesh>(Mesh(nFaces, std::move(triangles), std::move(vertices),
                               std::move(normals), std::move(textureCoordinates), std::move(vertexColours)));
    return mesh_out;
  } catch (...) {
    ifs.close();
    assert(false && "Error reading mesh file.");
  }
}