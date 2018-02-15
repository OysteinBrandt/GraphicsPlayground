#ifndef ENGINE_STL_UTIL_HPP
#define ENGINE_STL_UTIL_HPP

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v)
{
  s.put('[');
  char comma[3] = { '\0', ' ', '\0' };
  for (const auto& e : v)
  {
    s << comma << e;
    comma[0] = ',';
  }
  return s << ']';
}

#endif // !ENGINE_STL_UTIL_HPP