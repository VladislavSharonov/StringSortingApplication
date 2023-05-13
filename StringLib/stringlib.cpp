#include "stringlib.h"
#include <stdexcept>

#pragma region Utils
void String::CheckString(const char* data)
{
    if (data == nullptr)
        throw std::invalid_argument("Nullptr string is not valid");
}

size_t String::ComputeMinCapacityToAllocate(size_t length)
{
    return length < minCapacity ? minCapacity : length;
}

void String::InitializeWithCopyOf(const char* data, size_t length)
{
    if (length > _capacity || _capacity == 0) {
        delete[] _data;
        _capacity = ComputeMinCapacityToAllocate(length);
        _data = new char[_capacity + 1];
    }

    if (length != 0)
        strcpy(_data, data);
    _length = length;
    _data[_length] = '\0';
}

String String::Concat(const char* data, const char* otherData, size_t minimumCapacity)
{
    CheckString(data);
    CheckString(otherData);

    size_t length = strlen(data);
    size_t otherLength = strlen(otherData);
    String result;
    result._length = length + otherLength;
    if (result._length == 0)
        return String("");

    result._capacity = result._length < minimumCapacity
        ? minimumCapacity
        : ComputeMinCapacityToAllocate(result._length);
    result._data = new char[result._capacity + 1];
    strcpy(result._data, data);
    strcpy(result._data + length, otherData);
    result._data[result._length] = '\0';
    return result;
}

void String::Append(const char* data, size_t length)
{
    if (length == 0)
        return;

    size_t newLength = _length + length;
    if (newLength > _capacity)
        *this = std::move(Concat(_data, data, _capacity * capacityMultiplier));
    else {
        strcat(_data, data);
        _length = newLength;
    }
}
#pragma endregion

#pragma region Constructors and Destructor
String::String(const char* data)
{
    CheckString(data);
    InitializeWithCopyOf(data, strlen(data));
}

String::String(const String& other)
{
    InitializeWithCopyOf(other._data, other._length);
}

String::String(String&& other) noexcept
    : _data(other._data)
    , _length(other._length)
    , _capacity(other._capacity)
{
    other._data = nullptr;
    other._length = 0;
    other._capacity = 0;
}

String::~String() noexcept
{
    delete[] _data;
    _data = nullptr;
    _length = 0;
    _capacity = 0;
}
#pragma endregion

#pragma region Operators
void String::operator+=(const char* other)
{
    CheckString(other);
    Append(other, strlen(other));
}

void String::operator+=(const String& other)
{
    Append(other._data, other.Length());
}

String& String::operator=(String&& other) noexcept
{
    if (this == &other)
        return *this;

    delete[] _data;
    _data = other._data;
    _length = other._length;
    _capacity = other._capacity;

    other._data = nullptr;
    other._length = 0;
    other._capacity = 0;
    return *this;
}

String& String::operator=(const String& other)
{
    if (this != &other)
        InitializeWithCopyOf(other._data, other._length);
    return *this;
}

String& String::operator=(const char* other)
{
    CheckString(other);
    InitializeWithCopyOf(other, strlen(other));
    return *this;
}

size_t compute_min_capacity_to_reallocate(size_t firstLength, size_t firstCapacity, size_t secondLength)
{
    size_t capacity = firstCapacity;
    if (firstLength + secondLength > capacity)
        capacity *= String::capacityMultiplier;

    return capacity;
}

String operator+(const String& left, const String& right)
{
    size_t capacity = compute_min_capacity_to_reallocate(
        left.Length(),
        left.Capacity(),
        right.Length());
    return String::Concat(left.CStr(), right.CStr(), capacity);
}

String operator+(const String& left, const char* right)
{
    size_t capacity = compute_min_capacity_to_reallocate(
        left.Length(),
        left.Capacity(),
        strlen(right));
    return String::Concat(left.CStr(), right, capacity);
}

String operator+(const char* left, const String& right)
{
    return String::Concat(left, right.CStr());
}
#pragma endregion