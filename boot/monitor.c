/* 
 * File:	 usb-cdc.c
 * Author:   Robinson Mittmann (bobmittmann@gmail.com)
 * Target:
 * Comment:
 * Copyright(C) 2011 Bob Mittmann. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifdef CONFIG_H
#include "config.h"
#endif

#include <sys/stm32f.h>
#include <arch/cortex-m3.h>
#include <sys/param.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define __THINKOS_DBGMON__
#include <thinkos/dbgmon.h>
#define __THINKOS_BOOTLDR__
#include <thinkos/bootldr.h>
#include <thinkos.h>
#include <sys/dcclog.h>

#ifndef MONITOR_CONFIGURE_ENABLE
#define MONITOR_CONFIGURE_ENABLE   1
#endif

#ifndef MONITOR_DUMPMEM_ENABLE
#define MONITOR_DUMPMEM_ENABLE     1
#endif

#ifndef MONITOR_UPGRADE_ENABLE
#define MONITOR_UPGRADE_ENABLE     1
#endif

#ifndef MONITOR_STACKUSAGE_ENABLE
#define MONITOR_STACKUSAGE_ENABLE  1
#endif

#ifndef MONITOR_THREADINFO_ENABLE
#define MONITOR_THREADINFO_ENABLE  1
#endif

#ifndef MONITOR_APPWIPE_ENABLE
#define MONITOR_APPWIPE_ENABLE     1
#endif

#ifndef MONITOR_APPTERM_ENABLE
#define MONITOR_APPTERM_ENABLE     1
#endif

#ifndef MONITOR_APPRESTART_ENABLE
#define MONITOR_APPRESTART_ENABLE  1
#endif

#ifndef MONITOR_SELFTEST_ENABLE
#define MONITOR_SELFTEST_ENABLE    1
#endif

#ifndef MONITOR_FAULT_ENABLE
#define MONITOR_FAULT_ENABLE       THINKOS_ENABLE_EXCEPTIONS
#endif

#ifndef BOOT_ENABLE_GDB
#define BOOT_ENABLE_GDB 0
#endif

#if (BOOT_ENABLE_GDB)
#include <gdb.h>
#endif

/* ASCII Keyboard codes */

#define _NULL_ 0x00 /* Null (Ctrl+@) */
#define CTRL_A 0x01 /* SOH */
#define CTRL_B 0x02 /* STX */
#define CTRL_C 0x03 /* ETX */
#define CTRL_D 0x04 /* EOT */
#define CTRL_E 0x05 /* ENQ */
#define CTRL_F 0x06 /* ACK */
#define CTRL_G 0x07 /* BEL */
#define CTRL_H 0x08 /* BS */
#define CTRL_I 0x09 /* TAB */
#define CTRL_J 0x0a /* LF */
#define CTRL_K 0x0b /* VT */
#define CTRL_L 0x0c /* FF */
#define CTRL_M 0x0d /* CR */
#define CTRL_N 0x0e /* SO */
#define CTRL_O 0x0f /* SI */
#define CTRL_P 0x10 /* DLE */
#define CTRL_Q 0x11 /* DC1 */
#define CTRL_R 0x12 /* DC2 */
#define CTRL_S 0x13 /* DC3 */
#define CTRL_T 0x14 /* DC4 */
#define CTRL_U 0x15 /* NAK */
#define CTRL_V 0x16 /* SYN */
#define CTRL_W 0x17 /* ETB */
#define CTRL_X 0x18 /* CAN */
#define CTRL_Y 0x19 /* EM */
#define CTRL_Z 0x1a /* SUB */
#define _ESC_  0x1b /* ESC (Ctrl+[) */
#define _FS_   0x1c /* FS  (Ctrl+\) */
#define _GS_   0x1d /* GS  (Ctrl+]) */
#define _RS_   0x1e /* RS  (Ctrl+^) */
#define _US_   0x1f /* US  (Ctrl+_) */

extern int __heap_end;
const void * heap_end = &__heap_end; 
extern int __heap_base;
const void * heap_base = &__heap_base; 

struct monitor {
	struct dmon_comm * comm;
#if (MONITOR_THREADINFO_ENABLE)
	#define MONITOR_STARTUP_MAGIC -111
	int8_t thread_id;
#endif
#if (MONITOR_DUMPMEM_ENABLE)
	struct {
		uint32_t addr;
		unsigned int size;
	} memdump;
#endif
};

