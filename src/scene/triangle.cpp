#include "triangle.h"

#include "CGL/CGL.h"
#include "GL/glew.h"

namespace CGL {
namespace SceneObjects {

Triangle::Triangle(const Mesh *mesh, size_t v1, size_t v2, size_t v3) {
  p1 = mesh->positions[v1];
  p2 = mesh->positions[v2];
  p3 = mesh->positions[v3];
  n1 = mesh->normals[v1];
  n2 = mesh->normals[v2];
  n3 = mesh->normals[v3];
  bbox = BBox(p1);
  bbox.expand(p2);
  bbox.expand(p3);

  bsdf = mesh->get_bsdf();
}

BBox Triangle::get_bbox() const { return bbox; }

bool Triangle::has_intersection(const Ray &r) const {
  // Part 1, Task 3: implement ray-triangle intersection
  // The difference between this function and the next function is that the next
  // function records the "intersection" while this function only tests whether
  // there is a intersection.
  Vector3D n = cross((p2-p1), (p3-p1));
  if (dot(n,r.d)==0){return false;}
  float t = dot(n,(r.o - p1))/dot(n,r.d);

  Vector3D intersectionPoint = r.o + r.d * t;

  //check if intersectionPoint is in the triangle
  Vector3D v0 = p2 - p1;
  Vector3D v1 = p3 - p1;
  Vector3D v2 = intersectionPoint - p1;

float d00 = dot(v0, v0);
float d01 = dot(v0, v1);
float d11 = dot(v1, v1);
float d20 = dot(v2, v0);
float d21 = dot(v2, v1);

float denom = d00 * d11 - d01 * d01;
float v = (d11 * d20 - d01 * d21) / denom;
float w = (d00 * d21 - d01 * d20) / denom;
float u =  - v - w;

return v>= 0 && u >= 0 && w >=0;

}
bool Triangle::intersect(const Ray &r, Intersection *isect) const {
  // Part 1, Task 3:
  // implement ray-triangle intersection. When an intersection takes
  // place, the Intersection data should be updated accordingly


  return true;


}

void Triangle::draw(const Color &c, float alpha) const {
  glColor4f(c.r, c.g, c.b, alpha);
  glBegin(GL_TRIANGLES);
  glVertex3d(p1.x, p1.y, p1.z);
  glVertex3d(p2.x, p2.y, p2.z);
  glVertex3d(p3.x, p3.y, p3.z);
  glEnd();
}

void Triangle::drawOutline(const Color &c, float alpha) const {
  glColor4f(c.r, c.g, c.b, alpha);
  glBegin(GL_LINE_LOOP);
  glVertex3d(p1.x, p1.y, p1.z);
  glVertex3d(p2.x, p2.y, p2.z);
  glVertex3d(p3.x, p3.y, p3.z);
  glEnd();
}

} // namespace SceneObjects
} // namespace CGL
