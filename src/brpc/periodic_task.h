// Copyright (c) 2018 brpc authors.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Authors: Ge,Jun (gejun@baidu.com)

#ifndef BRPC_HEALTH_CHECK_MANAGER_H
#define BRPC_HEALTH_CHECK_MANAGER_H

namespace brpc {


// Override DoPeriodicTask() with code that needs to be periodically run. If
// the task is completed, the method should return false; Otherwise the method
// should return true and set `next_abstime' to the time that the task should
// be run next time.
// Each call to DoPeriodicTask() is run in a separated bthread which can be
// suspended. To preserve states between different calls, put the states as
// fields of (subclass of) PeriodicTask.
// If any error occurs or DoPeriodicTask() returns false, the task is called
// with DoPeriodicTask(NULL) and will not be scheduled anymore.
class PeriodicTask {
public:
    virtual ~PeriodicTask();
    virtual bool DoPeriodicTask(timespec* next_abstime) = 0;
};

class PeriodicTaskManager {
public:
    static void StartTaskAt(PeriodicTask* task, const timespec& abstime);
};


} // namespace brpc

#endif  // BRPC_HEALTH_CHECK_MANAGER_H
