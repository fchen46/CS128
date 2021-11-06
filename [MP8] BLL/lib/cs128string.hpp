#ifndef _CS128_STRING_HPP
#define _CS128_STRING_HPP

#include <cstddef>
#include <ostream>
#include <cstring>

namespace cs128 {
  class string {
    public:
      string();
      string(const string& rhs);
      string(const char* rhs);
      string(char rhs);
      ~string();
      size_t size() const;
      size_t length() const;
      bool empty() const;
      string& operator=(const string& rhs);
      string& operator=(const char* rhs);
      string& operator=(char rhs);
      void push_back(char c);
      void push_front(char c);
      void pop_back();
      void clear();
      char at(size_t idx) const;
      const char& operator[] (size_t idx) const;
      void append(const string& rhs);
      void append(const char* rhs);
      void append(char rhs);
      string& operator+=(const string& rhs);
      string& operator+=(const char* rhs);
      string& operator+=(char rhs);
      friend std::ostream& operator<<(std::ostream& os, const string &rhs);
      int strcmp(const string& rhs) const;
      int strcmp(const char* rhs) const;
    private:
      struct _string_node {
        char data = ' ';
        _string_node* next = nullptr;
      };
      typedef _string_node* _string_node_t;

      size_t _size = 0;
      _string_node_t _head = nullptr;
      _string_node_t _tail = nullptr;

      void free();
      const char* c_str() const;
  };

  string itoa(int tgt);

  inline auto operator<=>(const string& lhs, const string& rhs);
  inline bool operator==(const string& lhs, const string& rhs);
  inline bool operator!=(const string& lhs, const string& rhs);

  inline auto operator<=>(const string& lhs, const char* rhs);
  inline bool operator==(const string& lhs, const char* rhs);
  inline bool operator!=(const string& lhs, const char* rhs);

  inline auto operator<=>(const char* lhs, const string& rhs);
  inline bool operator==(const char* lhs, const string& rhs);
  inline bool operator!=(const char* lhs, const string& rhs);

  inline auto operator<=>(const string& lhs, const string& rhs) { return lhs.strcmp(rhs); }
  inline bool operator==(const string& lhs, const string& rhs) { return (lhs <=> rhs) == 0; }
  inline bool operator!=(const string& lhs, const string& rhs) { return !(lhs == rhs); }

  inline auto operator<=>(const string& lhs, const char* rhs) { return lhs.strcmp(rhs); }
  inline bool operator==(const string& lhs, const char* rhs) { return (lhs <=> rhs) == 0; }
  inline bool operator!=(const string& lhs, const char* rhs) { return !(lhs == rhs); }

  inline auto operator<=>(const char* lhs, const string& rhs) { return rhs <=> lhs; }
  inline bool operator==(const char* lhs, const string& rhs) { return rhs == lhs; }
  inline bool operator!=(const char* lhs, const string& rhs) { return rhs != lhs; }
}

#endif // _CS128_STRING_HPP
