//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class CollisionInfo : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal CollisionInfo(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(CollisionInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CollisionInfo() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_CollisionInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public CollisionInfo() : this(Engine2PINVOKE.new_CollisionInfo(), true) {
  }

  public CVec3 m_vecObjectIntersection {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecObjectIntersection_set(swigCPtr, CVec3.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecObjectIntersection_get(swigCPtr);
      CVec3 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CVec3(cPtr, false);
      return ret;
    } 
  }

  public CVec3 m_vecIntersection {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecIntersection_set(swigCPtr, CVec3.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecIntersection_get(swigCPtr);
      CVec3 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CVec3(cPtr, false);
      return ret;
    } 
  }

  public CVec3 m_vecNormal {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecNormal_set(swigCPtr, CVec3.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecNormal_get(swigCPtr);
      CVec3 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CVec3(cPtr, false);
      return ret;
    } 
  }

  public CVec3 m_vecSkinnedIntersection {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecSkinnedIntersection_set(swigCPtr, CVec3.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecSkinnedIntersection_get(swigCPtr);
      CVec3 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CVec3(cPtr, false);
      return ret;
    } 
  }

  public CVec2 m_vecTextureCoordinate {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecTextureCoordinate_set(swigCPtr, CVec2.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecTextureCoordinate_get(swigCPtr);
      CVec2 ret = (cPtr == global::System.IntPtr.Zero) ? null : new CVec2(cPtr, false);
      return ret;
    } 
  }

  public int m_iTextureID {
    set {
      Engine2PINVOKE.CollisionInfo_m_iTextureID_set(swigCPtr, value);
    } 
    get {
      int ret = Engine2PINVOKE.CollisionInfo_m_iTextureID_get(swigCPtr);
      return ret;
    } 
  }

  public int m_iRequestedTextureLayer {
    set {
      Engine2PINVOKE.CollisionInfo_m_iRequestedTextureLayer_set(swigCPtr, value);
    } 
    get {
      int ret = Engine2PINVOKE.CollisionInfo_m_iRequestedTextureLayer_get(swigCPtr);
      return ret;
    } 
  }

  public int m_iAdditional {
    set {
      Engine2PINVOKE.CollisionInfo_m_iAdditional_set(swigCPtr, value);
    } 
    get {
      int ret = Engine2PINVOKE.CollisionInfo_m_iAdditional_get(swigCPtr);
      return ret;
    } 
  }

  public bool m_bUseLOD {
    set {
      Engine2PINVOKE.CollisionInfo_m_bUseLOD_set(swigCPtr, value);
    } 
    get {
      bool ret = Engine2PINVOKE.CollisionInfo_m_bUseLOD_get(swigCPtr);
      return ret;
    } 
  }

  public bool m_bSaveAllCollisions {
    set {
      Engine2PINVOKE.CollisionInfo_m_bSaveAllCollisions_set(swigCPtr, value);
    } 
    get {
      bool ret = Engine2PINVOKE.CollisionInfo_m_bSaveAllCollisions_get(swigCPtr);
      return ret;
    } 
  }

  public bool m_bGetTextureCoordinates {
    set {
      Engine2PINVOKE.CollisionInfo_m_bGetTextureCoordinates_set(swigCPtr, value);
    } 
    get {
      bool ret = Engine2PINVOKE.CollisionInfo_m_bGetTextureCoordinates_get(swigCPtr);
      return ret;
    } 
  }

  public SWIGTYPE_p_Engine2__VectorT_CVec3_t m_vecAllIntersections {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecAllIntersections_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_CVec3_t.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecAllIntersections_get(swigCPtr);
      SWIGTYPE_p_Engine2__VectorT_CVec3_t ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_Engine2__VectorT_CVec3_t(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_Engine2__VectorT_CVec3_t m_vecAllNormals {
    set {
      Engine2PINVOKE.CollisionInfo_m_vecAllNormals_set(swigCPtr, SWIGTYPE_p_Engine2__VectorT_CVec3_t.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CollisionInfo_m_vecAllNormals_get(swigCPtr);
      SWIGTYPE_p_Engine2__VectorT_CVec3_t ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_Engine2__VectorT_CVec3_t(cPtr, false);
      return ret;
    } 
  }

}