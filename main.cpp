#include "Instance.hpp"
#include "Window.hpp"
#include "Vulkan.hpp"
#include "PhysicalDevice.hpp"
#include "LogicalDevice.hpp"
#include "Surface.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
      "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
      auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
      if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
      } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
      }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
      auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
      if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
      }
}

struct _QueueFamilyIndices {
      std::optional<uint32_t> graphicsFamily;
      std::optional<uint32_t> presentFamily;
      
      bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
      }
};

class HelloTriangleApplication {
public:
      void run() {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
      }
      
//private:
      GLFWwindow* window;
      
      VkInstance instance;
      VkDebugUtilsMessengerEXT debugMessenger;
      VkSurfaceKHR surface;
      
      VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
      VkDevice device;
      
      VkQueue graphicsQueue;
      VkQueue presentQueue;
      
      void initWindow() {
            glfwInit();
            
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            
            window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
      }
      
      void initVulkan() {
            createInstance();
            setupDebugMessenger();
            createSurface();
            pickPhysicalDevice();
            createLogicalDevice();
      }
      
      void mainLoop() {
            while (!glfwWindowShouldClose(window)) {
                  glfwPollEvents();
            }
      }
      
      void cleanup() {
            vkDestroyDevice(device, nullptr);
            
            if (enableValidationLayers) {
                  DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
            }
            
            vkDestroySurfaceKHR(instance, surface, nullptr);
            vkDestroyInstance(instance, nullptr);
            
            glfwDestroyWindow(window);
            
            glfwTerminate();
      }
      
      void createInstance() {
            instance = Create <Instance>
            {
                  Create <Instance::Layers>
                  {
                        //                  Instance::Layers::P_VALIDATION
                        "VK_LAYER_KHRONOS_validation"
                  },
                  
                  Create <Instance::Extensions>
                  {
                        Instance::Extensions::glfw,
                        Instance::Extensions::P_DEBUG_UTILS,
                        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
//                        Instance::Extensions::P_SURFACE,
//                        Instance::Extensions::P_METAL_SURFACE
                        
                  }
            };
            
            
            
            return;
            if (enableValidationLayers && !checkValidationLayerSupport()) {
                  throw std::runtime_error("validation layers requested, but not available!");
            }
            
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Hello Triangle";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;
            
            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;
            
            auto extensions = getRequiredExtensions();
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();
            
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
            if (enableValidationLayers) {
                  createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                  createInfo.ppEnabledLayerNames = validationLayers.data();
                  
                  populateDebugMessengerCreateInfo(debugCreateInfo);
                  createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
            } else {
                  createInfo.enabledLayerCount = 0;
                  
                  createInfo.pNext = nullptr;
            }
            
            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
                  throw std::runtime_error("failed to create instance!");
            }
      }
      
      void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
            createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            createInfo.pfnUserCallback = debugCallback;
      }
      
      void setupDebugMessenger() {
            if (!enableValidationLayers) return;
            
            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);
            
            if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
                  throw std::runtime_error("failed to set up debug messenger!");
            }
      }
      
      void createSurface() {
            if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
                  throw std::runtime_error("failed to create window surface!");
            }
      }
      
      void pickPhysicalDevice() {
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
            
            if (deviceCount == 0) {
                  throw std::runtime_error("failed to find GPUs with Vulkan support!");
            }
            
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
            
            for (const auto& device : devices) {
                  if (isDeviceSuitable(device)) {
                        physicalDevice = device;
                        break;
                  }
            }
            
            if (physicalDevice == VK_NULL_HANDLE) {
                  throw std::runtime_error("failed to find a suitable GPU!");
            }
      }
      
      void createLogicalDevice() {
            _QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
            
            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
            
            float queuePriority = 1.0f;
            for (uint32_t queueFamily : uniqueQueueFamilies) {
                  VkDeviceQueueCreateInfo queueCreateInfo{};
                  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                  queueCreateInfo.queueFamilyIndex = queueFamily;
                  queueCreateInfo.queueCount = 1;
                  queueCreateInfo.pQueuePriorities = &queuePriority;
                  queueCreateInfos.push_back(queueCreateInfo);
            }
            
            VkPhysicalDeviceFeatures deviceFeatures{};
            
            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            
            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            
            createInfo.pEnabledFeatures = &deviceFeatures;
            
            createInfo.enabledExtensionCount = 0;
            
            if (enableValidationLayers) {
                  createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                  createInfo.ppEnabledLayerNames = validationLayers.data();
            } else {
                  createInfo.enabledLayerCount = 0;
            }
            
            if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
                  throw std::runtime_error("failed to create logical device!");
            }
            
            vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
      }
      
      bool isDeviceSuitable(VkPhysicalDevice device) {
            _QueueFamilyIndices indices = findQueueFamilies(device);
            
            return indices.isComplete();
      }
      
      _QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
            _QueueFamilyIndices indices;
            
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
            
            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
            
            int i = 0;
            for (const auto& queueFamily : queueFamilies) {
                  if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                        indices.graphicsFamily = i;
                  }
                  
                  VkBool32 presentSupport = false;
                  vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
                  
                  if (presentSupport) {
                        indices.presentFamily = i;
                  }
                  
                  if (indices.isComplete()) {
                        break;
                  }
                  
                  i++;
            }
            
            return indices;
      }
      
      std::vector<const char*> getRequiredExtensions() {
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
            
            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
            
            if (enableValidationLayers) {
                  extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }
            
            return extensions;
      }

      bool checkValidationLayerSupport() {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
            
            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
            
            for (const char* layerName : validationLayers) {
                  bool layerFound = false;
                  
                  for (const auto& layerProperties : availableLayers) {
                        if (strcmp(layerName, layerProperties.layerName) == 0) {
                              layerFound = true;
                              break;
                        }
                  }
                  
                  if (!layerFound) {
                        return false;
                  }
            }
            
            return true;
      }
      
      static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
            
            return VK_FALSE;
      }
};






