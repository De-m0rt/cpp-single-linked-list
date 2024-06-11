#pragma once
#include <string>


template <typename Type>
class SingleLinkedList {

    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator
    {
        friend class SingleLinkedList;
        explicit BasicIterator(Node* node)
        {
           node_ = node;
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;
        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type>& other) noexcept
        {
            node_ = other.node_;
        }

        BasicIterator& operator=(const BasicIterator& rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept
        {
           return node_ == rhs.node_;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept
        {
            return node_ != rhs.node_;
        }

        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept
        {
            return node_== rhs.node_;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept
        {
            return node_ != rhs.node_;
        }

        BasicIterator& operator++() noexcept
        {
            node_ = node_->next_node;
            return *this;
        }

        BasicIterator operator++(int) noexcept
        {
            auto old(*this);
            node_ = node_->next_node;
            return old;
        }

        [[nodiscard]] reference operator*() const noexcept
        {
            return node_->value;
        }

        [[nodiscard]] pointer operator->() const noexcept
        {
            return &node_->value;
        }
    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;

    SingleLinkedList() = default;

    SingleLinkedList(std::initializer_list<Type> values)
    {
        for(const auto& value : values)
     //   for (auto value = values.begin(); value != values.end(); ++value)
        {
            Node* tmp = &head_;
            while (tmp->next_node != nullptr)
            {
                tmp = tmp->next_node;
            }
            tmp->next_node = new Node(value, nullptr);
            ++size_;
        }
    }

    SingleLinkedList(const SingleLinkedList& other)
    {
        SingleLinkedList tmp;
        Node* tmp_node = &tmp.head_;
        for(const auto& value : other)
        {
            tmp_node->next_node = new Node (value, nullptr);
            tmp_node = tmp_node->next_node;
        }
        swap(tmp);
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs)
    {
        if (&rhs == nullptr)
        {
            this->Clear();
        }

        else if(&rhs != this)
        {
            SingleLinkedList tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    [[nodiscard]] size_t GetSize() const noexcept
    {
        return size_;
    }

    [[nodiscard]] bool IsEmpty() const noexcept
    {
        return size_ == 0;
    }

    [[nodiscard]] Iterator begin() noexcept
    {
        return Iterator{head_.next_node};
    }

    [[nodiscard]] Iterator end() noexcept
    {
        auto tmp = head_.next_node;
        while(tmp != nullptr)
        {
            tmp = tmp->next_node;
        }
        return Iterator{tmp};
    }

    [[nodiscard]] Iterator before_begin() noexcept
    {
        return Iterator{&head_};
    }

    [[nodiscard]] ConstIterator cbefore_begin() const noexcept
    {
        return Iterator{ const_cast<Node*>(&head_) };
    }

    [[nodiscard]] ConstIterator before_begin() const noexcept
    {
        return cbefore_begin();
    }

    [[nodiscard]] ConstIterator begin() const noexcept
    {
        return Iterator{head_.next_node};
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept
    {
        return Iterator{head_.next_node};
    }

    [[nodiscard]] ConstIterator cend() const noexcept
    {
        auto tmp = head_.next_node;
        while(tmp != nullptr)
        {
            tmp = tmp->next_node;
        }
        return Iterator{tmp};
    }

    [[nodiscard]] ConstIterator end() const noexcept
    {
        auto tmp = head_.next_node;
        while(tmp != nullptr)
        {
            tmp = tmp->next_node;
        }
        return Iterator{tmp};
    }

    Iterator InsertAfter(ConstIterator pos, const Type& value) {
        Node* new_node = new Node(value, pos.node_->next_node);
        pos.node_->next_node = new_node;
        ++size_;
        return Iterator{new_node};
    }

    void PopFront() noexcept {
        Node* clr = head_.next_node;
        head_.next_node = head_.next_node->next_node;
        --size_;
        delete clr;
    }

    Iterator EraseAfter(ConstIterator pos) noexcept
    {
        Node* clr = pos.node_->next_node;
        pos.node_->next_node = pos.node_->next_node->next_node;
        --size_;
        delete clr;
        return Iterator{pos.node_->next_node};
    }

    void PushFront(const Type& value)
    {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
    }

    void Clear() noexcept
    {
        while  (head_.next_node != nullptr )
        {
            Node* curr = head_.next_node;
            head_.next_node = curr->next_node;
            delete curr;
        }
        size_ = 0;
    }

    void swap(SingleLinkedList& other) noexcept
    {
        std::swap(other.head_.next_node, head_.next_node);
        std::swap(other.size_,size_);
    }

    ~SingleLinkedList() {
        Clear();
    }

    private:
        Node head_;
        size_t size_ = 0;
};