static const char monitor_menu[] = 
#if (MONITOR_APPTERM_ENABLE)
" Ctrl+C - Stop app\r\n"
#endif
#if (MONITOR_SELFTEST_ENABLE)
" Ctrl+E - Run selftest\r\n"
#endif
#if (MONITOR_CONFIGURE_ENABLE)
" Ctrl+K - Configure Board\r\n"
#endif
#if (MONITOR_UPGRADE_ENABLE)
" Ctrl+L - Upload ThinkOS\r\n"
#endif
#if (MONITOR_THREADINFO_ENABLE)
" Ctrl+N - Select Next Thread\r\n"
" Ctrl+O - ThinkOS info\r\n"
" Ctrl+P - Pause all threads\r\n"
" Ctrl+Q - Restart monitor\r\n"
" Ctrl+R - Resume all threads\r\n"
#endif
#if (MONITOR_DUMPMEM_ENABLE)
" Ctrl+S - Show memory\r\n"
#endif
#if (MONITOR_THREADINFO_ENABLE)
" Ctrl+T - Thread info\r\n"
#endif
#if (MONITOR_STACKUSAGE_ENABLE)
" Ctrl+U - Stack usage info\r\n"
#endif
" Ctrl+V - Help\r\n"
#if (MONITOR_APPWIPE_ENABLE)
" Ctrl+W - Wipe application\r\n"
#endif
#if (THINKOS_ENABLE_EXCEPTIONS)
" Ctrl+X - Exception info\r\n"
#endif
" Ctrl+Y - YMODEM app upload\r\n"
#if (MONITOR_APPRESTART_ENABLE)
" Ctrl+Z - Restart app\r\n"
#endif
;

static const char __hr__[] = 
"--------------------------------------------------------------\r\n";

static void monitor_show_help(struct dmon_comm * comm)
{
	dmon_comm_send(comm, __hr__, sizeof(__hr__) - 1);
	dmprintf(comm, "ThinkOS-%d.%d.%d (%s):\r\n", 
			 this_board.sw_ver.major,
			 this_board.sw_ver.minor,
			 this_board.sw_ver.build,
			 this_board.name);
	dmon_comm_send(comm, monitor_menu, sizeof(monitor_menu) - 1);
	dmon_comm_send(comm, __hr__, sizeof(__hr__) - 1);
}

#if (THINKOS_ENABLE_EXCEPTIONS)
static void monitor_print_fault(struct dmon_comm * comm)
{
	struct thinkos_except * xcpt = &thinkos_except_buf;

	if (xcpt->type == 0) {
		dmprintf(comm, "No fault!");
		return;
	}

	dmon_print_exception(comm, xcpt);
}

static void monitor_on_fault(struct dmon_comm * comm)
{
	struct thinkos_except * xcpt = &thinkos_except_buf;

	DCC_LOG(LOG_TRACE, "dmon_wait_idle()...");

	if (dbgmon_wait_idle() < 0) {
		DCC_LOG(LOG_WARNING, "dmon_wait_idle() failed!");
	}

	DCC_LOG(LOG_TRACE, "<<IDLE>>");

	if (dmon_comm_isconnected(comm)) {
		DCC_LOG(LOG_TRACE, "comm is connected!");
		dmprintf(comm, __hr__);
		dmon_print_exception(comm, xcpt);
		dmprintf(comm, __hr__);
	} else {
		DCC_LOG(LOG_TRACE, "comm NOT connected!");
	}
}
#endif

#if (MONITOR_THREADINFO_ENABLE)
static void monitor_pause_all(struct dmon_comm * comm)
{
	dmputs("\r\nPausing all threads...\r\n", comm);
	DCC_LOG(LOG_WARNING, "__thinkos_pause_all()");
	__thinkos_pause_all();
	if (dbgmon_wait_idle() < 0) {
		DCC_LOG(LOG_WARNING, "dmon_wait_idle() failed!");
	}
}

static void monitor_resume_all(struct dmon_comm * comm)
{
	dmputs("\r\nResuming all threads...\r\n", comm);
	__thinkos_resume_all();
	dmputs("Restarting...\r\n", comm);
}
#endif

static void monitor_exec(struct dmon_comm * comm, unsigned int addr)
{
	if (dmon_app_exec(addr, false) < 0) {
		dmputs("\r\n#ERROR: Invalid app!\r\n", comm);
		return;
	}
}

static void monitor_ymodem_recv(struct dmon_comm * comm, 
								uint32_t addr, unsigned int size)
{
	dmputs("\r\nYMODEM receive (^X to cancel) ... ", comm);
	dbgmon_soft_reset();
	if (dmon_ymodem_flash(comm, addr, size) < 0) {
		dmputs("\r\n#ERROR: YMODEM failed!\r\n", comm); 
		return;
	}	

	monitor_exec(comm, addr);
}

