//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IAtmosphere : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public IAtmosphere(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(IAtmosphere obj) {
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

  public virtual void SetParam(EAtmosphereParams param, float fValue) {
    Engine2PINVOKE.IAtmosphere_SetParam(swigCPtr, (int)param, fValue);
  }

  public virtual float GetParam(EAtmosphereParams param) {
    float ret = Engine2PINVOKE.IAtmosphere_GetParam(swigCPtr, (int)param);
    return ret;
  }

  public virtual CVec3 GetBetaRayleigh() {
    CVec3 ret = new CVec3(Engine2PINVOKE.IAtmosphere_GetBetaRayleigh(swigCPtr), true);
    return ret;
  }

  public virtual CVec3 GetBetaDashRayleigh() {
    CVec3 ret = new CVec3(Engine2PINVOKE.IAtmosphere_GetBetaDashRayleigh(swigCPtr), true);
    return ret;
  }

  public virtual CVec3 GetBetaMie() {
    CVec3 ret = new CVec3(Engine2PINVOKE.IAtmosphere_GetBetaMie(swigCPtr), true);
    return ret;
  }

  public virtual CVec3 GetBetaDashMie() {
    CVec3 ret = new CVec3(Engine2PINVOKE.IAtmosphere_GetBetaDashMie(swigCPtr), true);
    return ret;
  }

}
