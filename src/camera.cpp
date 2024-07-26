#include "camera.h"

Camera::Camera(size_t width, size_t height, float fov, float nearClipping, float farClipping) : pixelWidth(width),
                                                                                                pixelHeight(height),
                                                                                                fov(fov),
                                                                                                nearClippingDistance(nearClipping),
                                                                                                farClippingDistance(farClipping)
{
  init();
}

void Camera::init()
{
  Id(camMat);
  camMat[2][2] = -1;
  recompute_projection_mat();
}

const Matf4 &Camera::world_to_cam_mat() const
{
  return camMat;
}

const Matf4 Camera::cam_to_world_mat() const
{
  return inv(camMat);
}

const Matf4 &Camera::projection_mat() const
{
  return projectionMat;
}

void Camera::set_near_clipping_distance(float distance)
{
  nearClippingDistance = distance;
  recompute_projection_mat();
}

void Camera::set_far_clipping_distance(float distance)
{
  farClippingDistance = distance;
  recompute_projection_mat();
}

void Camera::set_fov(float angle)
{
  fov = angle;
  recompute_projection_mat();
}

void Camera::recompute_projection_mat()
{
  // this matrix maps from screen space to NDC space ([-1,1]) accounting for clipping and fov
  // should be pre-multiplication by worldToCam and after should be normalised to [0, 1] for raster space
  float s = (static_cast<float>(1 / tan((fov * 0.5 * pi / 180))));
  projectionMat = {{s, 0, 0, 0},
                   {0, s, 0, 0},
                   {0, 0, (-1 * farClippingDistance) / (farClippingDistance - nearClippingDistance), -1},
                   {0, 0, (-1 * farClippingDistance * nearClippingDistance) / (farClippingDistance - nearClippingDistance), 0}};
}

void Camera::set_pos(Point3 &p)
{
  // build the translation matrix from the default position to the desired point
  camMat[3][0] = p[0] - defaultPos[0];
  camMat[3][1] = p[1] - defaultPos[1];
  camMat[3][2] = p[2] - defaultPos[2];
}

Point3 Camera::get_pos() const
{
  return Point3(camMat[3][0], camMat[3][1], camMat[3][2]);
}

Point3h &Camera::cam_to_screen(const Point3h &src_pt, Point3h &dst_pt) const
{
  dst_pt.x() = src_pt.x() / (-1 * src_pt.z());
  dst_pt.y() = src_pt.y() / (-1 * src_pt.z());
  dst_pt.z() = -1 * src_pt.z();
  return dst_pt;
}

/*
  normalise the x and y coordinates in screen space to raster space
  (width and height limited by fov and rounded)
*/
Point3h &Camera::screen_to_raster(const Point3h &src_pt, Point3h &dst_pt) const
{
  float normalised_x = (src_pt.x() + (viewportWidth / 2)) / viewportWidth;
  float normalised_y = (src_pt.y() + (viewportHeight / 2)) / viewportHeight;
  dst_pt.x() = std::floor(normalised_x * pixelWidth);
  dst_pt.y() = std::floor((1 - normalised_y) * pixelHeight);
  return dst_pt;
}

/*
 * compute the raster coordinate of a world coordinate
 */
Point3h &Camera::compute_pixel_coordinate(const Point3h &src_pt, Point3h &dst_pt) const
{
  cam_to_screen(src_pt, dst_pt);
  screen_to_raster(dst_pt, dst_pt);
  return dst_pt;
}

std::vector<Point3h> Camera::project_vertices(const Mesh &mesh)
{
  const std::vector<Point3h> &vertices = mesh.get_vertices();
  std::vector<Point3h> projected_vertices(vertices.size());
  for (size_t i = 0; i < vertices.size(); i++)
  {
    Point3h p;
    vertex_shader(vertices[i], projection_mat(), world_to_cam_mat(), p);
    projected_vertices[i] = p;
  }
  return projected_vertices;
}