#if (MONITOR_APPWIPE_ENABLE)
static void monitor_app_erase(struct dmon_comm * comm, 
							  uint32_t addr, unsigned int size)
{
	dmputs("\r\nErasing application block ... ", comm);
	dbgmon_soft_reset();
	if (dmon_app_erase(comm, addr, size))
		dmputs("done.\r\n", comm);
	else	
		dmputs("failed!\r\n", comm);
}
#endif

#if (MONITOR_DUMPMEM_ENABLE)
int long2hex_le(char * s, unsigned long val);
int char2hex(char * s, int c);

void monitor_dump_mem(struct dmon_comm * comm, 
					  uint32_t addr, unsigned int size)
{
	char buf[14 + 16 * 3];
	unsigned int rem = size;
	uint8_t * cmp = (uint8_t *)-1;
	bool eq = false;

	while (rem) {
		int n = rem < 16 ? rem : 16;
		uint8_t * src = (uint8_t *)addr;
		char * cp = buf;
		unsigned int i;
	
		if (cmp != (uint8_t *)-1) {
			for (i = 0; i < n; ++i) {
				if (src[i] != cmp[i]) {
					eq = false;
					goto dump_line;
				}
			}

			if (!eq) {
				dmon_comm_send(comm, " ...\r\n", 6);
				eq = true;
			}
		} else {	

dump_line:
			cp += long2hex_le(cp, addr);
			*cp++ = ':';

			for (i = 0; i < n; ++i) {
				*cp++ = ' ';
				cp += char2hex(cp, src[i]);
			}

			*cp++ = '\r';
			*cp++ = '\n';

			dmon_comm_send(comm, buf, cp - buf);
		}

		addr += n;
		rem -= n;
		cmp = src;
	}
}

void monitor_show_mem(struct monitor * mon)
{
	uint32_t addr = mon->memdump.addr;
	unsigned int size = mon->memdump.size;

	dmprintf(mon->comm, "Addr (0x%08x): ", addr);
	dmscanf(mon->comm, "%x", &addr);
	dmprintf(mon->comm, "Size (%d): ", size);
	dmscanf(mon->comm, "%u", &size);

	monitor_dump_mem(mon->comm, addr, size);
	mon->memdump.addr = addr;
	mon->memdump.size = size;
}

#endif

void monitor_task(struct dmon_comm *);

#if (MONITOR_SELFTEST_ENABLE)
void __attribute__((naked)) selftest_bootstrap(struct dmon_comm * comm) 
{
	if (this_board.selftest)
		this_board.selftest(comm);
	dbgmon_exec(monitor_task);
}
#endif

#if (BOOT_ENABLE_GDB)
void __attribute__((naked)) gdb_bootstrap(struct dmon_comm * comm) 
{
	DCC_LOG1(LOG_TRACE, "sp=0x%08x", cm3_sp_get());
	gdb_task(comm);
	dbgmon_exec(monitor_task);
}
#endif

