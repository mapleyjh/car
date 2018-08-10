#ifndef __HC_H_
#define __HC_H_

#include "stm32f4xx.h"
#include "sys.h"
#include "systick.h"


#define  TRIG	PEout(5)
#define  ECHO	PEin(6)

void HC_init(void);
float  Get_distan(void);


extern u32 tim_count;

#endif


