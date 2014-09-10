/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class ListJobResults extends EObject {
  private long swigCPtr;

  public ListJobResults(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.ListJobResults_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListJobResults obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_ListJobResults(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ListJobResults() {
    this(VISHNUJNI.new_ListJobResults(), true);
  }

  public void _initialize() {
    VISHNUJNI.ListJobResults__initialize(swigCPtr, this);
  }

  public int getNbJobs() {
    return VISHNUJNI.ListJobResults_getNbJobs(swigCPtr, this);
  }

  public void setNbJobs(int _nbJobs) {
    VISHNUJNI.ListJobResults_setNbJobs(swigCPtr, this, _nbJobs);
  }

  public EJobResultList getResults() {
    return new EJobResultList(VISHNUJNI.ListJobResults_getResults(swigCPtr, this), false);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.ListJobResults_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.ListJobResults_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.ListJobResults_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.ListJobResults_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.ListJobResults__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
