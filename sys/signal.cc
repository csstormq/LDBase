//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License,
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#include "LDBase/sys/signal.hpp"
#include <signal.h>

namespace LDBase {
namespace sys {

void Signal::BlockAllBlockableSignals()
{
  OperateAllBlockableSignals(SIG_BLOCK);
}

void Signal::UnblockAllBlockableSignals()
{
  OperateAllBlockableSignals(SIG_UNBLOCK);
}

bool Signal::BlockSignal(int sig)
{
  if (IsBlockableSignal(sig))
  {
      OperateOneBlockableSignal(sig, SIG_BLOCK);
      return true;
  }
  return false;
}

bool Signal::UnblockSignal(int sig)
{
  if (IsBlockableSignal(sig))
  {
      OperateOneBlockableSignal(sig, SIG_UNBLOCK);
      return true;
  }
  return false;
}

bool Signal::IsBlockableSignal(int sig)
{
  return SIGKILL != sig && SIGSTOP != sig;
}

void Signal::OperateAllBlockableSignals(int op)
{
  sigset_t mask;
  sigfillset(&mask);
  sigprocmask(op, &mask, nullptr);
}

void Signal::OperateOneBlockableSignal(int sig, int op)
{
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, sig);;
  sigprocmask(op, &mask, nullptr);
}

}   // namespace sys
}   // namespace LDBase
