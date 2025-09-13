/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

// *INDENT-OFF*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// Check Configurations /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Check handle method, choose one of the following:
 *  - ESP_UTILS_CHECK_HANDLE_WITH_NONE:      Do nothing when check failed (Minimum code size)
 *  - ESP_UTILS_CHECK_HANDLE_WITH_ERROR_LOG: Print error message when check failed (Recommended)
 *  - ESP_UTILS_CHECK_HANDLE_WITH_ASSERT:    Assert when check failed
 */
#define ESP_UTILS_CONF_CHECK_HANDLE_METHOD                  (ESP_UTILS_CHECK_HANDLE_WITH_ERROR_LOG)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// Log Configurations //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Global log level, logs with a level lower than this will not be compiled. Choose one of the following:
 *  - ESP_UTILS_LOG_LEVEL_DEBUG:   Extra information which is not necessary for normal use (values, pointers, sizes, etc)
 *                                 (lowest level)
 *  - ESP_UTILS_LOG_LEVEL_INFO:    Information messages which describe the normal flow of events
 *  - ESP_UTILS_LOG_LEVEL_WARNING: Error conditions from which recovery measures have been taken
 *  - ESP_UTILS_LOG_LEVEL_ERROR:   Critical errors, software module cannot recover on its own
 *  - ESP_UTILS_LOG_LEVEL_NONE:    No log output (highest level) (Minimum code size)
 */
#define ESP_UTILS_CONF_LOG_LEVEL                            (ESP_UTILS_LOG_LEVEL_INFO)
#define ESP_UTILS_CONF_LOG_IMPL_TYPE                        (ESP_UTILS_CONF_LOG_IMPL_STDLIB)
#if ESP_UTILS_CONF_LOG_LEVEL == ESP_UTILS_LOG_LEVEL_DEBUG

    /**
     * @brief Set to 1 if print trace log messages when enter/exit functions, useful for debugging
     */
    #define ESP_UTILS_CONF_ENABLE_LOG_TRACE                 (0)

#endif // ESP_UTILS_CONF_LOG_LEVEL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// Memory Configurations /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Default enable memory allocation.
 *
 * If enabled, the driver will use general memory allocation by default, otherwise, the driver will use `malloc` and
 * `free` by default
 */
#define ESP_UTILS_CONF_MEM_GEN_ALLOC_DEFAULT_ENABLE         (1)

/**
 * General Memory allocation type, choose one of the following:
 *  - ESP_UTILS_MEM_ALLOC_TYPE_STDLIB:      Use the standard library memory allocation functions (malloc, free)
 *  - ESP_UTILS_MEM_ALLOC_TYPE_ESP:         Use the ESP-IDF memory allocation functions (heap_caps_aligned_alloc, heap_caps_free)
 *  - ESP_UTILS_MEM_ALLOC_TYPE_MICROPYTHON: Use the MicroPython memory allocation functions (m_malloc, m_free)
 *  - ESP_UTILS_MEM_ALLOC_TYPE_CUSTOM:      Use custom memory allocation functions (ESP_UTILS_MEM_ALLOC_CUSTOM_MALLOC,
 *                                          ESP_UTILS_MEM_ALLOC_CUSTOM_FREE)
 */
#define ESP_UTILS_CONF_MEM_GEN_ALLOC_TYPE                   (ESP_UTILS_MEM_ALLOC_TYPE_STDLIB)
#if ESP_UTILS_CONF_MEM_GEN_ALLOC_TYPE == ESP_UTILS_MEM_ALLOC_TYPE_ESP

    #define ESP_UTILS_CONF_MEM_GEN_ALLOC_ESP_ALIGN          (1)
    #define ESP_UTILS_CONF_MEM_GEN_ALLOC_ESP_CAPS           (MALLOC_CAP_DEFAULT | MALLOC_CAP_8BIT)

