// SPDX-FileCopyrightText: 2014 MicroPython & CircuitPython contributors (https://github.com/adafruit/circuitpython/graphs/contributors)
// SPDX-FileCopyrightText: Copyright (c) 2013, 2014 Damien P. George
//
// SPDX-License-Identifier: MIT

#ifndef MICROPY_INCLUDED_EXTMOD_VFS_FAT_H
#define MICROPY_INCLUDED_EXTMOD_VFS_FAT_H

#include "py/lexer.h"
#include "py/obj.h"
#include "lib/oofatfs/ff.h"
#include "extmod/vfs.h"

// these are the values for fs_user_mount_t.flags
#define FSUSER_NATIVE        (0x0001) // readblocks[2]/writeblocks[2] contain native func
#define FSUSER_FREE_OBJ      (0x0002) // fs_user_mount_t obj should be freed on umount
#define FSUSER_HAVE_IOCTL    (0x0004) // new protocol with ioctl
#define FSUSER_NO_FILESYSTEM (0x0008) // the block device has no filesystem on it
// Device is writable over USB and read-only to MicroPython.
#define FSUSER_USB_WRITABLE  (0x0010)
// Bit set when the above flag is checked before opening a file for write.
#define FSUSER_CONCURRENT_WRITE_PROTECTED (0x0020)

typedef struct _fs_user_mount_t {
    mp_obj_base_t base;
    uint16_t flags;
    mp_obj_t readblocks[4];
    mp_obj_t writeblocks[4];
    // new protocol uses just ioctl, old uses sync (optional) and count
    union {
        mp_obj_t ioctl[4];
        struct {
            mp_obj_t sync[2];
            mp_obj_t count[2];
        } old;
    } u;
    FATFS fatfs;
} fs_user_mount_t;

typedef struct _pyb_file_obj_t {
    mp_obj_base_t base;
    FIL fp;
} pyb_file_obj_t;

extern const byte fresult_to_errno_table[20];
extern const mp_obj_type_t mp_fat_vfs_type;
extern const mp_obj_type_t mp_type_vfs_fat_fileio;
extern const mp_obj_type_t mp_type_vfs_fat_textio;

mp_import_stat_t fat_vfs_import_stat(void *vfs, const char *path);

MP_DECLARE_CONST_FUN_OBJ_3(fat_vfs_open_obj);

mp_obj_t fat_vfs_ilistdir2(struct _fs_user_mount_t *vfs, const char *path, bool is_str_type);

MP_DECLARE_CONST_FUN_OBJ_KW(fsuser_mount_obj);
MP_DECLARE_CONST_FUN_OBJ_1(fsuser_umount_obj);
MP_DECLARE_CONST_FUN_OBJ_KW(fsuser_mkfs_obj);

#endif  // MICROPY_INCLUDED_EXTMOD_VFS_FAT_H
