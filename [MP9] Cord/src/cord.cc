#include "cord.hpp"

#include <stdexcept>
#include <string>

Cord::Cord(std::string dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(Cord* left_cord, Cord* right_cord) {
  left_ = left_cord;
  right_ = right_cord;
  if (left_cord == nullptr) {
    length_ = right_cord->length_;
  } else if (right_cord == nullptr) {
    length_ = left_cord->length_;
  } else {
    length_ = left_cord->length_ + right_cord->length_;
  }
}

size_t Cord::Length() const { return length_; }

Cord* Cord::GetLeft() const { return left_; }

Cord* Cord::GetRight() const { return right_; }

Cord*& Cord::GetLeftRef() { return left_; };
Cord*& Cord::GetRightRef() { return right_; };

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
  if (GetLeft() == nullptr && GetRight() == nullptr) {
    return GetData();
  }
  if (GetLeft() != nullptr && GetRight() != nullptr) {
    return GetData() + GetLeft()->ToString() + GetRight()->ToString();
  }
  if (GetRight() != nullptr && GetRight() == nullptr) {
    return GetData() + GetRight()->ToString();
  }
  if (GetLeft() != nullptr && GetRight() == nullptr) {
    return GetData() + GetLeft()->ToString();
  }
  return GetData();
}

Cord* Cord::SubString(size_t lower_idx, size_t upper_idx) {
  if (GetLeft() == nullptr && GetRight() == nullptr) {
    if (lower_idx == 0 && upper_idx == Length()) {
      return this;
    }
    std::string str = GetString(lower_idx, upper_idx);
    Cord* new_cord = new Cord(str);
    return new_cord;
  }
  if (lower_idx == 0 && upper_idx == Length()) {
    return this;
  }
  if (upper_idx <= GetLeft()->Length()) {
    return GetLeft()->SubString(lower_idx, upper_idx);
  }
  if (upper_idx >= GetLeft()->Length() && lower_idx < GetLeft()->Length()) {
    size_t splice_point = GetLeft()->Length();
    return ConcatCords(GetLeft()->SubString(lower_idx, splice_point),
                       GetRight()->SubString(0, upper_idx - splice_point));
  }
  if (lower_idx >= GetLeft()->Length()) {
    size_t left_len = GetLeft()->Length();
    return GetRight()->SubString(lower_idx - left_len, upper_idx - left_len);
  }
  return this;
}

std::string Cord::GetString(size_t lower_idx, size_t upper_idx) {
  std::string str = "";
  for (int i = (int)lower_idx; i < (int)upper_idx; i++) {
    str += At(i);
  }
  return str;
}

bool Cord::IsValidCord() const {
  if (GetLeft() == nullptr && GetRight() == nullptr) {
    return true;
  }
  if (GetLeft() != nullptr && GetRight() != nullptr) {
    if (Length() != GetLeft()->Length() + GetRight()->Length()) {
      return false;
    }
    return GetLeft()->IsValidCord() && GetRight()->IsValidCord();
  }
  if (GetLeft() != nullptr) {
    if (Length() != GetLeft()->Length()) {
      return false;
    }
    return GetLeft()->IsValidCord();
  }
  if (GetRight() != nullptr) {
    if (Length() != GetRight()->Length()) {
      return false;
    }
    return GetRight()->IsValidCord();
  }
  return true;
}

char Cord::At(size_t idx) const {
  // Check for index out of bound
  if (idx < 0 || idx >= Length()) {
    throw std::runtime_error("Index Out Of Bound");
  }
  char to_return = '\0';
  // Base Case
  if (GetLeft() == nullptr && GetRight() == nullptr) {
    std::string data = GetData();
    for (char c : data) {
      if (idx == 0) {
        return c;
      }
      idx--;
    }
  }
  // Left and Right
  if (GetLeft() != nullptr && GetRight() != nullptr) {
    // Left word is not long enough
    if (GetLeft()->Length() <= idx) {
      return GetRight()->At(idx - GetLeft()->Length());
    }
    // Left word is long enough
    return GetLeft()->At(idx);
  }
  // Left Only
  if (GetLeft() != nullptr) {
    return GetLeft()->At(idx);
  }
  // Right Only
  if (GetRight() != nullptr) {
    return GetRight()->At(idx);
  }
  return to_return;
}