int monitor_process_input(struct monitor * mon, char * buf, int len)
{
	struct dmon_comm * comm = mon->comm;
	int i;
	int j;
	int c;

	for (i = 0; i < len; ++i) {
		c = buf[i];
		switch (c) {
#if (BOOT_ENABLE_GDB)
		case '+':
			dbgmon_exec(gdb_bootstrap);
			break;
#endif
#if (MONITOR_APPTERM_ENABLE)
		case CTRL_C:
			dmputs("^C\r\n", comm);
			dbgmon_soft_reset();
			break;
#endif
#if (MONITOR_SELFTEST_ENABLE)
		case CTRL_E:
			dmputs("^E\r\n", comm);
			dbgmon_soft_reset();
			dbgmon_exec(selftest_bootstrap);
			break;
#endif
#if (MONITOR_CONFIGURE_ENABLE)
		case CTRL_K:
			dmputs("^K\r\n", comm);
			dbgmon_soft_reset();
			this_board.configure(comm);
			break;
#endif
#if (MONITOR_UPGRADE_ENABLE)
		case CTRL_L:
			dbgmon_soft_reset();
			dmputs("^L\r\nConfirm (yes/no)? ", comm);
			dmscanf(comm, "yes%n", &i);
			if (i == 3) {
				this_board.upgrade(comm);
				dmputs("Failed !!!\r\n", comm);
			}
			break;
#endif
#if (MONITOR_THREADINFO_ENABLE)
		case CTRL_N:
			mon->thread_id = __thinkos_thread_getnext(mon->thread_id);
			if (mon->thread_id == - 1)
				mon->thread_id = __thinkos_thread_getnext(mon->thread_id);
			dmprintf(comm, "Thread = %d\r\n", mon->thread_id);
			dmon_print_thread(comm, mon->thread_id);
			break;
		case CTRL_O:
			dmon_print_osinfo(comm);
			break;
		case CTRL_P:
			dmputs("^P\r\n", comm);
			monitor_pause_all(comm);
			break;
		case CTRL_Q:
			dmputs("^Q\r\n", comm);
			dbgmon_exec(monitor_task);
			break;
		case CTRL_R:
			dmputs("^R\r\n", comm);
			monitor_resume_all(comm);
			break;
#endif
#if (MONITOR_DUMPMEM_ENABLE)
		case CTRL_S:
			dmputs("^S\r\n", comm);
			monitor_show_mem(mon);
			break;
#endif
#if (MONITOR_THREADINFO_ENABLE)
		case CTRL_T:
			dmon_print_thread(comm, mon->thread_id);
			break;
#endif
#if (MONITOR_STACKUSAGE_ENABLE)
		case CTRL_U:
			dmon_print_stack_usage(comm);
			break;
#endif
		case CTRL_V:
			monitor_show_help(comm);
			break;
#if (MONITOR_FAULT_ENABLE)
		case CTRL_X:
			monitor_print_fault(comm);
			break;
#endif
		case CTRL_Y:
			dmputs("^Y\r\n", comm);
			monitor_ymodem_recv(comm, this_board.application.start_addr, 
								this_board.application.block_size);
			break;
#if (MONITOR_APPWIPE_ENABLE)
		case CTRL_W:
			dmputs("^W\r\n", comm);
			monitor_app_erase(comm, this_board.application.start_addr, 
							  this_board.application.block_size);
			break;
#endif
#if (MONITOR_APPRESTART_ENABLE)
		case CTRL_Z:
			dmputs("^Z\r\n", comm);
			dbgmon_soft_reset();
			monitor_exec(comm, this_board.application.start_addr);
			break;
#endif
		default:
			continue;
		}
		/* shift the input to remove the consumed character */
		for (j = i; j < len - 1; ++j)
			buf[j] = buf[j + 1];
		len--;
	}

	return len;
}

/*
   Dafault Monitor Task
 */

