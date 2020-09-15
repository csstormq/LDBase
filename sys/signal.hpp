//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_SYS_SIGNAL_HPP
#define LDBASE_SYS_SIGNAL_HPP

namespace LDBase {
namespace sys {

class Signal
{
public:
  /**
   * @brief Block all blockable signals.
   * @return true on success, otherwise false.
   */
  static bool BlockAll();

  /**
   * @brief Unblock all blockable signals.
   * @return true on success, otherwise false.
   */
  static bool UnblockAll();

  /**
   * @brief Block a signal specified by sig.
   * @param sig Signal number to block.
   * @return true on success, false if the signal can't be blocked or failed.
   */
  static bool BlockOne(int sig);

  /**
   * @brief Unblock a signal specified by sig.
   * @param sig Signal number to unblock.
   * @return true on success, false if the signal can't be unblocked or failed.
   */
  static bool UnblockOne(int sig);

  /**
   * @brief Returns whether a signal specified by sig is blockable.
   * @param sig Signal number.
   * @return true if the signal can be blocked, otherwise false.
   */
  static bool IsBlockable(int sig);

  /**
   * @brief Returns whether a signal specified by sig has been blocked.
   * @param sig Signal number.
   * @return true if the signal has been blocked, 
   *         false if the signal can't be blocked or is not blocked or failed.
   */
  static bool IsBlocked(int sig);

  /**
   * @brief Install a signal handler function (handler) that is called
   *        asynchronously, interrupting the current control flow,
   *        whenever the process receives a signal specified by sig.
   *        And provide behavior compatible with BSD signal semantics
   *        by making certain system calls restartable across signals.
   * @param sig Specifies the signal and can be any valid signal except
   *            SIGKILL and SIGSTOP.
   * @param hanlder Signal handler function to install.
   * @return On success, return true.
   *         On error, false is returned, and errno is set appropriately.
   */
  static bool SetSignalHanlder(int sig, void (*hanlder)(int));

private:
  static bool OperateAllSignals(int op);
  static bool OperateOneSignal(int sig, int op);
};

}   // namespace sys
}   // namespace LDBase

#endif  // LDBASE_SYS_SIGNAL_HPP
