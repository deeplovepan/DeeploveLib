// debug.h
// lib
// debug

/*
 *  debug.h
 *  DeeploveLib
 *
 *  Created by System Administrator on 8/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
	#define DbgMsg(x...) printf(x)
#else
	#define DbgMsg(x...)
#endif

#endif