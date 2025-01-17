#include "obj.h"

ObjLoader::ObjLoader() { initRNG(); }

void ObjLoader::initRNG() {
  gen = std::mt19937(rd());
  dis = std::uniform_real_distribution<>(0.0, 1.0);
}

shared_ptr<VertexColourDecorator> ObjLoader::load(const char *file) {
  std::ifstream ifs;
  try {
    // read the input line by line
    ifs.open(file);
    if (ifs.fail()) throw;
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string line;

    unique_ptr<std::vector<Point3h>> vertices = make_unique<std::vector<Point3h>>();
    unique_ptr<std::vector<TextureCoord>> textureCoordinates = make_unique<std::vector<TextureCoord>>();
    unique_ptr<std::vector<ColourRGB>> vertexColours = make_unique<std::vector<ColourRGB>>();
    unique_ptr<std::vector<Triangle>> triangles = make_unique<std::vector<Triangle>>();

    while (std::getline(ss, line)) {
      std::stringstream lineStream(line);
      std::string type;
      // ----------
      // clear the type flag from the start of the stringstream
      lineStream >> type;
      std::string lineStreamContent = lineStream.str();
      if (!lineStreamContent.empty()) {
        lineStreamContent.erase(0, 2);
      }
      lineStream.str(lineStreamContent);
      lineStream.clear();
      lineStream.seekg(0);
      // ---------
      if (type == "#") {
        continue;
      } else if (type == "v") {
        // vertex positioning data -  these are repeated positions that may be shared among several faces of a mesh
        Point3h vertex = parse_vertex(lineStream);
        vertices->push_back(vertex);
      } else if (type == "f") {
        parse_face(lineStream, *triangles);
      } else if (type == "vc") {
        ColourRGB col;
        lineStream >> col[0] >> col[1] >> col[2];
        vertexColours->push_back(col);
      }
    }

    if (coloursRequired > 0) {
      // colour definitions are needed to colour vertices without given colours
      for (size_t i = 0; i < coloursRequired; i++) {
        vertexColours->push_back(random_colour());
      }
      coloursRequired = 0;
    }

    unique_ptr<std::vector<Point3h>> normals = make_unique<std::vector<Point3h>>(triangles->size());
    if (computeSmoothNormals) {
      compute_rough_normals(*triangles, *vertices, *normals);
    }

    shared_ptr<MeshData> data = make_shared<MeshData>(std::move(triangles), std::move(vertices));
    unique_ptr<Mesh> mesh = make_unique<Mesh>(data);
    unique_ptr<VertexColourDecorator> vertexColourDec =
        make_unique<VertexColourDecorator>(data, std::move(mesh), std::move(vertexColours));
    return vertexColourDec;
  } catch (...) {
    ifs.close();
    assert(false && "Error reading mesh file.");
  }
}

/*
 * find the number of chunks separated by whitespace in a stringstream
 */
size_t ObjLoader::find_n_stringstream_chunks(std::stringstream &ss) { return find_n_stringstream_chunks(ss, ' '); }

/*
 * find number of chunks separated by a set delimiter in a stringstream
 */
size_t ObjLoader::find_n_stringstream_chunks(std::stringstream &ss, char delimiter) {
  std::string ssContent = ss.str();
  size_t count = 0;
  std::string chunk;
  while (getline(ss, chunk, delimiter)) {
    count++;
  }
  ss.clear();
  ss.seekg(0);
  return count;
}

void ObjLoader::parse_face(std::stringstream &ss, std::vector<Triangle> &triangles) {
  size_t vertexCount = find_n_stringstream_chunks(ss);

  if (vertexCount == 4) {
    parse_polygon_face(ss, triangles, 4);
  }

  if (vertexCount == 3) {
    parse_triangle_face(ss, triangles);
  }
}

Point3h ObjLoader::parse_vertex(std::stringstream &ss) {
  Point3h vertex;
  ss >> vertex.x() >> vertex.y() >> vertex.z();
  // std::cerr << "v: " << vertex << std::endl;
  return vertex;
}

ColourRGB ObjLoader::random_colour() { return ColourRGB({(float)dis(gen), (float)dis(gen), (float)dis(gen)}); }

void ObjLoader::compute_rough_normals(std::vector<Triangle> &triangles, const std::vector<Vertex> &vertices,
                                      std::vector<Point3h> &normals) {
  for (size_t i = 0; i < triangles.size(); i++) {
    normals[i] = triangles[i].normal(vertices);
    std::cerr << "computed normal: " << normals[i] << std::endl;
  }
}

