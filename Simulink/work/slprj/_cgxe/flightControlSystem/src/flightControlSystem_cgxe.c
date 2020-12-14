/* Include files */

#include "flightControlSystem_cgxe.h"
#include "m_9zZeOQuMzxfN9oN4tdYNSH.h"

unsigned int cgxe_flightControlSystem_method_dispatcher(SimStruct* S, int_T
  method, void* data)
{
  if (ssGetChecksum0(S) == 2343501446 &&
      ssGetChecksum1(S) == 1594048323 &&
      ssGetChecksum2(S) == 1586333305 &&
      ssGetChecksum3(S) == 1189338287) {
    method_dispatcher_9zZeOQuMzxfN9oN4tdYNSH(S, method, data);
    return 1;
  }

  return 0;
}
