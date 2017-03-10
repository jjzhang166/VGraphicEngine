#ifndef __CJ_TOOLFUNCTIONS_H__
#define __CJ_TOOLFUNCTIONS_H__
#include "vgTypes.h"

namespace vg
{
	namespace core
	{
		//***********************************
		//memory functions
		/*! this function fills or sets unsigned 16-bit aligned memory
		count is number of words*/
		inline void Mem_Set_WORD(void *dest, u16 data, int count)
		{
			_asm
			{
				mov edi, dest; edi points to destination memory
				mov ecx, count; number of 16 - bit words to move
				mov ax, data; 16 - bit data
				rep stosw; move data
			} // end asm

		} // end Mem_Set_WORD

		  /*! this function fills or sets unsigned 32-bit aligned memory
		  count is number of quads*/
		inline void Mem_Set_QUAD(void *dest, u32 data, s32 count)
		{
			_asm
			{
				mov edi, dest; edi points to destination memory
				mov ecx, count; number of 32 - bit words to move
				mov eax, data; 32 - bit data
				rep stosd; move data
			} // end asm

		} // end Mem_Set_QUAD


#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }

		inline int Write_Error(char *string, ...)
		{
			/*
			// this function prints out the error string to the error file

			char buffer[80]; // working buffer

			va_list arglist; // variable argument list

			// make sure both the error file and string are valid
			if (!string || !fp_error)
			return(0);

			// print out the string using the variable number of arguments on stack
			va_start(arglist, string);
			vsprintf(buffer, string, arglist);
			va_end(arglist);

			// write string to file
			fprintf(fp_error, buffer);

			// flush buffer incase the system bails
			fflush(fp_error);

			// return success*/
			printf("%s", string);
			return(1);
		} // end Write_Error
	}
}

#endif