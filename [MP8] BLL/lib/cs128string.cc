#include "cs128string.hpp"

namespace cs128 {
  string itoa(int tgt) {
    int tmp = tgt;
    string st;
    while(tmp > 0) {
      st.push_front((tmp % 10) + '0');
      tmp /= 10;
    }
    return st;
  }
  string::string() {
    clear();
  }
  string::string(const string& rhs) {
    clear();
    append(rhs);
  }
  string::string(const char* rhs) {
    clear();
    append(rhs);
  }
  string::string(char rhs) {
    clear();
    append(rhs);
  }
  string::~string() {
    clear();
  }
  size_t string::size() const { return _size; }
  size_t string::length() const { return _size; }
  bool string::empty() const { return _size == 0; }
  string& string::operator=(const string& rhs) {
    if(this == &rhs) return *this;
    clear();
    append(rhs);
    return *this;
  }
  string& string::operator=(const char* rhs) {
    clear();
    append(rhs);
    return *this;
  }
  string& string::operator=(char rhs) {
    clear();
    append(rhs);
    return *this;
  }
  void string::push_back(char c) {
    _string_node_t new_node = new _string_node;
    new_node->data = c;
    new_node->next = nullptr;
    _size += 1;
    if(this->_head == nullptr) {
        this->_head = new_node;
        this->_tail = new_node;
        return;
    }
    _tail->next = new_node;
    _tail = new_node;
    return; // unreachable
  }
  void string::push_front(char c) {
    _string_node_t new_node = new _string_node;
    new_node->data = c;
    _size += 1;
    if(this->_head == nullptr) {
        this->_head = new_node;
        this->_tail = new_node;
        return;
    }
    new_node->next = _head;
    _head = new_node;
    return; // unreachable
  }
  void string::pop_back() {
    if(_head == nullptr) return;
    _string_node_t it = _head;
    _string_node_t prev = nullptr;
    while(it->next != nullptr) {
      prev = it;
      it = it->next;
    }
    if(prev == nullptr) _head = nullptr;
    else prev->next = nullptr;
    _tail = prev;
    _size -= 1;
    delete it;
  }
  const char* string::c_str() const {
    char* data = new char[_size+1];
    _string_node_t it = _head;
    size_t i = 0;
    while(it != nullptr) {
      data[i] = it->data;
      ++i;
      it = it->next;
    }
    data[i] = 0;
    return data;
  }
  void string::clear() {
    free();
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
  }
  char string::at(size_t idx) const {
    if(idx >= _size) {
      string msg = "Attempting to access index ";
      msg += itoa(static_cast<int>(idx));
      msg += " when string size is ";
      msg += itoa(static_cast<int>(_size));
      msg.push_back('.');
      char* text = (char*) alloca(sizeof(char) * (msg.length() + 1));
      const char* a = msg.c_str();
      sprintf(text, "%s", a);
      delete[] a;
      throw std::out_of_range(text);
    }
    _string_node_t it = _head;
    for(size_t i = 0; i < idx; ++i) it = it->next;
    return it->data;
  }
  const char& string::operator[] (size_t idx) const {
    if(idx >= _size) {
      int* ptr = NULL;
      *ptr = 1; // forced segfault
    }
    _string_node_t it = _head;
    for(size_t i = 0; i < idx; ++i) it = it->next;
    return it->data;
  }
  void string::append(const string& rhs) {
    _string_node_t it = rhs._head;
    while(it != nullptr) {
      push_back(it->data);
      it = it->next;
    }
  }
  void string::append(const char* rhs) {
    for(size_t i = 0; i < strlen(rhs); ++i) push_back(rhs[i]);
  }
  void string::append(char rhs) {
    push_back(rhs);
  }
  string& string::operator+=(const string& rhs) {
    append(rhs);
    return *this;
  }
  string& string::operator+=(const char* rhs) {
    append(rhs);
    return *this;
  }
  string& string::operator+=(char rhs) {
    append(rhs);
    return *this;
  }
  std::ostream& operator<<(std::ostream& os, const string& rhs) {
      string::_string_node_t it = rhs._head;
      while(it != nullptr) {
        os << it->data;
        it = it->next;
      }
      return os;            
  }
  int string::strcmp(const string& rhs) const {
      const char* a = c_str();
      const char* b = rhs.c_str();
      bool c = std::strcmp(a, b);
      delete[] a;
      delete[] b;
      return c;
  }
  int string::strcmp(const char* rhs) const {
    const char* a = c_str();
    bool b = std::strcmp(a, rhs);
    delete[] a;
      return b;
  }
  void string::free() {
    _string_node_t it = _head;
    while(it != nullptr) {
      _string_node_t next = it->next;
      delete it;
      it = next;
    }
  }

}
