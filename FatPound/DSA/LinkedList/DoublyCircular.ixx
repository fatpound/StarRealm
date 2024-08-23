module;

export module FatPound.DSA.LinkedList.DoublyCircular;

import FatPound.DSA.LinkedList.Doubly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class DoublyCircular final : public Doubly<T>
    {
        using typename Doubly<T>::Node_;

        using Doubly<T>::Doubly;

    public:
        DoublyCircular() = default;
        DoublyCircular(const DoublyCircular& src) = delete;
        DoublyCircular& operator = (const DoublyCircular& src) = delete;

        DoublyCircular(DoublyCircular&& src) noexcept
            :
            Doubly(std::move(src))
        {

        }
        DoublyCircular& operator = (DoublyCircular&& src) noexcept
        {
            if ((this not_eq std::addressof(src)) and (typeid(src) == typeid(*this)) and (src.m_list_ not_eq nullptr))
            {
                Delete_();

                this->m_list_ = std::exchange(src.m_list_, nullptr);
                this->m_end_  = std::exchange(src.m_end_,  nullptr);

                this->m_item_count_ = std::exchange(src.m_item_count_, 0u);
            }

            return *this;
        }
        virtual ~DoublyCircular() noexcept
        {
            Delete_();
        }


    public:
        virtual void Add(const T& new_item) override final
        {
            Node_* new_part = new Node_(new_item);

            ++this->m_item_count_;

            if (this->m_list_ == nullptr)
            {
                new_part->next = new_part;
                new_part->prev = new_part;

                this->m_list_ = new_part;
                this->m_end_ = new_part;

                return;
            }

            this->m_end_->next = new_part;
            new_part->prev = this->m_end_;
            new_part->next = this->m_list_;

            this->m_list_->prev = new_part;
            this->m_end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item) override final
        {
            Node_* new_part = new Node_(new_item);

            ++this->m_item_count_;

            if (this->m_list_ == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;
                this->m_list_ = new_part;

                return;
            }

            if (new_item < this->m_list_->item)
            {
                new_part->next = this->m_list_;
                this->m_list_->prev = new_part;
                this->m_list_ = new_part;

                this->m_end_->next = this->m_list_;
                this->m_list_->prev = this->m_end_;

                return;
            }

            Node_* temp = this->m_list_;
            Node_* start = temp;

            while (temp->next not_eq start)
            {
                if ((temp->item <= new_item) and (new_item <= temp->next->item))
                {
                    new_part->next = temp->next;
                    new_part->prev = temp;
                    temp->next->prev = new_part;
                    temp->next = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next = new_part;
            new_part->prev = temp;

            new_part->next = start;
            start->prev = new_part;
        }
        virtual void Reverse() override final
        {
            if (this->m_list_ == nullptr)
            {
                return;
            }

            if (this->m_item_count_ < 2u)
            {
                return;
            }

            Node_* temp  = this->m_list_;
            Node_* start = this->m_list_;

            while (temp->next not_eq start)
            {
                std::swap(temp->prev, temp->next);

                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);

            this->m_list_ = temp;
        }
        virtual void Print() const override final
        {
            if (this->m_list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty DoublyCircular!");
            }

            Node_* temp = this->m_list_;
            Node_* start = temp;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';

                temp = temp->next;
            }
            while (temp not_eq start);

            std::cout << '\n';
        }


    protected:
        virtual void Delete_() override final
        {
            if (this->m_list_ == nullptr)
            {
                return;
            }

            Node_* start = this->m_list_;
            Node_* ex = this->m_list_;

            Node_* temp;

            do
            {
                temp = ex->next;

                delete ex;

                ex = temp;
            }
            while (ex not_eq start);

            this->m_list_ = nullptr;
            this->m_end_  = nullptr;

            this->m_item_count_ = 0u;
        }


    private:
    };
}