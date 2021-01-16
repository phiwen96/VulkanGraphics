#include "queue.hpp"


uint32_t Queue::getIndex (Device::Physical const& physicalDevice, Type const& type) {
      
      if (type == Type::Graphics){
            if (!physicalDevice.m_graphicsFamily.has_value()){
                  throw std::runtime_error ("Physical device does not have a graphics family.");
            }
            return physicalDevice.m_graphicsFamily.value();
      } else if (type == Type::Compute){
            if (!physicalDevice.m_computeFamily.has_value()){
                  throw std::runtime_error ("Physical device does not have a graphics family.");
            }
            return physicalDevice.m_computeFamily.value();
      } else if (type == Type::Present) {
            
      }
      throw std::runtime_error ("failed to find queue family on physical device!");
}

ostream& operator<< (ostream& os, Queue::Type const& t) {
      using Type = Queue::Type;
      switch (t)
      {
            case Type::Graphics:
                  os << "Graphics";
                  break;
            case Type::Compute:
                  os << "Compute";
                  break;
      }
      return os;
}
