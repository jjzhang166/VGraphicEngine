#ifndef _CHANGVOXEL_ALLOCATOR_H_
#define _CHANGVOXEL_ALLOCATOR_H_

#include "vgTypes.h"
#include <new>

#include <memory.h>

namespace vg
{
	namespace core
	{
#ifdef DEBUG_CLIENTBLOCK
		#udef DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK new
#endif

			//! Simple allocator
			template<typename T>
		class vgAllocator
		{
		public:

			//! Destructor
			virtual ~vgAllocator() {}

			//! Allocate memory for an array of objects
			T* allocate(size_t cnt)
			{
				return (T*)internal_new(cnt * sizeof(T));
			}

			//! Deallocate memory for an array of objects
			void deallocate(T* ptr)
			{
				internal_delete(ptr);
			}

			//! Construct an element
			void construct(T* ptr, const T&e)
			{
				new ((void*)ptr) T(e);
			}

			//! Destruct an element
			void destruct(T* ptr)
			{
				ptr->~T();
			}

		protected:

			virtual void* internal_new(size_t cnt)
			{
				return operator new(cnt);
			}

			virtual void internal_delete(void* ptr)
			{
				operator delete(ptr);
			}
		};//end class cvAllocator

		  //! Fast allocator, only to be used in containers inside the same memory heap.
		  /** Containers using it are NOT able to be used it across dll boundaries. Use this
		  when using in an internal class or function or when compiled into a static lib */
		template<typename T>
		class cvAllocatorFast
		{
		public:
			//! Allocate memory for an array of objects
			T* allocate(size_t cnt)
			{
				return (T*)operator new(cnt * sizeof(T));
			}

			//! Deallocate memory for an array of objects
			void deallocate(T* ptr)
			{
				operator delete(ptr);
			}
		private:

			//! Construct an element
			void construct(T* ptr, const T& e)
			{
				new ((void*)ptr)T(e);
			}

			//! Destruct an element
			void destruct(T* ptr)
			{
				ptr->~T();
			}
		};//end cvAllocatorFast

#ifdef DEBUG_CLIENTBLOCK
#undef DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif

		  //! defines an allocation strategy
		enum eAllocStrategy
		{
			ALLOC_STRATEGY_SAFE = 0,
			ALLOC_STRATEGY_DOUBLE = 1,
			ALLOC_STRATEGY_SQRT = 2,
		};


	}//end core
}//end cv
#endif