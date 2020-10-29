#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <vector>

template<class T>
class MaxHeap
{
public:
    /// \brief Creates an empty heap
    MaxHeap () {}

    /// \brief Creates a new heap containing the elements of v in O(n)
    MaxHeap (const std::vector<T> &v) :
        m_heap (v)
    {
        assert(leftChild(m_heap.size()/2-1) < (int)m_heap.size());
        assert(leftChild(m_heap.size()/2) >= (int)m_heap.size());

        for (int i0=m_heap.size()/2-1; i0>=0; i0--) {
            int i = i0;

            while (leftChild(i) < (int)m_heap.size()) {
                int maxChild = leftChild(i);
                if (rightChild(i) < (int)m_heap.size() &&
                    m_heap[rightChild(i)] > m_heap[leftChild(i)]) {
                    maxChild = rightChild(i);
                }

                if (m_heap[maxChild] > m_heap[i]) {
                    swap(m_heap[i], m_heap[maxChild]);
                    i = maxChild;
                }
                else {
                    break;
                }
            }
        }
    }

    inline int size () const
    {
        return m_heap.size();
    }

    inline bool isEmpty () const
    {
        return m_heap.empty();
    }

    inline const T& max () const
    {
        return m_heap[0];
    }

    void insert (const T&);

    void removeMax ();


private:
    inline int parent (const int n) const
    {
        return (n-1) / 2;
    }

    inline int leftChild (const int n) const
    {
        return n*2 + 1;
    }

    inline int rightChild (const int n) const
    {
        return n*2 + 2;
    }

    std::vector<T> m_heap;
};

template<class T>
void MaxHeap<T>::insert (const T &e)
{
    int i = m_heap.size();
    m_heap.push_back(e);

    while (i > 0 && m_heap[i] > m_heap[parent(i)]) {
        std::swap(m_heap[i], m_heap[parent(i)]);
        i = parent(i);
    }
}

template<class T>
void MaxHeap<T>::removeMax ()
{
    std::swap(m_heap.front(), m_heap.back());
    m_heap.pop_back();

    int i = 0;

    while (leftChild(i) < (int)m_heap.size()) {
        int maxChild = leftChild(i);
        if (rightChild(i) < (int)m_heap.size() &&
            m_heap[rightChild(i)] > m_heap[leftChild(i)]) {
            maxChild = rightChild(i);
        }

        if (m_heap[maxChild] > m_heap[i]) {
            swap(m_heap[i], m_heap[maxChild]);
            i = maxChild;
        }
        else {
            break;
        }
    }
}

#endif // MAXHEAP_HPP
