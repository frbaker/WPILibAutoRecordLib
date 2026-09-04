#include "autoRecordLib/AutonomousRecorder.h"
#include "autoRecordLib/ControllerSnapshot.h"

namespace autoRecordLib{

AutonomousRecorder::AutonomousRecorder(){
    
}

void AutonomousRecorder::RecordSnapshot(ControllerSnapshot snapshot){
    snapshots.push_back(snapshot);
}
void AutonomousRecorder::RecordSnapshot(frc::XboxController& controller){
    ControllerSnapshot snapshot{controller.GetLeftX(), controller.GetLeftY(), controller.GetRightX(), controller.GetRightY(), controller.GetLeftTriggerAxis(), controller.GetRightTriggerAxis(), controller.GetAButton(), controller.GetBButton(), controller.GetXButton(), controller.GetYButton(), controller.GetLeftBumperButton(), controller.GetRightBumperButton(), controller.GetPOV()};
    snapshots.push_back(snapshot);
}

void AutonomousRecorder::ClearSnapshots(){
    snapshots.clear();
}

std::vector<ControllerSnapshot> AutonomousRecorder::GetRoutine(){
    return snapshots;
}

}