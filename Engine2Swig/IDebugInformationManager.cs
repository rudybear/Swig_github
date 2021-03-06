//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IDebugInformationManager : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IDebugInformationManager(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(IDebugInformationManager obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IDebugInformationManager() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IDebugInformationManager(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual void LoadParam(SWIGTYPE_p_CParam arg0) {
    Engine2PINVOKE.IDebugInformationManager_LoadParam(swigCPtr, SWIGTYPE_p_CParam.getCPtr(arg0));
  }

  public virtual void AddDebugParam(SWIGTYPE_p_CParam arg0, string section) {
    Engine2PINVOKE.IDebugInformationManager_AddDebugParam(swigCPtr, SWIGTYPE_p_CParam.getCPtr(arg0), section);
  }

  public virtual void RemoveDebugParam(SWIGTYPE_p_CParam arg0) {
    Engine2PINVOKE.IDebugInformationManager_RemoveDebugParam(swigCPtr, SWIGTYPE_p_CParam.getCPtr(arg0));
  }

  public virtual uint GetDebugParamNums() {
    uint ret = Engine2PINVOKE.IDebugInformationManager_GetDebugParamNums(swigCPtr);
    return ret;
  }

  public virtual string GetDebugParamSection(uint num) {
    string ret = Engine2PINVOKE.IDebugInformationManager_GetDebugParamSection(swigCPtr, num);
    return ret;
  }

  public virtual SWIGTYPE_p_CParam GetDebugParam(uint num) {
    global::System.IntPtr cPtr = Engine2PINVOKE.IDebugInformationManager_GetDebugParam(swigCPtr, num);
    SWIGTYPE_p_CParam ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_CParam(cPtr, false);
    return ret;
  }

  public virtual SWIGTYPE_p_CParam GetDebugParamByName(string sParamName) {
    global::System.IntPtr cPtr = Engine2PINVOKE.IDebugInformationManager_GetDebugParamByName(swigCPtr, sParamName);
    SWIGTYPE_p_CParam ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_CParam(cPtr, false);
    return ret;
  }

  public virtual void ExecuteString(string arg0) {
    Engine2PINVOKE.IDebugInformationManager_ExecuteString(swigCPtr, arg0);
  }

  public virtual int GetNumCVars() {
    int ret = Engine2PINVOKE.IDebugInformationManager_GetNumCVars(swigCPtr);
    return ret;
  }

  public virtual string GetCVarName(int num) {
    string ret = Engine2PINVOKE.IDebugInformationManager_GetCVarName(swigCPtr, num);
    return ret;
  }

  public virtual string GetCVarValue(int num) {
    string ret = Engine2PINVOKE.IDebugInformationManager_GetCVarValue(swigCPtr, num);
    return ret;
  }

  public virtual string GetCVarType(int num) {
    string ret = Engine2PINVOKE.IDebugInformationManager_GetCVarType(swigCPtr, num);
    return ret;
  }

  public virtual bool SetDebugParamInt(string sParamName, int value) {
    bool ret = Engine2PINVOKE.IDebugInformationManager_SetDebugParamInt(swigCPtr, sParamName, value);
    return ret;
  }

  public virtual bool SetDebugParamFloat(string sParamName, float value) {
    bool ret = Engine2PINVOKE.IDebugInformationManager_SetDebugParamFloat(swigCPtr, sParamName, value);
    return ret;
  }

  public virtual bool SetDebugParamString(string sParamName, string sValue) {
    bool ret = Engine2PINVOKE.IDebugInformationManager_SetDebugParamString(swigCPtr, sParamName, sValue);
    return ret;
  }

}