namespace ph::vulkan {



template <class T>
struct Const : public T
{
      Const(){}
      ~Const(){}
};

template<> Const<VkApplicationInfo>::Const() : VkApplicationInfo {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
      .pApplicationName = "appname",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "noname",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = VK_API_VERSION_1_2
}{
      
}

template<> Const<VkInstanceCreateInfo>::Const() : VkInstanceCreateInfo {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pApplicationInfo = nullptr,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = nullptr
}{
      
}

template <class...>
class Node;


////////////////////////////////////////////////////////////////
/// @brief Det är via virtual inheritance av denna som
/// exempelvis Node<VkApplicationInfo> kan kasta om den till
/// VkInstanceCreateInfo, eftersom Base är päron till alla
/// Nodeer
////////////////////////////////////////////////////////////////
template <class Root>
struct Base
{
      
protected:
      Base () : root (nullptr)
      {
            throw runtime_error("use constructor Base (T* t)");
      }
      Base (Root* const root) : root(root)
      {
            
      }
      
//      template <class T>
//      T& cast ()
//      {
////            return *static_cast<T*>(this);
//            return *dynamic_cast<T*>(root);
//      }
      
      template <class T>
      T& cast ()
      {
            //            return *static_cast<T*>(this);
            return *static_cast<T*>(root);
      }

      ////////////////////////////////////////////////////////////////
      /// @brief Behövs om Node inte definierar denna
      ////////////////////////////////////////////////////////////////
      template <class A>
      void update ()
      {
            
      }
      
      ////////////////////////////////////////////////////////////////
      /// @brief Behövs så att exempelvis så att Node med
      /// operator VkInstance kan notifiera att VkInstanceCreateInfo
      /// ska göras klar innan den används.
      ////////////////////////////////////////////////////////////////
      template <class A>
      void notify ()
      {
            root -> template update<A> ();
      }
      
private:
      Root* const root;
};







template <class Element, class Base>
struct Node<Element, Base> : public Element, public virtual Base
{
      using Base::root;
      
      template <class A>
      void update ()
      {
      
      }
};




template <class...>
struct NodeBase;




template <class Element, class Root>
struct NodeBase<Element, Root> :Node<Element, Base<Root>>
{

};

template <class...> struct Root;


template <class Head, class... Tail>
struct Root<Head, Tail...> : NodeBase<Head, Root<Head, Tail...>>, NodeBase<Tail, Root<Head, Tail...>>...
{
      using Self = Root<Head, Tail...>;

      
      
      ////////////////////////////////////////////////////////////////
      /// Varför skickar denna sig själv till Head?
      ////////////////////////////////////////////////////////////////
      Root () : Base<Self> (this)
      {
            
      }
      
      template <class A>
      void update ()
      {
            updateFirst<A>();
            updateRest<A>();
      }
      
private:
      template <class A>
      void updateFirst ()
      {
            NodeBase<Head, Root<Head, Tail...>>::template update<A> ();
      }
      template <class A>
      void updateRest ()
      {
            (NodeBase<Tail, Root<Head, Tail...>>::template update<A> (), ...);
      }
};

template<class...> struct Tuple;

template<class Head, class... Tail>
struct Tuple<Head, Tail...>
{
      
