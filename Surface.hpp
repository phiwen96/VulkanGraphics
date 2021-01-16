#pragma once
#include "Create.hpp"
#include "Info.hpp"


struct Surface
{
      Surface (Surface&& other) : m_instance (other.m_instance) {
            swap (*this, other);
            cout << "Surface::Surface(Surface&& other)" << endl;
      }
      Surface (Surface const& other) : m_surface (other.m_surface), m_instance (other.m_instance) {
            cout << "Surface::Surface(Surface const& other)" << endl;
      }
      Surface (VkSurfaceKHR const& surface, VkInstance const& instance) : m_surface (surface), m_instance (instance) {
            cout << "Surface::Surface(VkSurfaceKHR const&, VkInstance const&)" << endl;
      }
      Surface (VkSurfaceKHR&& surface, VkInstance const& instance) : m_surface (std::move(surface)), m_instance (instance) {
            cout << "Surface::Surface(VkSurfaceKHR&&, VkInstance const&)" << endl;
      }
      ~Surface () {
            vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
      }
      friend void swap (Surface& lhs, Surface& rhs) {
            using std::swap;
            swap (lhs.m_surface, rhs.m_surface);
      }
      operator VkSurfaceKHR& (){
            cout << "VkSurfaceKHR const&()" << endl;
            return m_surface;
      }
      
//private:
      VkSurfaceKHR m_surface;
      VkInstance const& m_instance;
      
};


template <>
struct Create <Surface>
{
      Create (VkInstance const& instance, GLFWwindow * window);
      
      operator Surface () {
            return {m_surface, m_instance};
      }
      
      
      VkSurfaceKHR m_surface;
      VkInstance const& m_instance;
};
