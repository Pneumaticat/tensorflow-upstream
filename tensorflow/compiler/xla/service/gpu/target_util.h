/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_COMPILER_XLA_SERVICE_GPU_TARGET_UTIL_H_
#define TENSORFLOW_COMPILER_XLA_SERVICE_GPU_TARGET_UTIL_H_

#include <string>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/Module.h"
#include "tensorflow/compiler/xla/xla_data.pb.h"


namespace xla {
namespace gpu {

// Enumeration to get target specific function information.
enum class TargetFunctionID {
  kShflDownF32 = 0,
  kShflDownI32,
  kThreadIdx,
  kThreadIdy,
  kThreadIdz,
  kBlockIdx,
  kBlockIdy,
  kBlockIdz,
  kBarrierId,
  kPow,
  kErfcinv,
  kLog,
  kLog1p,
  kSin,
  kCos,
  kExp,
  kExpm1,
  kSqrt,
  kRsqrt,
  kAtan2,
  kFmod,
  kRound,
};

// Emits a call to the specified target function  with the given operands.
// Target function can either be an intrinsic or a device function.

// Overloaded intrinsics (for example, "minnum") must include a type
// in overloaded_types  for each overloaded type. Typically, overloaded
// intrinsics have only a single overloaded type.
llvm::Value* EmitCallToTargetFunction(
    TargetFunctionID function_id, absl::Span<llvm::Value* const> operands,
    absl::Span<const PrimitiveType> input_types, PrimitiveType output_type,
    absl::Span<const llvm::Attribute::AttrKind> attributes,
    absl::Span<llvm::Type* const> overloaded_types, llvm::IRBuilder<>* b);

}  // namespace gpu
}  // namespace xla

#endif  // TENSORFLOW_COMPILER_XLA_SERVICE_GPU_TARGET_UTIL_H_
