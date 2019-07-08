/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  ARM_Compute                            */
/*      FILE         :  ARM_Compute.cpp                        */
/*      DESCRIPTION  :  Main Program                           */
/*                                                             */
/*      This file was generated by e2 studio.                  */
/*                                                             */
/***************************************************************/
#include <typedefine.h>
#include <iodefine.h>

#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/MultiHOG.h"
#include "arm_compute/runtime/NEON/functions/NEHOGMultiDetection.h"
#include "arm_compute/runtime/Tensor.h"

#ifdef CPPAPP
//Initialize global constructors
extern void __main()
{
  static int initialized;
  if (! initialized)
    {
      typedef void (*pfunc) ();
      extern pfunc __ctors[];
      extern pfunc __ctors_end[];
      pfunc *p;

      initialized = 1;
      for (p = __ctors_end; p > __ctors; )
    (*--p) ();

    }
}
#endif 

int main(void) {

    while(1) {
	// TODO: add application code here
    }
return 0;
}