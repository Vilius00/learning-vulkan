#pragma once
#include <vma/vk_mem_alloc.h>
#include <vulkan/vulkan.h>

class BufferCreator {
public:
  BufferCreator(VmaAllocator &allocator);
  void createBackingBLASBuffer(VkDeviceSize size, VkBuffer &buffer,
                               VmaAllocation &bufferAllocation);

  void createScratchBuffer(VkDeviceSize size, VkDeviceSize alignment,
                           VkBuffer &buffer, VmaAllocation &bufferAllocation);
  void createBackingTLASBuffer(VkDeviceSize size, VkBuffer &buffer,
                               VmaAllocation &bufferAllocation);

  void createInstanceBuffer(VkAccelerationStructureInstanceKHR asInstance,
                            VkDeviceSize size, VkBuffer &buffer,
                            VmaAllocation &bufferAllocation);

private:
  VmaAllocator &allocator;
};
