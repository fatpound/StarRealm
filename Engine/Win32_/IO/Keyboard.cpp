module;

module Keyboard;

namespace fatpound::win32::io
{
    auto Keyboard::ReadKeyFromBuffer() noexcept -> Event
    {
        if (keybuffer_.size() > 0u)
        {
            Event e = keybuffer_.front();
            keybuffer_.pop();

            return e;
        }

        return {};
    }

    char Keyboard::ReadCharFromBuffer() noexcept
    {
        if (charbuffer_.size() > 0u)
        {
            unsigned char charcode = charbuffer_.front();
            charbuffer_.pop();

            return charcode;
        }
        else
        {
            return 0;
        }
    }

    bool Keyboard::AutoRepeatIsEnabled() const noexcept
    {
        return autoRepeatEnabled_;
    }
    bool Keyboard::CharBufferIsEmpty() const noexcept
    {
        return charbuffer_.empty();
    }
    bool Keyboard::KeyBufferIsEmpty() const noexcept
    {
        return keybuffer_.empty();
    }
    bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
    {
        return keystates_[keycode];
    }

    void Keyboard::FlushKeyBuffer() noexcept
    {
        keybuffer_ = std::queue<Event>();
    }
    void Keyboard::FlushCharBuffer() noexcept
    {
        charbuffer_ = std::queue<char>();
    }
    void Keyboard::FlushBuffers() noexcept
    {
        FlushKeyBuffer();
        FlushCharBuffer();
    }
    void Keyboard::EnableAutoRepeat() noexcept
    {
        autoRepeatEnabled_ = true;
    }
    void Keyboard::DisableAutoRepeat() noexcept
    {
        autoRepeatEnabled_ = false;
    }

    void Keyboard::OnKeyPressed_(unsigned char keycode) noexcept
    {
        keystates_[keycode] = true;
        keybuffer_.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));

        TrimBuffer_(keybuffer_);
    }
    void Keyboard::OnKeyReleased_(unsigned char keycode) noexcept
    {
        keystates_[keycode] = false;
        keybuffer_.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));

        TrimBuffer_(keybuffer_);
    }
    void Keyboard::OnChar_(char character) noexcept
    {
        charbuffer_.push(character);

        TrimBuffer_(charbuffer_);
    }
    void Keyboard::ClearKeyStateBitset_() noexcept
    {
        keystates_.reset();
    }


    // Event

    Keyboard::Event::Event() noexcept
        :
        type_(Event::Type::Invalid),
        code_(0u)
    {

    }
    Keyboard::Event::Event(Type type, unsigned char code) noexcept
        :
        type_(type),
        code_(code)
    {

    }

    unsigned char Keyboard::Event::GetCode() const noexcept
    {
        return code_;
    }

    bool Keyboard::Event::IsPress() const noexcept
    {
        return type_ == Event::Type::Press;
    }
    bool Keyboard::Event::IsRelease() const noexcept
    {
        return type_ == Event::Type::Release;
    }
    bool Keyboard::Event::IsInvalid() const noexcept
    {
        return type_ == Event::Type::Invalid;
    }
}