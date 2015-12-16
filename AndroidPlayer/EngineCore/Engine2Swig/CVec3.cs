//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class CVec3 : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal CVec3(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(CVec3 obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CVec3() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_CVec3(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public float x {
    set {
      Engine2PINVOKE.CVec3_x_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec3_x_get(swigCPtr);
      return ret;
    } 
  }

  public float y {
    set {
      Engine2PINVOKE.CVec3_y_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec3_y_get(swigCPtr);
      return ret;
    } 
  }

  public float z {
    set {
      Engine2PINVOKE.CVec3_z_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec3_z_get(swigCPtr);
      return ret;
    } 
  }

  public CVec3(SWIGTYPE_p_CIdentity arg0) : this(Engine2PINVOKE.new_CVec3__SWIG_0(SWIGTYPE_p_CIdentity.getCPtr(arg0)), true) {
  }

  public CVec3(float _x, float _y, float _z) : this(Engine2PINVOKE.new_CVec3__SWIG_1(_x, _y, _z), true) {
  }

  public CVec3() : this(Engine2PINVOKE.new_CVec3__SWIG_2(), true) {
  }

  public CVec3(SWIGTYPE_p_CQuaternion q) : this(Engine2PINVOKE.new_CVec3__SWIG_3(SWIGTYPE_p_CQuaternion.getCPtr(q)), true) {
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public CVec3(CMatrix44 mat) : this(Engine2PINVOKE.new_CVec3__SWIG_4(CMatrix44.getCPtr(mat)), true) {
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public void Set(float _x, float _y, float _z) {
    Engine2PINVOKE.CVec3_Set(swigCPtr, _x, _y, _z);
  }

  public CVec3 assign(CVec3 rhv) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_assign__SWIG_0(swigCPtr, CVec3.getCPtr(rhv)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 add_assign(CVec3 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_add_assign(swigCPtr, CVec3.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 sub_assign(CVec3 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_sub_assign(swigCPtr, CVec3.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 mul_assign(float s) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_mul_assign(swigCPtr, s), false);
    return ret;
  }

  public CVec3 div_assign(float s) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_div_assign(swigCPtr, s), false);
    return ret;
  }

  public bool equal(CVec3 v) {
    bool ret = Engine2PINVOKE.CVec3_equal(swigCPtr, CVec3.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool not_equal(CVec3 v) {
    bool ret = Engine2PINVOKE.CVec3_not_equal(swigCPtr, CVec3.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 assign(CVec4 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_assign__SWIG_1(swigCPtr, CVec4.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 assign(CVec2 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_assign__SWIG_2(swigCPtr, CVec2.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 sub() {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_sub__SWIG_0(swigCPtr), true);
    return ret;
  }

  public CVec3 add(CVec3 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_add(swigCPtr, CVec3.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 sub(CVec3 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_sub__SWIG_1(swigCPtr, CVec3.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 mul(float f) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_mul__SWIG_0(swigCPtr, f), true);
    return ret;
  }

  public CVec3 div(float f) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_div__SWIG_0(swigCPtr, f), true);
    return ret;
  }

  public CVec3 div(CVec3 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_div__SWIG_1(swigCPtr, CVec3.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 mul(CVec3 v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_mul__SWIG_1(swigCPtr, CVec3.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 mul(CMatrix44 mat) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_mul__SWIG_2(swigCPtr, CMatrix44.getCPtr(mat)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public float LengthSq() {
    float ret = Engine2PINVOKE.CVec3_LengthSq(swigCPtr);
    return ret;
  }

  public float Length() {
    float ret = Engine2PINVOKE.CVec3_Length(swigCPtr);
    return ret;
  }

  public float Dot(CVec3 v) {
    float ret = Engine2PINVOKE.CVec3_Dot(swigCPtr, CVec3.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public SWIGTYPE_p_float cast() {
    global::System.IntPtr cPtr = Engine2PINVOKE.CVec3_cast(swigCPtr);
    SWIGTYPE_p_float ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_float(cPtr, false);
    return ret;
  }

  public SWIGTYPE_p_float const_cast() {
    global::System.IntPtr cPtr = Engine2PINVOKE.CVec3_const_cast(swigCPtr);
    SWIGTYPE_p_float ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_float(cPtr, false);
    return ret;
  }

  public CVec3 Cross(CVec3 v1) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_Cross(swigCPtr, CVec3.getCPtr(v1)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 Lerp(CVec3 v, float t) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_Lerp(swigCPtr, CVec3.getCPtr(v), t), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 TransformNormal(CMatrix44 mat) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_TransformNormal(swigCPtr, CMatrix44.getCPtr(mat)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 TransformPoint(CMatrix44 mat) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_TransformPoint(swigCPtr, CMatrix44.getCPtr(mat)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec3 SetScale(float v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_SetScale(swigCPtr, v), false);
    return ret;
  }

  public void CheckMax(CVec3 other) {
    Engine2PINVOKE.CVec3_CheckMax(swigCPtr, CVec3.getCPtr(other));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public void CheckMin(CVec3 other) {
    Engine2PINVOKE.CVec3_CheckMin(swigCPtr, CVec3.getCPtr(other));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public CVec3 Scale(float v) {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_Scale(swigCPtr, v), true);
    return ret;
  }

  public bool NotNULL() {
    bool ret = Engine2PINVOKE.CVec3_NotNULL(swigCPtr);
    return ret;
  }

  public CVec3 NormalizeFast() {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_NormalizeFast(swigCPtr), false);
    return ret;
  }

  public CVec3 Normalize() {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_Normalize(swigCPtr), false);
    return ret;
  }

  public CVec3 GetNormalized() {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_GetNormalized(swigCPtr), true);
    return ret;
  }

  public CVec3 GetNormalizedFast() {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_GetNormalizedFast(swigCPtr), true);
    return ret;
  }

  public CVec3 GetRotation() {
    CVec3 ret = new CVec3(Engine2PINVOKE.CVec3_GetRotation(swigCPtr), true);
    return ret;
  }

  public float GetDistance(CVec3 v) {
    float ret = Engine2PINVOKE.CVec3_GetDistance(swigCPtr, CVec3.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public float GetDistanceSq(CVec3 v) {
    float ret = Engine2PINVOKE.CVec3_GetDistanceSq(swigCPtr, CVec3.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetLength(float s) {
    Engine2PINVOKE.CVec3_SetLength(swigCPtr, s);
  }

  public void Validate() {
    Engine2PINVOKE.CVec3_Validate(swigCPtr);
  }

}