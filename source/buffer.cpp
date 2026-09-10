#include "buffer.h"
#include "checking.h"
#include <vma/vk_mem_alloc.h>
#include <vulkan/vulkan.h>

BufferCreator::BufferCreator(VmaAllocator &allocator) : allocator(allocator) {};

void BufferCreator::createAccelerationStructureBackingBuffer(
    VkDeviceSize size, VkBuffer &buffer, VmaAllocation &bufferAllocation) {
  VkBufferCreateInfo bufferCI{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = size,
      .usage = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR |
               VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT};

  VmaAllocationCreateInfo vBufferAllocCI{.usage = VMA_MEMORY_USAGE_AUTO};
  VmaAllocationInfo vBufferAllocInfo{};
  chk(vmaCreateBuffer(allocator, &bufferCI, &vBufferAllocCI, &buffer,
                      &bufferAllocation, &vBufferAllocInfo));
}

void BufferCreator::createScratchBuffer(VkDeviceSize size,
                                        VkDeviceSize alignment,
                                        VkBuffer &buffer,
                                        VmaAllocation &bufferAllocation) {
  VkBufferCreateInfo bufferCI{.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                              .size = size,
                              .usage =
                                  VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                  VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT};

  VmaAllocationCreateInfo vBufferAllocCI{.usage = VMA_MEMORY_USAGE_AUTO};
  VmaAllocationInfo vBufferAllocInfo{};

  chk(vmaCreateBufferWithAlignment(allocator, &bufferCI, &vBufferAllocCI,
                                   alignment, &buffer, &bufferAllocation,
                                   &vBufferAllocInfo));
}

void BufferCreator::createInstanceBuffer(VkDeviceSize size, VkBuffer &buffer,
                                         VmaAllocation &bufferAllocation,
                                         VmaAllocationInfo &allocationInfo) {
  VkBufferCreateInfo bufferCI{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size = size,
      .usage =
          VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
          VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR};

  VmaAllocationCreateInfo vBufferAllocCI{
      .flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT |
               VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT |
               VMA_ALLOCATION_CREATE_MAPPED_BIT,
      .usage = VMA_MEMORY_USAGE_AUTO};
  chk(vmaCreateBuffer(allocator, &bufferCI, &vBufferAllocCI, &buffer,
                      &bufferAllocation, &allocationInfo));
}
