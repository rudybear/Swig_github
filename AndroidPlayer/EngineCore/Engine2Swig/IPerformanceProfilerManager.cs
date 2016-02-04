//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IPerformanceProfilerManager : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public IPerformanceProfilerManager(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(IPerformanceProfilerManager obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IPerformanceProfilerManager() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IPerformanceProfilerManager(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual int StartProfilerInfo(string section, string name) {
    int ret = Engine2PINVOKE.IPerformanceProfilerManager_StartProfilerInfo(swigCPtr, section, name);
    return ret;
  }

  public virtual void EndProfilerInfo(int arg0, double arg1) {
    Engine2PINVOKE.IPerformanceProfilerManager_EndProfilerInfo(swigCPtr, arg0, arg1);
  }

  public virtual void DumpProfilerInfoToLog() {
    Engine2PINVOKE.IPerformanceProfilerManager_DumpProfilerInfoToLog(swigCPtr);
  }

  public virtual void SetProfilerListener(IProfilerListener arg0) {
    Engine2PINVOKE.IPerformanceProfilerManager_SetProfilerListener(swigCPtr, IProfilerListener.getCPtr(arg0));
  }

}
