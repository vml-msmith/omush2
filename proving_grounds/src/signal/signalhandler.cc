/**
 * \file signalhandler.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "signal/signalhandler.h"
#include <signal.h>

namespace omush {
namespace signal {
/// Create the delegates_ static variable.
SignalDelegateMap SignalHandler::delegates_;

void SignalHandler::registerDelegate(SignalHandlerDelegate* delegate,
                                     int signal) {
  delegates_.insert(SignalDelegatePair(signal, delegate));
}

void SignalHandler::signalHandler(int signum) {
  std::pair<SignalDelegateMap::iterator, SignalDelegateMap::iterator> ret;
  ret = delegates_.equal_range(signum);

  for (SignalDelegateMap::iterator it = ret.first;
       it != ret.second;
       ++it) {
      (it->second)->handleSignal(signum);
  }
}

void SignalHandler::setupSignalHandling() {
  ::signal(SIGINT, SignalHandler::signalHandler);
}

}  // namespace signal
}  // namespace omush
