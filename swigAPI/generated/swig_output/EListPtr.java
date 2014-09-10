/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class EListPtr {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public EListPtr(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EListPtr obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_EListPtr(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EListPtr() {
    this(VISHNUJNI.new_EListPtr__SWIG_0(), true);
  }

  public EListPtr(SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t t, boolean ownership) {
    this(VISHNUJNI.new_EListPtr__SWIG_1(SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t.getCPtr(t), ownership), true);
  }

  public EListPtr(EListPtr other) {
    this(VISHNUJNI.new_EListPtr__SWIG_2(EListPtr.getCPtr(other), other), true);
  }

  public SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t get() {
    long cPtr = VISHNUJNI.EListPtr_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t(cPtr, false);
  }

  public SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t __ref__() {
    return new SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t(VISHNUJNI.EListPtr___ref__(swigCPtr, this), false);
  }

  public SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t __deref__() {
    long cPtr = VISHNUJNI.EListPtr___deref__(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t(cPtr, false);
  }

  public SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t release() {
    long cPtr = VISHNUJNI.EListPtr_release(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t(cPtr, false);
  }

  public void reset(SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t other, boolean ownership) {
    VISHNUJNI.EListPtr_reset(swigCPtr, this, SWIGTYPE_p_ecorecpp__mapping__EListT_ecore__EObject_t.getCPtr(other), ownership);
  }

}
