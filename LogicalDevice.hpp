#pragma once
#include <ph/common/vec.hpp>
#include "Create.hpp"
#include "Info.hpp"
#include "QueueFamilyIndices.hpp"
#include "PhysicalDevice.hpp"
#include "Device.hpp"
#include "Complete.hpp"
#include "queue.hpp"
#include "Surface.hpp"
using namespace ph;

struct Device::Logical
{
      Logical (){
            
      }
      Logical(Logical&& other) : Logical(){
            swap (*this, other);
      }
      Logical (Logical const& other) : m_logicalDevice (other.m_logicalDevice), m_queues (other.m_queues) {
            
      }
      Logical (VkDevice const& logicalDevice, vec<Queue> const& queues) : m_logicalDevice (logicalDevice), m_queues (queues)
      {
            
      }
      ~Logical ()
      {
            vkDestroyDevice (m_logicalDevice, nullptr);
      }
      friend void swap (Logical& lhs, Logical& rhs) {
            using std::swap;
            swap (lhs.m_logicalDevice, rhs.m_logicalDevice);
            swap (lhs.m_queues, rhs.m_queues);
      }
      
private:
      VkDevice m_logicalDevice;
      vec<Queue> m_queues;
};










template <>
struct Info <VkDeviceQueueCreateInfo> :  VkDeviceQueueCreateInfo
{
      using Base = VkDeviceQueueCreateInfo;
      
      Info () : VkDeviceQueueCreateInfo {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = 0,
            .queueCount = 0,
            .pQueuePriorities = new float (1.0f)
      }
      {

      }
      Info (Info&& other) : Base ((Base&&) other) {
            
      }
      Info (Info const& other) : Base ((Base const&) other) {
            
      }
  
};


template <>
struct Info <Queue> : Info<VkDeviceQueueCreateInfo>
{
      using Base = Info<VkDeviceQueueCreateInfo>;
      using Self = Info <Queue>;
      Info (Queue::Type queueType, float count) : m_queueType (queueType) {
            queueCount = count;
      }
      Info () : Base () {
            
      }
      Info (Info const& other) : Base ((Base const&) other), m_queueType (other.m_queueType) {
            
      }
      Info (Info&& other) : Base ((Base&&) other) {
            swap (*this, other);
      }
      uint32_t accept (Device::Physical const& physicalDevice) {
            uint32_t index = Queue::getIndex (physicalDevice, m_queueType);
            Base::queueFamilyIndex = index;
            return index;
      }
      friend void swap (Info& lhs, Info& rhs) {
            using std::swap;
            swap (lhs.m_queueType, rhs.m_queueType);
      }
      friend ostream& operator<< (ostream& os, Self const& s) {
            os << s.m_queueType << "\t" << s.Base::queueCount;
            return os;
      }
      

      Queue::Type m_queueType;
};


template <>
struct Info <VkDeviceCreateInfo> : VkDeviceCreateInfo
{
      using Base = VkDeviceCreateInfo;
      
      Info () : VkDeviceCreateInfo {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pQueueCreateInfos = nullptr,
            .queueCreateInfoCount = 0,
            .pEnabledFeatures = nullptr,
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
            .enabledExtensionCount = 0,
            .ppEnabledExtensionNames = nullptr
      }
      {
            
      }
      Info (Info&& other) : Base((Base&&)other){
            
      }
      Info (Info const& other) : Base((Base const&)other) {
            
      }
};

template <>
struct Info <Device::Logical> : Info<VkDeviceCreateInfo>
{
      using Base = Info<VkDeviceCreateInfo>;
      using Self = Info <Device::Logical>;
      
      Info () {
            
      }
      Info (Self&& other) : Base ((Base&&) other){
            
      }
      Info (Self const& other) : Base ((Base const&) other) {
            
      }

};






template <>
struct Create <Device::Logical> : Info <Device::Logical>//, Complete <Queue>
{
      template <class... Rest>
      Create (Device::Physical const& physicalDevice, Info <Queue> const& queueInfo, Rest const&... rest) :  m_physicalDevice (physicalDevice), m_queueInfos (queueInfo, (Info <Queue> const&)rest...)
      {
            pQueueCreateInfos = m_queueInfos.data();
            queueCreateInfoCount = m_queueInfos.size();//cout<<"hejsan!:)"<<endl;
//            ppEnabledLayerNames = 
      }
      
      operator Device::Logical ()
      {
            VkDevice logicalDevice;
      
            VkPhysicalDeviceFeatures deviceFeatures{};
            
            pEnabledFeatures = &deviceFeatures;
            
            if (vkCreateDevice((VkPhysicalDevice const&)m_physicalDevice, (VkDeviceCreateInfo*)(this), nullptr, &logicalDevice) != VK_SUCCESS) {
                  throw std::runtime_error("failed to create logical device!");
            }
            
            vec<Queue> queues (m_queueInfos.size());
            for (int i = 0; i < m_queueInfos.size(); ++i) {
                  VkQueue queue;
                  uint32_t queueIndex;
//                  Device::Logical l (logicalDevice);
                  m_queueInfos[i].accept(m_physicalDevice);
                  vkGetDeviceQueue(logicalDevice, m_queueInfos[i].queueFamilyIndex, 0, &queue);
                  queues += Queue {std::move(queue), m_queueInfos[i].m_queueType};
            }
            return {std::move(logicalDevice), std::move(queues)};
//            return logicalDevice;
      }
      

      
      
private:
      Device::Physical const& m_physicalDevice;
      vec<Info<Queue>> m_queueInfos;
      
};




