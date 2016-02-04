//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class CVec4 : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public CVec4(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(CVec4 obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CVec4() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_CVec4(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public CVec4() : this(Engine2PINVOKE.new_CVec4__SWIG_0(), true) {
  }

  public float x {
    set {
      Engine2PINVOKE.CVec4_x_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec4_x_get(swigCPtr);
      return ret;
    } 
  }

  public float y {
    set {
      Engine2PINVOKE.CVec4_y_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec4_y_get(swigCPtr);
      return ret;
    } 
  }

  public float z {
    set {
      Engine2PINVOKE.CVec4_z_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec4_z_get(swigCPtr);
      return ret;
    } 
  }

  public float w {
    set {
      Engine2PINVOKE.CVec4_w_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec4_w_get(swigCPtr);
      return ret;
    } 
  }

  public CVec4(float _x, float _y, float _z, float _w) : this(Engine2PINVOKE.new_CVec4__SWIG_1(_x, _y, _z, _w), true) {
  }

  public CVec4(uint dColor) : this(Engine2PINVOKE.new_CVec4__SWIG_2(dColor), true) {
  }

  public CVec4(float c) : this(Engine2PINVOKE.new_CVec4__SWIG_3(c), true) {
  }

  public CVec4(CVec3 v, float _w) : this(Engine2PINVOKE.new_CVec4__SWIG_4(CVec3.getCPtr(v), _w), true) {
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public CVec4(SWIGTYPE_p_CQuaternion arg0) : this(Engine2PINVOKE.new_CVec4__SWIG_5(SWIGTYPE_p_CQuaternion.getCPtr(arg0)), true) {
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public CVec4 add(CVec4 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_add__SWIG_0(swigCPtr, CVec4.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 sub(CVec4 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_sub__SWIG_0(swigCPtr, CVec4.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 mul(CVec4 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_mul__SWIG_0(swigCPtr, CVec4.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 mul(float f) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_mul__SWIG_1(swigCPtr, f), true);
    return ret;
  }

  public CVec4 div(float f) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_div(swigCPtr, f), true);
    return ret;
  }

  public SWIGTYPE_p_float cast() {
    global::System.IntPtr cPtr = Engine2PINVOKE.CVec4_cast(swigCPtr);
    SWIGTYPE_p_float ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_float(cPtr, false);
    return ret;
  }

  public SWIGTYPE_p_float const_cast() {
    global::System.IntPtr cPtr = Engine2PINVOKE.CVec4_const_cast(swigCPtr);
    SWIGTYPE_p_float ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_float(cPtr, false);
    return ret;
  }

  public CVec4 add_assign(CVec4 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_add_assign(swigCPtr, CVec4.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 sub_assign(CVec4 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_sub_assign(swigCPtr, CVec4.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 mul_assign(float s) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_mul_assign(swigCPtr, s), false);
    return ret;
  }

  public CVec4 div_assign(float s) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_div_assign(swigCPtr, s), false);
    return ret;
  }

  public CVec4 add() {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_add__SWIG_1(swigCPtr), true);
    return ret;
  }

  public CVec4 sub() {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_sub__SWIG_1(swigCPtr), true);
    return ret;
  }

  public bool equal(CVec4 v) {
    bool ret = Engine2PINVOKE.CVec4_equal(swigCPtr, CVec4.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool not_equal(CVec4 v) {
    bool ret = Engine2PINVOKE.CVec4_not_equal(swigCPtr, CVec4.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 mul(CMatrix44 arg0) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_mul__SWIG_2(swigCPtr, CMatrix44.getCPtr(arg0)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 mul(SWIGTYPE_p_CQuaternion arg0) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_mul__SWIG_3(swigCPtr, SWIGTYPE_p_CQuaternion.getCPtr(arg0)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool NotNULL() {
    bool ret = Engine2PINVOKE.CVec4_NotNULL(swigCPtr);
    return ret;
  }

  public float Dot(CVec4 v) {
    float ret = Engine2PINVOKE.CVec4_Dot(swigCPtr, CVec4.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Set(float _x, float _y, float _z, float _w) {
    Engine2PINVOKE.CVec4_Set(swigCPtr, _x, _y, _z, _w);
  }

  public CVec4 Cross(CVec4 v1, CVec4 v2, CVec4 v3) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_Cross(swigCPtr, CVec4.getCPtr(v1), CVec4.getCPtr(v2), CVec4.getCPtr(v3)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public float Length() {
    float ret = Engine2PINVOKE.CVec4_Length(swigCPtr);
    return ret;
  }

  public float LengthSq() {
    float ret = Engine2PINVOKE.CVec4_LengthSq(swigCPtr);
    return ret;
  }

  public CVec4 Lerp(CVec4 v, float t) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_Lerp(swigCPtr, CVec4.getCPtr(v), t), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 NormalizeFast() {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_NormalizeFast(swigCPtr), false);
    return ret;
  }

  public CVec4 Normalize() {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_Normalize(swigCPtr), false);
    return ret;
  }

  public CVec4 GetNormalized() {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_GetNormalized(swigCPtr), true);
    return ret;
  }

  public CVec4 GetNormalizedFast() {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_GetNormalizedFast(swigCPtr), true);
    return ret;
  }

  public CVec4 TransformPoint(CMatrix44 mat) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_TransformPoint(swigCPtr, CMatrix44.getCPtr(mat)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 assign(CVec2 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_assign__SWIG_0(swigCPtr, CVec2.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec4 assign(CVec3 v) {
    CVec4 ret = new CVec4(Engine2PINVOKE.CVec4_assign__SWIG_1(swigCPtr, CVec3.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Validate() {
    Engine2PINVOKE.CVec4_Validate(swigCPtr);
  }

}
