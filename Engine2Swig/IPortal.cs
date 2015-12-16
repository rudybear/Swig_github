//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IPortal : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IPortal(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(IPortal obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IPortal() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IPortal(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual void AddPoint(CVec3 point) {
    Engine2PINVOKE.IPortal_AddPoint(swigCPtr, CVec3.getCPtr(point));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual bool BuildFrustum(SWIGTYPE_p_CFrustum frustum, CVec3 eye) {
    bool ret = Engine2PINVOKE.IPortal_BuildFrustum(swigCPtr, SWIGTYPE_p_CFrustum.getCPtr(frustum), CVec3.getCPtr(eye));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool BuildCameraFrustum() {
    bool ret = Engine2PINVOKE.IPortal_BuildCameraFrustum(swigCPtr);
    return ret;
  }

  public virtual int IsObjectVisible(SWIGTYPE_p_CAABBox box) {
    int ret = Engine2PINVOKE.IPortal_IsObjectVisible__SWIG_0(swigCPtr, SWIGTYPE_p_CAABBox.getCPtr(box));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual int IsObjectVisible(SWIGTYPE_p_CSphere sphere) {
    int ret = Engine2PINVOKE.IPortal_IsObjectVisible__SWIG_1(swigCPtr, SWIGTYPE_p_CSphere.getCPtr(sphere));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual SWIGTYPE_p_CFrustum GetFrustum() {
    SWIGTYPE_p_CFrustum ret = new SWIGTYPE_p_CFrustum(Engine2PINVOKE.IPortal_GetFrustum(swigCPtr), false);
    return ret;
  }

  public virtual int GetVisArea1() {
    int ret = Engine2PINVOKE.IPortal_GetVisArea1(swigCPtr);
    return ret;
  }

  public virtual int GetVisArea2() {
    int ret = Engine2PINVOKE.IPortal_GetVisArea2(swigCPtr);
    return ret;
  }

}