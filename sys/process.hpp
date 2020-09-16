//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020, csstormq. Distributed under the BSD 3-Clause License.
// (See accompanying file LICENSE or copy at
// https://github.com/csstormq/LDBase/blob/master/LICENSE)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef LDBASE_SYS_PROCESS_HPP
#define LDBASE_SYS_PROCESS_HPP

namespace LDBase {
namespace sys {

class Process
{
public:
  /**
   * @brief Returns the process ID of calling process.
   * @return On success, returns the positive integer process ID.
   *         On error, -1 is returned, and errno is set appropriately.
   */
  static int GetSelfProcessID();

  /**
   * @brief Returns the process ID of calling process's parent.
   * @return On success, returns the positive integer process ID.
   *         On error, -1 is returned, and errno is set appropriately.
   */
  static int GetParentProcessID();

  /**
   * @brief Returns the process group ID of calling process.
   * @return On success, returns the positive integer process group ID.
   *         On error, -1 is returned, and errno is set appropriately.
   */
  static int GetSelfProcessGroupID();

  /**
   * @brief Returns the process group ID of the process specified by pid.
   * @param pid Process ID.
   *            If pid is zero, the process ID of the calling process is used.
   * @return On success, returns the positive integer process group ID.
   *         On error, -1 is returned, and errno is set appropriately.
   */
  static int GetProcessGroupIDOf(int pid);

  /**
   * @brief Set the process group ID of calling process to itself process ID.
   * @return On success, returns the positive integer process group ID.
   *         On error, -1 is returned, and errno is set appropriately.
   */
  static int SetDefaultProcessGroupID();

  /**
   * @brief Waits for any child process to terminate.
   *        If a child has already terminated, then this call return immediately.
   *        Otherwise, it blocks until either a child terminated. That is,
   *        if interrupted by signals, this call restarts waiting automatically.
   * @param status The exit code of the terminated child. status is valid iff
   *               the child terminated normally, via a call to exit or returning
   *               from the main routine.
   * @return On success, returns the process ID of a terminated child.
   *         On error, -1 is returned, and errno is set appropriately.
   */
  static int Wait(int *status);

  /**
   * @brief Waits for all child processes to terminate.
   * @return On success, return true. That is, there are no child processes or
   *         all child processes has been reaped successfully.
   *         On error, false is returned, and errno is set appropriately.
   */
  static bool WaitForAllChildren();
};

}   // namespace sys
}   // namespace LDBase

#endif  // LDBASE_SYS_PROCESS_HPP
