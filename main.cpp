#include <algorithm>
#include <iostream>
#include <list>
#include <stringlib.h>

bool is_greater_or_equal(const String& left, const String& right)
{
    return !std::lexicographical_compare(
        left.CStr(),
        left.CStr() + left.Length(),
        right.CStr(),
        right.CStr() + right.Length(),
        [](char left, char right) { return tolower(left) < tolower(right); });
}

std::list<String> read_strings(size_t count)
{
    std::list<String> strings;
    constexpr int maxStringLength = 256;
    char str[maxStringLength];
    for (int i = 0; i < count; ++i) {
        std::cin.getline(str, maxStringLength);
        strings.emplace_back(str);
    }
    return strings;
}

int main()
{
    std::cout << "=========[ String Sort ]=========\n\n";

    std::cout << "Enter the number of strings:\n";
    size_t count = 0;
    std::cin >> count;

    std::cout << "Enter strings(one per line):\n";
    std::cin.ignore();
    std::list<String> strings = read_strings(count);
    strings.sort(is_greater_or_equal);

    std::cout << "Strings in reverse lexicographic order:\n";
    for (const String& s : strings)
        std::cout << s.CStr() << "\n";

    std::cout << "Press Enter to exit...\n";
    getchar();

    return 0;
}
