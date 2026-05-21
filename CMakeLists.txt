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
# SECTION: "01".."04" (maps to dirs "1. ...", "2. ...", etc.)
# WEEK   : "01".."25" (maps to "Week_1", ...)
# CLASS  : "01".."50" (used for naming; auto-inferred in SingleFile mode)
set(SECTION "01" CACHE STRING "Section to build (01..04)")
set(WEEK    "01" CACHE STRING "Week to build (01..25)")
set(CLASS   "01" CACHE STRING "Class to build (01..50)")
set_property(CACHE SECTION PROPERTY STRINGS 01 02 03 04)

# =======================
# Build mode (drives UI)
# =======================
# SingleFile: Sections 1–2. Auto-create one target per .cpp (with main()) in the chosen Week.
# MultiFile   : Sections 3–4. Build the whole section from a single main.cpp at the Section class root.
set(BUILD_MODE "SingleFile" CACHE STRING "Build mode: SingleFile (Sections 1–2) or MultiFile (Section 3–4)")
set_property(CACHE BUILD_MODE PROPERTY STRINGS SingleFile MultiFile)

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
if(NOT "${SECTION_NUM}" MATCHES "^[1-4]$")
  message(FATAL_ERROR "Only Section 01..04 are buildable. '${SECTION}' is not.")
endif()

# Find MultiFile dir by numeric prefix "N. "
file(GLOB _section_matches RELATIVE "${CMAKE_SOURCE_DIR}" "${SECTION_NUM}. *")
list(FILTER _section_matches INCLUDE REGEX "^[0-4]+\\. .*$")
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

# ---------- CLASS dropdown from disk (for SECTION mode; SingleFile will infer) ----------
set(_CLASS_CHOICES "")
if(EXISTS "${WEEK_DIR}")
  file(GLOB _classes LIST_DIRECTORIES TRUE "${WEEK_DIR}/Class *")
  foreach(c ${_classes})
    get_filename_component(_cl "${c}" NAME)
    if(_cl MATCHES "^Class ([0-9]+)$")
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

# Resolve class dir (used by MultiFile mode)
_strip_zeros("${CLASS}" CLASS_NUM)
set(CLASS_DIR "${WEEK_DIR}/Class ${CLASS_NUM}")

message(STATUS "==> Selection: SECTION=${SECTION}  WEEK=${WEEK}  CLASS=${CLASS}")
message(STATUS "    Paths: SECTION_DIR='${SECTION_DIR}'  WEEK_DIR='${WEEK_DIR}'  CLASS_DIR='${CLASS_DIR}'")

# =======================
# Build logic
# =======================
if(BUILD_MODE STREQUAL "SingleFile")
  set(MODE "SingleFile (Sections 1–2)")

  # Only Section 1–2 are valid here
  if(NOT "${SECTION_NUM}" MATCHES "^[12]$")
    message(FATAL_ERROR "In SingleFile mode, Section must be 01 or 02 (got ${SECTION}).")
  endif()

  # Require the selected class folder
  if(NOT EXISTS "${CLASS_DIR}")
    message(FATAL_ERROR "Class directory not found: ${CLASS_DIR}")
  endif()

  # >>> STRICT: only compile .cpp that live directly in THIS class folder (no recursion)
    file(GLOB _cpps CONFIGURE_DEPENDS "${CLASS_DIR}/*.cpp")

    set(_targets "")

    foreach(f IN LISTS _cpps)
      file(READ "${f}" _txt LIMIT 32768)

      string(REGEX MATCH "(^|[^A-Za-z0-9_])main[ \t\r\n]*\\(" _has_main "${_txt}")

      if(_has_main)
        get_filename_component(_stem "${f}" NAME_WE)

        string(REGEX REPLACE "^[Cc][Ll][Aa][Ss][Ss][ \t]*0*[0-9]+[ _-]*" "" _subject "${_stem}")
        if(_subject STREQUAL "")
          set(_subject "program")
        endif()

        string(REGEX REPLACE "[^A-Za-z0-9]+" "_" _subject "${_subject}")
        string(REGEX REPLACE "_+" "_" _subject "${_subject}")
        string(REGEX REPLACE "^_+|_+$" "" _subject "${_subject}")

        _pad2("${CLASS}" CLASS_PAD)
        set(_tgt "class${CLASS_PAD}_${_subject}")

        add_executable(${_tgt} "${f}")
        target_include_directories(${_tgt} PRIVATE "${CLASS_DIR}")

        if(MSVC)
          target_compile_options(${_tgt} PRIVATE /W4 /permissive-)
        else()
          target_compile_options(${_tgt} PRIVATE -Wall -Wextra -Wpedantic)
        endif()

        set_target_properties(${_tgt} PROPERTIES
          RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
          VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

        list(APPEND _targets "${_tgt}")

        message(STATUS "  + ${f} -> target ${_tgt}")
      endif()
    endforeach()

    if(NOT _targets)
      message(FATAL_ERROR
        "SingleFile mode requires at least one .cpp with main() in:\n  ${CLASS_DIR}")
    endif()

    list(GET _targets 0 _startup)
    set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                 PROPERTY VS_STARTUP_PROJECT ${_startup})

