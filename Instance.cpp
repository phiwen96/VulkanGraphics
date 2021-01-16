#include "Instance.hpp"

cstr const Instance::Layers::P_VALIDATION = "VK_LAYER_KHRONOS_validation";

cstr const Instance::Extensions::P_DEVICE_GROUP_CREATION = "VK_KHR_device_group_creation";
cstr const Instance::Extensions::P_EXTERNAL_FENCE_CAPABILITIES = "VK_KHR_external_fence_capabilities";
cstr const Instance::Extensions::P_EXTERNAL_MEMORY_CAPABILITIES = "VK_KHR_external_memory_capabilities";
cstr const Instance::Extensions::P_EXTERNAL_SEMAPHORE_CAPABILITIES = "VK_KHR_external_semaphore_capabilities";
cstr const Instance::Extensions::P_PHYSICAL_DEVICE_PROPERTIES2 = "VK_KHR_get_physical_device_properties2";
cstr const Instance::Extensions::P_GET_SURFACE_CAPABILITIES2 = "VK_KHR_get_surface_capabilities2";
cstr const Instance::Extensions::P_SURFACE = "VK_KHR_surface";
cstr const Instance::Extensions::P_DEBUG_REPORT = "VK_EXT_debug_report";
cstr const Instance::Extensions::P_DEBUG_UTILS = "VK_EXT_debug_utils";
cstr const Instance::Extensions::P_METAL_SURFACE = "VK_EXT_metal_surface";
cstr const Instance::Extensions::P_SWAPCHAIN_COLORSPACE = "VK_EXT_swapchain_colorspace";
cstr const Instance::Extensions::P_MACOS_SURFACE = "VK_MVK_macos_surface";


vec<char const*> const Instance::Extensions::glfw = []()->std::pair<char const**, size_t>{
      glfwInit();
      uint32_t glfwExtensionCount = 0;
      char const** glfwExtensions = nullptr;
      
      glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
      return {glfwExtensions, glfwExtensionCount};
}();

vec<VkLayerProperties> const Instance::Layers::available = []()->std::pair<VkLayerProperties*, size_t>{
      uint32_t layerCount;
      vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
      VkLayerProperties* layers = new VkLayerProperties[layerCount];
      vkEnumerateInstanceLayerProperties(&layerCount, layers);
      return {layers, layerCount};
}();

vec<VkExtensionProperties> const Instance::Extensions::available = []()->std::pair<VkExtensionProperties*, size_t>{
      uint32_t extensionCount = 0;
      vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
      VkExtensionProperties* extensions = new VkExtensionProperties [(int) extensionCount];
      vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions);
      return {extensions, extensionCount};
}();
//vec<VkPhysicalDevice> const Instance::available = []()->std::pair<VkPhysicalDevice*, size_t>{
//      uint32_t deviceCount = 0;
//      vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
//      if (deviceCount == 0) {
//            throw std::runtime_error("failed to find GPUs with Vulkan support!");
//      }
//      VkPhysicalDevice* devices = new VkPhysicalDevice[deviceCount];
//      vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
//      return {devices, deviceCount};
//}();




Info<VkApplicationInfo>::Info () : VkApplicationInfo {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = "Hello Triangle",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = VK_API_VERSION_1_2}
{
      
}



Info<VkInstanceCreateInfo>::Info () : VkInstanceCreateInfo {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = nullptr
}
{
      
}



Info<Instance>::Info ()
{
      pApplicationInfo = static_cast<VkApplicationInfo*>(this);
}
Info<Instance>::operator VkInstance() const
{
      VkInstance instance;
      if (vkCreateInstance(static_cast<VkInstanceCreateInfo const*>(this), nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
      }
      return std::move(instance);
      }

vec<VkPhysicalDevice> Instance::Devices::available (VkInstance const& instance) {
      uint32_t deviceCount = 0;
      vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
      if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
      }
      VkPhysicalDevice* devices = new VkPhysicalDevice[deviceCount];
      vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
      return {devices, deviceCount};
      }

Instance::operator vec<VkPhysicalDevice> () const {
      uint32_t deviceCount = 0;
      vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
      if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
      }
      VkPhysicalDevice* devices = new VkPhysicalDevice[deviceCount];
      vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices);
      return {devices, deviceCount};
      }


Instance::Instance () : m_instance (Info<Instance> {})
{
      
}
Instance::~Instance ()
{
      vkDestroyInstance(m_instance, nullptr);
}




