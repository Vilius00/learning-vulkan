#include "checking.h"
#include <vma/vk_mem_alloc.h>
#include <vulkan/vulkan.h>

class BufferCreator {
public:
  BufferCreator(VmaAllocator &allocator) : allocator(allocator) {};

  void createBackingBLASBuffer(VkDeviceSize size, VkBuffer &buffer,
                               VmaAllocation &bufferAllocation) {
    VkBufferCreateInfo bufferCI{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR |
                 VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT};

    VmaAllocationCreateInfo vBufferAllocCI{
        .usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE};
    VmaAllocationInfo vBufferAllocInfo{};
    chk(vmaCreateBuffer(allocator, &bufferCI, &vBufferAllocCI, &buffer,
                        &bufferAllocation, &vBufferAllocInfo));
  }

  void createScratchBuffer(VkDeviceSize size, VkBuffer &buffer,
                           VmaAllocation &bufferAllocation) {
    VkBufferCreateInfo bufferCI{.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                .size = size,
                                .usage =
                                    VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                    VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT};

    VmaAllocationCreateInfo vBufferAllocCI{
        .usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE};
    VmaAllocationInfo vBufferAllocInfo{};
    chk(vmaCreateBuffer(allocator, &bufferCI, &vBufferAllocCI, &buffer,
                        &bufferAllocation, &vBufferAllocInfo));
  }

private:
  VmaAllocator &allocator;
};