void ObjLoader::parse_triangle_face(std::stringstream &ss, std::vector<Triangle> &triangles) {
  bool faceRequiresColour = false;
  std::string chunk;
  std::array<size_t, 3> vertexIndices;
  std::array<size_t, 3> colourIndices;
  std::array<size_t, 3> normalIndices;
  std::array<size_t, 3> textureCoordIndices;

  size_t currentIdx = 0;
  while (ss >> chunk) {
    std::replace(chunk.begin(), chunk.end(), '/', ' ');
    std::stringstream chunkStream(chunk);
    size_t nVertexPropertiesProvided = find_n_stringstream_chunks(chunkStream);
    if (nVertexPropertiesProvided == 1) {
      // only vertex information is provided, no colour, texture or normal information given
      size_t vertexId;
      chunkStream >> vertexId;
      vertexId--;
      vertexIndices[currentIdx] = vertexId;
      colourIndices[currentIdx] = coloursRequired;
      faceRequiresColour = true;
    } else if (nVertexPropertiesProvided == 2) {
      size_t vertexId;
      size_t colourId;
      chunkStream >> vertexId >> colourId;
      vertexId--;
      colourId--;
      vertexIndices[currentIdx] = vertexId;
      colourIndices[currentIdx] = colourId;
    } else if (nVertexPropertiesProvided == 3) {
      assert(false && "3 face properties not tested");
    } else {
      assert(false && "unsupported number of vertex parameters provided in face definition");
    }
    currentIdx++;
  }
  if (faceRequiresColour) {
    coloursRequired++;
  }
  Triangle tri(vertexIndices, textureCoordIndices, normalIndices, colourIndices);
  triangles.push_back(tri);
}

void ObjLoader::parse_polygon_face(std::stringstream &ss, std::vector<Triangle> &triangles, size_t nVertices) {
  bool faceRequiresColour = false;
  std::string chunk;
  std::vector<size_t> vertexIndices(nVertices);
  std::vector<size_t> colourIndices(nVertices);
  std::vector<size_t> normalIndices(nVertices);
  std::vector<size_t> textureCoordIndices(nVertices);

  size_t currentIdx = 0;
  while (ss >> chunk) {
    std::replace(chunk.begin(), chunk.end(), '/', ' ');
    std::stringstream chunkStream(chunk);
    size_t nVertexPropertiesProvided = find_n_stringstream_chunks(chunkStream);
    if (nVertexPropertiesProvided == 1) {
      // only vertex information is provided, no colour, texture or normal information given
      size_t vertexId;
      chunkStream >> vertexId;
      vertexId--;
      vertexIndices[currentIdx] = vertexId;
      colourIndices[currentIdx] = coloursRequired;
      faceRequiresColour = true;
    } else if (nVertexPropertiesProvided == 2) {
      size_t vertexId;
      size_t colourId;
      chunkStream >> vertexId >> colourId;
      vertexId--;
      colourId--;
      vertexIndices[currentIdx] = vertexId;
      colourIndices[currentIdx] = colourId;
    } else if (nVertexPropertiesProvided == 3) {
      assert(false && "3 face properties not tested");
    } else {
      assert(false && "unsupported number of vertex parameters provided in face definition");
    }
    currentIdx++;
  }
  if (faceRequiresColour) {
    coloursRequired++;
  }

  // triangulation
  std::array<size_t, 3> vertexIndicesA({vertexIndices[0], vertexIndices[1], vertexIndices[2]});
  std::array<size_t, 3> colourIndicesA({colourIndices[0], colourIndices[1], colourIndices[2]});
  std::array<size_t, 3> normalIndicesA({normalIndices[0], normalIndices[1], normalIndices[2]});
  std::array<size_t, 3> textureCoordIndicesA({textureCoordIndices[0], textureCoordIndices[1], textureCoordIndices[2]});
  std::array<size_t, 3> vertexIndicesB({vertexIndices[0], vertexIndices[2], vertexIndices[3]});
  std::array<size_t, 3> colourIndicesB({colourIndices[0], colourIndices[2], colourIndices[3]});
  std::array<size_t, 3> normalIndicesB({normalIndices[0], normalIndices[2], normalIndices[3]});
  std::array<size_t, 3> textureCoordIndicesB({textureCoordIndices[0], textureCoordIndices[2], textureCoordIndices[3]});
  Triangle triA(vertexIndicesA, textureCoordIndicesA, normalIndicesA, colourIndicesA);
  Triangle triB(vertexIndicesB, textureCoordIndicesB, normalIndicesB, colourIndicesB);
  triangles.push_back(triA);
  triangles.push_back(triB);
}
