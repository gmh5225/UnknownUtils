//===-- PluginLoader.cpp - Implement -load command line option ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the -load <plugin> command line option handler.
//
//===----------------------------------------------------------------------===//

#define DONT_GET_PLUGIN_LOADER_OPTION
#include "unknown/Support/PluginLoader.h"
#include "unknown/Support/DynamicLibrary.h"
#include "unknown/Support/ManagedStatic.h"
#include "unknown/Support/Mutex.h"
#include "unknown/Support/raw_ostream.h"
#include <vector>
using namespace unknown;

static ManagedStatic<std::vector<std::string> > Plugins;
static ManagedStatic<sys::SmartMutex<true> > PluginsLock;

void PluginLoader::operator=(const std::string &Filename) {
  sys::SmartScopedLock<true> Lock(*PluginsLock);
  std::string Error;
  if (sys::DynamicLibrary::LoadLibraryPermanently(Filename.c_str(), &Error)) {
    errs() << "Error opening '" << Filename << "': " << Error
           << "\n  -load request ignored.\n";
  } else {
    Plugins->push_back(Filename);
  }
}

unsigned PluginLoader::getNumPlugins() {
  sys::SmartScopedLock<true> Lock(*PluginsLock);
  return Plugins.isConstructed() ? Plugins->size() : 0;
}

std::string &PluginLoader::getPlugin(unsigned num) {
  sys::SmartScopedLock<true> Lock(*PluginsLock);
  assert(Plugins.isConstructed() && num < Plugins->size() &&
         "Asking for an out of bounds plugin");
  return (*Plugins)[num];
}
