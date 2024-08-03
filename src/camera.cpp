#include "camera.h"

Camera::Camera(size_t width, size_t height, float fov, float nearClipping, float farClipping)
    : pixelWidth(width),
      pixelHeight(height),
      fov(fov),
      nearClippingDistance(nearClipping),
      farClippingDistance(farClipping) {
    init();
}

void Camera::init() {
    Id(worldToCamera);
    worldToCamera[2][2] = 1;
    recompute_projection_mat();
}

const Matf4 &Camera::world_to_cam_mat() const { return worldToCamera; }

const Matf4 Camera::cam_to_world_mat() const { return inv(worldToCamera); }

const Matf4 &Camera::projection_mat() const { return projectionMat; }

void Camera::set_near_clipping_distance(float distance) {
    nearClippingDistance = distance;
    recompute_projection_mat();
}

void Camera::set_far_clipping_distance(float distance) {
    farClippingDistance = distance;
    recompute_projection_mat();
}

void Camera::set_fov(float angle) {
    fov = angle;
    recompute_projection_mat();
}

void Camera::recompute_projection_mat() {
    // this matrix maps from screen space to NDC space ([-1,1]) accounting for
    // clipping and fov should be pre-multiplication by worldToCam and after
    // should be normalised to [0, 1] for raster space
    float s = (static_cast<float>(1 / tan((fov * 0.5 * pi) / 180)));
    projectionMat = {
        {s, 0, 0, 0},
        {0, s, 0, 0},
        {0, 0, (-1 * farClippingDistance) / (farClippingDistance - nearClippingDistance), -1},
        {0, 0, (-1 * farClippingDistance * nearClippingDistance) / (farClippingDistance - nearClippingDistance), 0}};
}

void Camera::set_pos(Point3 &p) {
    // build the translation matrix from the default position to the desired point
    worldToCamera[3][0] = p[0] - defaultPos[0];
    worldToCamera[3][1] = p[1] - defaultPos[1];
    worldToCamera[3][2] = p[2] - defaultPos[2];
}

Point3 Camera::get_pos() const { return Point3(worldToCamera[3][0], worldToCamera[3][1], worldToCamera[3][2]); }

// std::vector<Point3h> Camera::project_vertices(const std::vector<Point3h> &vertices) {
//     std::vector<Point3h> projected_vertices(vertices.size());
//     for (size_t i = 0; i < vertices.size(); i++) {
//         Point3h p;
//         vertex_shader(vertices[i], projection_mat(), world_to_cam_mat(), p);
//         projected_vertices[i] = p;
//     }
//     return projected_vertices;
// }

std::vector<Point3h> Camera::project_vertices(const std::vector<Point3h> &vertices) {
    std::vector<Point3h> projected_vertices(vertices.size());
    for (size_t i = 0; i < vertices.size(); i++) {
        Point3h p;
        vertex_shader(vertices[i], projection_mat(), world_to_cam_mat(), p);
        projected_vertices[i] = p;
    }
    return projected_vertices;
}

std::vector<float> Camera::build_img_buffer(const Mesh &mesh) {
    std::vector<Point3h> projectedVertices = project_vertices(mesh.get_vertices());
    // for (auto &v : projectedVertices) {
    //     std::cerr << v << std::endl;
    // }
    // screen buffers
    std::vector<float> buffer(pixelWidth * pixelHeight * 3);
    std::vector<float> depthBuffer(pixelWidth * pixelHeight, std::numeric_limits<float>::max());


    const size_t nFaces = mesh.get_n_faces();
    std::cerr << "mesh has " << nFaces << " faces." << std::endl;
    for (size_t f = 0; f < nFaces; f++) {
        // std::cerr << "processing face " << f << ", ";
        // std::cerr << "face has " << mesh.get_triangle(f).nVertices << " vertices: ";
        const size_t startVertIdx = f * 3;  // 3 vertices in a triangle
        const Triangle &triangle = mesh.get_triangle(f);
        // std::cerr << triangle.vertexIndices[0] << ", " << triangle.vertexIndices[1] << ", " << triangle.vertexIndices[2] << std::endl;
        const Point3h &p0 = projectedVertices[triangle.vertexIndices[0]];
        const Point3h &p1 = projectedVertices[triangle.vertexIndices[1]];
        const Point3h &p2 = projectedVertices[triangle.vertexIndices[2]];
        size_t xmax;
        size_t xmin;
        size_t ymax;
        size_t ymin;
        std::tie(xmax, xmin, ymax, ymin) = triangle_raster_bbox(p0, p1, p2, pixelWidth, pixelHeight);

        for (size_t y = ymin; y < ymax; y++) {
            for (size_t x = xmin; x < xmax; x++) {
                Point3h p = Point3h(x, y, 1000000);
                size_t bufferIdx = y * pixelWidth * 3 + 3 * x;

                ColourRGB c0 = mesh.get_vertex_colour(triangle.vertexColourIndices[0]);
                ColourRGB c1 = mesh.get_vertex_colour(triangle.vertexColourIndices[1]);
                ColourRGB c2 = mesh.get_vertex_colour(triangle.vertexColourIndices[2]);

                // perspective-correct vertex attribute interpolation
                c0[0] /= p0[2], c0[1] /= p0[2], c0[2] /= p0[2];
                c1[0] /= p1[2], c1[1] /= p1[2], c1[2] /= p1[2];
                c2[0] /= p2[2], c2[1] /= p2[2], c2[2] /= p2[2];

                // vertex z-coordinate inversion
                // p0[2] = 1 / p0[2], p1[2] = 1 / p1[2], p2[2] = 1 / p2[2];
                float p0z_inverted = 1 / p0[2];
                float p1z_inverted = 1 / p1[2];
                float p2z_inverted = 1 / p2[2];

                // compute the pineda edge function of various proper and improper sub-triangles
                float area = pineda_edge(p0, p1, p2);
                float w0 = pineda_edge(p, p1, p2);
                float w1 = pineda_edge(p, p2, p0);
                float w2 = pineda_edge(p, p0, p1);

                // find the edges of the triangle
                Point3h edge0 = p2 - p1;
                Point3h edge1 = p0 - p2;
                Point3h edge2 = p1 - p0;

                bool overlaps = true;

                overlaps &= (w0 == 0 ? ((edge0.y() == 0 && edge0.x() > 0) || edge0.y() > 0) : (w0 > 0));
                overlaps &= (w1 == 0 ? ((edge1.y() == 0 && edge1.x() > 0) || edge1.y() > 0) : (w1 > 0));
                overlaps &= (w2 == 0 ? ((edge2.y() == 0 && edge2.x() > 0) || edge2.y() > 0) : (w2 > 0));

                if (overlaps) {
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;

                    float z = 1 / (w0 * p0z_inverted + w1 * p1z_inverted + w2 * p2z_inverted);
                    if (z < depthBuffer[bufferIdx / 3]) {
                        depthBuffer[bufferIdx / 3] = z;
                        ColourRGBA rasterColour;
                        texture_shader(mesh, rasterColour, w0, w1, w2, c0, c1, c2, z);

                        buffer[bufferIdx] = rasterColour[0];
                        buffer[bufferIdx + 1] = rasterColour[1];
                        buffer[bufferIdx + 2] = rasterColour[2];
                    }
                }
            }
        }
    }
    return buffer;
}

