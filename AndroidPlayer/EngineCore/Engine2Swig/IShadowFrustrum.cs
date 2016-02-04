//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IShadowFrustrum : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public IShadowFrustrum(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(IShadowFrustrum obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          throw new global::System.MethodAccessException("C++ destructor does not have public access");
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual int GetShadowMap() {
    int ret = Engine2PINVOKE.IShadowFrustrum_GetShadowMap(swigCPtr);
    return ret;
  }

  public virtual int GetShadowMapSize() {
    int ret = Engine2PINVOKE.IShadowFrustrum_GetShadowMapSize(swigCPtr);
    return ret;
  }

  public virtual void SetViewProjMatrices(CMatrix44 mxView, CMatrix44 mxProj) {
    Engine2PINVOKE.IShadowFrustrum_SetViewProjMatrices(swigCPtr, CMatrix44.getCPtr(mxView), CMatrix44.getCPtr(mxProj));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void SetNearFar(float fNear, float fFar) {
    Engine2PINVOKE.IShadowFrustrum_SetNearFar(swigCPtr, fNear, fFar);
  }

  public virtual void GetNearFar(SWIGTYPE_p_float fNear, SWIGTYPE_p_float fFar) {
    Engine2PINVOKE.IShadowFrustrum_GetNearFar(swigCPtr, SWIGTYPE_p_float.getCPtr(fNear), SWIGTYPE_p_float.getCPtr(fFar));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void SetBiasScale(float fBiasScale) {
    Engine2PINVOKE.IShadowFrustrum_SetBiasScale(swigCPtr, fBiasScale);
  }

  public virtual CMatrix44 GetViewMatrix() {
    CMatrix44 ret = new CMatrix44(Engine2PINVOKE.IShadowFrustrum_GetViewMatrix(swigCPtr), false);
    return ret;
  }

  public virtual CMatrix44 GetProjMatrix() {
    CMatrix44 ret = new CMatrix44(Engine2PINVOKE.IShadowFrustrum_GetProjMatrix(swigCPtr), false);
    return ret;
  }

  public virtual CMatrix44 GetViewProjMatrix() {
    CMatrix44 ret = new CMatrix44(Engine2PINVOKE.IShadowFrustrum_GetViewProjMatrix(swigCPtr), false);
    return ret;
  }

  public virtual ILight GetParent() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IShadowFrustrum_GetParent(swigCPtr);
    ILight ret = (cPtr == global::System.IntPtr.Zero) ? null : new ILight(cPtr, false);
    return ret;
  }

}
