//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class SCoreStatistics : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal SCoreStatistics(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(SCoreStatistics obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~SCoreStatistics() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_SCoreStatistics(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public SWIGTYPE_p_Engine2__VectorT_ComponentInfo_t m_Components {
    set {
      Engine2PINVOKE.SCoreStatistics_m_Components_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_ComponentInfo_t.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.SCoreStatistics_m_Components_get(swigCPtr);
      SWIGTYPE_p_Engine2__VectorT_ComponentInfo_t ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_Engine2__VectorT_ComponentInfo_t(cPtr, false);
      return ret;
    } 
  }

  public SCoreStatistics() : this(Engine2PINVOKE.new_SCoreStatistics(), true) {
  }

}