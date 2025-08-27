cmake_minimum_required(VERSION 3.26)
project(CppCourse LANGUAGES CXX)

# =======================
# C++ Standard
# =======================
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =======================
# Selection knobs (cached)
# =======================
# SECTION  : "01".."09"    (maps to dir "1. ...", "2. ...", etc.)
# WEEK     : "01".."25"    (maps to "Week_1", ...)
# CLASS    : "01".."50"    (maps to "Class 1", ...)
set(SECTION "01" CACHE STRING "Section to build (01..09)")
set(WEEK    "01" CACHE STRING "Week to build (01..25)")
set(CLASS   "01" CACHE STRING "Class to build (01..50)")

# For Sections 1–2 only: choose which single-file program to compile in the Class folder.
# Example: -DPROGRAM=topic2  -> picks classNN_topic2.cpp
# If empty and only one .cpp exists, it auto-selects that file.
set(PROGRAM "" CACHE STRING "Sections 1–2: substring/suffix for classNN_*.cpp; empty=auto if only one")

# (Nice for VS UI: restrict selectable values)
set_property(CACHE SECTION PROPERTY STRINGS 01 02 03 04 05 06 07 08 09)

# ---------- helpers ----------
function(_strip_zeros IN OUTVAR)
  string(REGEX REPLACE "^0+" "" _tmp "${IN}")
  if(_tmp STREQUAL "") 
    set(_tmp "0") 
  endif()
  set(${OUTVAR} "${_tmp}" PARENT_SCOPE)
endfunction()

function(_pad2 IN OUTVAR)
  set(_src "00${IN}")
  string(LENGTH "${_src}" _L)
  math(EXPR _start "${_L}-2")
  string(SUBSTRING "${_src}" ${_start} 2 _res)
  set(${OUTVAR} "${_res}" PARENT_SCOPE)
endfunction()

# ---------- cache vars with sane defaults ----------
set(SECTION "01" CACHE STRING "Section to build (01..09)")
set(WEEK    "01" CACHE STRING "Week to build (01..25)")
set(CLASS   "01" CACHE STRING "Class to build (01..50)")
set(MAIN_FILE "" CACHE STRING "For Sections 1–2: pick the .cpp that defines main() in this Class")

# Hard guard: only 01..09 are buildable
set_property(CACHE SECTION PROPERTY STRINGS 01 02 03 04 05 06 07 08 09)
_strip_zeros("${SECTION}" SECTION_NUM)
if(NOT SECTION_NUM MATCHES "^[1-9]$")
  message(FATAL_ERROR "Only Sections 01..09 are buildable. '${SECTION}' is not.")
endif()

# Locate section dir by numeric prefix "N. "
file(GLOB _section_matches RELATIVE "${CMAKE_SOURCE_DIR}" "${SECTION_NUM}. *")
list(FILTER _section_matches INCLUDE REGEX "^[0-9]+\\. .*$")
list(LENGTH _section_matches _sec_count)
if(_sec_count EQUAL 0)
  message(FATAL_ERROR "No directory like '${SECTION_NUM}. <Name>' under ${CMAKE_SOURCE_DIR}")
elseif(_sec_count GREATER 1)
  message(FATAL_ERROR "Multiple directories match '${SECTION_NUM}. ': ${_section_matches}")
endif()
list(GET _section_matches 0 SECTION_DIRNAME)
set(SECTION_DIR "${CMAKE_SOURCE_DIR}/${SECTION_DIRNAME}")
message(STATUS "==> Section: ${SECTION_DIRNAME}")

# ---------- populate WEEK dropdown from disk ----------
set(_WEEK_CHOICES "")
file(GLOB _weeks LIST_DIRECTORIES TRUE "${SECTION_DIR}/Week_*")
foreach(w ${_weeks})
  get_filename_component(_wk "${w}" NAME)
  if(_wk MATCHES "^Week_([0-9]+)$")
    list(APPEND _WEEK_CHOICES "${CMAKE_MATCH_1}")
  endif()
endforeach()
list(REMOVE_DUPLICATES _WEEK_CHOICES)
list(SORT _WEEK_CHOICES COMPARE NATURAL)
# Pad to 2 digits for UI consistency
set(_WEEK_CHOICES_PAD "")
foreach(n ${_WEEK_CHOICES})
  _pad2("${n}" n2)
  list(APPEND _WEEK_CHOICES_PAD "${n2}")
endforeach()
if(_WEEK_CHOICES_PAD)  # avoid empty property (VS UI quirk)
  set_property(CACHE WEEK PROPERTY STRINGS ${_WEEK_CHOICES_PAD})
endif()

# Resolve selected week dir
_strip_zeros("${WEEK}" WEEK_NUM)
set(WEEK_DIR "${SECTION_DIR}/Week_${WEEK_NUM}")

# ---------- populate CLASS dropdown from disk ----------
set(_CLASS_CHOICES "")
if(EXISTS "${WEEK_DIR}")
  file(GLOB _classes LIST_DIRECTORIES TRUE "${WEEK_DIR}/Class *")
  foreach(c ${_classes})
    get_filename_component(_cl "${c}" NAME)
    if(_cl MATCHES "^Class[ ]+([0-9]+)$")
      list(APPEND _CLASS_CHOICES "${CMAKE_MATCH_1}")
    endif()
  endforeach()
endif()
list(REMOVE_DUPLICATES _CLASS_CHOICES)
list(SORT _CLASS_CHOICES COMPARE NATURAL)
set(_CLASS_CHOICES_PAD "")
foreach(n ${_CLASS_CHOICES})
  _pad2("${n}" n2)
  list(APPEND _CLASS_CHOICES_PAD "${n2}")
