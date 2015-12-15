////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


enum eGestureType
{
  eSwiping,
  ePinching,
  ePanning,
  eTap_1Finger_1Tap,
  eTap_2Finger_1Tap,
  eTap_3Finger_1Tap,
  eTap_4Finger_1Tap,
  eTap_5Finger_1Tap,
  eTap_1Finger_2Tap,
  eTap_2Finger_2Tap,
  eTap_3Finger_2Tap,
  eTap_4Finger_2Tap,
  eTap_5Finger_2Tap,
  eRotating,
  eLongPressing,
  eNoGesture
};

class IGestureRecognizer;

class IGestureListener
{
public:
  virtual void FireEvent(const IGestureRecognizer * ) = 0;
};

class IGestureRecognizer
{
public:
  virtual eGestureType GetGestureType() const = 0;

  virtual void RegisterGestureListener(IGestureListener *) = 0;
  virtual void UnRegisterGestureListener(IGestureListener *) = 0;

};

// Deferred way to get results
class ISwipingGestureRecognizer : public IGestureRecognizer
{
public:
  virtual bool IsSwipeUp() const = 0;
  virtual bool IsSwipeDown() const = 0;
  virtual bool IsSwipeLeft() const = 0;
  virtual bool IsSwipeRight() const = 0;
  virtual float GetSwipeDistance() const = 0;
};

class IAccelerometerRecognizer
{
public:
  virtual void SetUpdateInterval(float ms) = 0;
  virtual float GetXAxis() const = 0;
  virtual float GetYAxis() const = 0;
  virtual float GetZAxis() const = 0;
};

class IAttitudeRecognizer
{
public:
//  virtual void SetUpdateInterval(float ms) = 0; -- TODO
  virtual float GetYaw() const = 0;
  virtual float GetPitch() const = 0;
  virtual float GetRoll() const = 0;
};

class ITapGestureRecognizer : public IGestureRecognizer
{
public:
  virtual bool IsTap() const = 0;
  virtual int GetXPos() const = 0;
  virtual int GetYPos() const = 0;
};


class IInput
{
public:

  // Gestures
  // Synchronous interface
  virtual IGestureRecognizer * CreateGestureRecognizer(eGestureType) = 0;
  virtual void DeleteGestureRecognizer(eGestureType) = 0;

  // Asynchronous interface
  virtual bool RegisterGestureListener(eGestureType, IGestureListener *) = 0;
  virtual void UnRegisterGestureListener(eGestureType, IGestureListener *) = 0;

  //Accelerometer
  virtual IAccelerometerRecognizer * CreateAccelerometerRecognizer() = 0;
  virtual void DeleteAccelerometerRecognizer() = 0;

  //Attitude
  virtual IAttitudeRecognizer * CreateAttitudeRecognizer() = 0;
  virtual void DeleteAttitudeRecognizer() = 0;

  //Keyboard
  //TODO!

};