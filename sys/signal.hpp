//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License,
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
  static void BlockAllBlockableSignals();
  static void UnblockAllBlockableSignals();
  static bool BlockSignal(int sig);
  static bool UnblockSignal(int sig);
  static bool IsBlockableSignal(int sig);

private:
  static void OperateAllBlockableSignals(int op);
  static void OperateOneBlockableSignal(int sig, int op);
};

}   // namespace sys
}   // namespace LDBase

#endif  // _LDBASE_SYS_SIGNAL_H_
