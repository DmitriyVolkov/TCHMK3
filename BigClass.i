%module BigClass
%{
/* Includes the header in the wrapper code */
#include "BigClass.h"
%}


/* Parse the header file to generate wrappers */
%include "BigClass.h"