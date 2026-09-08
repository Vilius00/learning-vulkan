#pragma once
#include <vma/vk_mem_alloc.h>
#include <vulkan/vulkan.h>

class BufferCreator {
public:
  BufferCreator(VmaAllocator &);
  void createBackingBLASBuffer(VkDeviceSize size, VkBuffer &buffer,
                               VmaAllocation &bufferAllocation);

  void createScratchBuffer(VkDeviceSize size, VkBuffer &buffer,
                           VmaAllocation &bufferAllocation);
};
