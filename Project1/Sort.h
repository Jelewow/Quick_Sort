#pragma once
#include <utility>

const int kLimit = 16;

namespace Quick_sort
{
    template<class T>
    void Swap(T& a, T& b)
    {
        T buff = std::move(a);
        a = std::move(b);
        b = std::move(buff);
    }

    template<typename T>
    auto GetPivot(T* first, T* last)
    {
        int mid = (last - first - 1) / 2;

        if (*(first + mid) < *first)
            Swap(*(first + mid), *first);

        if (*last < *first)
            Swap(*last, *first);

        if (*(first + mid) < *last)
            Swap(*last, *(first + mid));

        return *last;
    }

    template<typename T, typename Compare>
    void InsertingSort(T* first, T* last, Compare comp)
    {
        int length = (last - first);

        for (int i = 1; i < length + 1; ++i)
        {
            T temp = first[i];
            int tempIndex = i;

            while (comp(temp, first[tempIndex - 1]) && (tempIndex > 0))
            {
                first[tempIndex] = first[tempIndex - 1];
                --tempIndex;
            }

            first[tempIndex] = temp;
        }
    }

    template<typename T, typename Compare>
    void QuickSort(T* first, T* last, Compare comp)
    {
    start:
        int length = last - first;

        if (length <= kLimit)
        {
            InsertingSort(first, last, comp);
            return;
        }

        auto pivot = GetPivot<T>(first, last);
        T* firstTmp = first;
        T* lastTmp = last;
        do
        {
            while (comp(*first, pivot))
            {
                first++;
            }
            while (comp(pivot, *last))
            {
                last--;
            }

            if (first < last)
            {
                Swap(*first, *last);

                first++;
                last--;
            }
        } while (first < last);

        if (lastTmp - first > last - firstTmp)
        {
            if (first < lastTmp)
            {
                if (firstTmp - last < kLimit)
                {
                    QuickSort(first, lastTmp, comp);
                }
                else
                {
                    last = lastTmp;
                    goto start;
                }
            }

            if (firstTmp < last)
                QuickSort(firstTmp, last, comp);
        }
        else
        {
            if (firstTmp < last)
                QuickSort(firstTmp, last, comp);

            if (first < lastTmp)
            {
                if (lastTmp - first < kLimit)
                {
                    QuickSort(first, lastTmp, comp);
                }
                else
                {
                    last = lastTmp;
                    goto start;
                }
            }
        }
    }
}