/*
Copyright (C) 2013- The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file COPYING for details.
*/

#ifndef RMONITOR_POLL_INTERNAL_H
#define RMONITOR_POLL_INTERNAL_H

#include "itable.h"
#include "hash_table.h"

#include "rmonitor_types.h"
#if defined(CCTOOLS_OPSYS_DARWIN) || defined(CCTOOLS_OPSYS_FREEBSD)
  #include <sys/param.h>
  #include <sys/mount.h>
  #include <sys/resource.h>
#else
  #include  <sys/vfs.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>

#ifdef HAS_SYS_STATFS_H
#include <sys/statfs.h>
#endif

#ifdef HAS_SYS_STATVFS_H
#include <sys/statvfs.h>
#endif

#ifdef HAS_FTS_H
#include <fts.h>
#endif
#include <ftw.h>

#include "int_sizes.h"
#include "rmonitor_types.h"
#include "rmsummary.h"

#include "rmonitor_poll.h"

void rmonitor_poll_all_processes_once(struct itable *processes, struct rmonitor_process_info *acc);
void rmonitor_poll_all_wds_once(      struct hash_table *wdirs, struct rmonitor_wdir_info *acc);
void rmonitor_poll_all_fss_once(      struct itable *filesysms, struct rmonitor_filesys_info *acc);

int rmonitor_poll_process_once(struct rmonitor_process_info *p);
int rmonitor_poll_wd_once(     struct rmonitor_wdir_info    *d);
int rmonitor_poll_fs_once(     struct rmonitor_filesys_info *f);

void rmonitor_info_to_rmsummary(struct rmsummary *tr, struct rmonitor_process_info *p, struct rmonitor_wdir_info *d, struct rmonitor_filesys_info *f, uint64_t start_time);

int rmonitor_get_cpu_time_usage(pid_t pid,        struct rmonitor_cpu_time_info *cpu);
int rmonitor_get_mem_usage(     pid_t pid,        struct rmonitor_mem_info *mem);
int rmonitor_get_sys_io_usage(  pid_t pid,        struct rmonitor_io_info *io);
int rmonitor_get_map_io_usage(  pid_t pid,        struct rmonitor_io_info *io);
int rmonitor_get_dsk_usage(     const char *path, struct statfs *disk);

int rmonitor_get_wd_usage(struct rmonitor_wdir_info *d);

void acc_cpu_time_usage( struct rmonitor_cpu_time_info *acc, struct rmonitor_cpu_time_info *other);
void acc_mem_usage(      struct rmonitor_mem_info *acc,      struct rmonitor_mem_info *other);
void acc_sys_io_usage(   struct rmonitor_io_info *acc,       struct rmonitor_io_info *other);
void acc_map_io_usage(   struct rmonitor_io_info *acc,       struct rmonitor_io_info *other);
void acc_dsk_usage(      struct statfs *acc,                 struct statfs *other);
void acc_wd_usage(       struct rmonitor_wdir_info *acc,     struct rmonitor_wdir_info *other);

FILE *open_proc_file(pid_t pid, char *filename);
int get_int_attribute(FILE *fstatus, char *attribute, uint64_t *value, int rewind_flag);

uint64_t usecs_since_epoch();

#endif