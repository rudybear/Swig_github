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

  public MeshMergerInstanceInfo(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(MeshMergerInstanceInfo obj) {
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

  public uint m_iDiffuseColor {
    set {
      Engine2PINVOKE.MeshMergerInstanceInfo_m_iDiffuseColor_set(swigCPtr, value);
    } 
    get {
      uint ret = Engine2PINVOKE.MeshMergerInstanceInfo_m_iDiffuseColor_get(swigCPtr);
      return ret;
    } 
  }

  public MeshMergerInstanceInfo() : this(Engine2PINVOKE.new_MeshMergerInstanceInfo(), true) {
  }

}
