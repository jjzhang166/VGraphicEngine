#ifndef __VGRAPHICENGINE__ASSERT_H__
#define __VGRAPHICENGINE__ASSERT_H__
#include "Config.h"

//namespace ce
//{
//��ASSERT_LEVEL<=-1�򲻻��������ļ�����assert��Ϣ.
#if( ASSERT_LEVEL > EAL_CLOSE)
//����һ����������õ�������ͣ����
//��ͬƽ̨�в�ͬʵ��
#define DEBUG_BREAK {_asm {int 3}}
//����Ƿ����,��������򱨸����,������true
inline bool CustomAssertPFailure(bool exp, char* description, char* file, int line, int level)
{
	//������ȷ
	if (exp)
		return false;
	//���Դ���
	std::cerr << "ASSERT:\n\tleve:" << level << "\n\tfile:" << file << "\n\tline:" << line
		<< "\n\tdescription:" << description
		//<<"\n\texp:"<< exp  
		<< std::endl;
	if (level >= ASSERT_LEVEL)
		return true;
	return false;
}
/**
* ASSERT_LEVEL:���Եȼ�,�����Ҫ�жϵȼ�С�ڵ�ǰ���Եȼ�,���ж�,���ǻὫ���󱨸�.
\param expr ��������
\param description ������Ϣ:Ϊchar*,
�Լ�д��ȱ�ݾ����޷�����������ֱ����ʾ,������Ҫ�����Ϊ��ʾ
\param P ���Եȼ�,���ڵ���ASSERT_LEVEL�Ż��ж�*/
#define AssertP(expr,description,P)\
	{\
		if ( CustomAssertPFailure((bool)(expr), description, __FILE__,__LINE__,P ))\
			{\
				DEBUG_BREAK; \
			}\
	}

#else
//�����κ�����
#define AssertP(expr, description, P)
#endif
//}
#endif//__VGRAPHICENGINE__ASSERT_H__