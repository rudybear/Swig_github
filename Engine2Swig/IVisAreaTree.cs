//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IVisAreaTree : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IVisAreaTree(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(IVisAreaTree obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IVisAreaTree() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IVisAreaTree(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual void RegisterObject(IMeshInfo arg0) {
    Engine2PINVOKE.IVisAreaTree_RegisterObject(swigCPtr, IMeshInfo.getCPtr(arg0));
  }

  public virtual void UnregisterObject(IMeshInfo arg0) {
    Engine2PINVOKE.IVisAreaTree_UnregisterObject(swigCPtr, IMeshInfo.getCPtr(arg0));
  }

  public virtual void MoveObject(IMeshInfo arg0) {
    Engine2PINVOKE.IVisAreaTree_MoveObject(swigCPtr, IMeshInfo.getCPtr(arg0));
  }

  public virtual void RegisterStaticObject(IMeshInfo arg0) {
    Engine2PINVOKE.IVisAreaTree_RegisterStaticObject(swigCPtr, IMeshInfo.getCPtr(arg0));
  }

  public virtual void UnregisterStaticObject(IMeshInfo arg0) {
    Engine2PINVOKE.IVisAreaTree_UnregisterStaticObject(swigCPtr, IMeshInfo.getCPtr(arg0));
  }

  public virtual void RegisterLight(SWIGTYPE_p_CLight arg0) {
    Engine2PINVOKE.IVisAreaTree_RegisterLight(swigCPtr, SWIGTYPE_p_CLight.getCPtr(arg0));
  }

  public virtual void UnregisterLight(SWIGTYPE_p_CLight arg0) {
    Engine2PINVOKE.IVisAreaTree_UnregisterLight(swigCPtr, SWIGTYPE_p_CLight.getCPtr(arg0));
  }

  public virtual void MoveLight(SWIGTYPE_p_CLight arg0) {
    Engine2PINVOKE.IVisAreaTree_MoveLight(swigCPtr, SWIGTYPE_p_CLight.getCPtr(arg0));
  }

  public virtual void SetAABB(SWIGTYPE_p_CAABBox box) {
    Engine2PINVOKE.IVisAreaTree_SetAABB(swigCPtr, SWIGTYPE_p_CAABBox.getCPtr(box));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual SWIGTYPE_p_CAABBox GetAABB() {
    SWIGTYPE_p_CAABBox ret = new SWIGTYPE_p_CAABBox(Engine2PINVOKE.IVisAreaTree_GetAABB(swigCPtr), false);
    return ret;
  }

  public virtual void SetPartialLimit(float arg0) {
    Engine2PINVOKE.IVisAreaTree_SetPartialLimit(swigCPtr, arg0);
  }

  public virtual void Draw(SWIGTYPE_p_eRenderType type, bool bImmediate, SWIGTYPE_p_RenderStatistics stats) {
    Engine2PINVOKE.IVisAreaTree_Draw(swigCPtr, SWIGTYPE_p_eRenderType.getCPtr(type), bImmediate, SWIGTYPE_p_RenderStatistics.getCPtr(stats));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void SetNewFrame() {
    Engine2PINVOKE.IVisAreaTree_SetNewFrame(swigCPtr);
  }

  public virtual void DecideVisibility() {
    Engine2PINVOKE.IVisAreaTree_DecideVisibility(swigCPtr);
  }

  public virtual void AddToDeleteList(SWIGTYPE_p_void arg0) {
    Engine2PINVOKE.IVisAreaTree_AddToDeleteList(swigCPtr, SWIGTYPE_p_void.getCPtr(arg0));
  }

  public virtual void RemoveFromDeleteList(SWIGTYPE_p_void arg0) {
    Engine2PINVOKE.IVisAreaTree_RemoveFromDeleteList(swigCPtr, SWIGTYPE_p_void.getCPtr(arg0));
  }

}
