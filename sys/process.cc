//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#include "LDBase/sys/process.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

namespace LDBase {
namespace sys {

int Process::GetSelfProcessID()
{
  return static_cast<int>(getpid());
}

int Process::GetParentProcessID()
{
  return static_cast<int>(getppid());
}

int Process::GetSelfProcessGroupID()
{
  return GetProcessGroupIDOf(0);
}

int Process::GetProcessGroupIDOf(int pid)
{
  return static_cast<int>(getpgid(static_cast<pid_t>(pid)));
}

int Process::SetDefaultProcessGroupID()
{
  const auto success = 0 == setpgid(0, 0);
  return success ? GetSelfProcessID() : -1;
}

int Process::Wait(int *status)
{
  int pid = 0;
  do
  {
    pid = wait(status);
  } while (-1 == pid && EINTR == errno);

  if (nullptr != status && WIFEXITED(*status))
  {
    *status = WEXITSTATUS(*status);
  }
  return pid;
}

bool Process::WaitForAllChildren()
{
  while (Wait(nullptr) > 0)
  {
  }
  return ECHILD == errno;
}

}   // namespace sys
}   // namespace LDBase
