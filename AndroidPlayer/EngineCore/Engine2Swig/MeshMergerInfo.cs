//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class MeshMergerInfo : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal MeshMergerInfo(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(MeshMergerInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~MeshMergerInfo() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_MeshMergerInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public MeshMergerInfo() : this(Engine2PINVOKE.new_MeshMergerInfo(), true) {
  }

  public SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t m_vSourceToMerge {
    set {
      Engine2PINVOKE.MeshMergerInfo_m_vSourceToMerge_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.MeshMergerInfo_m_vSourceToMerge_get(swigCPtr);
      SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t m_vResultMeshes {
    set {
      Engine2PINVOKE.MeshMergerInfo_m_vResultMeshes_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.MeshMergerInfo_m_vResultMeshes_get(swigCPtr);
      SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_Engine2__VectorT_IMeshInfo_p_t(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_Engine2__VectorT_size_t_t m_vNotProcessedMeshes {
    set {
      Engine2PINVOKE.MeshMergerInfo_m_vNotProcessedMeshes_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_size_t_t.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_Engine2__VectorT_size_t_t ret = new SWIGTYPE_p_Engine2__VectorT_size_t_t(Engine2PINVOKE.MeshMergerInfo_m_vNotProcessedMeshes_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_uint32 m_Flags {
    set {
      Engine2PINVOKE.MeshMergerInfo_m_Flags_set(swigCPtr, SWIGTYPE_p_uint32.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_uint32 ret = new SWIGTYPE_p_uint32(Engine2PINVOKE.MeshMergerInfo_m_Flags_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

}
