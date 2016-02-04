//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.7
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class CXmlElement : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public CXmlElement(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(CXmlElement obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~CXmlElement() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          Engine2PINVOKE.delete_CXmlElement(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public CXmlElement() : this(Engine2PINVOKE.new_CXmlElement(), true) {
  }

  public int Serialize(Engine2String FileName) {
    int ret = Engine2PINVOKE.CXmlElement_Serialize__SWIG_0(swigCPtr, Engine2String.getCPtr(FileName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int SerializeThroughAPI(string szFileName) {
    int ret = Engine2PINVOKE.CXmlElement_SerializeThroughAPI(swigCPtr, szFileName);
    return ret;
  }

  public int Serialize(SWIGTYPE_p_FILE to, int level) {
    int ret = Engine2PINVOKE.CXmlElement_Serialize__SWIG_1(swigCPtr, SWIGTYPE_p_FILE.getCPtr(to), level);
    return ret;
  }

  public int SerializeBuffer(Engine2String buffer, int level) {
    int ret = Engine2PINVOKE.CXmlElement_SerializeBuffer(swigCPtr, Engine2String.getCPtr(buffer), level);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetName(Engine2String pName) {
    Engine2PINVOKE.CXmlElement_SetName(swigCPtr, Engine2String.getCPtr(pName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
  }

  public int LoadFromXml(Engine2String szFileName) {
    int ret = Engine2PINVOKE.CXmlElement_LoadFromXml__SWIG_0(swigCPtr, Engine2String.getCPtr(szFileName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LoadFromXml(string szFileName) {
    int ret = Engine2PINVOKE.CXmlElement_LoadFromXml__SWIG_1(swigCPtr, szFileName);
    return ret;
  }

  public int LoadFromStr(Engine2String szString) {
    int ret = Engine2PINVOKE.CXmlElement_LoadFromStr__SWIG_0(swigCPtr, Engine2String.getCPtr(szString));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int LoadFromStr(string szString, uint strLen) {
    int ret = Engine2PINVOKE.CXmlElement_LoadFromStr__SWIG_1(swigCPtr, szString, strLen);
    return ret;
  }

  public string GetParamValueByName(Engine2String szName) {
    string ret = Engine2PINVOKE.CXmlElement_GetParamValueByName(swigCPtr, Engine2String.getCPtr(szName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public CXmlElement GetElementByName(Engine2String szName) {
    global::System.IntPtr cPtr = Engine2PINVOKE.CXmlElement_GetElementByName(swigCPtr, Engine2String.getCPtr(szName));
    CXmlElement ret = (cPtr == global::System.IntPtr.Zero) ? null : new CXmlElement(cPtr, false);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int Deserialize(Engine2String FileName) {
    int ret = Engine2PINVOKE.CXmlElement_Deserialize__SWIG_0(swigCPtr, Engine2String.getCPtr(FileName));
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int Deserialize(Engine2String buffer, int offset) {
    int ret = Engine2PINVOKE.CXmlElement_Deserialize__SWIG_1(swigCPtr, Engine2String.getCPtr(buffer), offset);
    if (Engine2PINVOKE.SWIGPendingException.Pending) throw Engine2PINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void ClearContents() {
    Engine2PINVOKE.CXmlElement_ClearContents(swigCPtr);
  }

  public CXmlElement Clone() {
    global::System.IntPtr cPtr = Engine2PINVOKE.CXmlElement_Clone(swigCPtr);
    CXmlElement ret = (cPtr == global::System.IntPtr.Zero) ? null : new CXmlElement(cPtr, false);
    return ret;
  }

  public int ProcessXmlNode(SWIGTYPE_p_xml__TiXmlNode pNode, CXmlElement pElement) {
    int ret = Engine2PINVOKE.CXmlElement_ProcessXmlNode(swigCPtr, SWIGTYPE_p_xml__TiXmlNode.getCPtr(pNode), CXmlElement.getCPtr(pElement));
    return ret;
  }

  public void CopyFrom(CXmlElement xml) {
    Engine2PINVOKE.CXmlElement_CopyFrom(swigCPtr, CXmlElement.getCPtr(xml));
  }

  public string GetName() {
    string ret = Engine2PINVOKE.CXmlElement_GetName(swigCPtr);
    return ret;
  }

  public CXmlParams m_Params {
    set {
      Engine2PINVOKE.CXmlElement_m_Params_set(swigCPtr, CXmlParams.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CXmlElement_m_Params_get(swigCPtr);
      CXmlParams ret = (cPtr == global::System.IntPtr.Zero) ? null : new CXmlParams(cPtr, false);
      return ret;
    } 
  }

  public CXmlVector m_Elements {
    set {
      Engine2PINVOKE.CXmlElement_m_Elements_set(swigCPtr, CXmlVector.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CXmlElement_m_Elements_get(swigCPtr);
      CXmlVector ret = (cPtr == global::System.IntPtr.Zero) ? null : new CXmlVector(cPtr, false);
      return ret;
    } 
  }

  public Engine2String m_szName {
    set {
      Engine2PINVOKE.CXmlElement_m_szName_set(swigCPtr, Engine2String.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = Engine2PINVOKE.CXmlElement_m_szName_get(swigCPtr);
      Engine2String ret = (cPtr == global::System.IntPtr.Zero) ? null : new Engine2String(cPtr, false);
      return ret;
    } 
  }

  public int AppendXML(CXmlElement pXmlToAdd) {
    int ret = Engine2PINVOKE.CXmlElement_AppendXML(swigCPtr, CXmlElement.getCPtr(pXmlToAdd));
    return ret;
  }

}
