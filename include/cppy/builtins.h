#ifndef CPPY_BUILTINS_H
#define CPPY_BUILTINS_H

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* Return evenly spaced numbers over a specified interval.
*
*  Returns `num` evenly spaced samples, calculated over the interval [`start`, `stop`].
*  The endpoint of the interval can optionally be excluded.
*
*  start
*    The starting value
*  stop
*    The end value
*  num : int, optional
*    Number of samples to generate. Must be non-negative.
*  endpoint : bool, optional
*    If True, `stop` is the last sample. Otherwise, it is not included.
*    Default is True.
*
*  >>> np.linspace(2.0, 3.0, 5)
*  array([2.  , 2.25, 2.5 , 2.75, 3.  ])
*  >>> np.linspace(2.0, 3.0, 5, endpoint=False)
*  array([2. ,  2.2,  2.4,  2.6,  2.8])
*/
CPPY_API CPPY_ERROR_t CPPY_BUILTINS_linspace(double start, double end, int num, double result[], bool endpoint = true);

#endif // CPPY_BUILTINS_H
