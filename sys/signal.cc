//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#include "LDBase/sys/signal.hpp"
#include <signal.h>

namespace LDBase {
namespace sys {

bool Signal::BlockAll()
{
  return OperateAllSignals(SIG_BLOCK);
}

bool Signal::UnblockAll()
{
  return OperateAllSignals(SIG_UNBLOCK);
}

bool Signal::BlockOne(int sig)
{
  return IsBlockable(sig) ? OperateOneSignal(sig, SIG_BLOCK) : false;
}

bool Signal::UnblockOne(int sig)
{
  return IsBlockable(sig) ? OperateOneSignal(sig, SIG_UNBLOCK) : false;
}

bool Signal::IsBlockable(int sig)
{
  return SIGKILL != sig && SIGSTOP != sig;
}

bool Signal::IsBlocked(int sig)
{
  if (IsBlockable(sig))
  {
    sigset_t prev_mask;
    sigemptyset(&prev_mask);
    sigprocmask(SIG_BLOCK, nullptr, &prev_mask);
    return sigismember(&prev_mask, sig);
  }
  return false;
}

bool Signal::OperateAllSignals(int op)
{
  sigset_t mask;
  sigfillset(&mask);
  return 0 == sigprocmask(op, &mask, nullptr);
}

bool Signal::OperateOneSignal(int sig, int op)
{
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, sig);
  return 0 == sigprocmask(op, &mask, nullptr);
}

}   // namespace sys
}   // namespace LDBase
