//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class SMemTextureInfo : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal SMemTextureInfo(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(SMemTextureInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~SMemTextureInfo() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_SMemTextureInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public SWIGTYPE_p_uint32 m_iWidth {
    set {
      Engine2PINVOKE.SMemTextureInfo_m_iWidth_set(swigCPtr, SWIGTYPE_p_uint32.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_uint32 ret = new SWIGTYPE_p_uint32(Engine2PINVOKE.SMemTextureInfo_m_iWidth_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_uint32 m_iHeight {
    set {
      Engine2PINVOKE.SMemTextureInfo_m_iHeight_set(swigCPtr, SWIGTYPE_p_uint32.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_uint32 ret = new SWIGTYPE_p_uint32(Engine2PINVOKE.SMemTextureInfo_m_iHeight_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_TEXFORMAT m_Format {
    set {
      Engine2PINVOKE.SMemTextureInfo_m_Format_set(swigCPtr, SWIGTYPE_p_TEXFORMAT.getCPtr(value));
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_TEXFORMAT ret = new SWIGTYPE_p_TEXFORMAT(Engine2PINVOKE.SMemTextureInfo_m_Format_get(swigCPtr), true);
      if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SMemTextureInfo() : this(Engine2PINVOKE.new_SMemTextureInfo(), true) {
  }

}