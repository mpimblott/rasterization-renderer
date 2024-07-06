#pragma once

//https://stackoverflow.com/q/44037870
template <typename T>
class Property
{
private:
  T& t;
public:
    inline Property(T& a): t(a) {}

    inline void Set(const T &a) { t = a; }
    inline T& Get() { return t; }

    operator T&() { return t; }
    T &operator=(const T &a) { return t = a; }
};