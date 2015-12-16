//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IIndoorMeshInfo : IMeshInfo {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal IIndoorMeshInfo(global::System.IntPtr cPtr, bool cMemoryOwn) : base(Engine2PINVOKE.IIndoorMeshInfo_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(IIndoorMeshInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IIndoorMeshInfo() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IIndoorMeshInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public virtual int GetNumSubmeshes() {
    int ret = Engine2PINVOKE.IIndoorMeshInfo_GetNumSubmeshes(swigCPtr);
    return ret;
  }

  public virtual string GetSubmeshName(int num) {
    string ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshName(swigCPtr, num);
    return ret;
  }

  public virtual int GetSubmeshFromName(string arg0) {
    int ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshFromName(swigCPtr, arg0);
    return ret;
  }

  public virtual bool GetSubmeshVisibility(int num) {
    bool ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshVisibility(swigCPtr, num);
    return ret;
  }

  public virtual void SetSubmeshVisibility(int num, bool visible) {
    Engine2PINVOKE.IIndoorMeshInfo_SetSubmeshVisibility(swigCPtr, num, visible);
  }

  public virtual void SetSubmeshesVisibility(SWIGTYPE_p_int arrayptr, int count, bool visibility) {
    Engine2PINVOKE.IIndoorMeshInfo_SetSubmeshesVisibility(swigCPtr, SWIGTYPE_p_int.getCPtr(arrayptr), count, visibility);
  }

  public virtual bool RebuildMesh() {
    bool ret = Engine2PINVOKE.IIndoorMeshInfo_RebuildMesh(swigCPtr);
    return ret;
  }

  public virtual void SetActivationDistance(float dist) {
    Engine2PINVOKE.IIndoorMeshInfo_SetActivationDistance(swigCPtr, dist);
  }

  public virtual float GetActivationDistance() {
    float ret = Engine2PINVOKE.IIndoorMeshInfo_GetActivationDistance(swigCPtr);
    return ret;
  }

  public virtual int GetSubmeshVertCount(int num) {
    int ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshVertCount(swigCPtr, num);
    return ret;
  }

  public virtual int GetSubmeshIndCount(int num) {
    int ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshIndCount(swigCPtr, num);
    return ret;
  }

  public virtual bool GetSubmeshPositions(int num, CVec3 arg1) {
    bool ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshPositions(swigCPtr, num, CVec3.getCPtr(arg1));
    return ret;
  }

  public virtual bool GetSubmeshNormals(int num, CVec3 arg1) {
    bool ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshNormals(swigCPtr, num, CVec3.getCPtr(arg1));
    return ret;
  }

  public virtual bool GetSubmeshIndices(int num, SWIGTYPE_p_short arg1) {
    bool ret = Engine2PINVOKE.IIndoorMeshInfo_GetSubmeshIndices(swigCPtr, num, SWIGTYPE_p_short.getCPtr(arg1));
    return ret;
  }

}