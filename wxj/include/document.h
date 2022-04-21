#pragma once

#include "types.h"
#include "observer.h"
#include "registry.h"

#include <list>
#include <mutex>

namespace wxj
{
    class Document : public Subject<std::string>
    {
    public:
        using Pointer = std::shared_ptr<Document>;

        Document(String tag);
        ~Document();
        void lock();
        void unlock();

        Json &json();
        const String getTag() const;

        void notify();

    private:
        const String m_tag;
        Json m_doc;
        std::recursive_mutex m_mtx;
    };

    using DocumentRegistry = Registry<std::shared_ptr<Document>>;
}
