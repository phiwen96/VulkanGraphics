#pragma once

#include <ph/common/vec.hpp>
#include <ph/common/str.hpp>
#include "Info.hpp"
#include "Create.hpp"
#include "Debugger.hpp"

using cstr = char const *;





using ph::vec;
using ph::str;

struct Instance;






template <>
struct Info<VkApplicationInfo> : VkApplicationInfo
{
      Info ();
      
};

template <>
struct Info<VkInstanceCreateInfo> : VkInstanceCreateInfo
{
      Info ();
};

template <>
struct Info<Instance> : Info<VkApplicationInfo>, Info<VkInstanceCreateInfo>
{
      Info ();
      operator VkInstance() const;
};





//template <>
//struct vec<Instance::Extensions::glfw>;

struct Instance
{
      template <class...>
      struct Create;
   
      
      struct Layers{
            struct Create
            {
                  
            };
            enum {hej};
            static cstr const P_VALIDATION;

            vec<VkLayerProperties> const static available;
      };
      struct Extensions{
            struct Create
            {
                  
            };
            static vec<VkExtensionProperties> const available;
            static vec<char const*> const glfw;
            
            static cstr const P_DEVICE_GROUP_CREATION;
            static cstr const P_EXTERNAL_FENCE_CAPABILITIES;
            static cstr const P_EXTERNAL_MEMORY_CAPABILITIES;
            static cstr const P_EXTERNAL_SEMAPHORE_CAPABILITIES ;
            static cstr const P_PHYSICAL_DEVICE_PROPERTIES2;
            static cstr const P_GET_SURFACE_CAPABILITIES2;
            static cstr const P_SURFACE;
            static cstr const P_DEBUG_REPORT;
            static cstr const P_DEBUG_UTILS;
            static cstr const P_METAL_SURFACE;
            static cstr const P_SWAPCHAIN_COLORSPACE;
            static cstr const P_MACOS_SURFACE;
      };
      struct Devices{
            static vec<VkPhysicalDevice> available (VkInstance const& instance);
      };
      
      operator vec<VkPhysicalDevice> () const;
      
      
      
//      vec<VkPhysicalDevice> const static available;

      
   
      Instance ();
      ~Instance ();
      Instance (VkInstance const& instance) : m_instance (instance) {
            
      }
      Instance (VkInstance&& instance) : m_instance (std::move(instance)) {
            
      }
      Instance (Instance&& other) : Instance () {
            swap (*this, other);
      }
      Instance (Instance const& other) : m_instance (other.m_instance) {
            
      }
      friend void swap (Instance& lhs, Instance& rhs) {
            using std::swap;
            swap (lhs.m_instance, rhs.m_instance);
      }
      
      operator VkInstance&(){
            cout << "VkInstance const&()" << endl;
            return m_instance;
      }
      
//private:
      VkInstance m_instance;
      friend class Create <Instance>;
      
};

template <>
struct Instance::Create<Instance::Layers>{};




















template <>
struct Create<Instance::Layers> : vec<char const*>
{
      using Layers      =     Instance::Layers;
      template <class... U>
      Create (U const&... u) : vec<char const*> (u...) {
            check ();
      }
//      template <class... U, class... V>
//      Create (U const&... u, V const&... v) : vec<char const*> (u...) {
//            (this->operator+=(v), ...);
//            check ();
//      }

     
      
private:

      void check () {
            
            int layersNotFound = size();

            int i = 0;
            while (layersNotFound > 0 and i < size()) {
                  int j = 0;
                  while (j < Instance::Layers::available.size()) {
                        if (strcmp(get(i),Instance::Layers::available.get(j).layerName) == 0) {
                              --layersNotFound;
                              break;
                        }
                        ++j;
                  }
                  ++i;
            }
            if (layersNotFound > 0) {
                  throw std::runtime_error ("validation layers requested, but not available!");
            }
      }
};






