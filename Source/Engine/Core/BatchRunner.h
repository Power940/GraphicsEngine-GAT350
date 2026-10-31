#pragma once
#include <string>

bool RunBatch(const std::string& batchFilePathAndName, const std::vector<std::string>& args, bool closeTerminalOnFinish = true, bool relativePathing = true, const std::string& workingDirectory = "");