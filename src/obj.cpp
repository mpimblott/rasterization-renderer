#include "obj.h"

ObjLoader::ObjLoader() { initRNG(); }

void ObjLoader::initRNG() {
  gen = std::mt19937(rd());
  dis = std::uniform_real_distribution<>(0.0, 1.0);
}

shared_ptr<Mesh> ObjLoader::load(const char *file) {
  std::ifstream ifs;
  try {
    // read the input line by line
    ifs.open(file);
    if (ifs.fail()) throw;
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string line;

    bool autoColourFaces = false;

    unique_ptr<std::vector<Point3h>> vertices = make_unique<std::vector<Point3h>>();
    unique_ptr<std::vector<Point3h>> normals = make_unique<std::vector<Point3h>>();
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
        parse_face(lineStream, triangles);
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

    shared_ptr<Mesh> mesh_out = make_shared<Mesh>(Mesh(std::move(triangles), std::move(vertices), std::move(normals),
                                                       std::move(textureCoordinates), std::move(vertexColours)));
    return mesh_out;
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

void ObjLoader::parse_face(std::stringstream &ss, unique_ptr<std::vector<Triangle>> &triangles) {
  std::string chunk;
  bool faceRequiresColour = false;
  size_t vertexCount = find_n_stringstream_chunks(ss);

  if (vertexCount == 4) {
    std::array<size_t, 4> vertexIndices;
    std::array<size_t, 4> colourIndices;
    std::array<size_t, 4> normalIndices;
    std::array<size_t, 4> textureCoordIndices;

    size_t currentIdx = 0;
    while (ss >> chunk) {
      std::replace(chunk.begin(), chunk.end(), '/', ' ');
      std::stringstream chunkStream(chunk);
      size_t nVertexPropertiesProvided = find_n_stringstream_chunks(chunkStream);
      if (nVertexPropertiesProvided == 1) {
        // only vertex information is provided, no colour, texture or normal information given
        // assert(false && "1 face property not tested");
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
        // size_t vertexId;
        // size_t textureId;
        // size_t normalId;
        // chunkStream >> vertexId >> textureId >> normalId;
        // vertexId--;
        // textureId--;
        // normalId--;
        // vertexIndices[currentIdx] = vertexId;
        // textureCoordIndices[currentIdx] = textureId;
        // normalIndices[currentIdx] = normalId;
      } else {
        assert(false && "unsupported number of vertex parameters provided in face definition");
      }
      currentIdx++;
    }
    if (faceRequiresColour)
    {
      coloursRequired++;
    }
    std::cerr << "building triangle" << std::endl;
    std::array<size_t, 3> vertexIndicesA({vertexIndices[0], vertexIndices[1], vertexIndices[2]});
    std::array<size_t, 3> colourIndicesA({colourIndices[0], colourIndices[1], colourIndices[2]});
    std::array<size_t, 3> normalIndicesA({normalIndices[0], normalIndices[1], normalIndices[2]});
    std::array<size_t, 3> textureCoordIndicesA(
        {textureCoordIndices[0], textureCoordIndices[1], textureCoordIndices[2]});
    std::array<size_t, 3> vertexIndicesB({vertexIndices[0], vertexIndices[2], vertexIndices[3]});
    std::array<size_t, 3> colourIndicesB({colourIndices[0], colourIndices[2], colourIndices[3]});
    std::array<size_t, 3> normalIndicesB({normalIndices[0], normalIndices[2], normalIndices[3]});
    std::array<size_t, 3> textureCoordIndicesB(
        {textureCoordIndices[0], textureCoordIndices[2], textureCoordIndices[3]});
    Triangle triA(vertexIndicesA, textureCoordIndicesA, normalIndicesA, colourIndicesA);
    Triangle triB(vertexIndicesB, textureCoordIndicesB, normalIndicesB, colourIndicesB);
    triangles->push_back(triA);
    triangles->push_back(triB);
  }

  if (vertexCount == 3) {
    std::array<size_t, 3> vertexIndices;
    std::array<size_t, 3> colourIndices;
    std::array<size_t, 3> normalIndices;
    std::array<size_t, 3> textureCoordIndices;

    /*
     * process each block, which has the form: x/x/x
     * default obj spec is vertex/vertexTexture/vertexNormal with '/' remaining when value
     * is not provided
     * in the case no '/' is left, we will use this for auto-generating random colours
     */
    size_t currentIdx = 0;
    while (ss >> chunk) {
      std::replace(chunk.begin(), chunk.end(), '/', ' ');
      std::stringstream chunkStream(chunk);
      size_t nVertexPropertiesProvided = find_n_stringstream_chunks(chunkStream);
      if (nVertexPropertiesProvided == 1) {
        // only vertex information is provided, no colour, texture or normal information given
        // size_t vertexId;
        // chunkStream >> vertexId;
        // vertexId--;
        // vertexIndices[currentIdx] = vertexId;
        assert(false && "1 face property not tested");
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
        // size_t vertexId;
        // size_t textureId;
        // size_t normalId;
        // chunkStream >> vertexId >> textureId >> normalId;
        // vertexId--;
        // textureId--;
        // normalId--;
        // vertexIndices[currentIdx] = vertexId;
        // textureCoordIndices[currentIdx] = textureId;
        // normalIndices[currentIdx] = normalId;
      } else {
        assert(false && "unsupported number of vertex parameters provided in face definition");
      }
      currentIdx++;
    }
    std::cerr << "building triangle" << std::endl;
    Triangle tri(vertexIndices, textureCoordIndices, normalIndices, colourIndices);
    triangles->push_back(tri);
  }
}

Point3h ObjLoader::parse_vertex(std::stringstream &ss) {
  Point3h vertex;
  ss >> vertex.x() >> vertex.y() >> vertex.z();
  std::cerr << "v: " << vertex << std::endl;
  return vertex;
}

ColourRGB ObjLoader::random_colour() {
  return ColourRGB({(float)dis(gen), (float)dis(gen), (float)dis(gen)});
}
