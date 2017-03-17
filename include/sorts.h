#ifndef __CHANGVOXEL_HEAPSORT_H__
#define __CHANGVOXEL_HEAPSORT_H__
/**!heapsort function*/
#include "vgTypes.h"
#include "Config.h"

namespace vg
{
	namespace core
	{
		//! Sinks an element into the heap.
		// 所以自定义类至少需要提供operator<,才可以数组排序
		template<class T>
		inline void heapsink(T*array, s32 element, s32 max)
		{
			while ((element << 1) < max) // there is a left child
			{
				s32 j = (element << 1);

				if (j + 1 < max && array[j] < array[j + 1])
					j = j + 1; // take right child

				if (array[element] < array[j])
				{
					T t = array[j]; // swap elements
					array[j] = array[element];
					array[element] = t;
					element = j;
				}
				else
					return;
			}
		}
		//! Sorts an array with size 'size' using heapsort.
		template<class T>
		inline void heapsort(T* array_, s32 size)
		{
			// for heapsink we pretent this is not c++, where
			// arrays start with index 0. So we decrease the array pointer,
			// the maximum always +2 and the element always +1

			T* virtualArray = array_ - 1;
			s32 virtualSize = size + 2;
			s32 i;

			// build heap

			for (i = ((size - 1) / 2); i >= 0; --i)
				heapsink(virtualArray, i + 1, virtualSize - 1);

			// sort array, leave out the last element (0)
			for (i = size - 1; i>0; --i)
			{
				T t = array_[0];
				array_[0] = array_[i];
				array_[i] = t;
				heapsink(virtualArray, 1, i + 1);
			}
		}


		//! O(n^2)
		template<typename T>
		inline void insertsort(T* array_, s32 size)
		{
			for (s32 i = 1; i < size; ++i)
			{
				T key = array_[i];
				s32 j = i - 1
					// from back to front,search and move
					for (; array_[j]>key&&j>-1; --j)
					{
						array_[j + 1] = array_[j];
					}
				array_[j + 1] = key;//if j = i-1,useless
			}
		}

		//! binary insert sort,O(n^2) stable
		template<typename T>
		inline void binaryinsertsort(T* array_, s32 size)
		{
			s32 low = 0, high = 0;
			for (s32 i = 1; i < size; ++i)
			{
				T key = array_[i];
				low = 0;
				high = i - 1;
				while (low <= high)
				{
					s32 mid = (low + high) >> 1;
					if (key > array_[mid])
						low = mid + 1;
					else
						high = mid - 1;
				}
				// now move
				for (s32 j = i - 1; j >= high; --j)
					array_[j + 1] = array_[j];
				array_[high + 1] = key;
			}
		}

		//! bubble modified sort,O(n*(n-1)/2)
		template<typename T>
		inline void bubblemodifiedsort(T* array_, s32 size)
		{
			s32 i = size;
			s32 lastExchangeIndex = 0;
			while (i > 0)
			{
				lastExchangeIndex = 0;
				for (s32 j = 0; j < i; ++j)
				{
					if (array_[j] > array_[j + 1])
					{
						std::swap(array_[j], array_[j + 1]);
						lastExchangeIndex = j;
					}
				}//end for j
				i = lastExchangeIndex;
			}// end while
		}

		//! quick sort,O(nlog2(n))+O(log2(n))~O(n^2)
		/** Usually from = 0,to = size-1;
		\param from the position begin.
		\param to the positoin end.
		*/
		template<typename T>
		inline void quicksort(T* array_, s32 size, s32 from, s32 to)
		{
			while (from < to)
			{
				s32 index;
				s32 i = from, j = to;
				// quick partition
				{
					T key = array_[i];
					while (i < j)
					{
						while (i < j&&array_[j] >= key)
							--j;// j move left
						if (i < j)
						{
							array_[i] = array_[j];
							++i;
						}
						while (i < j&&array_[i] <= key)
							--j;// j move left
						if (i < j)
						{
							array_[j] = array_[i];
							--j;
						}
					}
					array_[i] = key;
					index = i;
				}
				quicksort(array_, from, index - 1);
				quicksort(array_, index + 1, to);
			}
		}

		//! simple select sort,O(n*(n-1)/2)
		template<typename T>
		inline void simpleselectsort(T* data, s32 size)
		{
			for (s32 i = 0; i < size; ++i)
			{
				s32 k = i;
				for (s32 j = i + 1; j < size; ++j)
				{
					if (data[j] < data[k])// find the smallest data
						k = j;
				}
				//if the key value isn't at position i,swap k i
				if (i != k)6
					std::swap(data[i], data[k]);
			}
		}

	}//end core
}//end cv
#endif