#elif ESP_UTILS_CONF_MEM_GEN_ALLOC_TYPE == ESP_UTILS_MEM_ALLOC_TYPE_CUSTOM

    #define ESP_UTILS_CONF_MEM_GEN_ALLOC_CUSTOM_INCLUDE     "stdlib.h"
    #define ESP_UTILS_CONF_MEM_GEN_ALLOC_CUSTOM_MALLOC      malloc
    #define ESP_UTILS_CONF_MEM_GEN_ALLOC_CUSTOM_FREE        free

#endif // ESP_UTILS_CONF_MEM_GEN_ALLOC_TYPE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// File Version ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// C++ Global Memory Allocation ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * If enabled, the driver will override `new` and `delete` operators to use global memory allocator
 */
#define ESP_UTILS_CONF_MEM_ENABLE_CXX_GLOB_ALLOC            (0)
#if ESP_UTILS_CONF_MEM_ENABLE_CXX_GLOB_ALLOC
/**
 * If enabled, the driver will use global memory allocation by default, otherwise, the driver will use
 * the standard `malloc` and `free` by default
 */
#define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_DEFAULT_ENABLE    (1)

/**
 * C++ global memory allocation type, choose one of the following:
 *  - ESP_UTILS_MEM_ALLOC_TYPE_ESP:         Use the ESP-IDF memory allocation functions (heap_caps_aligned_alloc, heap_caps_free)
 *  - ESP_UTILS_MEM_ALLOC_TYPE_MICROPYTHON: Use the MicroPython memory allocation functions (m_malloc, m_free)
 *  - ESP_UTILS_MEM_ALLOC_TYPE_CUSTOM:      Use custom memory allocation functions (ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_CUSTOM_MALLOC,
 *                                          ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_CUSTOM_FREE)
 */
#define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_TYPE              (ESP_UTILS_MEM_ALLOC_TYPE_ESP)
#if ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_TYPE == ESP_UTILS_MEM_ALLOC_TYPE_ESP

/**
 * ESP memory caps, choose one of the following:
 *  - ESP_UTILS_MEM_ALLOC_ESP_CAPS_DEFAULT:    Default
 *  - ESP_UTILS_MEM_ALLOC_ESP_CAPS_SRAM:       Internal RAM (SRAM)
 *  - ESP_UTILS_MEM_ALLOC_ESP_CAPS_PSRAM:      External RAM (PSRAM)
 */
#   define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_ESP_CAPS       (ESP_UTILS_MEM_ALLOC_ESP_CAPS_DEFAULT)
#   define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_ESP_ALIGN      (1)

#elif ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_TYPE == ESP_UTILS_MEM_ALLOC_TYPE_CUSTOM

#   define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_CUSTOM_INCLUDE     "esp_heap_caps.h"
#   define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_CUSTOM_NEW(x)      heap_caps_aligned_alloc(1, x, MALLOC_CAP_DEFAULT | MALLOC_CAP_8BIT)
#   define ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_CUSTOM_DELETE(x)   heap_caps_free(x)

#endif // ESP_UTILS_CONF_MEM_CXX_GLOB_ALLOC_TYPE

#endif // ESP_UTILS_CONF_MEM_ENABLE_CXX_GLOB_ALLOC

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// Plugin Configurations /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief If enabled, the driver will support plugin mechanism
 *
 * @note This configuration requires C++ RTTI support
 */
#define ESP_UTILS_CONF_PLUGIN_SUPPORT                       (0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// File Version ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Do not change the following versions, they are used to check if the configurations in this file are compatible with
 * the current version of `esp_utils_conf.h` in the library. The detailed rules are as follows:
 *
 *   1. If the major version is not consistent, then the configurations in this file are incompatible with the library
 *      and must be replaced with the file from the library.
 *   2. If the minor version is not consistent, this file might be missing some new configurations, which will be set to
 *      default values. It is recommended to replace it with the file from the library.
 *   3. Even if the patch version is not consistent, it will not affect normal functionality.
 */
#define ESP_UTILS_CONF_FILE_VERSION_MAJOR 1
#define ESP_UTILS_CONF_FILE_VERSION_MINOR 5
#define ESP_UTILS_CONF_FILE_VERSION_PATCH 0

// *INDENT-ON*
