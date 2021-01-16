#pragma once

#include <ph/common/vec.hpp>
#include <ph/common/str.hpp>
#include "Info.hpp"
#include "Create.hpp"

using ph::vec;
using ph::str;

struct Window
{
      Window () : m_window (nullptr) {
            
      }
      Window (Window&& other) : Window () {
            swap (*this, other);
      }
      Window (Window const& other) : m_width (other.m_width), m_height (other.m_height), m_title (other.m_title) {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
      }
      Window (uint32_t width, uint32_t height, char const* title) : m_window ([&width, &height, &title]{
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            GLFWwindow* window = glfwCreateWindow(width, height, "hej", nullptr, nullptr);
            return window;
      }()), m_width (width), m_height (height), m_title (title)
      {
            //            glfwSetWindowCloseCallback(m_window, window_close_callback);
      }
      ~Window (){
            glfwDestroyWindow(m_window);
      }
      void show (){
            while (!glfwWindowShouldClose(m_window)) {
                  glfwPollEvents();
            }
      }
      operator GLFWwindow* (){
            return m_window;
      }
      friend void swap (Window& lhs, Window& rhs) {
            using std::swap;
            swap (lhs.m_window, rhs.m_window);
            swap (lhs.m_width, rhs.m_width);
            swap (lhs.m_height, rhs.m_height);
            swap (lhs.m_title, rhs.m_title);
      }
//private:
      GLFWwindow* m_window;
      uint32_t m_width;
      uint32_t m_height;
      char const* m_title;
      
//      static void window_close_callback(GLFWwindow* window)
//      {
//                  glfwSetWindowShouldClose(window, GLFW_TRUE);
//      }
};