float Camera::pineda_edge(const Point3h &p, const Point3h &p0, const Point3h &p1) {
    return (p.x() - p0.x()) * (p1.y() - p0.y()) - (p.y() - p0.y()) * (p1.x() - p0.x());
}

inline std::tuple<size_t, size_t, size_t, size_t> Camera::triangle_raster_bbox(const Point3h &a, const Point3h &b,
                                                                               const Point3h &c, size_t xMaximumLimit,
                                                                               size_t yMaximumLimit) {
    size_t xmax = std::max({a.x(), b.x(), c.x()}) - 1;
    size_t xmin = std::min({a.x(), b.x(), c.x()}) - 1;
    size_t ymax = std::max({a.y(), b.y(), c.y()}) - 1;
    size_t ymin = std::min({a.y(), b.y(), c.y()}) - 1;
    xmax = std::min(xmax + 3, xMaximumLimit);
    xmin = std::max(xmin - 3, (size_t)0);
    ymax = std::min(ymax + 3, yMaximumLimit);
    ymin = std::max(ymin - 3, (size_t)0);
    return {xmax, xmin, ymax, ymin};
}

void Camera::vertex_shader(const Point3h &vertex, const Matf4 &projectionMatrix, const Matf4 &worldToCameraMatrix,
                           Point3h &out) {
    // std::cerr << "Point: " << vertex;
    out = vertex * worldToCameraMatrix;
    // std::cerr << ", cam space: " << out;
    out = out * projectionMatrix;
    // std::cerr << ", NDC space: " << out;
    // if (out.x() < -1 || out.x() > 1 || out.y() < -1 || out.y() > 1) return;
    // convert to raster space
    out.x() = (uint32_t)((out.x() + 1) * 0.5 * pixelWidth);
    out.y() = (uint32_t)((1 - (out.y() + 1) * 0.5) * pixelHeight);
    // std::cerr << ", raster space: " << out << std::endl;
}

void Camera::texture_shader(const Mesh &mesh, ColourRGBA &out, const float &w0, const float &w1, const float &w2,
                            const Vec<float, 3> &c0, const Vec<float, 3> &c1, const Vec<float, 3> &c2, const float &z) {
    float r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
    float g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
    float b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
    r *= z, g *= z, b *= z;
    out[0] = r, out[1] = g, out[2] = b;
}

void Camera::set_look_at(const Point3h &from, const Point3h &to, const Vec3h &arbUp)
{
  Vec3h forward = (from-to).normalise();
  Vec3h right = cross(arbUp, forward).normalise();
  Vec3h up = cross(forward, right).normalise();
  const Matf4 camMove = {
    {right[0], right[1], right[2], 0},
    {up[0], up[1], up[2], 0},
    {forward[0], forward[1], forward[2], 0},
    {from[0], from[1], from[2], 1}};
  // const Matf4 invertZ = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, 1}};
  Matf4 cameraToWorld = camMove;
  worldToCamera = inv(cameraToWorld);
  std::cerr << "worldToCamera: \n" << worldToCamera << std::endl;
}

void ppmRenderer::render(size_t width, size_t height, const std::vector<float> &imgBuffer) {
    // first line of the image file
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j = 0; j < height; j++) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            size_t idx = j * width * 3 + 3 * i;
            std::cout << static_cast<int>(255 * imgBuffer[idx]) << ' ' << static_cast<int>(255 * imgBuffer[idx + 1])
                      << ' ' << static_cast<int>(255 * imgBuffer[idx + 2]) << '\n';
        }
    }
    std::clog << "\rDone.                       \n";
}