void __attribute__((noreturn)) monitor_task(struct dmon_comm * comm)
{
	struct monitor monitor;
	uint32_t sigmask = 0;
	uint32_t sigset;
#if THINKOS_ENABLE_CONSOLE
	bool connected;
	uint8_t * ptr;
	int cnt;
#endif
	int tick_cnt = 0;
	char buf[64];
	int len;
	
	monitor.comm = comm;
#if (MONITOR_THREADINFO_ENABLE)
	monitor.thread_id = MONITOR_STARTUP_MAGIC;
#endif
#if (MONITOR_DUMPMEM_ENABLE)
	monitor.memdump.addr = this_board.application.start_addr;
	monitor.memdump.size = this_board.application.block_size;
#endif


	DCC_LOG1(LOG_TRACE, "Monitor sp=%08x ...", cm3_sp_get());
//	dmon_comm_connect(comm);
//	DCC_LOG(LOG_TRACE, "Comm connected.");

//	dmon_sleep(100);

#if 0
	dmprintf(comm, "\r\n\r\n");
	dmprintf(comm, __hr__);
	dmprintf(comm, " ThikOS Debug Monitor (Ctrl+V for Help)\r\n");
	dmprintf(comm, __hr__);
#endif

#if (THINKOS_ENABLE_EXCEPTIONS)
	sigmask |= (1 << DBGMON_THREAD_FAULT);
	sigmask |= (1 << DBGMON_EXCEPT);
#endif
	sigmask |= (1 << DBGMON_COMM_RCV);
#if THINKOS_ENABLE_CONSOLE
	sigmask |= (1 << DBGMON_COMM_CTL);
	sigmask |= (1 << DBGMON_TX_PIPE);
	sigmask |= (1 << DBGMON_RX_PIPE);
#endif
	sigmask |= (1 << DBGMON_SOFTRST);

#if (MONITOR_THREADINFO_ENABLE)
	if (monitor.thread_id == MONITOR_STARTUP_MAGIC) {
#endif
		/* first time we run the monitor, start a timer to call the 
		   board_tick() periodically */
		sigmask |= (1 << DBGMON_ALARM);
		dbgmon_alarm(125);
#if (MONITOR_THREADINFO_ENABLE)
		monitor.thread_id = -1;
	}
#endif

#if THINKOS_ENABLE_CONSOLE
	connected = dmon_comm_isconnected(comm);
#endif

	for(;;) {
		sigset = dbgmon_select(sigmask);
		DCC_LOG1(LOG_MSG, "sigset=%08x", sigset);

		if (sigset & (1 << DBGMON_SOFTRST)) {
			this_board.softreset();
			dbgmon_clear(DBGMON_SOFTRST);
		}

#if THINKOS_ENABLE_CONSOLE
		if (sigset & (1 << DBGMON_COMM_CTL)) {
			DCC_LOG(LOG_MSG, "Comm Ctl.");
			dbgmon_clear(DBGMON_COMM_CTL);
			connected = dmon_comm_isconnected(comm);
		}
#endif

		if (sigset & (1 << DBGMON_COMM_RCV)) {
#if THINKOS_ENABLE_CONSOLE
			if ((cnt = __console_rx_pipe_ptr(&ptr)) > 0) {
				DCC_LOG1(LOG_MSG, "Comm recv. rx_pipe.free=%d", cnt);
				if ((len = dmon_comm_recv(comm, ptr, cnt)) > 0) {
					len = monitor_process_input(&monitor, (char *)ptr, len);
					__console_rx_pipe_commit(len); 
				} else {
					DCC_LOG(LOG_WARNING, "dmon_comm_recv() failed, "
							"masking DBGMON_COMM_RCV!");
					sigmask &= ~(1 << DBGMON_COMM_RCV);
				}
			} else {
				DCC_LOG(LOG_TRACE, "Comm recv. rx pipe full!");
				if ((len = dmon_comm_recv(comm, buf, sizeof(buf))) > 0) {
					monitor_process_input(&monitor, buf, len);
				} else {
					DCC_LOG(LOG_WARNING, "dmon_comm_recv() failed, "
							"masking DBGMON_COMM_RCV!");
					sigmask &= ~(1 << DBGMON_COMM_RCV);
				}
			}
#else
			if ((len = dmon_comm_recv(comm, buf, sizeof(buf))) > 0) {
				monitor_process_input(&moniotr, buf, len);
			}
#endif
		}

#if THINKOS_ENABLE_CONSOLE
		if (sigset & (1 << DBGMON_RX_PIPE)) {
			if ((cnt = __console_rx_pipe_ptr(&ptr)) > 0) {
				DCC_LOG1(LOG_TRACE, "RX Pipe. rx_pipe.free=%d. "
						 "Unmaksing DBGMON_COMM_RCV!", cnt);
				sigmask |= (1 << DBGMON_COMM_RCV);
			} else {
				DCC_LOG(LOG_TRACE, "RX Pipe empty!!!");
			}
			dbgmon_clear(DBGMON_RX_PIPE);
		}


		if (sigset & (1 << DBGMON_TX_PIPE)) {
			DCC_LOG(LOG_MSG, "TX Pipe.");
			if ((cnt = __console_tx_pipe_ptr(&ptr)) > 0) {
				DCC_LOG1(LOG_MSG, "TX Pipe, %d pending chars.", cnt);
				if (connected) 
					len = dmon_comm_send(comm, ptr, cnt);
				else
					len = cnt;
				__console_tx_pipe_commit(len); 
			} else {
				DCC_LOG(LOG_MSG, "TX Pipe empty!!!");
				dbgmon_clear(DBGMON_TX_PIPE);
			}
		}
#endif

		if (sigset & (1 << DBGMON_ALARM)) {
			dbgmon_clear(DBGMON_ALARM);
			if (this_board.autoboot(tick_cnt++) && 
				dmon_app_exec(this_board.application.start_addr, false)) {
				sigmask &= ~(1 << DBGMON_ALARM);
				this_board.on_appload();
			} else {
				/* reastart the alarm timer */
				dbgmon_alarm(125);
			}  
		}

#if (THINKOS_ENABLE_EXCEPTIONS)
		if (sigset & (1 << DBGMON_THREAD_FAULT)) {
			DCC_LOG(LOG_TRACE, "Thread fault.");
			monitor_on_fault(comm);
			dbgmon_clear(DBGMON_THREAD_FAULT);
		}

		if (sigset & (1 << DBGMON_EXCEPT)) {
			DCC_LOG(LOG_TRACE, "System exception.");
			monitor_on_fault(comm);
			dbgmon_clear(DBGMON_EXCEPT);
		}
#endif
	}
}

