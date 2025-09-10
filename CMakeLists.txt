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
# SECTION: "01".."09" (maps to dirs "1. ...", "2. ...", etc.)
# WEEK   : "01".."25" (maps to "Week_1", ...)
# CLASS  : "01".."50" (used for naming; auto-inferred in SingleFile mode)
set(SECTION "01" CACHE STRING "Section to build (01..09)")
set(WEEK    "01" CACHE STRING "Week to build (01..25)")
set(CLASS   "01" CACHE STRING "Class to build (01..50)")
set_property(CACHE SECTION PROPERTY STRINGS 01 02 03 04 05 06 07 08 09)

# =======================
# Build mode (drives UI)
# =======================
# SingleFile: Sections 1–2. Auto-create one target per .cpp (with main()) in the chosen Week.
# Section   : Sections 3–9. Build the whole section from a single main.cpp at the section root.
set(BUILD_MODE "SingleFile" CACHE STRING "Build mode: SingleFile (Sections 1–2) or Section (Sections 3–9)")
set_property(CACHE BUILD_MODE PROPERTY STRINGS SingleFile Section)

# Optional: user-visible picker for default run file (we'll populate its choices later)
set(MAIN_FILE "" CACHE STRING "Optional: pick the .cpp to run by default (must contain main())")

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

# ---------- resolve SECTION dir ----------
_strip_zeros("${SECTION}" SECTION_NUM)
if(NOT "${SECTION_NUM}" MATCHES "^[1-9]$")
  message(FATAL_ERROR "Only Sections 01..09 are buildable. '${SECTION}' is not.")
endif()

# Find section dir by numeric prefix "N. "
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

# ---------- WEEK dropdown from disk ----------
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
set(_WEEK_CHOICES_PAD "")
foreach(n ${_WEEK_CHOICES})
  _pad2("${n}" n2)
  list(APPEND _WEEK_CHOICES_PAD "${n2}")
endforeach()
if(_WEEK_CHOICES_PAD)
  set_property(CACHE WEEK PROPERTY STRINGS ${_WEEK_CHOICES_PAD})
endif()

# Resolve week dir
_strip_zeros("${WEEK}" WEEK_NUM)
set(WEEK_DIR "${SECTION_DIR}/Week_${WEEK_NUM}")

# ---------- CLASS dropdown from disk (for Section mode; SingleFile will infer) ----------
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

# Resolve class dir (used by Section mode)
_strip_zeros("${CLASS}" CLASS_NUM)
set(CLASS_DIR "${WEEK_DIR}/Class ${CLASS_NUM}")

message(STATUS "==> Selection: SECTION=${SECTION}  WEEK=${WEEK}  CLASS=${CLASS}")
message(STATUS "    Paths: SECTION_DIR='${SECTION_DIR}'  WEEK_DIR='${WEEK_DIR}'  CLASS_DIR='${CLASS_DIR}'")

