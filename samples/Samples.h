#ifndef __VG_SAMPLES_H__
#define __VG_SAMPLES_H__

#ifndef INCLUDE_VGENGINE
#define INCLUDE_VGENGINE
#include "VGraphicEngine.h"
#include "VRenderer.h"
#endif

#define CURRENT_SAMPLEID 3

#if(CURRENT_SAMPLEID==0)
#define __SAMPLE_TEST_0__
#elif((CURRENT_SAMPLEID==1))
#define __SAMPLE_TEST_1__
#elif((CURRENT_SAMPLEID==2))
#define __SAMPLE_TEST_2__
#elif((CURRENT_SAMPLEID==3))
#define __SAMPLE_TEST_3__

#endif



#endif//! __VG_SAMPLES_H__