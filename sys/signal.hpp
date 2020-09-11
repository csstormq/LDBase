//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _LDBASE_SYS_SIGNAL_H_
#define _LDBASE_SYS_SIGNAL_H_

namespace LDBase {
namespace sys {

class Signal
{
public:
  /**
   * @brief Block all blockable signals.
   */
  static void BlockAll();

  /**
   * @brief Unblock all blockable signals.
   */
  static void UnblockAll();

  /**
   * @brief Block a signal specified by sig.
   * @param sig Signal number to block.
   * @return True on success, false if the signal can't be blocked.
   */
  static bool BlockOne(int sig);

  /**
   * @brief Unblock a signal specified by sig.
   * @param sig Signal number to unblock.
   * @return true on success, false if the signal can't be unblocked.
   */
  static bool UnblockOne(int sig);

  /**
   * @brief Returns whether a signal specified by sig is blockable.
   * @param sig Signal number.
   * @return true if the signal can be blocked, otherwise false.
   */
  static bool IsBlockable(int sig);

private:
  static void OperateAllSignals(int op);
  static void OperateOneSignal(int sig, int op);
};

}   // namespace sys
}   // namespace LDBase

#endif  // _LDBASE_SYS_SIGNAL_H_
