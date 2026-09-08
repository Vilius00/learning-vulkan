#include "buffer.h"
#include "checking.h"
#include "vertex.h"
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
  RayTracing(VmaAllocator &allocator) : allocator(allocator) {};

  VkAccelerationStructureKHR
  accelerationStructure(VkDevice &device, VkDeviceAddress vertexBufferAddress,
                        VkDeviceAddress indexBufferAddress,
                        VkDeviceSize vertexCount) {
    // Check how much memory is needed to permanently store BVH and how much
    // discardable data is needed to build it
    VkAccelerationStructureGeometryTrianglesDataKHR triangleData{
        .sType =
            VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        .vertexFormat = VK_FORMAT_R32G32B32_SFLOAT,
        .vertexStride = sizeof(Vertex),
        .maxVertex = static_cast<uint32_t>(vertexCount - 1),
        .indexType = VK_INDEX_TYPE_UINT16,
        .indexData = {.deviceAddress = indexBufferAddress}};

    VkAccelerationStructureGeometryKHR geometry{
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        .geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        .geometry = {.triangles = triangleData},
        .flags = VK_GEOMETRY_OPAQUE_BIT_KHR,
    };

    VkAccelerationStructureBuildGeometryInfoKHR buildInfo{
        .sType =
            VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        .type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        .flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR,
        .mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        .geometryCount = 1,
        .pGeometries = &geometry,
    };

    VkAccelerationStructureBuildSizesInfoKHR sizeInfo{
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR};

    uint32_t triangleCount{static_cast<uint32_t>(vertexCount / 3)};
    vkGetAccelerationStructureBuildSizesKHR(
        device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &buildInfo,
        &triangleCount, &sizeInfo);

    BufferCreator bc{allocator};
    VkBuffer blasBuffer{VK_NULL_HANDLE};
    VmaAllocation blasAllocation{VK_NULL_HANDLE};
    bc.createBackingBLASBuffer(sizeInfo.accelerationStructureSize, blasBuffer,
                               blasAllocation);
    VkBuffer blasScratchBuffer{VK_NULL_HANDLE};
    VmaAllocation blasScratchAllocation{VK_NULL_HANDLE};
    bc.createScratchBuffer(sizeInfo.buildScratchSize, blasScratchBuffer,
                           blasScratchAllocation);

    VkAccelerationStructureKHR as;
    // TODO: Try VkAccelerationStructureCreateInfo2KHR.
    VkAccelerationStructureCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        .buffer = blasBuffer,
        .size = sizeInfo.accelerationStructureSize,
        .type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
    };
    return as;
  }

private:
  VmaAllocator &allocator;
};
