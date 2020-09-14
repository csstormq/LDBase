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

void Signal::BlockAll()
{
  OperateAllSignals(SIG_BLOCK);
}

void Signal::UnblockAll()
{
  OperateAllSignals(SIG_UNBLOCK);
}

bool Signal::BlockOne(int sig)
{
  if (IsBlockable(sig))
  {
    OperateOneSignal(sig, SIG_BLOCK);
    return true;
  }
  return false;
}

bool Signal::UnblockOne(int sig)
{
  if (IsBlockable(sig))
  {
    OperateOneSignal(sig, SIG_UNBLOCK);
    return true;
  }
  return false;
}

bool Signal::IsBlockable(int sig)
{
  return SIGKILL != sig && SIGSTOP != sig;
}

void Signal::OperateAllSignals(int op)
{
  sigset_t mask;
  sigfillset(&mask);
  sigprocmask(op, &mask, nullptr);
}

void Signal::OperateOneSignal(int sig, int op)
{
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, sig);;
  sigprocmask(op, &mask, nullptr);
}

}   // namespace sys
}   // namespace LDBase
