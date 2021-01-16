#pragma once
// #include "create.hpp"
// #include "str.hpp"
// #include "vec.hpp"


// namespace ph::vulk{


// void main(){
//       vk::ApplicationInfo appInfo
//       {
//             "Hello Triangle",
//             VK_MAKE_VERSION(1, 0, 0),
//             "No Engine",
//             VK_MAKE_VERSION(1, 0, 0),
//             VK_API_VERSION_1_0
//       };
      
      
//       auto extensions = []() -> vec<str, int>
//       {
//             uint32_t glfwExtensionCount = 0;
//             const char** glfwExtensions;
//             glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//             return {glfwExtensions, glfwExtensions + glfwExtensionCount};
//       }();
      
//       auto layers = []() -> vec<str, int>
//       {
//             return str{"VK_LAYER_LUNARG_standard_validation"};
//       }();
      
//       cout << "kuk" << endl;
      
      
      
      
      
      
      
//       //      std::tuple<int, char> tup;
//       //      auto tup = make_tuple(extensions, layers);
      
//       //      create<Instance>(tup);
//       auto instance = create<Instance>({[]{
//             uint32_t glfwExtensionCount = 0;
//             const char** glfwExtensions;
//             glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//             return vec<str,int>{glfwExtensions, glfwExtensions + glfwExtensionCount};
//       }(), []{
//             return vec<str, int>{"VK_LAYER_LUNARG_standard_validation"};
//       }()});
//       //      Convert a {{5, 5}};
//       //      Convert<int, char, int const(&)[10]> a;
//       auto t = make_tuple(4, 'g');
//       Convert a (t);
//       auto t2 = vector<int>{1, 2, 3};
//       Convert a2 (t2);
// }


// }