else()

  # ============================================================
  # MultiFile Mode (Sections 3–4)
  # Build all .cpp in the selected class folder
  # Require exactly one main()
  # Entry priority:
  #   1) class##_main.cpp
  #   2) <section>/main.cpp fallback
  # ============================================================

  # Collect all .cpp in class folder (non-recursive)
  file(GLOB SRCS CONFIGURE_DEPENDS
       "${CLASS_DIR}/*.cpp")

  if(NOT SRCS)
    message(FATAL_ERROR
      "MultiFile mode: No .cpp files found in ${CLASS_DIR}")
  endif()

  # Look for class##_main.cpp inside class folder
  file(GLOB CLASS_MAIN_FILES CONFIGURE_DEPENDS
       "${CLASS_DIR}/class*_main.cpp")

  if(CLASS_MAIN_FILES)
    list(LENGTH CLASS_MAIN_FILES _count)
    if(NOT _count EQUAL 1)
      message(FATAL_ERROR
        "MultiFile mode: Expected exactly ONE class##_main.cpp in ${CLASS_DIR}, found ${_count}")
    endif()

    list(GET CLASS_MAIN_FILES 0 MAIN_SECTION)

  else()
    # Fallback to section-level main.cpp
    set(SECTION_MAIN "${SECTION_DIR}/main.cpp")

    if(EXISTS "${SECTION_MAIN}")
      set(MAIN_SECTION "${SECTION_MAIN}")
      list(APPEND SRCS "${SECTION_MAIN}")
    else()
      message(FATAL_ERROR
        "MultiFile mode: No class##_main.cpp found and no fallback main.cpp at ${SECTION_MAIN}")
    endif()
  endif()

  # Enforce exactly ONE main() total
  set(MAIN_FILES "")
  foreach(src IN LISTS SRCS)
    file(READ "${src}" _txt LIMIT 32768)

    string(REGEX MATCH "(^|[^A-Za-z0-9_])main[ \t\r\n]*\\(" _has_main "${_txt}")

    if(_has_main)
      list(APPEND MAIN_FILES "${src}")
    endif()
  endforeach()

  list(LENGTH MAIN_FILES _mc)
  if(NOT _mc EQUAL 1)
    message(FATAL_ERROR
      "MultiFile mode requires exactly ONE main() in ${CLASS_DIR}.\n"
      "Found ${_mc} in:\n  ${MAIN_FILES}")
  endif()

  # Build target
  _pad2("${CLASS}" CLASS_PAD)
  set(_tgt "lesson_${CLASS_PAD}")

  add_executable(${_tgt} ${SRCS} "3. Section_3/Week_15/Class 26/class26_main.cpp"   "3. Section_3/Week_16/Class 27/class27_main.cpp" "3. Section_3/Week_17/Class 28/class28_main.cpp" "3. Section_3/Week_18/Class 29/class29_main.cpp" "3. Section_3/Week_18/Class 29/class29_main.c" "3. Section_3/Week_18/Class_30/class30_main.cpp")

  target_include_directories(${_tgt} PRIVATE "${CLASS_DIR}")

  if(MSVC)
    target_compile_options(${_tgt} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(${_tgt} PRIVATE -Wall -Wextra -Wpedantic)
  endif()

  set_target_properties(${_tgt} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

  # Set startup project
  set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
               PROPERTY VS_STARTUP_PROJECT ${_tgt})

endif()