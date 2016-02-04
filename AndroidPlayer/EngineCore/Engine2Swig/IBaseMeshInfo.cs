//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class IBaseMeshInfo : IMaterialInfo {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  public IBaseMeshInfo(global::System.IntPtr cPtr, bool cMemoryOwn) : base(Engine2PINVOKE.IBaseMeshInfo_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(IBaseMeshInfo obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~IBaseMeshInfo() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_IBaseMeshInfo(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public virtual int GetNumSubmeshes() {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetNumSubmeshes(swigCPtr);
    return ret;
  }

  public virtual string GetSubmeshName(int num) {
    string ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshName(swigCPtr, num);
    return ret;
  }

  public virtual int GetSubmeshFromName(string arg0) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshFromName(swigCPtr, arg0);
    return ret;
  }

  public virtual bool GetSubmeshVisibility(int num) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshVisibility(swigCPtr, num);
    return ret;
  }

  public virtual bool GetSubmeshIsFatThin(int num) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshIsFatThin(swigCPtr, num);
    return ret;
  }

  public virtual float GetSubmeshFatThinBalance(int num) {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshFatThinBalance(swigCPtr, num);
    return ret;
  }

  public virtual void SetSubmeshFatThinBalance(int num, float balance) {
    Engine2PINVOKE.IBaseMeshInfo_SetSubmeshFatThinBalance(swigCPtr, num, balance);
  }

  public virtual void SetSubmeshVisibility(int num, bool visible) {
    Engine2PINVOKE.IBaseMeshInfo_SetSubmeshVisibility(swigCPtr, num, visible);
  }

  public virtual void SetSubmeshesVisibility(SWIGTYPE_p_int arrayptr, int count, bool visibility) {
    Engine2PINVOKE.IBaseMeshInfo_SetSubmeshesVisibility(swigCPtr, SWIGTYPE_p_int.getCPtr(arrayptr), count, visibility);
  }

  public virtual bool PrebuildMesh(PreloadInfo info) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_PrebuildMesh(swigCPtr, PreloadInfo.getCPtr(info));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool RebuildMesh(bool bAsync) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_RebuildMesh__SWIG_0(swigCPtr, bAsync);
    return ret;
  }

  public virtual bool RebuildMesh() {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_RebuildMesh__SWIG_1(swigCPtr);
    return ret;
  }

  public virtual int GetSubmeshVertCount(int num) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshVertCount(swigCPtr, num);
    return ret;
  }

  public virtual int GetSubmeshIndCount(int num) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshIndCount(swigCPtr, num);
    return ret;
  }

  public virtual bool GetSubmeshPositions(int num, CVec3 arg1) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshPositions(swigCPtr, num, CVec3.getCPtr(arg1));
    return ret;
  }

  public virtual bool GetSubmeshNormals(int num, CVec3 arg1) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshNormals(swigCPtr, num, CVec3.getCPtr(arg1));
    return ret;
  }

  public virtual bool GetSubmeshIndices(int num, SWIGTYPE_p_short arg1) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshIndices(swigCPtr, num, SWIGTYPE_p_short.getCPtr(arg1));
    return ret;
  }

  public virtual bool GetSubmeshMaterialsForTriangles(int num, SWIGTYPE_p_short arg1) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetSubmeshMaterialsForTriangles(swigCPtr, num, SWIGTYPE_p_short.getCPtr(arg1));
    return ret;
  }

  public virtual bool IsSubmeshMaxMaterialUsed(int num, int mat) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_IsSubmeshMaxMaterialUsed(swigCPtr, num, mat);
    return ret;
  }

  public virtual uint GetNumLods() {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetNumLods(swigCPtr);
    return ret;
  }

  public virtual void SetAccessibleLod(int arg0) {
    Engine2PINVOKE.IBaseMeshInfo_SetAccessibleLod(swigCPtr, arg0);
  }

  public virtual float GetLodDistance(int arg0) {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetLodDistance(swigCPtr, arg0);
    return ret;
  }

  public virtual void SetLodDistance(int arg0, float arg1) {
    Engine2PINVOKE.IBaseMeshInfo_SetLodDistance(swigCPtr, arg0, arg1);
  }

  public virtual uint GetVisibleLod() {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetVisibleLod(swigCPtr);
    return ret;
  }

  public virtual void SetLodDistances(int lod, float nearSwitch, float farSwitch) {
    Engine2PINVOKE.IBaseMeshInfo_SetLodDistances(swigCPtr, lod, nearSwitch, farSwitch);
  }

  public virtual void GetLodDistances(int lod, SWIGTYPE_p_float nearSwitch, SWIGTYPE_p_float farSwitch) {
    Engine2PINVOKE.IBaseMeshInfo_GetLodDistances(swigCPtr, lod, SWIGTYPE_p_float.getCPtr(nearSwitch), SWIGTYPE_p_float.getCPtr(farSwitch));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void ForceRenderingLod(int arg0) {
    Engine2PINVOKE.IBaseMeshInfo_ForceRenderingLod(swigCPtr, arg0);
  }

  public virtual bool TestRayIntersectionSubmesh(int num, SWIGTYPE_p_CSegment nRay, CVec3 vecIntersection, CVec3 vecNormal) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_TestRayIntersectionSubmesh(swigCPtr, num, SWIGTYPE_p_CSegment.getCPtr(nRay), CVec3.getCPtr(vecIntersection), CVec3.getCPtr(vecNormal));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual uint GetNumMaterials() {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetNumMaterials(swigCPtr);
    return ret;
  }

  public virtual uint GetVisibleGlobalMaterialNum(uint visibleNum) {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetVisibleGlobalMaterialNum(swigCPtr, visibleNum);
    return ret;
  }

  public virtual uint GetVisibleFromGlobalMaterialNum(uint globalNum) {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetVisibleFromGlobalMaterialNum(swigCPtr, globalNum);
    return ret;
  }

  public virtual uint GetMaxMaterialsCount() {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetMaxMaterialsCount(swigCPtr);
    return ret;
  }

  public virtual SWIGTYPE_p_MaxMeshMaterial GetMaxMaterial(uint num) {
    global::System.IntPtr cPtr = Engine2PINVOKE.IBaseMeshInfo_GetMaxMaterial(swigCPtr, num);
    SWIGTYPE_p_MaxMeshMaterial ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_MaxMeshMaterial(cPtr, false);
    return ret;
  }

  public virtual SWIGTYPE_p_ISkeleton GetSkeleton() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IBaseMeshInfo_GetSkeleton(swigCPtr);
    SWIGTYPE_p_ISkeleton ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_ISkeleton(cPtr, false);
    return ret;
  }

  public virtual SWIGTYPE_p_IBaseSkeleton GetBaseSkeleton() {
    global::System.IntPtr cPtr = Engine2PINVOKE.IBaseMeshInfo_GetBaseSkeleton(swigCPtr);
    SWIGTYPE_p_IBaseSkeleton ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_IBaseSkeleton(cPtr, false);
    return ret;
  }

  public virtual int LoadAnimation(string arg0) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_LoadAnimation(swigCPtr, arg0);
    return ret;
  }

  public virtual int CreateAnimationCopy(string arg0) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_CreateAnimationCopy(swigCPtr, arg0);
    return ret;
  }

  public virtual int GetAnimationSize(string arg0) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetAnimationSize(swigCPtr, arg0);
    return ret;
  }

  public virtual void UnloadAnimations() {
    Engine2PINVOKE.IBaseMeshInfo_UnloadAnimations(swigCPtr);
  }

  public virtual void UnloadAnimation(uint arg0) {
    Engine2PINVOKE.IBaseMeshInfo_UnloadAnimation(swigCPtr, arg0);
  }

  public virtual void StartAnimation(uint id, AnimationParam arg1) {
    Engine2PINVOKE.IBaseMeshInfo_StartAnimation(swigCPtr, id, AnimationParam.getCPtr(arg1));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void StopAnimation(uint id) {
    Engine2PINVOKE.IBaseMeshInfo_StopAnimation(swigCPtr, id);
  }

  public virtual int GetNumAnimations() {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetNumAnimations(swigCPtr);
    return ret;
  }

  public virtual string GetAnimationName(uint arg0) {
    string ret = Engine2PINVOKE.IBaseMeshInfo_GetAnimationName(swigCPtr, arg0);
    return ret;
  }

  public virtual int GetAnimationID(string arg0) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetAnimationID(swigCPtr, arg0);
    return ret;
  }

  public virtual bool GetParams(uint id, AnimationParam arg1) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetParams__SWIG_0(swigCPtr, id, AnimationParam.getCPtr(arg1));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool UpdateParams(uint id, AnimationParam param) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_UpdateParams__SWIG_0(swigCPtr, id, AnimationParam.getCPtr(param));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual float GetStartTime(uint id) {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetStartTime(swigCPtr, id);
    return ret;
  }

  public virtual float GetEndTime(uint id) {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetEndTime(swigCPtr, id);
    return ret;
  }

  public virtual void SetRootBone(int arg0) {
    Engine2PINVOKE.IBaseMeshInfo_SetRootBone(swigCPtr, arg0);
  }

  public virtual uint LoadUVAnimation(string arg0) {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_LoadUVAnimation(swigCPtr, arg0);
    return ret;
  }

  public virtual void UnloadUVAnimation(uint arg0) {
    Engine2PINVOKE.IBaseMeshInfo_UnloadUVAnimation(swigCPtr, arg0);
  }

  public virtual int GetNumUVAnimations() {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetNumUVAnimations(swigCPtr);
    return ret;
  }

  public virtual string GetUVAnimationName(uint arg0) {
    string ret = Engine2PINVOKE.IBaseMeshInfo_GetUVAnimationName(swigCPtr, arg0);
    return ret;
  }

  public virtual int GetUVAnimationID(string arg0) {
    int ret = Engine2PINVOKE.IBaseMeshInfo_GetUVAnimationID(swigCPtr, arg0);
    return ret;
  }

  public virtual void StartUVAnimation(uint id, UVAnimationParam arg1) {
    Engine2PINVOKE.IBaseMeshInfo_StartUVAnimation(swigCPtr, id, UVAnimationParam.getCPtr(arg1));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void StopUVAnimation(uint id) {
    Engine2PINVOKE.IBaseMeshInfo_StopUVAnimation(swigCPtr, id);
  }

  public virtual bool GetParams(uint id, UVAnimationParam arg1) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetParams__SWIG_1(swigCPtr, id, UVAnimationParam.getCPtr(arg1));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool UpdateParams(uint id, UVAnimationParam param) {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_UpdateParams__SWIG_1(swigCPtr, id, UVAnimationParam.getCPtr(param));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual uint GetXRefsCount() {
    uint ret = Engine2PINVOKE.IBaseMeshInfo_GetXRefsCount(swigCPtr);
    return ret;
  }

  public virtual IBaseMeshInfo GetXRef(int arg0) {
    global::System.IntPtr cPtr = Engine2PINVOKE.IBaseMeshInfo_GetXRef(swigCPtr, arg0);
    IBaseMeshInfo ret = (cPtr == global::System.IntPtr.Zero) ? null : new IBaseMeshInfo(cPtr, false);
    return ret;
  }

  public virtual eMeshCreation GetMeshCreation() {
    eMeshCreation ret = (eMeshCreation)Engine2PINVOKE.IBaseMeshInfo_GetMeshCreation(swigCPtr);
    return ret;
  }

  public virtual void SetTransparencyState(bool arg0) {
    Engine2PINVOKE.IBaseMeshInfo_SetTransparencyState(swigCPtr, arg0);
  }

  public virtual bool GetTransparencyState() {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_GetTransparencyState(swigCPtr);
    return ret;
  }

  public virtual void SetTransparency(float arg0) {
    Engine2PINVOKE.IBaseMeshInfo_SetTransparency(swigCPtr, arg0);
  }

  public virtual float GetTransparency() {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetTransparency(swigCPtr);
    return ret;
  }

  public virtual void SetAlphaTest(float f) {
    Engine2PINVOKE.IBaseMeshInfo_SetAlphaTest(swigCPtr, f);
  }

  public virtual float GetAlphaTest() {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetAlphaTest(swigCPtr);
    return ret;
  }

  public virtual void SetLightmapSource(LightmapInfo collisionTexCoordinates, SWIGTYPE_p_TEXNUM lightmapTexture) {
    Engine2PINVOKE.IBaseMeshInfo_SetLightmapSource(swigCPtr, LightmapInfo.getCPtr(collisionTexCoordinates), SWIGTYPE_p_TEXNUM.getCPtr(lightmapTexture));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual void SetImposterScale(float arg0) {
    Engine2PINVOKE.IBaseMeshInfo_SetImposterScale(swigCPtr, arg0);
  }

  public virtual float GetImposterScale() {
    float ret = Engine2PINVOKE.IBaseMeshInfo_GetImposterScale(swigCPtr);
    return ret;
  }

  public virtual CMatrix44 GetRootMatrix() {
    CMatrix44 ret = new CMatrix44(Engine2PINVOKE.IBaseMeshInfo_GetRootMatrix(swigCPtr), true);
    return ret;
  }

  public virtual bool IsLastFrameVisible() {
    bool ret = Engine2PINVOKE.IBaseMeshInfo_IsLastFrameVisible(swigCPtr);
    return ret;
  }

  public virtual void SetInstancingPositions(SWIGTYPE_p_Engine2__VectorT_CVec4_t positions) {
    Engine2PINVOKE.IBaseMeshInfo_SetInstancingPositions(swigCPtr, SWIGTYPE_p_Engine2__VectorT_CVec4_t.getCPtr(positions));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

}
