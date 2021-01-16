#include "PhysicalDevice.hpp"


//vec<VkPhysicalDevice> const PhysicalDevice::available = []()->std::pair<VkPhysicalDevice*, size_t>{
//      uint32_t deviceCount = 0;
//      vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
//      if (deviceCount == 0) {
//            throw std::runtime_error("failed to find GPUs with Vulkan support!");
//      }
//      VkPhysicalDevice* devices = new VkPhysicalDevice[deviceCount];
//      vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
//      return {devices, deviceCount};
//}();
