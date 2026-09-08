#include "checking.h"
#include <Volk/volk.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <vulkan/vulkan.h>

class Ray {
public:
  Ray() {}

  Ray(const glm::vec3 &origin, const glm::vec3 &direction)
      : orig(origin), dir(direction) {}

  const glm::vec3 &origin() const { return orig; }
  const glm::vec3 &direction() const { return dir; }

  glm::vec3 at(float t) { return orig + t * dir; }

private:
  glm::vec3 orig, dir;
};

class RayTracing {
public:
  VkAccelerationStructureKHR accelerationStructure() {
    VkAccelerationStructureKHR as;
    // VkAccelerationStructureBuildGeometryInfoKHR asbgInfo{
    //   .sType =
    //   VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
    //     .type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
    //     .mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
    //     .dstAccelerationStructure = as,
    //     .
    // };
    return as;
  }
};
