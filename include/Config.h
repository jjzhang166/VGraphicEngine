#ifndef __VGRAPHICENGINE_CONFIG_H_INCLUDE__
#define __VGRAPHICENGINE_CONFIG_H_INCLUDE__
#include <iostream>

#define VG_SDK_VERSION_STRING  "VGraphicEngine version 0.0.0"

//! WIN32 for Windows32
//! WIN64 for Windows64
// The windows platform and API support SDL and WINDOW device
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _VG_WINDOWS_
#define _VG_WINDOWS_API_
#define _VG_COMPILE_WITH_WINDOWS_DEVICE_
#endif

//����
#ifdef _DEBUG
#ifndef ASSERT_LEVEL 
//���Եȼ�����
//��6��
/*enum EnumAssertLevel
{
EAL_CLOSE = 0,//�ر�
EAL_OPENALL =1,//��������
EAL_PROPETY = 2,//��Դ��
EAL_MEMALLOC = 5,//�ڴ������
};*/
#define EAL_CLOSE  0//�ر�
#define EAL_OPENALL  1//��������
#define EAL_PROPETY 2//��Դ��
#define EAL_WARNING 3//warning
#define EAL_ERROR 4//error
#define EAL_MEMALLOC  5//�ڴ������

#define ASSERT_LEVEL EAL_OPENALL
#endif
//���ͼ������
#else

#endif


#endif//! __VGRAPHICENGINE_CONFIG_H_INCLUDE__