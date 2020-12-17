
/*
 * Copyright 2019 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <google/protobuf/util/message_differencer.h>
#include <vitis/ai/proto/dpu_model_param.pb.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace google::protobuf;

vitis::ai::proto::DpuModelResult get_msg(const string file) {
  vitis::ai::proto::DpuModelResult msg;
  fstream input(file, ios::in | ios::binary);
  if (!input) {
    cerr << file << " : File not found." << endl;
    abort();
  } else if (!msg.ParseFromIstream(&input)) {
    cerr << "Failed to parse " << file << endl;
  }
  return msg;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "usage: compare_proto <proto_file> <proto_file> " << endl;
    return 1;
  }

  auto msg1 = get_msg(argv[1]);
  // cout << "msg1 = " << msg1.DebugString() << endl;

  auto msg2 = get_msg(argv[2]);
  // cout << "msg2 = " << msg2.DebugString() << endl;

  auto equal = util::MessageDifferencer::Equals(msg1, msg2);
  if (!equal) {
    cout << argv[1] << " and " << argv[2] << " are diff." << endl;
  }

  return equal ? 0 : 1;
}