#pragma once

#ifndef _ENGINE_TYPE_TRAITS_H_
#define _ENGINE_TYPE_TRAITS_H_

#include <type_traits>
#include <ostream>

template <
  typename T, 
  typename Tag, // Tag models a phantom type
  template <typename> class... Skills
> 
class NamedType : public Skills<NamedType<T, Tag, Skills...>>...
{
private:
  T m_value;

public:
  explicit constexpr NamedType(const T& value)
    : m_value(value) {}

  // Use SFINAE to allow strong types of references
  template <typename T_ = T>
  explicit constexpr NamedType(T&& value, typename std::enable_if_t<!std::is_reference_v<T_>, std::nullptr_t> = nullptr)
    : m_value(std::move(value)) {}

  constexpr T& get() { return m_value; }
  constexpr const T& get() const { return m_value; }
};

/*********************************************************/

template <typename T, template<typename> class crtpType>
struct crtp
{
  T& underlying() { return static_cast<T&>(*this); }
  const T& underlying() const { return static_cast<const T&>(*this); }
};

/*********************************************************/

// -- Skills ---------------

/*********************************************************/

template <typename T>
struct Assignment : crtp<T, Assignment>
{
  // TODO: https://en.cppreference.com/w/cpp/language/operator_assignment

  T& operator += (const T& other) { this->underlying().get() += other.get(); return this->underlying(); }
};

/*********************************************************/

template <typename T>
struct Comparison : crtp<T, Comparison>
{
  // TODO: https://en.cppreference.com/w/cpp/language/operator_comparison

  bool operator < (const T& other) const { return this->underlying().get() < other.get(); }
  bool operator > (const T& other) const { return this->underlying().get() > other.get(); }
};

/*********************************************************/

template <typename T>
struct Arithmetic : crtp<T, Arithmetic>
{
  // TODO: https://en.cppreference.com/w/cpp/language/operator_arithmetic

  T operator - () const { return T(-this->underlying().get()); }
};

/*********************************************************/

template <typename T>
struct Printable : crtp<T, Printable>
{
  void print(std::ostream& os) const { os << this->underlying().get(); }
};

template <typename T, typename Tag, template<typename> class... Skills>
std::ostream& operator<<(std::ostream& os, const NamedType<T, Tag, Skills...>& object)
{
  object.print(os);
  return os;
}

/*********************************************************/

#endif