//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IWeather : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public IWeather(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(IWeather obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IWeather() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IWeather(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual ISun GetSun() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IWeather_GetSun(swigCPtr);
    ISun ret = (cPtr == global::System.IntPtr.Zero) ? null : new ISun(cPtr, false);
    return ret;
  }

  public virtual IAtmosphere GetAtmosphere() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IWeather_GetAtmosphere(swigCPtr);
    IAtmosphere ret = (cPtr == global::System.IntPtr.Zero) ? null : new IAtmosphere(cPtr, false);
    return ret;
  }

  public virtual IWind GetWind() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IWeather_GetWind(swigCPtr);
    IWind ret = (cPtr == global::System.IntPtr.Zero) ? null : new IWind(cPtr, false);
    return ret;
  }

  public virtual IOcean GetOcean() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IWeather_GetOcean(swigCPtr);
    IOcean ret = (cPtr == global::System.IntPtr.Zero) ? null : new IOcean(cPtr, false);
    return ret;
  }

  public virtual void SetSSAOAmount(float fAmount) {
    Engine2PINVOKE.IWeather_SetSSAOAmount(swigCPtr, fAmount);
  }

  public virtual float GetSSAOAmount() {
    float ret = Engine2PINVOKE.IWeather_GetSSAOAmount(swigCPtr);
    return ret;
  }

}
