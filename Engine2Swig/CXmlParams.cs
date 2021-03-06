//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class CXmlParams : IXmlParams {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal CXmlParams(global::System.IntPtr cPtr, bool cMemoryOwn) : base(Engine2PINVOKE.CXmlParams_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(CXmlParams obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CXmlParams() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_CXmlParams(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public CXmlParams() : this(Engine2PINVOKE.new_CXmlParams(), true) {
  }

  public override CXmlParam GetParam(int i) {
    global::System.IntPtr cPtr = Engine2PINVOKE.CXmlParams_GetParam(swigCPtr, i);
    CXmlParam ret = (cPtr == global::System.IntPtr.Zero) ? null : new CXmlParam(cPtr, false);
    return ret;
  }

  public override CXmlParam GetParamByName(Engine2String szName) {
    global::System.IntPtr cPtr = Engine2PINVOKE.CXmlParams_GetParamByName(swigCPtr, Engine2String.getCPtr(szName));
    CXmlParam ret = (cPtr == global::System.IntPtr.Zero) ? null : new CXmlParam(cPtr, false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public override int GetNumParams() {
    int ret = Engine2PINVOKE.CXmlParams_GetNumParams(swigCPtr);
    return ret;
  }

  public override string GetValueByName(Engine2String KeyName) {
    string ret = Engine2PINVOKE.CXmlParams_GetValueByName(swigCPtr, Engine2String.getCPtr(KeyName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public override void SetParam(Engine2String KeyName, Engine2String NewParamName) {
    Engine2PINVOKE.CXmlParams_SetParam(swigCPtr, Engine2String.getCPtr(KeyName), Engine2String.getCPtr(NewParamName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public SWIGTYPE_p_Engine2__VectorT_CXmlParam_t m_Contents {
    set {
      Engine2PINVOKE.CXmlParams_m_Contents_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_CXmlParam_t.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CXmlParams_m_Contents_get(swigCPtr);
      SWIGTYPE_p_Engine2__VectorT_CXmlParam_t ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_Engine2__VectorT_CXmlParam_t(cPtr, false);
      return ret;
    } 
  }

}
