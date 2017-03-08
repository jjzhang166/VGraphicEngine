#include "vgAssert.h"

bool CustomAssertPFailure(bool exp, char* description, char* file, int line, int level)
{
	//¶ÏÑÔÕıÈ·
	if (exp)
		return false;
	//¶ÏÑÔ´íÎó
	std::cerr << "ASSERT:\n\tleve:" << level << "\n\tfile:" << file << "\n\tline:" << line
		<< "\n\tdescription:" << description
		//<<"\n\texp:"<< exp  
		<< std::endl;
	if (level >= ASSERT_LEVEL)
		return true;
	return false;
}