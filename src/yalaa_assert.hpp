#ifndef __AFFINEASSERT_HPP__
#define __AFFINEASSERT_HPP__

#include "assert.h"

#ifndef NDEBUG
#include <iostream>
#define YALAA_ASSERT(cond,msg)						\
  do {									\
  if(! (cond) ) {							\
      std::cerr << "YALAA_ASSERT '" #cond " failed at "		\
		<< __FILE__ << ":" << __LINE__ << std::endl		\
		<< msg << std::endl;					\
      std::exit(EXIT_FAILURE);						\
  }                                                                     \
  } while(false)
#else
#define YALAA_ASSERT(cond,msg) do {		\
      } while(false)
#endif

#endif /*__AFFINEASSERT_HPP__*/
