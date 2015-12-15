////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE IS PROPRIETARY PROPERTY OF Alexey Medvedev, Andrey Honich.
// Copyright (c) 2004-2013
//
// The contents of this file may not be disclosed to third
// parties, copied or duplicated in any form, in whole or in part,
// without the prior written permission of authors.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MultiThread.h"

NaiveJobManager::TaskContainer NaiveJobManager::tasks;
int NaiveJobManager::iThreadsAvailable = 1;
extern int volatile g_TreadsLock;
int volatile g_TreadsLock;

