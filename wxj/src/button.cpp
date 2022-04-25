#include "button.h"
#include "common.h"
#include "binding.h"

#include <thread>

using namespace wxj;

BEGIN_EVENT_TABLE(wxjButton, wxPanel)

EVT_LEFT_DOWN(wxjButton::mouseDown)
EVT_LEFT_UP(wxjButton::mouseReleased)
EVT_LEAVE_WINDOW(wxjButton::mouseLeftWindow)
EVT_ENTER_WINDOW(wxjButton::mouseEnterWindow)
EVT_PAINT(wxjButton::paintEvent)

END_EVENT_TABLE()

wxjButton::wxjButton(wxWindow *parent, Settings settings) : wxWindow(),
                                                            m_settings(settings),
                                                            m_state(State::Default)
{
    // Make sure to take full control over paint/erase events
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Create a transparent window
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW);
    
    SetPosition(m_settings.pos);
    SetSize(m_settings.size);

    if (m_settings.bg)
    {
        auto bg = m_settings.bg.value();
        m_default = getScaledBitmap(bg._default, m_settings.size);

        if (bg.current)
        {
            m_current = getScaledBitmap(bg.current.value(), m_settings.size);
        }

        if (bg.pressed)
        {
            m_pressed = getScaledBitmap(bg.pressed.value(), m_settings.size);
        }

        if (bg.disabled)
        {
            m_disabled = getScaledBitmap(bg.disabled.value(), m_settings.size);
        }
    }
}

void wxjButton::paintEvent([[maybe_unused]] wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void wxjButton::paintNow()
{
    // Refresh Background to allow transparent buttons/images with alpha channel
    auto rect = wxRect(m_settings.pos, m_settings.size);
    GetParent()->Refresh(false, &rect);
}

void wxjButton::render(wxDC &dc)
{
    wxBitmap bitmap = m_default.value();
    switch (m_state)
    {
    case State::Default:
        if (m_default)
            bitmap = m_default.value();
        break;
    case State::Current:
        if (m_current)
            bitmap = m_current.value();
        break;
    case State::Disabled:
        if (m_disabled)
            bitmap = m_disabled.value();
        break;
    case State::Pressed:
        if (m_pressed)
            bitmap = m_pressed.value();
        break;
    }
    wxString label = "";

    if (bitmap.IsOk())
    {
        dc.DrawBitmap(bitmap, 0, 0, false);
    }

    if (m_settings.label)
    {
        wxRect rect(m_settings.size);
        dc.DrawLabel(m_settings.label.value(), rect, wxALIGN_CENTER);
    }
}

void wxjButton::mouseDown([[maybe_unused]] wxMouseEvent &event)
{
    m_state = State::Pressed;
    paintNow();
}
void wxjButton::mouseReleased([[maybe_unused]] wxMouseEvent &event)
{
    if (m_state == State::Pressed)
    {
        // We captured a click
        m_state = State::Current;
        onButtonEvent();
    }
    else
    {
        m_state = State::Default;
    }
    paintNow();
}
void wxjButton::mouseLeftWindow([[maybe_unused]] wxMouseEvent &event)
{
    if (m_state != State::Default)
    {
        m_state = State::Default;
        paintNow();
    }
}

// currently unused events
void wxjButton::mouseEnterWindow([[maybe_unused]] wxMouseEvent &event)
{
    m_state = State::Current;
    paintNow();
}

void wxjButton::onButtonEvent()
{
    if (m_settings.bind)
    {
        auto &reg = BindingRegistry::instance();
        auto tag = m_settings.bind.value();
        auto binding = reg.get(tag);

        if (binding)
        {
            // Execute notify in detached thread
            std::thread t([binding, tag]() {
                binding.value()->notify(tag);
            });
            
            t.detach();
        }
    }
}