std::vector<float> Camera::build_img_buffer(const Mesh &mesh)
{
  std::vector<Point3h> projectedVertices = project_vertices(mesh);
  for (auto &v : projectedVertices)
  {
    std::cerr << v << std::endl;
  }
  std::vector<float> buffer(pixelWidth * pixelHeight * 3);
  std::vector<float> depthBuffer(pixelWidth * pixelHeight, std::numeric_limits<float>::max());
  for (size_t f = 0; f < mesh.get_n_faces(); f++)
  {
    const size_t startVertIdx = f * 3; // 3 vertices in a triangle
    const size_t &p1Idx = mesh.get_vertex_order_idx(startVertIdx);
    const size_t &p2Idx = mesh.get_vertex_order_idx(startVertIdx + 1);
    const size_t &p3Idx = mesh.get_vertex_order_idx(startVertIdx + 2);
    const Point3h &p0 = projectedVertices[p1Idx];
    const Point3h &p1 = projectedVertices[p2Idx];
    const Point3h &p2 = projectedVertices[p3Idx];
    size_t xmax;
    size_t xmin;
    size_t ymax;
    size_t ymin;
    std::tie(xmax, xmin, ymax, ymin) = triangle_raster_bbox(p0, p1, p2, pixelWidth, pixelHeight);

    for (size_t y = ymin; y < ymax; y++)
    {
      for (size_t x = xmin; x < xmax; x++)
      {
        Point3h p = Point3h(x, y, 1000000);
        size_t bufferIdx = y * pixelWidth * 3 + 3 * x;
        // for each face in the mesh
        // vertex colours
        Vec<float, 3> c0 = mesh.get_vertex_colour(p1Idx);
        Vec<float, 3> c1 = mesh.get_vertex_colour(p2Idx);
        Vec<float, 3> c2 = mesh.get_vertex_colour(p3Idx);

        // perspective-correct vertex attribute interpolation
        c0[0] /= p0[2], c0[1] /= p0[2], c0[2] /= p0[2];
        c1[0] /= p1[2], c1[1] /= p1[2], c1[2] /= p1[2];
        c2[0] /= p2[2], c2[1] /= p2[2], c2[2] /= p2[2];

        // vertex z-coordinate inversion
        // p0[2] = 1 / p0[2], p1[2] = 1 / p1[2], p2[2] = 1 / p2[2];
        float p0y_inverted = 1 / p0[2];
        float p1y_inverted = 1 / p1[2];
        float p2y_inverted = 1 / p2[2];

        float area = pineda_edge(p0, p1, p2);
        float w0 = pineda_edge(p, p1, p2);
        float w1 = pineda_edge(p, p2, p0);
        float w2 = pineda_edge(p, p0, p1);

        Point3h edge0 = p2 - p1;
        Point3h edge1 = p0 - p2;
        Point3h edge2 = p1 - p0;

        bool overlaps = true;

        overlaps &= (w0 == 0 ? ((edge0.y() == 0 && edge0.x() > 0) || edge0.y() > 0) : (w0 > 0));
        overlaps &= (w1 == 0 ? ((edge1.y() == 0 && edge1.x() > 0) || edge1.y() > 0) : (w1 > 0));
        overlaps &= (w2 == 0 ? ((edge2.y() == 0 && edge2.x() > 0) || edge2.y() > 0) : (w2 > 0));

        if (overlaps)
        {
          w0 /= area;
          w1 /= area;
          w2 /= area;

          float z = 1 / (w0 * p0y_inverted + w1 * p1y_inverted + w2 * p2y_inverted);
          if (z < depthBuffer[bufferIdx / 3])
          {
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

float Camera::pineda_edge(const Point3h &p, const Point3h &p0, const Point3h &p1)
{
  return (p.x() - p0.x()) * (p1.y() - p0.y()) - (p.y() - p0.y()) * (p1.x() - p0.x());
}

inline std::tuple<size_t, size_t, size_t, size_t> Camera::triangle_raster_bbox(
    const Point3h &a,
    const Point3h &b,
    const Point3h &c,
    size_t xMaximumLimit,
    size_t yMaximumLimit)
{
  size_t xmax = std::max({a.x(), b.x(), c.x()}) - 1;
  size_t xmin = std::min({a.x(), b.x(), c.x()}) - 1;
  size_t ymax = std::max({a.y(), b.y(), c.y()}) - 1;
  size_t ymin = std::min({a.y(), b.y(), c.y()}) - 1;
  xmax = std::min(xmax, xMaximumLimit);
  xmin = std::max(xmin, (size_t)0);
  ymax = std::min(ymax, yMaximumLimit);
  ymin = std::max(ymin, (size_t)0);
  return {xmax, xmin, ymax, ymin};
}

void Camera::vertex_shader(const Point3h &vertex, const Matf4 &projectionMatrix, const Matf4 &worldToCameraMatrix, Point3h &out)
{
  std::cerr << "shader" << std::endl;
  out = vertex * worldToCameraMatrix;
  out = out * projectionMatrix;
  if (out.x() < -1 || out.x() > 1 || out.y() < -1 || out.y() > 1)
    return;
  // convert to raster space
  out.x() = std::min((uint32_t)(pixelWidth - 1), (uint32_t)((out.x() + 1) * 0.5 * pixelWidth));
  out.y() = std::min((uint32_t)(pixelHeight - 1), (uint32_t)((1 - (out.y() + 1) * 0.5) * pixelHeight));
}

void Camera::texture_shader(
    const Mesh &mesh,
    ColourRGBA &out,
    const float &w0,
    const float &w1,
    const float &w2,
    const Vec<float, 3> &c0,
    const Vec<float, 3> &c1,
    const Vec<float, 3> &c2,
    const float &z)
{
  float r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
  float g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
  float b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
  r *= z, g *= z, b *= z;
  out[0] = r, out[1] = g, out[2] = b;
}

void ppmRenderer::render(size_t width, size_t height, const std::vector<float> &imgBuffer)
{
  // first line of the image file
  std::cout << "P3\n"
            << width << ' ' << height << "\n255\n";
  for (int j = 0; j < height; j++)
  {
    std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
    for (int i = 0; i < width; i++)
    {
      size_t idx = j * width * 3 + 3 * i;
      std::cout << static_cast<int>(255 * imgBuffer[idx]) << ' '
                << static_cast<int>(255 * imgBuffer[idx + 1]) << ' '
                << static_cast<int>(255 * imgBuffer[idx + 2]) << '\n';
    }
  }
  std::clog << "\rDone.                       \n";
}