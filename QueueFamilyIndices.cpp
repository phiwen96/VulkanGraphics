#include "QueueFamilyIndices.hpp"


QueueFamilyIndices::QueueFamilyIndices (VkPhysicalDevice const& physicalDevice, VkSurfaceKHR const& surface) : m_graphicsFamily (0)
{
      uint32_t queueFamilyCount = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
      
      std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
      vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());
      
      uint32_t i = 0;
      for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                  m_graphicsFamily = i;
            }
            if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                  m_computeFamily = i;
            }
   
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
            
            if (presentSupport) {
                  m_presentFamily = i;
            }
            
            i++;
      }
}
