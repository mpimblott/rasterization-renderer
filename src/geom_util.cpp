#include "geom_util.h"

Matf4 RotateAboutX(float radians)
{
  Matf4 tmp = {
      {1, 0, 0, 0},
      {0, std::cos(radians), std::sin(radians), 0},
      {0, -1 * std::sin(radians), std::cos(radians), 0},
      {0, 0, 0, 1}};
  return tmp;
}

Matf4 RotateAboutY(float radians)
{
  Matf4 tmp = {
      {std::cos(radians), 0, -1 * std::sin(radians), 0},
      {0, 1, 0, 0},
      {std::sin(radians), 0, std::cos(radians), 0},
      {0, 0, 0, 1}};
  return tmp;
}

Matf4 RotateAboutZ(float radians)
{
  Matf4 tmp = {
      {std::cos(radians), std::sin(radians), 0, 0},
      {0, -1 * std::sin(radians), std::cos(radians), 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}};
  return tmp;
}

shared_ptr<Mesh> loadGeoFile(const char *file)
{
  std::ifstream ifs;
  try
  {
    ifs.open(file);
    if (ifs.fail())
      throw;
    std::stringstream ss;
    ss << ifs.rdbuf();
    size_t numFaces;
    // >> shifts the internal pointer, stops at whitespace
    ss >> numFaces;
    std::cerr << "Mesh has " << numFaces << " faces " << std::endl;
    unique_ptr<std::vector<size_t>> verticesPerFace = make_unique<std::vector<size_t>>(numFaces);
    size_t vertsIndexArraySize = 0;

    // reading face index array
    // face index array stores the number of vertices in each face
    for (uint32_t i = 0; i < numFaces; i++)
    {
      ss >> (*verticesPerFace)[i];
      vertsIndexArraySize += (*verticesPerFace)[i];
      std::cerr << (*verticesPerFace)[i] << std::endl;
      vertsIndexArraySize += 1;
    }
    std::cerr << "Number of vertices (incl repeats): " << vertsIndexArraySize << std::endl;
    // stores the vertex ordering data
    unique_ptr<std::vector<size_t>> vertexOrderingIndices = make_unique<std::vector<size_t>>(vertsIndexArraySize);
    uint32_t numVertices = 0;

    // reading vertex index array
    for (uint32_t i = 0; i < vertsIndexArraySize; i++)
    {
      ss >> (*vertexOrderingIndices)[i];
      if ((*vertexOrderingIndices)[i] > numVertices)
        numVertices = (*vertexOrderingIndices)[i]; // track the largest vertex index
      std::cerr << (*vertexOrderingIndices)[i] << std::endl;
    }
    numVertices += 1;
    std::cerr << "Max verts index " << numVertices << std::endl;

    // reading vertices
    unique_ptr<std::vector<Point3h>> vertices = make_unique<std::vector<Point3h>>(numVertices);
    for (uint32_t i = 0; i < numVertices; i++)
    {
      ss >> (*vertices)[i].x() >> (*vertices)[i].y() >> (*vertices)[i].z();
      std::cerr << (*vertices)[i] << std::endl;
    }

    // reading normals
    std::cerr << "Reading normals\n";
    unique_ptr<std::vector<Point3h>> normals = make_unique<std::vector<Point3h>>(numFaces);
    for (uint32_t i = 0; i < numFaces; i++)
    {
      ss >> (*normals)[i].x() >> (*normals)[i].y() >> (*normals)[i].z();
      std::cerr << (*normals)[i] << std::endl;
    }

    // reading st coordinates
    std::cerr << "Reading texture coordinates\n";
    unique_ptr<std::vector<Vec<float, 2>>> textureCoordinates = make_unique<std::vector<Vec<float, 2>>>(vertsIndexArraySize);
    for (uint32_t i = 0; i < vertsIndexArraySize; i++)
    {
      ss >> (*textureCoordinates)[i][0] >> (*textureCoordinates)[i][1];
      std::cerr << (*textureCoordinates)[i] << std::endl;
    }
    shared_ptr<Mesh> mesh_out = make_shared<Mesh>(Mesh(
        std::move(verticesPerFace),
        vertsIndexArraySize,
        std::move(vertexOrderingIndices),
        std::move(vertices),
        std::move(normals),
        std::move(textureCoordinates)));
  ifs.close();
  return mesh_out;
  }
  catch (...)
  {
    ifs.close();
    assert(false && "Error reading mesh file.");
  }
}