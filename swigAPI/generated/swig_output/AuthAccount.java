/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class AuthAccount extends EObject {
  private long swigCPtr;

  protected AuthAccount(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.SWIGAuthAccountUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AuthAccount obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_AuthAccount(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public AuthAccount() {
    this(VISHNUJNI.new_AuthAccount(), true);
  }

  public void _initialize() {
    VISHNUJNI.AuthAccount__initialize(swigCPtr, this);
  }

  public String getAuthSystemId() {
    return VISHNUJNI.AuthAccount_getAuthSystemId(swigCPtr, this);
  }

  public void setAuthSystemId(String _authSystemId) {
    VISHNUJNI.AuthAccount_setAuthSystemId(swigCPtr, this, _authSystemId);
  }

  public String getUserId() {
    return VISHNUJNI.AuthAccount_getUserId(swigCPtr, this);
  }

  public void setUserId(String _userId) {
    VISHNUJNI.AuthAccount_setUserId(swigCPtr, this, _userId);
  }

  public String getAcLogin() {
    return VISHNUJNI.AuthAccount_getAcLogin(swigCPtr, this);
  }

  public void setAcLogin(String _acLogin) {
    VISHNUJNI.AuthAccount_setAcLogin(swigCPtr, this, _acLogin);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.AuthAccount_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.AuthAccount_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.AuthAccount_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.AuthAccount_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.AuthAccount__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
