/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class IDObject extends Serializable {
  private long swigCPtr;

  protected IDObject(long cPtr, boolean cMemoryOwn) {
    super(openpadJNI.IDObject_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IDObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        openpadJNI.delete_IDObject(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public IDObject() {
    this(openpadJNI.new_IDObject(), true);
  }

  public SWIGTYPE_p_Value serializeJSON(SWIGTYPE_p_Document__AllocatorType a) {
    return new SWIGTYPE_p_Value(openpadJNI.IDObject_serializeJSON(swigCPtr, this, SWIGTYPE_p_Document__AllocatorType.getCPtr(a)), false);
  }

  public boolean parseJSON(SWIGTYPE_p_Value v) {
    return openpadJNI.IDObject_parseJSON(swigCPtr, this, SWIGTYPE_p_Value.getCPtr(v));
  }

  public void setPhoneid(String value) {
    openpadJNI.IDObject_phoneid_set(swigCPtr, this, value);
  }

  public String getPhoneid() {
    return openpadJNI.IDObject_phoneid_get(swigCPtr, this);
  }

  public void setFirstname(String value) {
    openpadJNI.IDObject_firstname_set(swigCPtr, this, value);
  }

  public String getFirstname() {
    return openpadJNI.IDObject_firstname_get(swigCPtr, this);
  }

  public void setLastname(String value) {
    openpadJNI.IDObject_lastname_set(swigCPtr, this, value);
  }

  public String getLastname() {
    return openpadJNI.IDObject_lastname_get(swigCPtr, this);
  }

  public void setUsername(String value) {
    openpadJNI.IDObject_username_set(swigCPtr, this, value);
  }

  public String getUsername() {
    return openpadJNI.IDObject_username_get(swigCPtr, this);
  }

  public void setFbuid(String value) {
    openpadJNI.IDObject_fbuid_set(swigCPtr, this, value);
  }

  public String getFbuid() {
    return openpadJNI.IDObject_fbuid_get(swigCPtr, this);
  }

}
