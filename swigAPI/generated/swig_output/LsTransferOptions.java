/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class LsTransferOptions extends EObject {
  private long swigCPtr;

  public LsTransferOptions(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.LsTransferOptions_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(LsTransferOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_LsTransferOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public LsTransferOptions() {
    this(VISHNUJNI.new_LsTransferOptions(), true);
  }

  public void _initialize() {
    VISHNUJNI.LsTransferOptions__initialize(swigCPtr, this);
  }

  public String getTransferId() {
    return VISHNUJNI.LsTransferOptions_getTransferId(swigCPtr, this);
  }

  public void setTransferId(String _transferId) {
    VISHNUJNI.LsTransferOptions_setTransferId(swigCPtr, this, _transferId);
  }

  public String getFromMachineId() {
    return VISHNUJNI.LsTransferOptions_getFromMachineId(swigCPtr, this);
  }

  public void setFromMachineId(String _fromMachineId) {
    VISHNUJNI.LsTransferOptions_setFromMachineId(swigCPtr, this, _fromMachineId);
  }

  public String getUserId() {
    return VISHNUJNI.LsTransferOptions_getUserId(swigCPtr, this);
  }

  public void setUserId(String _userId) {
    VISHNUJNI.LsTransferOptions_setUserId(swigCPtr, this, _userId);
  }

  public int getStatus() {
    return VISHNUJNI.LsTransferOptions_getStatus(swigCPtr, this);
  }

  public void setStatus(int _status) {
    VISHNUJNI.LsTransferOptions_setStatus(swigCPtr, this, _status);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.LsTransferOptions_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.LsTransferOptions_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.LsTransferOptions_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.LsTransferOptions_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.LsTransferOptions__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
