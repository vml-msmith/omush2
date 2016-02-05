/**
 * \file signalhandler.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_SIGNAL_SIGNALHANDLER_H_
#define OMUSH_HDRS_OMUSH_SIGNAL_SIGNALHANDLER_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>
#include <utility>

namespace omush {

namespace signal {
/**
 * Delegatge interface for any object that needs to handle signals.
 */
class SignalHandlerDelegate {
 public:
  virtual void handleSignal(int signal) = 0;
};

/**
 * Multimap holding sginal -> delegate.
 */
typedef std::multimap<int, SignalHandlerDelegate*> SignalDelegateMap;

/**
 * Pair holding singal -> delegate.
 */
typedef std::pair<int, SignalHandlerDelegate*> SignalDelegatePair;

/**
 * Static class that handles catching signals.
 */
class SignalHandler {
 public:
  /**
   * Register an instance of SignalHandlerDelegate to receive siginals.
   *
   * @param delegate   Instance of SiginalHandlerDelegate that will receive the
   *                  signal.
   * @param signal     The signal that the delegate will respond to.
   */
  static void registerDelegate(SignalHandlerDelegate*, int);

  /**
   * Register any siginals we care about in the application. Those siginals
   * will be caught by signalHandler().
   */
  static void setupSignalHandling();

  /**
   * Method to intercept singals. Registered by setupSiginalHandling().
   *
   * Will call handleSignal() on any SignalHandlerDelegate that has registered
   * with signum. Signum is passed to handleSignal() so the
   * SignalHandlerDelegate knows how to handle it.
   *
   * @param signum The siginal caught by the class.
   */
  static void signalHandler(int signum);

 private:
  static SignalDelegateMap delegates_;
  SignalHandler(const SignalHandler&);
  void operator=(const SignalHandler&);
  SignalHandler() {}
  ~SignalHandler() {}
};

}  // namespace signal
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_SIGNAL_SIGNALHANDLER_H_
