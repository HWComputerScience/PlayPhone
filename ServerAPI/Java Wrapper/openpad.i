%module(directors="1") openpad
%{
#include "../PlayPhone/openpad.h"
%}

%feature("directors");

%include "std_string.i"
%include "std_vector.i"
#include <string>
#include <vector>

%include "../PlayPhone/openpad.h"
%include "../PlayPhone/Server.h"
%include "../PlayPhone/Request.h"
%include "../PlayPhone/ServerHandler.h"