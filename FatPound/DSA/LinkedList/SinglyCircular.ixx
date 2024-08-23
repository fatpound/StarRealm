module;

export module FatPound.DSA.LinkedList.SinglyCircular;

import FatPound.DSA.LinkedList.Singly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class SinglyCircular final : public Singly<T>
    {
        using typename Singly<T>::Node_;

        using Singly<T>::Singly;

    public:
        SinglyCircular() = default;
        SinglyCircular(const SinglyCircular& src) = delete;
        SinglyCircular& operator = (const SinglyCircular& src) = delete;

        SinglyCircular(SinglyCircular&& src) noexcept
            :
            Singly(std::move(src))
        {

        }
        SinglyCircular& operator = (SinglyCircular&& src) noexcept
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
        virtual ~SinglyCircular() noexcept
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
                this->m_list_ = new_part;
                this->m_end_  = new_part;
                this->m_list_->next = this->m_list_;

                return;
            }

            this->m_end_->next = new_part;
            new_part->next = this->m_list_;
            this->m_end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item) override final
        {
            Node_* new_part = new Node_(new_item);

            ++this->m_item_count_;

            if (this->m_list_ == nullptr)
            {
                this->m_list_ = new_part;
                new_part->next = this->m_list_;

                return;
            }

            if (new_item < this->m_list_->item)
            {
                new_part->next = this->m_list_;
                this->m_list_ = new_part;

                this->m_end_->next = new_part;

                return;
            }

            Node_* temp = this->m_list_;
            Node_* start = temp;

            while (temp->next not_eq start)
            {
                if (temp->item <= new_item && new_item <= temp->next->item)
                {
                    new_part->next = temp->next;
                    temp->next = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next = new_part;
            new_part->next = start;
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

            Node_* start_backup = this->m_list_;

            Node_* t;
            Node_* a = nullptr;
            Node_* x;

            Node_* temp = this->m_list_;
            Node_* start = temp;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                if (t->next not_eq nullptr)
                {
                    temp = t->next;
                    t->next = x;
                }

                if (temp == start)
                {
                    start->next = t;

                    this->m_list_ = t;

                    return;
                }

                if (temp->next == start)
                {
                    start->next = temp;

                    temp->next = t;
                    this->m_list_ = temp;

                    return;
                }
            }

            start->next = temp;

            this->m_end_ = start_backup;
        }
        virtual void Print() const override final
        {
            if (this->m_list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty SinglyCircular!");
            }

            Node_* temp = this->m_list_;
            Node_* start = temp;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';

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
            while (ex != start);

            this->m_list_ = nullptr;
            this->m_end_  = nullptr;

            this->m_item_count_ = 0u;
        }


    private:
    };
}