//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class XRefInfo : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal XRefInfo(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(XRefInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~XRefInfo() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_XRefInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public CMatrix44 m_Mat {
    set {
      Engine2PINVOKE.XRefInfo_m_Mat_set(swigCPtr, CMatrix44.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.XRefInfo_m_Mat_get(swigCPtr);
      CMatrix44 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CMatrix44(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_Engine2__String m_sName {
    set {
      Engine2PINVOKE.XRefInfo_m_sName_set(swigCPtr, SWIGTYPE_p_Engine2__String.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_Engine2__String ret = new SWIGTYPE_p_Engine2__String(Engine2PINVOKE.XRefInfo_m_sName_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_Engine2__String m_sFileName {
    set {
      Engine2PINVOKE.XRefInfo_m_sFileName_set(swigCPtr, SWIGTYPE_p_Engine2__String.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_Engine2__String ret = new SWIGTYPE_p_Engine2__String(Engine2PINVOKE.XRefInfo_m_sFileName_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public XRefInfo() : this(Engine2PINVOKE.new_XRefInfo(), true) {
  }

}