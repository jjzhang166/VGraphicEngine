/**!
*与assert区分
*特点:当待检查和用户检查值类型不同时,通不过编译,即编译时检查
*作用:用户变量检查,特别是函数返回值检查
*/
#ifndef  __VGRAPHIC_CHECK_H__
#define __VGRAPHIC_CHECK_H__
#include "Config.h"

#ifdef _DEBUG
template<typename T>
class _check_t
{
	T _result;
public:
	explicit _check_t(const T& r) :_result(r) {}
	void check(const T&c, const char* file, size_t line)
	{
		if (_result != c)
			std::cerr << "CHECK\n\tfile:" << file << "\n\tline:" << line
			<< "\n\tcomment:" << c << "!=" << _result << "(expected)" << std::endl;
	}
};
template <typename T>
void _check(const T& r, const T& c, const char* file, size_t line)
{
	_check_t<T>(r).check(c, file, line);
}
#define CHECK(BECHECK,RESULT) _check((RESULT),(BECHECK),__FILE__,__LINE__)
#else
#define CHECK(BECHECK,RESULT) 
#endif

#endif // ! __VGRAPHIC_CHECK_H__