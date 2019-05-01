# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindReadline
-------

Finds the Readline library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``Readline::Readline``
  The Readline library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``Readline_FOUND``
  True if the system has the Readline library.
``Readline_INCLUDE_DIRS``
  Include directories needed to use Readline.
``Readline_LIBRARIES``
  Libraries needed to link to Readline.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``Readline_INCLUDE_DIR``
  The directory containing ``readline/readline.h``.
``Readline_LIBRARY``
  The path to the Readline library.

#]=======================================================================]

find_path(Readline_INCLUDE_DIR "readline/readline.h")
find_library(Readline_LIBRARY readline)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Readline
  FOUND_VAR Readline_FOUND
  REQUIRED_VARS
    Readline_LIBRARY
    Readline_INCLUDE_DIR
  VERSION_VAR Foo_VERSION
)

if(Readline_FOUND)
  if(NOT TARGET Readline::Readline)
    add_library(Readline::Readline UNKNOWN IMPORTED)
	set_target_properties(Readline::Readline PROPERTIES
	  IMPORTED_LOCATION ${Readline_LIBRARY}
	  INTERFACE_INCLUDE_DIRECTORIES ${Readline_INCLUDE_DIR}
	)
  endif()
endif()
