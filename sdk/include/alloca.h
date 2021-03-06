/* 
 * Copyright(c) 2004-2012 BORESTE (www.boreste.com). All Rights Reserved.
 *
 * This file is part of the YARD-ICE.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You can receive a copy of the GNU Lesser General Public License from 
 * http://www.gnu.org/
 */

/** 
 * @file alloca.h
 * @brief YARD-ICE libc
 * @author Robinson Mittmann <bobmittmann@gmail.com>
 */ 


#ifndef __ALLOCA_H__
#define __ALLOCA_H__

#define __need_size_t
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

#undef alloca

#ifdef __GNUC__
#define alloca(size) __builtin_alloca(size)
#else
	void * alloca(size_t);
#endif

#ifdef __cplusplus
}
#endif

#endif

