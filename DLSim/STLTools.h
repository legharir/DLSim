#pragma once

#include <optional>
#include <unordered_set>
#include <vector>

namespace STLTools
{
    template <typename T>
    T getElement(const std::unordered_set<T>& set, const T& elem, T defaultValue = T())
    {
        const auto itr = set.find(elem);
        if (itr != set.end())
        {
            return *itr;
        }
        else
        {
            return defaultValue;
        }
    }

    template <typename T>
    void extend(std::vector<T>& vec, const std::vector<T> extendVec)
    {
        vec.reserve(vec.size() + distance(extendVec.begin(), extendVec.end()));
        vec.insert(vec.end(), extendVec.begin(), extendVec.end());
    }
} // namespace STLTools