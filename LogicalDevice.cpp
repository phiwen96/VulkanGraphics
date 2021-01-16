#include "LogicalDevice.hpp"


//uint32_t Device::Logical::Queue::getIndex (Device::Physical const& physicalDevice, Type const& type) {
//      if (type == Type::Graphics){
//            if (!physicalDevice.m_graphicsFamily.has_value()){
//                  throw std::runtime_error ("Physical device does not have a graphics family.");
//            }
//            return physicalDevice.m_graphicsFamily.value();
//      } else if (type == Type::Compute){
//            if (!physicalDevice.m_computeFamily.has_value()){
//                  throw std::runtime_error ("Physical device does not have a graphics family.");
//            }
//            return physicalDevice.m_computeFamily.value();
//      }
//      throw std::runtime_error ("failed to find queue family on physical device!");
//}


//ostream& operator<< (ostream& os, Device::Logical::Queue::Type const& t) {
//      using Type = Device::Logical::Queue::Type;
//      switch (t)
//      {
//            case Type::Graphics:
//                  os << "Graphics";
//                  break;
//            case Type::Compute:
//                  os << "Compute";
//                  break;
//      }
//      return os;
//}
