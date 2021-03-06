//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class CVec2 : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public CVec2(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(CVec2 obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CVec2() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_CVec2(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public float x {
    set {
      Engine2PINVOKE.CVec2_x_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec2_x_get(swigCPtr);
      return ret;
    } 
  }

  public float y {
    set {
      Engine2PINVOKE.CVec2_y_set(swigCPtr, value);
    } 
    get {
      float ret = Engine2PINVOKE.CVec2_y_get(swigCPtr);
      return ret;
    } 
  }

  public CVec2() : this(Engine2PINVOKE.new_CVec2__SWIG_0(), true) {
  }

  public CVec2(int arg0) : this(Engine2PINVOKE.new_CVec2__SWIG_1(arg0), true) {
  }

  public CVec2(float _x, float _y) : this(Engine2PINVOKE.new_CVec2__SWIG_2(_x, _y), true) {
  }

  public CVec2 add_assign(CVec2 v) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_add_assign(swigCPtr, CVec2.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 sub_assign(CVec2 v) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_sub_assign(swigCPtr, CVec2.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 mul_assign(float s) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_mul_assign(swigCPtr, s), false);
    return ret;
  }

  public CVec2 div_assign(float s) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_div_assign(swigCPtr, s), false);
    return ret;
  }

  public bool equal(CVec2 v) {
    bool ret = Engine2PINVOKE.CVec2_equal(swigCPtr, CVec2.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool not_equal(CVec2 v) {
    bool ret = Engine2PINVOKE.CVec2_not_equal(swigCPtr, CVec2.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 add(CVec2 v) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_add(swigCPtr, CVec2.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 sub(CVec2 v) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_sub__SWIG_0(swigCPtr, CVec2.getCPtr(v)), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 mul(float f) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_mul(swigCPtr, f), true);
    return ret;
  }

  public CVec2 div(float f) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_div(swigCPtr, f), true);
    return ret;
  }

  public bool NotNULL() {
    bool ret = Engine2PINVOKE.CVec2_NotNULL(swigCPtr);
    return ret;
  }

  public float Dot(CVec2 v) {
    float ret = Engine2PINVOKE.CVec2_Dot(swigCPtr, CVec2.getCPtr(v));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public float Length() {
    float ret = Engine2PINVOKE.CVec2_Length(swigCPtr);
    return ret;
  }

  public float LengthSq() {
    float ret = Engine2PINVOKE.CVec2_LengthSq(swigCPtr);
    return ret;
  }

  public CVec2 Lerp(CVec2 v, float t) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_Lerp(swigCPtr, CVec2.getCPtr(v), t), true);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 Normalize() {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_Normalize(swigCPtr), false);
    return ret;
  }

  public CVec2 NormalizeFast() {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_NormalizeFast(swigCPtr), false);
    return ret;
  }

  public CVec2 GetNormalized() {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_GetNormalized(swigCPtr), true);
    return ret;
  }

  public CVec2 GetNormalizedFast() {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_GetNormalizedFast(swigCPtr), true);
    return ret;
  }

  public CVec2 sub() {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_sub__SWIG_1(swigCPtr), true);
    return ret;
  }

  public void Validate() {
    Engine2PINVOKE.CVec2_Validate(swigCPtr);
  }

  public CVec2 assign(CVec4 v) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_assign__SWIG_0(swigCPtr, CVec4.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CVec2 assign(CVec3 v) {
    CVec2 ret = new CVec2(Engine2PINVOKE.CVec2_assign__SWIG_1(swigCPtr, CVec3.getCPtr(v)), false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}
