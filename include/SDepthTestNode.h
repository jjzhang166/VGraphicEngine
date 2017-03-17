#ifndef __VG_VR_DEPTHTESTNODE_H_INCLUDE__
#define __VG_VR_DEPTHTESTNODE_H_INCLUDE__
#include "ConfigForSL.h"
#include "glm\glm.hpp"

namespace vg
{
	namespace vr
	{

		class SDepthTestNode
		{
		public:
			glm::vec4 color;
			float zwin;

		public:
		};

		//! insert new node
		/**
		* Should bind to mularray first
		* Firstly,this function will insert the newnode
		* based on its depth,it will be inserted if its
		* depth is smaller.
		* Secondly,if their are 3 nodes with depth{0.1,0.3,0.5}
		* and the new node has depth 0.2 (alpha 1.0).
		* The data will be {0.1,0.2} because the 0.2 node is soild.
		* Can be optimiz by Two point search.
		*/
		inline void SortInsertFuncForSDepthTestNode(SDepthTestNode* data,
			unsigned int& used, unsigned int size, SDepthTestNode&& value)
		{
			if (used == 0)
			{
				data[used++] = std::move(value);
				return;
			}
			else if (used < size)
			{
				//for alpha one
				if (value.color.a<MAX_FLOAT_1_0)
				{
					//insert sort and insert
					for (int i = used - 1; i >-1; --i)
					{
						// first come succ
						if (value.zwin >= data[i].zwin)
						{
							data[i + 1] = std::move(value);
							++used;
							return;
						}
						else
						{
							data[i + 1] = std::move(data[i]);
						}
					}
					data[0] = std::move(value);
					++used;

					return;
				}

				//for soild one
				else
				{
					//insert sort and insert
					for (unsigned int i = 0; i <used; ++i)
					{
						// new soild first
						if (value.zwin <= data[i].zwin)
						{
							data[i] = std::move(value);
							used = i + 1;
							return;
						}
					}
					data[used++] = std::move(value);

					return;
				}
			}
			else//used==size,drop the farthest
			{
				if (value.zwin >= data[used - 1].zwin)
					return;

				if (value.color.a >= MAX_FLOAT_1_0)
				{
					for (unsigned int i = 0; i <used; ++i)
					{
						// soild first
						if (value.zwin <= data[i].zwin)
						{
							data[i] = std::move(value);
							used = i + 1;
							return;
						}
					}
				}
				else
				{
					data[used - 1] = std::move(value);
					for (unsigned int i = used - 1; i > 0; --i)
					{
						if (data[i].zwin < data[i - 1].zwin)
						{
							std::swap(data[i], data[i - 1]);
						}
						else
							return;
					}
				}
			}
		}
	}
}

#endif//! __VG_VR_DEPTHTESTNODE_H_INCLUDE__