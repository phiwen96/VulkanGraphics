#pragma once
#include <ph/common/vec.hpp>
#include "Create.hpp"
#include "Info.hpp"
#include "QueueFamilyIndices.hpp"
#include "Instance.hpp"
#include "Device.hpp"
using namespace ph;



struct Device::Physical : QueueFamilyIndices
{
      Physical (VkPhysicalDevice const& physicalDevice, VkSurfaceKHR const& surface) : QueueFamilyIndices (physicalDevice, surface), m_physicalDevice (physicalDevice)
      {
//            cout << "ksdnmakmsd" << endl;
      }
      
      Physical () {
            
      }
      Physical (Physical&& other) : QueueFamilyIndices ((QueueFamilyIndices&&)other) {
            swap (*this, other);
      }
      Physical (Physical const& other) : QueueFamilyIndices ((QueueFamilyIndices const&)other), m_physicalDevice (other.m_physicalDevice) {
            
      }
      friend void swap (Physical& lhs, Physical& rhs) {
            using std::swap;
            swap (lhs.m_physicalDevice, rhs.m_physicalDevice);
//            swap (static_cast<QueueFamilyIndices&>(lhs), static_cast<QueueFamilyIndices&>(rhs));
      }
//      operator VkPhysicalDeviceProperties ()
//      {
//            VkPhysicalDeviceProperties deviceProperties;
//            vkGetPhysicalDeviceProperties(m_physicalDevice, &deviceProperties);
//            return deviceProperties;
//      }
//      operator VkPhysicalDeviceFeatures ()
//      {
//            VkPhysicalDeviceFeatures deviceFeatures;
//            vkGetPhysicalDeviceFeatures(m_physicalDevice, &deviceFeatures);
//            return deviceFeatures;
//      }
      operator VkPhysicalDevice& ()
      {
            cout << "VkPhysicalDevice const& ()" << endl;
            return m_physicalDevice;
      }
      operator VkPhysicalDevice ()
      {
            return m_physicalDevice;
      }
//      operator VkPhysicalDevice* ()
//      {
//            return &m_physicalDevice;
//      }
//
//private:
      VkPhysicalDevice m_physicalDevice;
      //      vec<VkPhysicalDevice> const static available;
};



//template <>
//struct Info <PhysicalDevice> : Info<Instance>
//{
//      VkInstance* m_instance;
//      operator VkPhysicalDevice* ()
//      {
//            if (m_instance == nullptr)
//            {
//                  throw std::runtime_error ("instance must be created before physical device");
//            }
//            uint32_t deviceCount = 0;
//            vkEnumeratePhysicalDevices(*m_instance, &deviceCount, nullptr);
//            if (deviceCount == 0)
//            {
//                  throw std::runtime_error("failed to find GPUs with Vulkan support!");
//            }
//            vec<VkPhysicalDevice> physicalDevices (deviceCount);
//            vkEnumeratePhysicalDevices(*m_instance, &deviceCount, physicalDevices.data());
//            return new VkPhysicalDevice (physicalDevices[0]);
//      }
//};







template <>
struct Create <Device::Physical>
{
      Create (VkInstance const& instance, VkSurfaceKHR const& surface) : m_physicalDevices (Instance::Devices::available(instance)), m_surface (surface)
      {
            
      }
      operator Device::Physical (){//cout<<"knfsdkandf"<<endl;
            return {(VkPhysicalDevice const&)m_physicalDevices[0], m_surface};
      }

private:
      vec<VkPhysicalDevice> m_physicalDevices;
      VkSurfaceKHR const& m_surface;

};
