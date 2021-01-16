#include "Surface.hpp"


Create<Surface>::Create (VkInstance const& instance, GLFWwindow * window) : m_instance (instance){
      
      if (glfwCreateWindowSurface(instance, window, nullptr, &m_surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
      }
      }
