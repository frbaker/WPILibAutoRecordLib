#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <fmt/format.h>
#include <autoRecordLib/ControllerSnapshot.h>
#include <autoRecordLib/AutonomousRecorder.h>
#include <autoRecordLib/Routine.h>
#include <frc2/command/CommandPtr.h>
#include <functional>
namespace autoRecordLib{
    void writeRoutineToDisk(const std::vector<ControllerSnapshot>& snapshots);
    std::vector<ControllerSnapshot> getRoutineAsVectorFromDisk(std::string path);
    autoRecordLib::Routine getRoutineFromDisk(std::string path);
    void writeRoutineToDisk(AutonomousRecorder recorder);
    frc2::CommandPtr CreateAutonomousRoutine(const std::vector<ControllerSnapshot>& snapshots);
    frc2::CommandPtr CreateAutonomousRoutine(const Routine& routine);
    void RegisterAutoCommands(std::function<void(const ControllerSnapshot&)> playbackAction);
}