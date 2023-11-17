# This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

if(CMAKE_SYSTEM_NAME MATCHES "Linux" AND NOT NOJEM)
  # We need to generate the jemalloc_def.h header based on platform-specific settings
  CHECK_SYMBOL_EXISTS(MADV_FREE "sys/mman.h" HAVE_MADV_FREE)
  
  if (PLATFORM EQUAL 32)
    set(JEM_SIZEDEF 2)
    set(JEM_TLSMODEL)
	set(JEM_VADDRBITS 32)
  else()
    set(JEM_SIZEDEF 3)
    set(JEM_TLSMODEL "__attribute__\(\(tls_model\(\"initial-exec\"\)\)\)")
	set(JEM_VADDRBITS 48)
  endif()

  if (HAVE_MADV_FREE)
    set(JEM_MADFREE_DEF "#define")
  else()
    set(JEM_MADFREE_DEF "#undef")
  endif()

  if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(JEM_CPU_SPINWAIT "")
    set(JEM_HAVE_CPU_SPINWAIT 0)
  else()
    set(JEM_CPU_SPINWAIT "__asm__ volatile\(\"pause\"\)")
    set(JEM_HAVE_CPU_SPINWAIT 1)
  endif()

  # Create the header, so we can use it
  configure_file(
    "${CMAKE_SOURCE_DIR}/dep/jemalloc/jemalloc_internal_defs.h.in.cmake"
    "${BUILDDIR}/jemalloc_internal_defs.h"
    @ONLY
  )

  # Done, let's continue
  set(jemalloc_STAT_SRC
          src/arena.c
          src/background_thread.c
          src/base.c
          src/bin.c
          src/bitmap.c
          src/ckh.c
          src/ctl.c
          src/div.c
          src/extent.c
          src/extent_dss.c
          src/extent_mmap.c
          src/hash.c
          src/hook.c
          src/jemalloc.c
          src/jemalloc_cpp.cpp
          src/large.c
          src/log.c
          src/malloc_io.c
          src/mutex.c
          src/mutex_pool.c
          src/nstime.c
          src/pages.c
          src/prng.c
          src/prof.c
          src/rtree.c
          src/safety_check.c
          src/stats.c
          src/sc.c
          src/sz.c
          src/tcache.c
          src/test_hooks.c
          src/ticker.c
          src/tsd.c
          src/witness.c
  )

  add_library(jemalloc STATIC ${jemalloc_STAT_SRC})

  target_include_directories(jemalloc
    PRIVATE
      ${BUILDDIR}
          include)

  target_compile_definitions(jemalloc
    PUBLIC
      -DNO_BUFFERPOOL
    PRIVATE
      -D_GNU_SOURCE
      -D_REENTRAN)

  target_link_libraries(jemalloc
    PRIVATE
      trinity-dependency-interface
    PUBLIC
      threads
      valgrind
	  ${CMAKE_DL_LIBS})

  set_target_properties(jemalloc
      PROPERTIES
        FOLDER
          "dep")

else()
  # Provide a dummy target for jemalloc which is used when jemalloc
  # is disabled or not supported.
  add_library(jemalloc INTERFACE)
  target_link_libraries(jemalloc
    INTERFACE
      valgrind)

endif()
