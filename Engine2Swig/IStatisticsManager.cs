//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IStatisticsManager : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IStatisticsManager(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(IStatisticsManager obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IStatisticsManager() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IStatisticsManager(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public virtual void AddTexturesReadBytesStats(uint arg0) {
    Engine2PINVOKE.IStatisticsManager_AddTexturesReadBytesStats(swigCPtr, arg0);
  }

  public virtual void AddModelsReadBytesStats(uint arg0) {
    Engine2PINVOKE.IStatisticsManager_AddModelsReadBytesStats(swigCPtr, arg0);
  }

  public virtual uint GetTexturesReadBytesStats() {
    uint ret = Engine2PINVOKE.IStatisticsManager_GetTexturesReadBytesStats(swigCPtr);
    return ret;
  }

  public virtual uint GetModelsReadBytesStats() {
    uint ret = Engine2PINVOKE.IStatisticsManager_GetModelsReadBytesStats(swigCPtr);
    return ret;
  }

  public virtual uint GetTotalReadBytesStats() {
    uint ret = Engine2PINVOKE.IStatisticsManager_GetTotalReadBytesStats(swigCPtr);
    return ret;
  }

  public virtual void DumpToLog() {
    Engine2PINVOKE.IStatisticsManager_DumpToLog(swigCPtr);
  }

  public virtual void DumpToScreen() {
    Engine2PINVOKE.IStatisticsManager_DumpToScreen(swigCPtr);
  }

  public virtual SWIGTYPE_p_IStats CreateStats(SWIGTYPE_p_EStatsType eStats, float fInterval) {
    global::System.IntPtr cPtr = Engine2PINVOKE.IStatisticsManager_CreateStats(swigCPtr, SWIGTYPE_p_EStatsType.getCPtr(eStats), fInterval);
    SWIGTYPE_p_IStats ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_IStats(cPtr, false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}