template <>
struct Create<Instance::Extensions> : vec<char const*>
{
      using Extensions      =     Instance::Extensions;
      template <class... U>
      Create (U const&... u) : vec<char const*> (u...) {
            check ();
      }
      template <class... V>
      Create (vec<char const*> const& u, V const&... v) : vec<char const*> (u) {
            (this->operator+=(v), ...);
            check ();
      }
      
      


      
     
      
private:
      void check () {
            
            int layersNotFound = size();
//            layersNotFound = 0;
            int i = 0;
            while (layersNotFound > 0 and i < size()) {
                  int j = 0;
                  while (j < Instance::Extensions::available.size()) {
                        if (strcmp(get(i), Instance::Extensions::available.get(j).extensionName) == 0) {
                              --layersNotFound;
                              break;
                        }
                        ++j;
                  }
                  ++i;
            }
            if (layersNotFound > 0) {
                  throw std::runtime_error ("instance extensions requested, but not available!");
            }
      }
};


//template <>
//struct Create_pbase <Instance>
//{
//      Create_pbase ()
//};


template <>
struct Create<Instance> : Info<Instance>
{
      using Base = Info<Instance>;
      using Self = Create<Instance>;
      using Layers      =     Instance::Layers;
      using Extensions  =     Instance::Extensions;
      
      Create (Create<Layers>&& layers, Create<Extensions>&& extensions) : m_layers (std::move(layers)), m_extensions (std::move(extensions))
      {
            enabledLayerCount = static_cast<uint32_t>(m_layers.size());
            ppEnabledLayerNames = m_layers.data();
            
            enabledExtensionCount = static_cast<uint32_t>(m_extensions.size());
            ppEnabledExtensionNames = m_extensions.data();
            
            if (vkCreateInstance(static_cast<VkInstanceCreateInfo const*>(this), nullptr, &(VkInstance&)m_instance) != VK_SUCCESS) {
                  throw std::runtime_error("failed to create instance!");
            }
      }
      Create () {
            
      }
//      Create ()
      operator VkInstance() {
            //            glfwInit();
            char const** s = new char const*[m_layers.size()];
            for (int i = 0; i < m_layers.size(); ++i)
            {
                  s[i] = m_layers[i];
            }
            enabledLayerCount = static_cast<uint32_t>(m_layers.size());
            //            ppEnabledLayerNames = m_layers.data();
            ppEnabledLayerNames = s;
            
            
            char const** e = new char const*[m_extensions.size()];
            for (int i = 0; i < m_extensions.size(); ++i)
            {
                  e[i] = m_extensions[i];
            }
            //            for(int i = 0; i < m_extensions.size(); ++i){
            //                  cout << e[i] << endl;
            //            }
            enabledExtensionCount = static_cast<uint32_t>(m_extensions.size());
            //            ppEnabledExtensionNames = m_extensions.data();
            ppEnabledExtensionNames = e;
            //            m_info.enabledExtensionCount = 0;
            //            m_info.ppEnabledExtensionNames = nullptr;
            VkInstance instance;
            if (vkCreateInstance(static_cast<VkInstanceCreateInfo const*>(this), nullptr, &instance) != VK_SUCCESS) {
                  throw std::runtime_error("failed to create instance!");
            }
            return std::move(instance);
            //            return m_info;
      }
      operator Instance() {
            return m_instance;
      }
    
      
protected:
      Create<Layers>          m_layers;
      Create<Extensions>      m_extensions;
      
      Info<Instance>          m_info;
      Instance m_instance;
};


template <>
struct Create<Instance, Debugger> : Create <Instance>, Create <Debugger>
{
//      Create (Create <Instance> )
};














inline ostream& operator<<(ostream& os, vec<VkExtensionProperties> const& v){
      os << "{ " << endl;
      for (int i = 0; i < v.size(); ++i) {
            os << "\t" << v[i].extensionName << endl;
      }
      os << "}";
      return os;
}

inline ostream& operator<<(ostream& os, vec<VkLayerProperties> const& v){
      os << "{ " << endl;
      for (int i = 0; i < v.size(); ++i) {
            os << "\t" << v[i].layerName << endl;
      }
      os << "}";
      return os;
}
