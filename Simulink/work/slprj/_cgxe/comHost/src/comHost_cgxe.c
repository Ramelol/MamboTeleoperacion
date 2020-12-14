/* Include files */

#include "comHost_cgxe.h"
#include "m_1WII9J5l3mzThe9nPY7wK.h"

unsigned int cgxe_comHost_method_dispatcher(SimStruct* S, int_T method, void
  * data)
{
  if (ssGetChecksum0(S) == 3804567295 &&
      ssGetChecksum1(S) == 2091495372 &&
      ssGetChecksum2(S) == 51182764 &&
      ssGetChecksum3(S) == 3899085951) {
    method_dispatcher_1WII9J5l3mzThe9nPY7wK(S, method, data);
    return 1;
  }

  return 0;
}