      template <class A>
      operator A ()
      {
//            root.template update<A> ();  Onödig?
            return (A) root;
      }
      
private:
      Root<Head, Tail...> root;
};



template<class T>
struct Tuple<T>
{
      
};

































#define BASE(Element, Rest) virtual Base<Rest>, Element
#define NODE(Element) template <class T> class Node<Element, Base<T>> : public virtual Base<T>, public Element





NODE(VkInstanceCreateInfo){
public:
      Node() : VkInstanceCreateInfo{
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .pApplicationInfo = nullptr,
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
            .enabledExtensionCount = 0,
            .ppEnabledExtensionNames = nullptr
      }
      {
            
      }
      
      
      operator VkInstance ()
      {
            Base<T>::template notify<VkInstanceCreateInfo> ();
//            Base<T>::template cast<Node<VkApplicationInfo, Base<T>>>().template update<VkInstanceCreateInfo>();
            
            VkInstance instance;
            if (vkCreateInstance(this, nullptr, &instance) != VK_SUCCESS)
            {
                  throw runtime_error("failed to create instance!");
            }
            return (VkInstance&&) instance;
      }
      
      
      
      
};



template<class T>
struct Node<VkApplicationInfo, Base<T>> : VkApplicationInfo, virtual Base<T>
{
      
      Node(): VkApplicationInfo{
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext = nullptr,
            .pApplicationName = "appname",
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "noname",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_2
      }
      {
            
      }
      
      template <class A>
      void update ()
      {
      
      }
      
      //template <class A> operator A();
      //ännu bättre
      //operator vkapplicationinfo ();
      
      template<>
      void update<VkInstanceCreateInfo> ()
      {
            Base<T>::template cast<VkInstanceCreateInfo>().pApplicationInfo = this;
      }
      
};

}





int main() {
      
 
      
      

      
      using namespace ph::vulkan;

//      HelloTriangleApplication app;
//
//      try {
////            app.run();
//      } catch (const std::exception& e) {
//            std::cerr << e.what() << std::endl;
//            return EXIT_FAILURE;
//      }
      
      Tuple<VkApplicationInfo, VkInstanceCreateInfo> a;
      VkInstance i = a;
      
      return 0;

      Window window {640, 480, "philip"};
      
      Create <Instance> instanceCreation
      {
            Create <Instance::Layers>
            {
                  Instance::Layers::P_VALIDATION
            },

            Create <Instance::Extensions>
            {
                  Instance::Extensions::glfw,
                  Instance::Extensions::P_DEBUG_UTILS
            }
      };
      
      Instance instance = instanceCreation;



      Surface surface = Create <Surface>
      {
            instance,
            window
      };


      Device::Physical physical_device = Create <Device::Physical>
      {
            instance,
            surface
      };


      Device::Logical l = Create <Device::Logical>
      {
            physical_device,
            Info<Queue>
            {
                  Queue::Type::Graphics,
                  1
            },

            Info<Queue>
            {
                  Queue::Type::Present,
                  1
            }
      };









//      Queue graphicsQueue =












//      PhysicalDevice p = Create<PhysicalDevice>
//      {
//
//      };


//      Vulkan v = Create <Vulkan>
//      {
//            Create <Instance>
//            {
//                  Create <Instance::Layers>
//                  {
//                        "VK_LAYER_KHRONOS_validation"
//                  },
//
//                  Create <Instance::Extensions>
//                  {
//                        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
//                        Instance::Extensions::glfw
//                  }
//            },
//
//            Create <PhysicalDevice>
//            {
//
//            }
//      };



      glfwTerminate();
      return 0;
}





//VkDeviceQueueCreateInfo queueCreateInfo
//{
//      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
//      .queueFamilyIndex = physical_device.m_graphicsFamily.value(),
//      .queueCount = 1,
//      .pQueuePriorities = new float (1.0f)
//};
//
//
//
//VkPhysicalDeviceFeatures deviceFeatures{};
//VkDeviceCreateInfo createInfo
//{
//      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
//      .pQueueCreateInfos = &queueCreateInfo,
//      .queueCreateInfoCount = 1,
//      .pEnabledFeatures = &deviceFeatures,
//      .enabledExtensionCount = 0,
//      .enabledLayerCount = 0
//};
//
//VkDevice device;
//if (vkCreateDevice(physical_device.m_physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
//      throw std::runtime_error("failed to create logical device!");
//      }





