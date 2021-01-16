#pragma once
#include "Info.hpp"
#include "Create.hpp"

struct Debugger
{
      
};


template <>
struct Info <VkDebugUtilsMessengerCreateInfoEXT> : VkDebugUtilsMessengerCreateInfoEXT
{
private:
      using Base = VkDebugUtilsMessengerCreateInfoEXT;
      
      static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
            
            return VK_FALSE;
      }
      
public:
      Info () : Base {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = debugCallback
      } {
            
      }
      
};

template <>
struct Info <Debugger> : Info <VkDebugUtilsMessengerCreateInfoEXT>
{
      using Base = Info <VkDebugUtilsMessengerCreateInfoEXT>;
      using Base::Base;
};


template <>
struct Create <Debugger> : Info <Debugger>
{
      using Base = Info <Debugger>;
      using Self = Create <Debugger>;
      
      Create (VkInstance const& instance) {
            
      }
      
private:
      VkDebugUtilsMessengerEXT m_debugMessenger;
};
