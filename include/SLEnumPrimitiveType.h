#ifndef __VG_SL_ENUMPRIMITIVETYPES_H_INCLUDE__
#define __VG_SL_ENUMPRIMITIVETYPES_H_INCLUDE__

namespace vg
{
	namespace sl
	{
		enum E_Primitive_Type
		{
			EPT_POINTS = 1,
			EPT_LINES = 2,
			EPT_TRIANGLES = 3,
			EPT_QUADS = 4,
			EPT_VOXEL = 5,
			//
			EPT_LINE_STRIP,
			EPT_LINE_LOOP,
			EPT_TRIANGLE_STRIP,
			EPT_TRIANGLE_FAN,
			EPT_QUAD_STRIP
		};
		inline int getEPTPointNum(E_Primitive_Type enm)
		{
			switch (enm)
			{
			case EPT_POINTS:
				return 1;
				break;
			case EPT_LINES:
				return 2;
				break;
			case EPT_TRIANGLES:
				return 3;
				break;
			case EPT_QUADS:
				return 4;
				break;
			case EPT_VOXEL:
				return 1;
				break;
			case EPT_LINE_STRIP:
				return 2;
				break;
			case EPT_LINE_LOOP:
				return 2;
				break;
			case EPT_TRIANGLE_STRIP:
				return 3;
				break;
			case EPT_TRIANGLE_FAN:
				return 3;
				break;
			case EPT_QUAD_STRIP:
				return 4;
				break;
			default:
				break;
			}
			return 0;
		}
	}
}

#endif//! 