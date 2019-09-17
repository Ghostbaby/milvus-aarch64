// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "utils/Status.h"

#include <vector>
#include <memory>

namespace zilliz {
namespace milvus {
namespace engine {

enum class EngineType {
    INVALID = 0,
    FAISS_IDMAP = 1,
    FAISS_IVFFLAT,
    FAISS_IVFSQ8,
    NSG_MIX,
    MAX_VALUE = NSG_MIX,
};

enum class MetricType {
    L2 = 1,
    IP = 2,
};

class ExecutionEngine {
public:

    virtual Status AddWithIds(long n, const float *xdata, const long *xids) = 0;

    virtual size_t Count() const = 0;

    virtual size_t Size() const = 0;

    virtual size_t Dimension() const = 0;

    virtual size_t PhysicalSize() const = 0;

    virtual Status Serialize() = 0;

    virtual Status Load(bool to_cache = true) = 0;

    virtual Status CopyToGpu(uint64_t device_id) = 0;

    virtual Status CopyToCpu() = 0;

    virtual std::shared_ptr<ExecutionEngine> Clone() = 0;

    virtual Status Merge(const std::string& location) = 0;

    virtual Status Search(long n,
                  const float *data,
                  long k,
                  long nprobe,
                  float *distances,
                  long *labels) const = 0;

    virtual std::shared_ptr<ExecutionEngine> BuildIndex(const std::string& location, EngineType engine_type) = 0;

    virtual Status Cache() = 0;

    virtual Status GpuCache(uint64_t gpu_id) = 0;

    virtual Status Init() = 0;

    virtual EngineType IndexEngineType() const = 0;

    virtual MetricType IndexMetricType() const = 0;

    virtual std::string GetLocation() const = 0;
};

using ExecutionEnginePtr = std::shared_ptr<ExecutionEngine>;


} // namespace engine
} // namespace milvus
} // namespace zilliz
