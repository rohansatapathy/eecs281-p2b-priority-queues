// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include <algorithm>
#include <deque>
#include <stdexcept>
#include <utility>

#include "Eecs281PQ.hpp"

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template <typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

  public:
    // Each node within the pairing heap
    class Node {
      public:
        // Description: Custom constructor that creates a node containing
        //              the given value.
        explicit Node(const TYPE& val) : elt{val} {}

        // Description: Allows access to the element at that Node's position.
        //              There are two versions, getElt() and a dereference
        //              operator, use whichever one seems more natural to you.
        // Runtime: O(1) - this has been provided for you.
        const TYPE& getElt() const {
            return elt;
        }
        const TYPE& operator*() const {
            return elt;
        }

        // The following line allows you to access any private data
        // members of this Node class from within the PairingPQ class.
        // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
        // function).
        friend PairingPQ;

      private:
        TYPE elt;
        Node* child = nullptr;
        Node* sibling = nullptr;
        Node* previous = nullptr;
    };  // Node

    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR())
        : BaseClass{comp}, root(nullptr), count(0) {}

    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template <typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end,
              COMP_FUNCTOR comp = COMP_FUNCTOR())
        : BaseClass{comp}, root(nullptr), count(0) {
        // TODO: Implement this function.
        (void)start;  // Delete this line when you implement this function
        (void)end;    // Delete this line when you implement this function
    }  // PairingPQ()

    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ& other)
        : BaseClass{other.compare}, root(nullptr), count(0) {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
    }  // PairingPQ()

    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ& operator=(const PairingPQ& rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        // lecture.
        (void)rhs;  // Delete this line when you implement this function
        return *this;
    }  // operator=()

    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        ;  // Delete this line, it prevents linter complaints
    }  // ~PairingPQ()

    // Description: Move constructor and assignment operators don't need any
    //              code, the members will be reused automatically.
    PairingPQ(PairingPQ&&) noexcept = default;
    PairingPQ& operator=(PairingPQ&&) noexcept = default;

    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
    }  // updatePriorities()

    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely
    //              in the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE& val) {
        addNode(val);
    }  // push()

    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the pairing heap is empty. Though you are welcome to
    // if you are familiar with them, you do not need to use exceptions in
    // this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        if (empty()) {
            throw std::out_of_range("PairingPQ is empty.");
        }

        std::deque<Node*> nodes;
        for (Node* current = root->child; current != nullptr;
             current = current->sibling) {
            nodes.push_back(current);
        }

        Node* a;
        Node* b;
        while (nodes.size() > 1) {
            a = nodes.front();
            nodes.pop_front();
            b = nodes.front();
            nodes.pop_front();

            a->previous = nullptr;
            a->sibling = nullptr;
            b->previous = nullptr;
            b->sibling = nullptr;

            nodes.push_back(meld(a, b));
        }

        delete root;
        if (nodes.size() == 0) {
            root = nullptr;
        } else {
            root = nodes.front();
        }

        count--;
    }  // pop()

    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE& top() const {
        if (empty()) {
            throw std::out_of_range("PairingPQ is empty.");
        }
        return root->elt;
    }  // top()

    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    [[nodiscard]] virtual std::size_t size() const {
        return count;
    }  // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    [[nodiscard]] virtual bool empty() const {
        return size() == 0;
    }  // empty()

    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value.  Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //              extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE& new_value) {
        // TODO: Implement this function
        (void)node;       // Delete this line when you implement this function
        (void)new_value;  // Delete this line when you implement this func
    }  // updateElt()

    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // Runtime: O(1)
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    Node* addNode(const TYPE& val) {
        Node* newNode = new Node(val);
        count++;
        if (root == nullptr) {
            root = newNode;
        } else {
            root = meld(root, newNode);
        }
        return newNode;
    }  // addNode()

  private:
    Node* root;
    size_t count;

    /*
     * Description: Combines the two pairing heaps with roots a and b into
     *              a single pairing heap.
     *
     * PRECONDITION: Both *a and *b must be the root node of their pairing heap,
     *              which means their previous and sibling pointers must be
     *              nullptr. We also need a, b != nullptr.
     */
    Node* meld(Node* a, Node* b) {
        Node* newRoot;
        Node* newChild;
        if (this->compare(a->elt, b->elt)) {
            newChild = a;
            newRoot = b;
        } else {
            newRoot = a;
            newChild = b;
        }

        if (newRoot->child != nullptr) {
            newRoot->child->previous = newChild;
            newChild->sibling = newRoot->child;
        }

        newRoot->child = newChild;
        newChild->previous = newRoot;

        return newRoot;
    }
};

#endif  // PAIRINGPQ_H
