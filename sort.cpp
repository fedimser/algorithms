#include <iostream>
#include <vector>
#include <random>

namespace QuickSort {
    template <typename T>
    swap (T& first, T& second) {
        T buffer = first;
        first = second;
        second = buffer;
    }


    template <class RandomAccessIterator, class Compare, class RandomGenerator>
    void sort (RandomAccessIterator begin, RandomAccessIterator end,
                Compare comp, RandomGenerator& gen) {
        int pivotIndex = gen() % (end - begin);
        typename std::iterator_traits<RandomAccessIterator>::value_type pivot =
                                                            *(begin + pivotIndex);
        RandomAccessIterator left = begin;
        RandomAccessIterator right = end - 1;

        while (left <= right) {
            while (comp(*left, pivot)) {
                ++left;
            }

            while (comp(pivot, *right)) {
                --right;
            }

            if (left <= right)
            {
                swap(*left, *right);
                ++left;
                --right;
            }
        }

        if (left < end-1) {
            sort(left, end, comp, gen);
        }

        if (begin < right) {
            sort(begin, right + 1, comp, gen);
        }
    }

    template <class RandomAccessIterator, class Compare>
    void sort (RandomAccessIterator begin, RandomAccessIterator end, Compare comp) {
        std::mt19937 generator;
        sort(begin, end, comp, generator);
    }
}

bool comp(const int& first, const int& second) {
    return first < second;
}


int main() {
    int N=1000000;
    std::vector<int> v;
    for(int i=0;i<N;i++)v.push_back(rand());
    QuickSort::sort(v.begin(), v.end(), comp);

    for(int i=1;i<N;i++)
        if(v[i-1]>v[i])
        {
            std::cout<<"FAIL";
            return 1;
        }
    std::cout<<"OK\n";
    return 0;
}
