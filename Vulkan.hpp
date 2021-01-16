#pragma once
#include "Create.hpp"
#include "Info.hpp"
#include <ph/common/vec.hpp>
#include "Instance.hpp"
#include "PhysicalDevice.hpp"
//
//
struct Vulkan;
//
//template <>
//struct Info<Vulkan> : Info<PhysicalDevice>
//{
////      Info (Create<Instance> instance, Create<PhysicalDevice> physicalDevice) : Info<Instance> (instance), Info<PhysicalDevice> (physicalDevice)
////      {
////
////      }
////      Info (Create<Instance> instance, Create<PhysicalDevice> physicalDevice) : m_instance (instance), m_physicalDevice (physicalDevice)
////      {
////
////      }
//
//
//private:
////      Create<Instance> m_instance;
////      Create<PhysicalDevice> m_physicalDevice;
//};
//
//
//
//struct Vulkan : Instance, PhysicalDevice
//{
////      VkInstance* m_instance;
////      VkPhysicalDevice* m_physcalDevice;
//      Vulkan (Info<Vulkan> info) : Instance (info), PhysicalDevice (info)
//      {
//
//      }
//
//private:
////      Instance m_instance;
////      PhysicalDevice m_physicalDevice;
//};
//
//
////template <>
////struct Create<Vulkan>
////{
////      Create (Create<Instance> instance, Create<PhysicalDevice> physicalDevice)
////      {
////            m_vulkan.m_instance = instance;
////      }
////      operator Vulkan ()
////      {
////            return m_vulkan;
////      }
////
////private:
////      Info<Vulkan> m_info;
//////      Vulkan m_vulkan;
////
////
////};
