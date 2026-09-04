#include "autoRecordLib/RoutineHandler.h"
#include <iostream>
#include <autoRecordLib/AutonomousRecorder.h>
#include <frc2/command/Commands.h>
#include <frc2/command/InstantCommand.h>
#include <autoRecordLib/ControllerSnapshot.h>

namespace{
    std::function<void(const autoRecordLib::ControllerSnapshot&)> localPlaybackAction = nullptr;
    static bool commandsRegistered;
}

namespace autoRecordLib{

void writeRoutineToDisk(const std::vector<ControllerSnapshot>& snapshots){
  std::filesystem::create_directories("/home/lvuser/controllerRecordings");

  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  auto tm = *std::localtime(&time);
  char filename[80];
  std::strftime(filename, sizeof(filename), "/home/lvuser/controllerRecordings/recording_%Y%m%d_%H%M%S.csv", &tm);

  std::ofstream file(filename);
  for (const auto& snapshot : snapshots){
    file << snapshot.toString() << "\n";
  }
  file.close();
}

std::vector<ControllerSnapshot> getRoutineAsVectorFromDisk(std::string& path){
    std::vector<ControllerSnapshot> snapshots;
    std::ifstream file(path);

    if(!file.is_open()){
        return snapshots;
    }

    std::string line;
    while (std::getline(file, line)) {
        if(line.empty()) continue;
        std::istringstream iss(line);
        std::string token;
        ControllerSnapshot snapshot;
        try {
            std::getline(iss, token, ','); snapshot.leftX = std::stod(token);
            std::getline(iss, token, ','); snapshot.leftY = std::stod(token);
            std::getline(iss, token, ','); snapshot.rightX = std::stod(token);
            std::getline(iss, token, ','); snapshot.rightY = std::stod(token);
            std::getline(iss, token, ','); snapshot.LT = std::stod(token);
            std::getline(iss, token, ','); snapshot.RT = std::stod(token);
            std::getline(iss, token, ','); snapshot.A = token == "true";
            std::getline(iss, token, ','); snapshot.B = token == "true";
            std::getline(iss, token, ','); snapshot.X = token == "true";
            std::getline(iss, token, ','); snapshot.Y = token == "true";
            std::getline(iss, token, ','); snapshot.LB = token == "true";
            std::getline(iss, token, ','); snapshot.RB = token == "true";
            std::getline(iss, token, ','); snapshot.POV = std::stoi(token);
            
            snapshots.push_back(snapshot);
        } catch (const std::exception& e) {
            std::cout << "Error parsing line: " << line << " - " << e.what() << std::endl;
            continue;
        }
    }
    
    file.close();
    return snapshots;
}

autoRecordLib::Routine getRoutineFromDisk(std::string& path){
    Routine r;
    r.snapshots = getRoutineAsVectorFromDisk(path);
    return r;
}

void writeRoutineToDisk(AutonomousRecorder recorder){
    writeRoutineToDisk(recorder.GetRoutine());
}

frc2::CommandPtr CreateAutonomousRoutine(const std::vector<ControllerSnapshot>& snapshots){
    //return frc2::cmd::Sequence(std::move(commands));
    auto state = std::make_shared<size_t>(0);
    return frc2::FunctionalCommand(
        []{},
        [state, snapshots]{
            if (*state < snapshots.size()) {
                const auto& snapshot = snapshots[*state];

                if(localPlaybackAction != nullptr){
                    localPlaybackAction(snapshot);
                }

                (*state)++;
            }
        },
        [](bool interrupted){
            //Maybe add ability to register onDone auto commands but i dont know if thats necessary
        },
        [state, snapshots] { // IsFinished
                return *state >= snapshots.size();
        }
    ).ToPtr();
    return frc2::InstantCommand([]{}).ToPtr();
}
void RegisterAutoCommands(std::function<void(const ControllerSnapshot&)> playbackAction){
    if(commandsRegistered){
        return;
    }
    commandsRegistered = true;
    localPlaybackAction = playbackAction;
}
}