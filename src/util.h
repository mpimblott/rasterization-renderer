#pragma once

// https://stackoverflow.com/q/44037870
template <typename T>
class Property {
   private:
    T &t;

   public:
    inline Property(T &a) : t(a) {}

    operator T &() { return t; }
    T &operator=(const T &a) { return t = a; }
};