# =======================
# Build logic
# =======================
if(BUILD_MODE STREQUAL "SingleFile")
  set(MODE "SingleFile (Sections 1–2)")

  # Only Sections 1–2 are valid here
  if(NOT "${SECTION_NUM}" MATCHES "^[12]$")
    message(FATAL_ERROR "In SingleFile mode, SECTION must be 01 or 02 (got ${SECTION}).")
  endif()

  # Require the selected class folder
  if(NOT EXISTS "${CLASS_DIR}")
    message(FATAL_ERROR "Class directory not found: ${CLASS_DIR}")
  endif()

  # >>> STRICT: only compile .cpp that live directly in THIS class folder (no recursion)
  file(GLOB _cpps CONFIGURE_DEPENDS "${CLASS_DIR}/*.cpp")

  set(_choices "")
  set(_first_target "")
  _pad2("${CLASS}" CLASS_PAD)

  foreach(f ${_cpps})
    file(READ "${f}" _txt LIMIT 32768)
    string(REGEX MATCH "[^A-Za-z0-9_]main[ \t\r\n]*\\(" _has_main "${_txt}")
    if(_has_main)
      get_filename_component(_fn "${f}" NAME)      # classNN_subject.cpp
      get_filename_component(_stem "${f}" NAME_WE) # classNN_subject

      # subject = filename minus leading 'class<digits>[_-]*'
      string(REGEX REPLACE "^[Cc][Ll][Aa][Ss][Ss][ \t]*0*[0-9]+[ _-]*" "" _subject "${_stem}")
      if(_subject STREQUAL "") 
        set(_subject "program") 
      endif()
      string(REGEX REPLACE "[^A-Za-z0-9]+" "_" _subject "${_subject}")
      string(REGEX REPLACE "_+" "_" _subject "${_subject}")
      string(REGEX REPLACE "^_+|_+$" "" _subject "${_subject}")

      set(_tgt "class${CLASS_PAD}_${_subject}")

      add_executable(${_tgt} "${f}" "1. Core Foundations/Week_2/Class 4/class04_char_arithmatic01.cpp" "1. Core Foundations/Week_2/Class 4/class04_int_arithmatic02.cpp" "1. Core Foundations/Week_2/Class 4/class04_float_arithmatic03.cpp")
      # >>> STRICT: only include THIS class folder (prevents accidental reach-up)
      target_include_directories(${_tgt} PRIVATE "${CLASS_DIR}")

      if(MSVC)
        target_compile_options(${_tgt} PRIVATE /W4 /permissive-)
      else()
        target_compile_options(${_tgt} PRIVATE -Wall -Wextra -Wpedantic)
      endif()
      set_target_properties(${_tgt} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

      list(APPEND _choices "${_fn}")
      if(_first_target STREQUAL "") 
        set(_first_target "${_tgt}") 
      endif()

      message(STATUS "  + ${_fn} -> target ${_tgt}")
    endif()
  endforeach()

  if(_choices STREQUAL "")
    message(FATAL_ERROR "No .cpp with main() found in ${CLASS_DIR}")
  endif()

  # Optional: populate the file dropdown (if you use the Cache UI)
  set_property(CACHE MAIN_FILE PROPERTY STRINGS ${_choices})

  # Startup target = chosen MAIN_FILE if set, else the first discovered
  set(_startup "${_first_target}")
  if(NOT "${MAIN_FILE}" STREQUAL "")
    foreach(f ${_cpps})
      get_filename_component(_fn "${f}" NAME)
      if(_fn STREQUAL "${MAIN_FILE}")
        get_filename_component(_stem "${f}" NAME_WE)
        string(REGEX REPLACE "^[Cc][Ll][Aa][Ss][Ss][ \t]*0*[0-9]+[ _-]*" "" _subject "${_stem}")
        string(REGEX REPLACE "[^A-Za-z0-9]+" "_" _subject "${_subject}")
        string(REGEX REPLACE "_+" "_" _subject "${_subject}")
        string(REGEX REPLACE "^_+|_+$" "" _subject "${_subject}")
        set(_startup "class${CLASS_PAD}_${_subject}")
      endif()
    endforeach()
  endif()

  # Make the chosen program the default ▶ in VS
  set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ${_startup})

else()
  # ---------- Sections 3–9: one entry at section root: <section>/main.cpp ----------
  set(SECTION_MAIN "${SECTION_DIR}/main.cpp")
  if(NOT EXISTS "${SECTION_MAIN}")
    message(FATAL_ERROR "For Sections 3–9, provide a single entry point at: ${SECTION_MAIN}")
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

  _pad2("${CLASS}" CLASS_PAD)
  add_executable(lesson_${CLASS_PAD} ${SRCS})
  target_include_directories(lesson_${CLASS_PAD} PRIVATE "${SECTION_DIR}")
  file(GLOB _subdirs LIST_DIRECTORIES TRUE "${SECTION_DIR}/*")
  foreach(d IN LISTS _subdirs)
    if(IS_DIRECTORY "${d}")
      target_include_directories(lesson_${CLASS_PAD} PRIVATE "${d}")
    endif()
  endforeach()

  if(MSVC)
    target_compile_options(lesson_${CLASS_PAD} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(lesson_${CLASS_PAD} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
  set_target_properties(lesson_${CLASS_PAD} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()
