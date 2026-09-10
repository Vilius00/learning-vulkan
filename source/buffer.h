#pragma once
#include <vma/vk_mem_alloc.h>
#include <vulkan/vulkan.h>

class BufferCreator {
public:
  BufferCreator(VmaAllocator &allocator);
  void
  createAccelerationStructureBackingBuffer(VkDeviceSize size, VkBuffer &buffer,
                                           VmaAllocation &bufferAllocation);

  void createScratchBuffer(VkDeviceSize size, VkDeviceSize alignment,
                           VkBuffer &buffer, VmaAllocation &bufferAllocation);

  void createInstanceBuffer(VkDeviceSize size, VkBuffer &buffer,
                            VmaAllocation &bufferAllocation,
                            VmaAllocationInfo &allocationInfo);

private:
  VmaAllocator &allocator;
};
