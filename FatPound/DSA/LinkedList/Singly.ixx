module;

export module FatPound.DSA.LinkedList.Singly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class Singly
    {
    public:
        Singly() = default;
        Singly(const Singly& src) = delete;
        Singly& operator = (const Singly& src) = delete;

        Singly(Singly&& src) noexcept
            :
            m_list_(std::exchange(src.m_list_, nullptr)),
            m_end_(std::exchange(src.m_end_, nullptr)),
            m_item_count_(std::exchange(src.m_item_count_, 0u))
        {

        }
        Singly& operator = (Singly&& src) noexcept
        {
            if (this != std::addressof(src) && typeid(src) == typeid(*this) && src.m_list_ != nullptr)
            {
                Delete_();

                m_list_ = std::exchange(src.m_list_, nullptr);
                m_end_ = std::exchange(src.m_end_, nullptr);

                m_item_count_ = std::exchange(src.m_item_count_, 0u);
            }

            return *this;
        }
        virtual ~Singly() noexcept
        {
            Delete_();
        }


    public:
        virtual bool Contains(const T& item) const final
        {
            return Find_(item) not_eq nullptr;
        }

        virtual void Add(const T& new_item)
        {
            Node_* new_part = new Node_(new_item);

            ++m_item_count_;

            if (m_list_ == nullptr)
            {
                m_list_ = new_part;
            }
            else
            {
                m_end_->next = new_part;
            }

            m_end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item)
        {
            Node_* new_part = new Node_(new_item);

            ++m_item_count_;

            if (m_list_ == nullptr)
            {
                m_list_ = new_part;
                m_end_ = new_part;

                return;
            }

            if (new_item < m_list_->item)
            {
                new_part->next = m_list_;
                m_list_ = new_part;

                return;
            }

            Node_* temp = m_list_;

            while (temp->next != nullptr)
            {
                if ((temp->item <= new_item) and (new_item <= temp->next->item))
                {
                    new_part->next = temp->next;
                    temp->next = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next = new_part;

            m_end_ = new_part;
        }
        virtual void Reverse()
        {
            if (m_list_ == nullptr)
            {
                return;
            }

            if (this->m_item_count_ < 2u)
            {
                return;
            }

            Node_* start_backup = m_list_;

            Node_* t;
            Node_* a = nullptr;
            Node_* x;

            Node_* temp = m_list_;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                temp = t->next;
                t->next = x;

                if (temp == nullptr)
                {
                    m_list_ = t;
                    return;
                }

                if (temp->next == nullptr)
                {
                    temp->next = t;
                    m_list_ = temp;

                    return;
                }
            }

            m_end_ = start_backup;
        }
        virtual void Print() const
        {
            if (m_list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty Singly!");
            }

            Node_* temp = m_list_;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';

                temp = temp->next;
            }
            while (temp != nullptr);

            std::cout << '\n';
        }


    protected:
        struct Node_ final
        {
            Node_(T new_item)
                :
                item(new_item)
            {

            }

            Node_* next = nullptr;

            T item;
        };


    protected:
        virtual Node_* Find_(const T& item) const final
        {
            if (m_item_count_ == 0u)
            {
                return nullptr;
            }

            if (m_item_count_ == 1u)
            {
                return m_list_->item == item
                    ? m_list_
                    : nullptr
                    ;
            }

            Node_* temp = m_list_;

            for (std::size_t i = 0u; i < m_item_count_; ++i)
            {
                if (temp->item == item)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr;
        }

        virtual void Delete_()
        {
            if (m_list_ == nullptr)
            {
                return;
            }

            Node_* ex = m_list_;
            Node_* temp;

            do
            {
                temp = ex->next;

                delete ex;

                ex = temp;
            }
            while (ex not_eq nullptr);

            m_list_ = nullptr;
            m_end_  = nullptr;

            m_item_count_ = 0u;
        }


    protected:
        Node_* m_list_ = nullptr;
        Node_* m_end_  = nullptr;

        std::size_t m_item_count_ = 0u;


    private:
    };
}