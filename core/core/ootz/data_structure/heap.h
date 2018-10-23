#pragma once

#include "ootz/base.h"

namespace ootz
{

// default compare function object is std::less<T>.
// using default compare function object is max heap.
template<
    typename T, 
    typename Compare = std::less<T>>
class Heap
{
public:

    // constructors and destructors

    Heap()
        : _vector()
    {}

    Heap(const std::vector<T>& vector)
        : _vector(vector)
    {
        makeHeap();
    }

    ~Heap() {}

    // public methods

    constexpr const T& top() const
    {
        assert(false == _vector.empty() && "heap is empty.");

        return _vector.front();
    }

    constexpr void push(const T& key)
    {
        _vector.push_back(key);

        upHeap(getIndexOfLast());
    }

    constexpr T pop()
    {
        const size_t lastIndex = getIndexOfLast();

        assert(isValidIndex(lastIndex) && "it is out of range.");

        if (0 != lastIndex)
        {
            swap(0, lastIndex);
        }

        const T back = _vector.back();
        _vector.pop_back();

        downHeap(0);

        return back;
    }

    constexpr size_t size() const 
    { 
        return _vector.size(); 
    }

    constexpr bool empty() const 
    { 
        return _vector.empty();
    }

    // operators

    constexpr T& operator[](size_t index)
    {
        assert(isValidIndex(index) && "it is out of range.");
        return _vector[index];
    }

    constexpr const T& operator[](size_t index) const
    {
        assert(isValidIndex(index) && "it is out of range.");
        return _vector[index];
    }

private:

    // private methods

    constexpr void makeHeap()
    {
        for (size_t i = 0; i < size(); ++i)
            upHeap(i);
    }

    constexpr void upHeap(const size_t index)
    {
        const size_t parentIndex = getIndexOfParent(index);

        if (isOutOfRange(parentIndex))
            return;

        if (Compare()(_vector[index], _vector[parentIndex]))
            return;

        swap(index, parentIndex);

        upHeap(parentIndex);
    }

    constexpr void downHeap(const size_t index)
    {
        const size_t leftChildIndex = getIndexOfLeftChild(index);
        const size_t rightChildIndex = getIndexOfRightChild(index);

        if (isOutOfRange(leftChildIndex))
            return;

        auto compare = Compare();
        size_t i = compare(_vector[index], _vector[leftChildIndex])? leftChildIndex : index;

        if (isValidIndex(rightChildIndex) && 
            compare(_vector[i], _vector[rightChildIndex]))
        {
            i = rightChildIndex;
        }

        if (i == index)
            return;

        swap(index, i);

        downHeap(i);
    }

    constexpr size_t getIndexOfParent(const size_t index) const
    {
        return (index - 1) / 2;
    }

    constexpr size_t getIndexOfLeftChild(const size_t index) const
    {
        return index * 2 + 1;
    }

    constexpr size_t getIndexOfRightChild(const size_t index) const
    {
        return index * 2 + 2;
    }

    constexpr size_t getIndexOfLast() const
    {
        return size() - 1;
    }

    constexpr bool isOutOfRange(const size_t index) const
    {
        return index >= size();
    }

    constexpr bool isValidIndex(const size_t index) const
    {
        return false == isOutOfRange(index);
    }

    constexpr void swap(const size_t i0, const size_t i1)
    {
        std::swap(_vector[i0], _vector[i1]);
    }

    // private member variables

    std::vector<T> _vector;
};

// helper functions

// helper function for heap to ostream
template<
    typename T, 
    typename Compare = std::less<T>>
constexpr std::ostream& operator<<(std::ostream& ostream, const Heap<T, Compare>& heap)
{
    ostream << "[ ";

    const size_t last = heap.size() - 1;
    for (size_t i = 0; i < heap.size(); ++i)
    {
        ostream << heap[i];

        if (i != last)
            ostream << ", ";
    }

    ostream << " ]";
    return ostream;
}

template<
    typename T, 
    typename Compare = std::less<T>>
class StdHeap
{
public:
    StdHeap()
        : _vector()
    {}

    ~StdHeap() {}

    StdHeap(const std::vector<T>& vector)
    {
        _vector = vector;
        std::make_heap(_vector.begin(), _vector.end(), Compare());
    }

    constexpr void push(const T& key) const
    {
        _vector.push_back(key);
        std::push_heap(_vector.begin(), _vector.end(), Compare());
    }

    constexpr T pop() const
    {
        std::pop_heap(_vector.begin(), _vector.end(), Compare());
        const T back = _vector.back();
        _vector.pop_back();
        return back;
    }

private:
    std::vector<T> _vector;
};

} // namespace ootz