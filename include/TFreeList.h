/**!
* �ڴ�� TFreeList.h - a templated freelist class.
* ����һ����Ϊ������ͬ���������ڴ�,������Ƭ��
* ������:����,������,����ڵ�,����ʵ��,����
* ��������޸�����Ϸ��̾���1,��ش��뼰������Ҫ��������Ȩ:
* "Portions Copyright (C) Steven Ranck, 2000"
*/


#ifndef __CHANGVOXEL_TFREELIST_H__
#define __CHANGVOXEL_TFREELIST_H__
#include "vgAssert.h"

namespace vg
{
	namespace core
	{
		/*
		*ʹ�þ���:TFreeList<CTreeNode> TreeNodePool(1024);
		CTreeNode* pNode = TreeNodePool.NewInstance();
		TreeNodePool.FreeInstance(pNode);
		//ʹ��:FreeList
		FLDataType��Ҫ��Ĭ�Ϲ��캯��.
		����ĳ�ʼ������Ĭ�Ϲ��캯��,������Ҫ���õı����������Ӻ���Reset����
		����:
		CParticle* pParticle  = ParticlePool.NewInstance();
		ԭ��:
		�������������FLDataType ����,���һ�������FLDataTypeָ��
		��,ָ��������Ϊһ��������ջ������ָ��ÿһ��FLDataType�����ָ��.
		*/
		template <class FLDataType>
		class TFreeList
		{
		public:

			// Construct a TFreeList with the specified number
			// of objects available for allocation.
			TFreeList(int iNumObjects)
			{
				AssertP((iNumObjects > 0), "Invalid TFreeList size specified.", EAL_MEMALLOC);

				m_pObjectData = new FLDataType[iNumObjects];
				m_ppFreeObjects = new FLDataType*[iNumObjects];

				AssertP(m_pObjectData != NULL, "Not enough memory to allocate object data!", EAL_MEMALLOC);
				AssertP(m_ppFreeObjects != NULL, "Not enough memory to allocate pointer stack!", EAL_MEMALLOC);

				m_iNumObjects = iNumObjects;
				m_bFreeOnDestroy = true;

				freeAll();
			}

			// Constructs a TFreeList with the specified number
			// of objects available for allocation from pre-allocated
			// memory referenced by "pObjectData" and "ppFreeObjects".
			// Note that pObjectData and ppFreeObjects must have
			// "iNumObjects" elements each.
			TFreeList(FLDataType *pObjectData, FLDataType **ppFreeObjects, int iNumObjects)
			{
				AssertP((iNumObjects > 0), "Invalid TFreeList size specified.", EAL_MEMALLOC);

				m_pObjectData = pObjectData;
				m_ppFreeObjects = ppFreeObjects;

				AssertP(m_pObjectData, "A NULL pointer was passed for the object data!", EAL_MEMALLOC);
				AssertP(m_ppFreeObjects, "A NULL pointer was passed for the pointer stack!", EAL_MEMALLOC);

				m_iNumObjects = iNumObjects;
				m_bFreeOnDestroy = false;

				freeAll();
			}

			~TFreeList(void)
			{
				// If we have allocated memory,
				// then we must free it.
				if (m_bFreeOnDestroy)
				{
					delete[] m_ppFreeObjects;
					delete[] m_pObjectData;
				}
			}

			/* Returns a pointer to a free instance of FLDataType.
			����Ҫ�ǳ�С��,����ڴ治��,�ڷ��а��ǲ��ܼ������
			������DEBUG������������.
			*/
			FLDataType *newInstance(void)
			{
				AssertP(m_iTop>0, "Tried to get a new instance but there"
					"were no free instances available for "
					"allocation. Consider using GetFree()!", EAL_MEMALLOC);

				return m_ppFreeObjects[--m_iTop];
			}

			// Reclaims the instance referenced by pInstance.
			void freeInstance(FLDataType *pInstance)
			{
				AssertP((pInstance >= &(m_pObjectData[0])) &&
					(pInstance <= &(m_pObjectData[m_iNumObjects - 1])),
					"Tried to free an object that was"
					"not from this TFreeList", EAL_MEMALLOC);

				// You might consider putting a debug-only check here to make sure
				// the instance that is being freed isn't already free.

				AssertP((m_iTop < m_iNumObjects), "You have freed at least one"
					"instance more than once.", EAL_MEMALLOC);

				m_ppFreeObjects[m_iTop++] = pInstance;
			}

			// Makes all instances available for allocation.
			void freeAll(void)
			{
				int iIndex = (m_iNumObjects - 1);

				for (m_iTop = 0; m_iTop < m_iNumObjects; m_iTop++)
				{
					m_ppFreeObjects[m_iTop] = &(m_pObjectData[iIndex--]);
				}
			}

			// Returns the total number of objects
			// managed by this TFreeList.
			int size(void)
			{
				return m_iNumObjects;
			}

			// Returns the number of instances available
			// for allocation.
			int getFree(void)
			{
				return m_iTop;
			}

		private:

			// Points to the array of objects.
			FLDataType *m_pObjectData;

			// The number of objects in m_pObjectData.
			int m_iNumObjects;


			// Points to an array of pointers to free
			// objects within m_pObjectData.  Used as
			// a fixed sized stack.
			FLDataType **m_ppFreeObjects;

			// Keeps track of the first available object in
			// m_ppFreeObjects (the top of the stack).
			int m_iTop;


			// Remembers weather or not to free memory on
			// destruction.
			bool m_bFreeOnDestroy;
		};

	}
}

#endif // __CHANGVOXEL_TFREELIST_H__
