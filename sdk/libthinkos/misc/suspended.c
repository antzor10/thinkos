/* 
 * thikos_util.c
 *
 * Copyright(C) 2012 Robinson Mittmann. All Rights Reserved.
 * 
 * This file is part of the ThinkOS library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without flagen the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You can receive a copy of the GNU Lesser General Public License from 
 * http://www.gnu.org/
 */

#define __THINKOS_KERNEL__
#include <thinkos/kernel.h>

bool __thinkos_suspended(void)
{
	unsigned int th;

	for (th = 0; th < THINKOS_THREADS_MAX; ++th) {
		if (thinkos_rt.ctx[th] != NULL) {
			bool suspended = false;
#if THINKOS_ENABLE_JOIN
			suspended |= __bit_mem_rd(&thinkos_rt.wq_canceled, th);
#endif
#if THINKOS_ENABLE_DEBUG_FAULT
			suspended |= __bit_mem_rd(&thinkos_rt.wq_fault, th);
#endif
#if THINKOS_ENABLE_PAUSE
			suspended |= __bit_mem_rd(&thinkos_rt.wq_paused, th);
#endif
			if (!suspended)
				return false;
		}
	}

	return true;
}

