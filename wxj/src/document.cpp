#include "document.h"
#include <algorithm>
using namespace wxj;

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
