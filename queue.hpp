#pragma once
#include "Info.hpp"
#include "Create.hpp"
#include "PhysicalDevice.hpp"

namespace ph::data_structures{

template <class Element>
class queue
{
public:
      bool empty () const {
            return m_begin == nullptr;
      }
      Element& top () {
            assert(!empty());
            return *m_begin->m_element;
      }
      queue& pop () {
            assert(!empty());
            node* newT = m_begin -> m_rest;
            m_begin -> m_rest = nullptr;
            delete m_begin;
            m_begin = newT;
            return *this;
      }
      
      queue () : m_begin (nullptr), m_end (nullptr) {

      }
      queue (Element element) : m_begin (new node {new Element (element), nullptr}), m_end (nullptr) {
            m_end = m_begin;
            cout << element << endl;
      }
      queue (Element element, queue s) : queue () {
            s += element;
            swap (*this, s);
      }
      
      friend void swap (queue& lhs, queue& rhs) {
            using std::swap;
            swap (lhs.m_begin, rhs.m_begin);
            swap (lhs.m_end, rhs.m_end);
      }
      queue& operator+= (Element element) {
            if ( m_end == nullptr ) {
                  m_begin = new node {new Element (element), nullptr};
                  m_end = m_begin;
//                  cout << "yeah" << *m_begin->m_element << endl;
            } else {
//                  cout << "whaat" << *m_begin->m_element << endl;
                  m_end -> m_rest = new node {new Element (element), nullptr};
                  m_end = m_end -> m_rest;
            }
            return *this;
      }
      queue& operator-- (int) {
            assert(!empty());
            node* newT = m_begin -> m_rest;
            m_begin -> m_rest = nullptr;
            delete m_begin;
            m_begin = newT;
            return *this;
      }
      friend ostream& operator<< (ostream& os, queue const& s) {
            if (s.m_begin != nullptr)
                  os << *s.m_begin;
            return os;
      }
      
private:
      struct node {
            Element*    m_element {nullptr};
            node*       m_rest    {nullptr};
            
            ~node () {
                  delete m_element;
                  delete m_rest;
            }
            friend ostream& operator<< (ostream& os, node const& q) {
                  os << *q.m_element << " ";
                  if (q.m_rest != nullptr)
                        os << *q.m_rest;
                  return os;
            }
      };
      node* m_begin;
      node* m_end;
};




}




struct Queue
{
      enum class Type{Graphics, Compute, Present};
      
      Queue () {
            
      }
      Queue (Queue&& other) : Queue () {
            swap (*this, other);
      }
      Queue (Queue const& other) : m_queue (other.m_queue), m_type (other.m_type) {
            
      }
      Queue (VkQueue && queue, Type type) : m_queue (std::move (queue)), m_type (type) {
            
      }
      Queue (VkQueue const& queue, Type type) : m_queue (queue), m_type (type) {
            
      }
      
      friend void swap (Queue& lhs, Queue& rhs) {
            using std::swap;
            swap (lhs.m_queue, rhs.m_queue);
            swap (lhs.m_type, rhs.m_type);
      }
      
      VkQueue m_queue;
      Type m_type;
      
      static uint32_t getIndex (Device::Physical const& physicalDevice, Type const& type);
};


//template <>
//struct Info <Queue>
//{
//      uint32_t    m_index;
//      Queue::Type m_type;
//};

ostream& operator<< (ostream& os, Queue::Type const& t);
