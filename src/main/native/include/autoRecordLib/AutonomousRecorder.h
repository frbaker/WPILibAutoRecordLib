#pragma once
#include <vector>
#include "autoRecordLib/ControllerSnapshot.h"
#include <frc/XboxController.h>

namespace autoRecordLib{
    class AutonomousRecorder{
        public:
        AutonomousRecorder();

        void RecordSnapshot(ControllerSnapshot snapshot);
        void RecordSnapshot(frc::XboxController controller);
        void ClearSnapshots();
        std::vector<ControllerSnapshot> GetRoutine();

        private:
        std::vector<ControllerSnapshot> snapshots;

    };
}