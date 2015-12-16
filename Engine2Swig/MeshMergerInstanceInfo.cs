//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class MeshMergerInstanceInfo : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal MeshMergerInstanceInfo(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(MeshMergerInstanceInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~MeshMergerInstanceInfo() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_MeshMergerInstanceInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public CMatrix44 m_Matrix {
    set {
      Engine2PINVOKE.MeshMergerInstanceInfo_m_Matrix_set(swigCPtr, CMatrix44.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.MeshMergerInstanceInfo_m_Matrix_get(swigCPtr);
      CMatrix44 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CMatrix44(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_uint32 m_iDiffuseColor {
    set {
      Engine2PINVOKE.MeshMergerInstanceInfo_m_iDiffuseColor_set(swigCPtr, SWIGTYPE_p_uint32.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_uint32 ret = new SWIGTYPE_p_uint32(Engine2PINVOKE.MeshMergerInstanceInfo_m_iDiffuseColor_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public MeshMergerInstanceInfo() : this(Engine2PINVOKE.new_MeshMergerInstanceInfo(), true) {
  }

}