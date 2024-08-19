module;

module FatPound.Win32.IO.Keyboard;

namespace fatpound::win32::io
{
    // Keyboard

    auto Keyboard::ReadKeyFromBuffer() noexcept -> Event
    {
        if (m_event_buffer_.size() > 0u)
        {
            Event e = m_event_buffer_.front();
            m_event_buffer_.pop();

            return e;
        }

        return Event{};
    }

    auto Keyboard::ReadCharFromBuffer() noexcept -> unsigned char
    {
        if (m_char_buffer_.size() > 0u)
        {
            const auto charcode = m_char_buffer_.front();
            m_char_buffer_.pop();

            return charcode;
        }

        return 0;
    }

    bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
    {
        return m_key_states_[keycode];
    }
    bool Keyboard::KeyBufferIsEmpty() const noexcept
    {
        return m_event_buffer_.empty();
    }
    bool Keyboard::CharBufferIsEmpty() const noexcept
    {
        return m_char_buffer_.empty();
    }
    bool Keyboard::AutoRepeatIsEnabled() const noexcept
    {
        return m_auto_repeat_enabled_;
    }

    void Keyboard::FlushKeyBuffer() noexcept
    {
        m_event_buffer_ = std::queue<Event>{};
    }
    void Keyboard::FlushCharBuffer() noexcept
    {
        m_char_buffer_ = std::queue<unsigned char>{};
    }
    void Keyboard::FlushBuffers() noexcept
    {
        FlushKeyBuffer();
        FlushCharBuffer();
    }
    void Keyboard::EnableAutoRepeat() noexcept
    {
        m_auto_repeat_enabled_ = true;
    }
    void Keyboard::DisableAutoRepeat() noexcept
    {
        m_auto_repeat_enabled_ = false;
    }

    void Keyboard::OnKeyPressed_(unsigned char keycode)
    {
        m_key_states_[keycode] = true;

        m_event_buffer_.push(Event{ Event::Type::Press, keycode });

        TrimBuffer_(m_event_buffer_);
    }
    void Keyboard::OnKeyReleased_(unsigned char keycode)
    {
        m_key_states_[keycode] = false;

        m_event_buffer_.push(Event{ Event::Type::Release, keycode });

        TrimBuffer_(m_event_buffer_);
    }
    void Keyboard::OnChar_(unsigned char character)
    {
        m_char_buffer_.push(character);

        TrimBuffer_(m_char_buffer_);
    }

    void Keyboard::ClearKeyStateBitset_() noexcept
    {
        m_key_states_.reset();
    }


    // Event

    Keyboard::Event::Event(Type type, unsigned char code) noexcept
        :
        m_type_(type),
        m_code_(code)
    {

    }

    unsigned char Keyboard::Event::GetCode() const noexcept
    {
        return m_code_;
    }

    bool Keyboard::Event::IsPress() const noexcept
    {
        return m_type_ == Type::Press;
    }
    bool Keyboard::Event::IsRelease() const noexcept
    {
        return m_type_ == Type::Release;
    }
    bool Keyboard::Event::IsInvalid() const noexcept
    {
        return m_type_ == Type::Invalid;
    }
}