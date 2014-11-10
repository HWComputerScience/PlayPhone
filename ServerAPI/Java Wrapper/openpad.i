%module(directors="1") openpad
%{
#include "../PlayPhone/openpad.h"
%}

%feature("directors");

%include "java/std_vector.i"
%include "../PlayPhone/openpad.h"
%include "../PlayPhone/Server.h"
%include "../PlayPhone/Request.h"
%include "../PlayPhone/ServerHandler.h"