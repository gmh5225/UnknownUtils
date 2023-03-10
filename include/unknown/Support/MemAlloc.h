//===- MemAlloc.h - Memory allocation functions -----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
/// \file
///
/// This file defines counterparts of C library allocation functions defined in
/// the namespace 'std'. The new allocation functions crash on allocation
/// failure instead of returning null pointer.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_MEMALLOC_H
#define LLVM_SUPPORT_MEMALLOC_H

#include "unknown/Support/Compiler.h"
#include "unknown/Support/ErrorHandling.h"
#include <cstdlib>

namespace unknown {

LLVM_ATTRIBUTE_RETURNS_NONNULL inline void *safe_malloc(size_t Sz) {
  void *Result = std::malloc(Sz);
  //gmh delete
  //if (Result == nullptr)
    //report_bad_alloc_error("Allocation failed");
  return Result;
}

LLVM_ATTRIBUTE_RETURNS_NONNULL inline void *safe_calloc(size_t Count,
                                                        size_t Sz) {
  void *Result = std::calloc(Count, Sz);
  //gmh delete
  //if (Result == nullptr)
    //report_bad_alloc_error("Allocation failed");
  return Result;
}

LLVM_ATTRIBUTE_RETURNS_NONNULL inline void *safe_realloc(void *Ptr, size_t Sz) {
  void *Result = std::realloc(Ptr, Sz);
  //gmh delete
  //if (Result == nullptr)
    //report_bad_alloc_error("Allocation failed");
  return Result;
}

}
#endif
