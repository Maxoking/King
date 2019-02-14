#include"kngpch.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


std::ostream& operator<<(std::ostream& stream, const glm::vec3& vec) {
  stream << "(" << vec.x << " , " << vec.y << " , " << vec.z << ")";
  return stream;
};