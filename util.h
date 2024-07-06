#pragma once

//https://stackoverflow.com/q/44037870
class Property
{
private:
  float& t;
public:
    inline Property(float& a): t(a) {}

    inline void Set(const float &a) { t = a; }
    inline float& Get() { return t; }

    operator float&() { return t; }
    float &operator=(const float &a) { return t = a; }
};