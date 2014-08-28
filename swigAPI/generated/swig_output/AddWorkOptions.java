/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class AddWorkOptions extends EObject {
  private long swigCPtr;

  protected AddWorkOptions(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.SWIGAddWorkOptionsUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(AddWorkOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_AddWorkOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public AddWorkOptions() {
    this(VISHNUJNI.new_AddWorkOptions(), true);
  }

  public void _initialize() {
    VISHNUJNI.AddWorkOptions__initialize(swigCPtr, this);
  }

  public String getApplicationId() {
    return VISHNUJNI.AddWorkOptions_getApplicationId(swigCPtr, this);
  }

  public void setApplicationId(String _applicationId) {
    VISHNUJNI.AddWorkOptions_setApplicationId(swigCPtr, this, _applicationId);
  }

  public String getSubject() {
    return VISHNUJNI.AddWorkOptions_getSubject(swigCPtr, this);
  }

  public void setSubject(String _subject) {
    VISHNUJNI.AddWorkOptions_setSubject(swigCPtr, this, _subject);
  }

  public int getPriority() {
    return VISHNUJNI.AddWorkOptions_getPriority(swigCPtr, this);
  }

  public void setPriority(int _priority) {
    VISHNUJNI.AddWorkOptions_setPriority(swigCPtr, this, _priority);
  }

  public String getOwner() {
    return VISHNUJNI.AddWorkOptions_getOwner(swigCPtr, this);
  }

  public void setOwner(String _owner) {
    VISHNUJNI.AddWorkOptions_setOwner(swigCPtr, this, _owner);
  }

  public long getEstimatedHour() {
    return VISHNUJNI.AddWorkOptions_getEstimatedHour(swigCPtr, this);
  }

  public void setEstimatedHour(long _estimatedHour) {
    VISHNUJNI.AddWorkOptions_setEstimatedHour(swigCPtr, this, _estimatedHour);
  }

  public String getDescription() {
    return VISHNUJNI.AddWorkOptions_getDescription(swigCPtr, this);
  }

  public void setDescription(String _description) {
    VISHNUJNI.AddWorkOptions_setDescription(swigCPtr, this, _description);
  }

  public String getProjectId() {
    return VISHNUJNI.AddWorkOptions_getProjectId(swigCPtr, this);
  }

  public void setProjectId(String _projectId) {
    VISHNUJNI.AddWorkOptions_setProjectId(swigCPtr, this, _projectId);
  }

  public String getMachineId() {
    return VISHNUJNI.AddWorkOptions_getMachineId(swigCPtr, this);
  }

  public void setMachineId(String _machineId) {
    VISHNUJNI.AddWorkOptions_setMachineId(swigCPtr, this, _machineId);
  }

  public int getNbCPU() {
    return VISHNUJNI.AddWorkOptions_getNbCPU(swigCPtr, this);
  }

  public void setNbCPU(int _nbCPU) {
    VISHNUJNI.AddWorkOptions_setNbCPU(swigCPtr, this, _nbCPU);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.AddWorkOptions_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.AddWorkOptions_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.AddWorkOptions_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.AddWorkOptions_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.AddWorkOptions__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
