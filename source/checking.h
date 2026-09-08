#pragma once
#include <iostream>
#include <vulkan/vulkan.h>

static inline void chk(VkResult result) {
  if (result != VK_SUCCESS) {
    std::cerr << "Vulkan call returned an error (" << result << ")\n";
    exit(result);
  }
}

static inline void chkSwapchain(VkResult result, bool &updateSwapchain) {
  if (result < VK_SUCCESS) {
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
      updateSwapchain = true;
      return;
    }
    std::cerr << "Vulkan call returned an error (" << result << ")\n";
    exit(result);
  }
}

static inline void chk(bool result) {
  if (!result) {
    std::cerr << "Vulkan call returned an error\n";
    exit(result);
  }
}
