%module(directors="1") openpad
%{
#include "../PlayPhone/openpad.h"
%}

#include "../PlayPhone/openpad.h"
%include "std_string.i"
%include "std_vector.i"
#include <string>
#include <vector>

%typemap(jni) std::string *INOUT, std::string &INOUT %{jobjectArray%}
%typemap(jtype) std::string *INOUT, std::string &INOUT "java.lang.String[]"
%typemap(jstype) std::string *INOUT, std::string &INOUT "java.lang.String[]"
%typemap(javain) std::string *INOUT, std::string &INOUT "$javainput"

%typemap(in) std::string *INOUT (std::string strTemp ), std::string &INOUT (std::string strTemp ) {
  if (!$input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
    return $null;
  }
  if (JCALL1(GetArrayLength, jenv, $input) == 0) {
    SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
    return $null;
  }

  jobject oInput = JCALL2(GetObjectArrayElement, jenv, $input, 0); 
  if ( NULL != oInput ) {
    jstring sInput = static_cast<jstring>( oInput );

    const char * $1_pstr = (const char *)jenv->GetStringUTFChars(sInput, 0); 
    if (!$1_pstr) return $null;
    strTemp.assign( $1_pstr );
    jenv->ReleaseStringUTFChars( sInput, $1_pstr);  
  }

  $1 = &strTemp;
}

%typemap(freearg) std::string *INOUT, std::string &INOUT ""

%typemap(argout) std::string *INOUT, std::string &INOUT
{ 
  jstring jStrTemp = jenv->NewStringUTF( strTemp$argnum.c_str() );
  JCALL3(SetObjectArrayElement, jenv, $input, 0, jStrTemp ); 
}

%ignore openpad::Server::handleRequest(Request &r, Client *cli);
%ignore openpad::Serializable::JSONvalue;

%include "../PlayPhone/openpad.h"
%include "../PlayPhone/Server.h"
%include "../PlayPhone/Request.h"

%feature("director") openpad::ServerHandler;
%include "../PlayPhone/ServerHandler.h"