endforeach()
if(_CLASS_CHOICES_PAD)
  set_property(CACHE CLASS PROPERTY STRINGS ${_CLASS_CHOICES_PAD})
endif()

# Resolve selected class dir
_strip_zeros("${CLASS}" CLASS_NUM)
set(CLASS_DIR "${WEEK_DIR}/Class ${CLASS_NUM}")

# ---------- selection logic & MAIN_FILE dropdown ----------
set(SRCS)
set(MODE "")

if(SECTION_NUM STREQUAL "1" OR SECTION_NUM STREQUAL "2")
  set(MODE "single-file")

  if(NOT EXISTS "${CLASS_DIR}")
    message(FATAL_ERROR "Class directory not found: ${CLASS_DIR}")
  endif()

  # Find only .cpp that actually contain main()
  set(_MAIN_CHOICES "")
  file(GLOB _cpps "${CLASS_DIR}/*.cpp")
  foreach(f ${_cpps})
    file(READ "${f}" _txt LIMIT 32768)  # read first 32KB is enough
    string(REGEX MATCH "[^A-Za-z0-9_]main[ \t\r\n]*\\(" _has_main "${_txt}")
    if(_has_main)
      get_filename_component(_fn "${f}" NAME)
      list(APPEND _MAIN_CHOICES "${_fn}")
    endif()
  endforeach()
  list(SORT _MAIN_CHOICES)

  if(_MAIN_CHOICES STREQUAL "")
    message(FATAL_ERROR "No .cpp with main() found in ${CLASS_DIR}")
  endif()

  # Populate dropdown for MAIN_FILE
  set_property(CACHE MAIN_FILE PROPERTY STRINGS ${_MAIN_CHOICES})

  # Auto-pick if only one, else require explicit choice
  if(MAIN_FILE STREQUAL "")
    list(LENGTH _MAIN_CHOICES _n)
    if(_n EQUAL 1)
      list(GET _MAIN_CHOICES 0 MAIN_FILE)
      # also write it back to cache so VS shows it selected
      set(MAIN_FILE "${MAIN_FILE}" CACHE STRING "For Sections 1–2: pick the .cpp that defines main() in this Class" FORCE)
    else()
      string(REPLACE "${CMAKE_SOURCE_DIR}/" "" _rel "${CLASS_DIR}")
      message(FATAL_ERROR
        "Multiple main() sources in ${_rel}:\n  ${_MAIN_CHOICES}\n"
        "Pick one via the 'MAIN_FILE' dropdown in CMake Settings.")
    endif()
  endif()

  set(MAIN_SRC "${CLASS_DIR}/${MAIN_FILE}")
  if(NOT EXISTS "${MAIN_SRC}")
    message(FATAL_ERROR "Chosen MAIN_FILE does not exist: ${MAIN_SRC}")
  endif()
  set(SRCS "${MAIN_SRC}")

else()
  set(MODE "multi-class (entire section)")

  set(SECTION_MAIN "${SECTION_DIR}/main.cpp")
  if(NOT EXISTS "${SECTION_MAIN}")
    message(FATAL_ERROR
      "For Sections 3–9, provide a single entry point at:\n  ${SECTION_MAIN}")
  endif()

  file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${SECTION_DIR}/*.cpp")

  # Enforce exactly one main(), and that it's SECTION_MAIN
  set(MAIN_FILES "")
  foreach(src IN LISTS SRCS)
    file(READ "${src}" _txt LIMIT 32768)
    string(REGEX MATCH "[^A-Za-z0-9_]main[ \t\r\n]*\\(" _has_main "${_txt}")
    if(_has_main) 
      list(APPEND MAIN_FILES "${src}") 
    endif()
  endforeach()
  list(LENGTH MAIN_FILES _mc)
  if(NOT _mc EQUAL 1 OR NOT "${MAIN_FILES}" STREQUAL "${SECTION_MAIN}")
    message(FATAL_ERROR
      "Expected exactly ONE main() at ${SECTION_MAIN}.\nFound (${_mc}):\n  ${MAIN_FILES}")
  endif()

  # Hide MAIN_FILE in UI by clearing choices (VS shows plain textbox otherwise)
  set_property(CACHE MAIN_FILE PROPERTY STRINGS "")
endif()

message(STATUS "==> Build mode: ${MODE}")
message(STATUS "Sources selected:")
foreach(s IN LISTS SRCS)
  message(STATUS "  ${s}")
endforeach()

# =======================
# Target
# =======================
add_executable(lesson_${CLASS} ${SRCS})

# Includes
if(MODE MATCHES "single-file")
  target_include_directories(lesson_${CLASS} PRIVATE "${CLASS_DIR}")
else()
  target_include_directories(lesson_${CLASS} PRIVATE "${SECTION_DIR}")
  file(GLOB _subdirs LIST_DIRECTORIES TRUE "${SECTION_DIR}/*")
  foreach(d IN LISTS _subdirs)
    if(IS_DIRECTORY "${d}")
      target_include_directories(lesson_${CLASS} PRIVATE "${d}")
    endif()
  endforeach()
endif()

# Warnings (tighten later with /WX)
if(MSVC)
  target_compile_options(lesson_${CLASS} PRIVATE /W4 /permissive-)
  # target_compile_options(lesson PRIVATE /WX)
else()
  target_compile_options(lesson_${CLASS} PRIVATE -Wall -Wextra -Wpedantic)
  # target_compile_options(lesson PRIVATE -Werror)
endif()

# Output dirs (stable paths for VS multi-config)
set_target_properties(lesson_${CLASS} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_BINARY_DIR}/bin"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin/Debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release"
)

# VS QOL
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT lesson_${CLASS})
source_group(TREE "${SECTION_DIR}" FILES ${SRCS})
