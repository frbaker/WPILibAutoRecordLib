#include "autoRecordLib/AutonomousRecorder.h"
#include "autoRecordLib/ControllerSnapshot.h"

namespace autoRecordLib{

AutonomousRecorder::AutonomousRecorder(){
    
}

void AutonomousRecorder::RecordSnapshot(ControllerSnapshot snapshot){
    snapshots.push_back(snapshot);
}

void AutonomousRecorder::ClearSnapshots(){
    snapshots.clear();
}

}