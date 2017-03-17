#ifndef __VG_MULARRAY_H_INCLUDE__
#define __VG_MULARRAY_H_INCLUDE__
/**
* copyright by lcj.uestc
* 2017.03.11
*/
#include "vgTypes.h"
#include "vgAllocator.h"
#include <functional>
#include "IStringException.h"


namespace vg
{
	namespace core
	{
		//!
		/**
		* Use like this;
		* Create row 1024 col 100 like data[1024][100]
		* mularray<NodeType> ma(1024,100,depth);
		* ma.push_back(node,i,j);
		* ma.sortAll();
		* ma.sort(i,j);
		* 用于Z排序算法中存储结果(同时包含alpha测试)
		*/
		template<typename T>
		class mularray
		{
		public:
			mularray(u32 row, u32 col, u32 depth)
				:strategy(ALLOC_STRATEGY_DOUBLE),
				RowSize(row), ColSize(col),
				AllocatedAll(depth)
			{
				allocateAll();
			}

			~mularray()
			{
				u32 size = RowSize*ColSize;
				if (UsedForEachTable)
					UsedForEachTable = new u32[size]();

				if (Datas)
				{
					for (u32 i = 0; i < size; ++i)
					{
						(*(Datas + i)) = (T*) new T[AllocatedAll];
					}
					delete[] UsedForEachTable;

					for (u32 i = 0; i < size; ++i)
					{
						delete[](*(Datas + i));
					}
					delete[] Datas;
				}
			}


			void sortAll()
			{
				for (u32 i = 0; i < RowSize; ++i)
				{
					for (u32 j = 0; j < ColSize; ++j)
					{
						sort(i, j);
					}
				}
			}

			void sort(u32 indexI, u32 indexJ)
			{
				if (indexI < RowSize&&indexJ < ColSize)
				{
					u32 index = getIndexFromIJ(indexI, indexJ);
					SortFunction(Datas[index], AllocatedForEachTable[index]);
				}
			}

			/**
			* Insert new value and keep the sorted status.
			*/
			bool sortInsert(u32 indexI, u32 indexJ, T&& value)
			{
				if (indexI < RowSize&&indexJ < ColSize)
				{
					u32 index = getIndexFromIJ(indexI, indexJ);
					if (SortInsertFunction)
					{
						
						SortInsertFunction(Datas[index], UsedForEachTable[index], AllocatedAll,
							std::move(value));
						return true;
					}

					else
					{
						throw io::IStringException("mularray InsertFunction hasn't set.");
						//push_back(index, std::move(value));
					}
				}
				return false;

			}

			/**
			* Insert the value in the first position of sub array.
			*/
			bool insert_front(u32 indexI, u32 indexJ,T&&value)
			{
				if (indexI < RowSize&&indexJ < ColSize)
					return false;
				u32 index = getIndexFromIJ(indexI, indexJ);
				Datas[index][0] = std::move(value);
				UsedForEachTable[index] = 1;
				return true;
			}

			void setSortFunction(std::function<void(T*, int)> sortFunc)
			{
				SortFunction = sortFunc;
			}

			void setSortInsertFunction(std::function<void(T*, u32&, u32, T&&)> sortInsertFunc)
			{
				SortInsertFunction = sortInsertFunc;
			}

			u32 getUsed(u32 indexI, u32 indexJ)
			{
				return UsedForEachTable[getIndexFromIJ(indexI, indexJ)];
			}

			T* getSubDataArrayOfIJ(u32 indexI, u32 indexJ)
			{
				return Datas[getIndexFromIJ(indexI, indexJ)];
			}

			const T& getSubDataOfIJ(u32 indexI, u32 indexJ, u32 depth)
			{
				return Datas[getIndexFromIJ(indexI, indexJ)][depth];
			}

			// 强制设置某一个子缓存尺寸为1,值为value
			void setForce(u32 indexI, u32 indexJ, T&& value)
			{
				insert_front(indexI, indexJ, std::move(value));
			}

			void setEmpty()
			{
				memset(UsedForEachTable, 0, RowSize*ColSize * sizeof(u32));
			}

		private:

			void allocateAll()
			{
				u32 size = RowSize*ColSize;
				UsedForEachTable = new u32[size]();

				Datas = (T**)new T[size];
				for (u32 i = 0; i < size; ++i)
				{
					(*(Datas + i)) = (T*) new T[AllocatedAll];
				}
			}


			void push_back(u32 dataIndex, const T&& element)
			{
				// insert the new element to the end
				Datas[index][UsedForEachTable[dataIndex++]] = std::move(element);
				//allocator.construct(&(Datas[index][UsedForEachTable[dataIndex++], element);
			}

			u32 getIndexFromIJ(u32 i, u32 j)
			{
				return j*RowSize + i;
			}

			u32 RowSize;
			u32 ColSize;
			u32 AllocatedAll;
			std::function<void(T*, int)> SortFunction;
			std::function<void(T*, u32&, u32, T&&)> SortInsertFunction;
			//hold the size of each small table
			//u32* AllocatedForEachTable;
			u32* UsedForEachTable;

			T** Datas;

			vgAllocator<T> allocator;
			eAllocStrategy strategy : 4;
		};
	}
}
#endif