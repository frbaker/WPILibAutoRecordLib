#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <fmt/format.h>
#include <autoRecordLib/ControllerSnapshot.h>
#include <autoRecordLib/AutonomousRecorder.h>
namespace autoRecordLib{
void writeRoutineToDisk(const std::vector<ControllerSnapshot>& snapshots);
std::vector<ControllerSnapshot> getRoutineFromDisk(std::string path);
void writeRoutineToDisk(AutonomousRecorder& recorder);
}