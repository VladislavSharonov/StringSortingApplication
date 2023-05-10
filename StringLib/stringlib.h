#pragma once
#include <algorithm>
#include <cstring>

class String {
public:
    explicit String(const char* data);
    String(const String& other);
    String(String&& other) noexcept;
    virtual ~String() noexcept;

    void operator+=(const String& other);
    void operator+=(const char* other);
    String& operator=(String&& other) noexcept;
    String& operator=(const String& other);
    String& operator=(const char* other);

    const char* CStr() const { return _data; }
    size_t Length() const { return _length; }
    size_t Capacity() const { return _capacity; }

    static String Concat(const char* data, const char* otherData, size_t minCapacity = String::minCapacity);

    static constexpr size_t minCapacity = 15;
    static constexpr size_t capacityMultiplier = 2;

private:
    String() = default;

    void InitializeWithCopyOf(const char* data, size_t length);
    void Append(const char* data, size_t length);

    char* _data = nullptr;
    size_t _length = 0;
    size_t _capacity = 0;

    static void CheckString(const char* data);
    static size_t ComputeMinCapacityToAllocate(size_t length);
};

String operator+(const String& left, const String& right);
String operator+(const String& left, const char* right);
String operator+(const char* left, const String& right);
