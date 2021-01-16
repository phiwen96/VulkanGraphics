#pragma once


struct QueueFamilyIndices
{
      QueueFamilyIndices (VkPhysicalDevice const& physicalDevice, VkSurfaceKHR const& surface);
      QueueFamilyIndices(){}
      QueueFamilyIndices(QueueFamilyIndices&& other) : QueueFamilyIndices () {
            swap (*this, other);
      }
      QueueFamilyIndices(QueueFamilyIndices const& other) : m_graphicsFamily(other.m_graphicsFamily), m_computeFamily(other.m_computeFamily), m_presentFamily(other.m_presentFamily){
            
      }
      friend void swap (QueueFamilyIndices& lhs, QueueFamilyIndices& rhs) {
            using std::swap;
            swap (lhs.m_graphicsFamily, rhs.m_graphicsFamily);
            swap (lhs.m_computeFamily, rhs.m_computeFamily);
            swap (lhs.m_presentFamily, rhs.m_presentFamily);
      }
//private:
      std::optional<uint32_t> m_graphicsFamily;
      std::optional<uint32_t> m_computeFamily;
      std::optional<uint32_t> m_presentFamily;
};
