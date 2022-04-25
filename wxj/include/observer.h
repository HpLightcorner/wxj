#pragma once

#include <list>
#include <algorithm>
#include <stdexcept>

namespace wxj
{
    template <typename T>
    class IObserver
    {
    public:
        using WeakPointer = IObserver<T> *;
        virtual ~IObserver(){};
        virtual void update(T message_from_subject) = 0;
    };

    template <typename T, int num_observers = 0>
    class Subject
    {
    public:
        void attach(IObserver<T> *observer)
        {
            bool found = (std::find(m_observers.begin(), m_observers.end(), observer) != m_observers.end());
            if (found)
                return;

            if (num_observers > 0)
            {
                if (m_observers.size() > num_observers)
                {
                    throw std::runtime_error("More observers given than allowed.");
                }
            }
            m_observers.push_back(observer);
        }

        void detach(IObserver<T> *observer)
        {
            m_observers.remove(observer);
        }

        void notify(T data)
        {
            for (const auto &observer : m_observers)
            {
                observer->update(data);
            }
        }

    private:
        std::list<IObserver<T> *> m_observers;
    };
}
