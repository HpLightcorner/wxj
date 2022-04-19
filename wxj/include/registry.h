#pragma once

#include <unordered_map>

namespace wxj
{
    template <typename T>
    class Registry
    {
    public:
        void add(const std::string tag, T value)
        {
            m_registry[tag] = value;
        }

        std::optional<T> get(const std::string tag)
        {
            if (m_registry.count(tag) > 0)
            {
                return m_registry[tag];
            }

            return std::nullopt;
        }

        static Registry<T> &instance()
        {
            static Registry<T> instance;
            return instance;
        }

    private:
        Registry() = default;
        std::unordered_map<std::string, T> m_registry;
    };

    template <typename T>
    class MultiRegistry
    {
    public:
        void add(const std::string tag, T value)
        {
            m_registry[tag].push_back(value);
        }

        std::optional<std::vector<T>> get(const std::string tag)
        {
            if (m_registry.count(tag) > 0)
            {
                return m_registry[tag];
            }

            return std::nullopt;
        }

        static MultiRegistry<T> &instance()
        {
            static MultiRegistry<T> instance;
            return instance;
        }

    private:
        MultiRegistry() = default;
        std::unordered_map<std::string, std::vector<T>> m_registry;
    };
}
