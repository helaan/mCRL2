# Authors: Jeroen Keiren
# Copyright: see the accompanying file COPYING or copy at
# https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

#-------------------------------------------------------------------------------
# This file copies the boost headers to the application bundle on MacOSX.
# These headers are needed in order to build the compiling rewriters,
# and this ugly workaround ensures that the bundle remains relocatable.
#-------------------------------------------------------------------------------

if( NOT (APPLE AND MCRL2_SINGLE_BUNDLE))
  return()
endif()

# Following configuration holds for Boost 1.51.0
set( R_MCRL2_BOOST_HEADER_FILES
  boost/assert.hpp
  boost/array.hpp
  boost/bind.hpp
  boost/call_traits.hpp
  boost/checked_delete.hpp
  boost/concept_check.hpp
  boost/config.hpp
  boost/cstdint.hpp
  boost/current_function.hpp
  boost/get_pointer.hpp
  boost/implicit_cast.hpp
  boost/integer_traits.hpp
  boost/is_placeholder.hpp
  boost/iterator.hpp
  boost/lexical_cast.hpp
  boost/limits.hpp
  boost/mem_fn.hpp
  boost/memory_order.hpp
  boost/next_prior.hpp
  boost/noncopyable.hpp
  boost/ref.hpp
  boost/shared_ptr.hpp
  boost/smart_ptr.hpp
  boost/static_assert.hpp
  boost/swap.hpp
  boost/throw_exception.hpp
  boost/type.hpp
  boost/utility.hpp
  boost/visit_each.hpp
)

set ( R_MCRL2_BOOST_HEADER_DIRS
  boost/bind
  boost/concept
  boost/config
  boost/container
  boost/detail
  boost/exception
  boost/functional
  boost/iterator
  boost/mpl
  boost/math
  boost/numeric
  boost/preprocessor
  boost/range
  boost/smart_ptr
  boost/type_traits
  boost/utility
)

message(${Boost_INCLUDE_DIRS})

foreach( hfile ${R_MCRL2_BOOST_HEADER_FILES})
  string(FIND ${hfile} "/" IDX REVERSE)
  install(FILES "${Boost_INCLUDE_DIRS}/${hfile}" DESTINATION "include/boost")
endforeach( hfile ${R_MCRL2_BOOST_HEADER_FILES})

foreach( hdir ${R_MCRL2_BOOST_HEADER_DIRS})
  string(FIND ${hdir} "/" IDX REVERSE)
  install(DIRECTORY "${Boost_INCLUDE_DIRS}/${hdir}" DESTINATION "include/boost")
endforeach( hdir ${R_MCRL2_BOOST_HEADER_DIRS})