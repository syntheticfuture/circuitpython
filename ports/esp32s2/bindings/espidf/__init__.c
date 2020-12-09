/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Scott Shawcroft for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/obj.h"
#include "py/runtime.h"

#include "bindings/espidf/__init__.h"

#include "components/heap/include/esp_heap_caps.h"

//| """Direct access to a few ESP-IDF details. This module *should not* include any functionality
//|    that could be implemented by other frameworks. It should only include ESP-IDF specific
//|    things."""

//| def heap_caps_get_total_size() -> int:
//|     """Return the total size of the ESP-IDF, which includes the CircuitPython heap."""
//|     ...
//|

STATIC mp_obj_t espidf_heap_caps_get_total_size(void) {
    return MP_OBJ_NEW_SMALL_INT(heap_caps_get_total_size(MALLOC_CAP_8BIT));
}
MP_DEFINE_CONST_FUN_OBJ_0(espidf_heap_caps_get_total_size_obj, espidf_heap_caps_get_total_size);

//| def heap_caps_get_free_size() -> int:
//|     """Return total free memory in the ESP-IDF heap."""
//|     ...
//|

STATIC mp_obj_t espidf_heap_caps_get_free_size(void) {
    return MP_OBJ_NEW_SMALL_INT(heap_caps_get_free_size(MALLOC_CAP_8BIT));
}
MP_DEFINE_CONST_FUN_OBJ_0(espidf_heap_caps_get_free_size_obj, espidf_heap_caps_get_free_size);

//| def heap_caps_get_largest_free_block() -> int:
//|     """Return the size of largest free memory block in the ESP-IDF heap."""
//|     ...
//|

STATIC mp_obj_t espidf_heap_caps_get_largest_free_block(void) {
    return MP_OBJ_NEW_SMALL_INT(heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
}
MP_DEFINE_CONST_FUN_OBJ_0(espidf_heap_caps_get_largest_free_block_obj, espidf_heap_caps_get_largest_free_block);

//| class MemoryError(MemoryError):
//|     """Raised when an ESP IDF memory allocation fails."""
//|     ...
//|
NORETURN void mp_raise_espidf_MemoryError(void) {
    nlr_raise(mp_obj_new_exception(&mp_type_espidf_MemoryError));
}

void espidf_exception_print(const mp_print_t *print, mp_obj_t o_in, mp_print_kind_t kind) {
    mp_print_kind_t k = kind & ~PRINT_EXC_SUBCLASS;
    bool is_subclass = kind & PRINT_EXC_SUBCLASS;
    if (!is_subclass && (k == PRINT_EXC)) {
        mp_print_str(print, qstr_str(MP_OBJ_QSTR_VALUE(MP_ROM_QSTR(MP_QSTR_espidf))));
        mp_print_str(print, ".");
    }
    mp_obj_exception_print(print, o_in, kind);
}

const mp_obj_type_t mp_type_espidf_MemoryError = {
    { &mp_type_type },
    .name = MP_QSTR_MemoryError,
    .print = espidf_exception_print,
    .make_new = mp_obj_exception_make_new,
    .attr = mp_obj_exception_attr,
    .parent = &mp_type_MemoryError,
};

STATIC const mp_rom_map_elem_t espidf_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_espidf) },

    { MP_ROM_QSTR(MP_QSTR_heap_caps_get_total_size), MP_ROM_PTR(&espidf_heap_caps_get_total_size_obj)},
    { MP_ROM_QSTR(MP_QSTR_heap_caps_get_free_size), MP_ROM_PTR(&espidf_heap_caps_get_free_size_obj)},
    { MP_ROM_QSTR(MP_QSTR_heap_caps_get_largest_free_block), MP_ROM_PTR(&espidf_heap_caps_get_largest_free_block_obj)},

    { MP_ROM_QSTR(MP_QSTR_MemoryError),      MP_ROM_PTR(&mp_type_espidf_MemoryError) },
};

STATIC MP_DEFINE_CONST_DICT(espidf_module_globals, espidf_module_globals_table);

const mp_obj_module_t espidf_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&espidf_module_globals,
};
