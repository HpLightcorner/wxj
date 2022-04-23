#pragma once
#include <unordered_map>
#include <string>

namespace wxj
{
    template <typename T>
    class Registry
    {
    public:
        void add(const std::string tag, T value)
        {
            bool found = m_registry.find(tag) != m_registry.end();
            if (!found)
            {
                m_registry[tag] = value;
            }
            else
            {
                throw std::runtime_error("Given tag already exists in regsitry.");
            }
        }

        void remove(const std::string tag)
        {
            auto it = m_registry.find(tag);
            if (it != m_registry.end())
            {
                m_registry.erase(it);
            }
        }

        bool exists(const std::string tag) const
        {
            return m_registry.find(tag) != m_registry.end();
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
}
