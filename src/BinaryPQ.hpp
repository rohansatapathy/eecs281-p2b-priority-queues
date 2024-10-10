// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H

#include <algorithm>
#include <stdexcept>
#include <utility>

#include "Eecs281PQ.hpp"

// A specialized version of the priority queue ADT implemented as a binary heap.
template <typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

  public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR())
        : BaseClass{comp}, data() {}  // BinaryPQ

    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template <typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end,
             COMP_FUNCTOR comp = COMP_FUNCTOR())
        : BaseClass{comp}, data(start, end) {
        updatePriorities();
    }  // BinaryPQ

    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() = default;

    // Description: Copy constructors don't need any code, the data vector
    //              will be copied automatically.
    BinaryPQ(const BinaryPQ&) = default;
    BinaryPQ(BinaryPQ&&) noexcept = default;

    // Description: Copy assignment operators don't need any code, the data
    //              vector will be copied automatically.
    BinaryPQ& operator=(const BinaryPQ&) = default;
    BinaryPQ& operator=(BinaryPQ&&) noexcept = default;

    // Description: Assumes that all elements inside the heap are out of order
    // and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        for (size_t i = size(); 1 <= i && i <= size(); i--) {
            fixDown(i);
        }

    }  // updatePriorities()

    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE& val) {
        data.push_back(val);
        fixUp();
    }  // push()

    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        std::swap(at(1), at(size()));
        data.pop_back();
        fixDown();
    }  // pop()

    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE& top() const {
        return at(1);
    }  // top()

    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    [[nodiscard]] virtual std::size_t size() const {
        return data.size();
    }  // size()

    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    [[nodiscard]] virtual bool empty() const {
        return size() == 0;
    }  // empty()

  private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    TYPE& at(size_t index) {
        if (!(1 <= index <= size()))
            throw std::out_of_range(
                "Binary heap index must be 1 <= index <= size.");
        return data.at(index - 1);
    }

    const TYPE& at(size_t index) const {
        if (!(1 <= index <= size()))
            throw std::out_of_range(
                "Binary heap index must be 1 <= index <= size.");
        return data.at(index - 1);
    }

    void fixUp() {
        size_t current = size();
        while (current > 1 && this->compare(at(current / 2), at(current))) {
            std::swap(at(current / 2), at(current));
            current /= 2;
        }
    }

    void fixDown(size_t start_index = 1) {
        size_t current = start_index;
        while (current * 2 <= size()) {
            size_t swapIndex;
            if (current * 2 + 1 <= size() &&
                this->compare(at(current * 2 + 1), at(current * 2))) {
                swapIndex = current * 2 + 1;
            } else {
                swapIndex = current * 2;
            }

            if (this->compare(at(current), at(swapIndex))) {
                std::swap(at(current), at(swapIndex));
                current = swapIndex;
            } else {
                break;
            }
        }
    }

};  // BinaryPQ

#endif  // BINARYPQ_H
