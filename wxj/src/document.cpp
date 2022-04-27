#include "document.h"
#include <algorithm>
using namespace wxj;

void wxj::registerDocument(Document::Pointer doc)
{
    auto &reg = DocumentRegistry::instance();
    reg.add(doc->getTag(), doc);
}

void wxj::unregisterDocument(Document::Pointer doc)
{
    auto &reg = DocumentRegistry::instance();
    reg.remove(doc->getTag());
}

Document::Document(String tag) : m_tag(tag)
{
}

Document::~Document()
{
}

Json &Document::json()
{
    return m_doc;
}

const String Document::getTag() const
{
    return m_tag;
}

void Document::lock()
{
    m_mtx.lock();
}

void Document::unlock()
{
    m_mtx.unlock();
}

void Document::notify()
{
    Subject::notify(m_tag);
}
