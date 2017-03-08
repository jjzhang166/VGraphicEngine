#ifndef __VGRAPHICENGINE__ASSERT_H__
#define __VGRAPHICENGINE__ASSERT_H__
#include "Config.h"

//namespace ce
//{
//当ASSERT_LEVEL<=-1则不会在生成文件加入assert信息.
#if( ASSERT_LEVEL > EAL_CLOSE)
//定义一个内敛汇编让调试器暂停程序
//不同平台有不同实现
#define DEBUG_BREAK {_asm {int 3}}
//检查是否出错,如果出错则报告错误,并返回true
extern bool CustomAssertPFailure(bool exp, char* description, char* file, int line, int level);
/**
* ASSERT_LEVEL:断言等级,如果需要判断等级小于当前调试等级,不中断,但是会将错误报告.
\param expr 断言内容
\param description 附加消息:为char*,
自己写的缺陷就是无法将断言内容直接显示,所以需要这个作为提示
\param P 断言等级,大于等于ASSERT_LEVEL才会中断*/
#define AssertP(expr,description,P)\
	{\
		if ( CustomAssertPFailure((bool)(expr), description, __FILE__,__LINE__,P ))\
			{\
				DEBUG_BREAK; \
			}\
	}

#else
//不做任何事情
#define AssertP(expr, description, P)
#endif
//}
#endif//__VGRAPHICENGINE__ASSERT_H__