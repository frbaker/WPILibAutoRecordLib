#pragma once
#include <vector>
#include "autoRecordLib/ControllerSnapshot.h"

namespace autoRecordLib{
    class AutonomousRecorder{
        public:
        AutonomousRecorder();

        void RecordSnapshot(ControllerSnapshot snapshot);
        void ClearSnapshots();
        std::vector<ControllerSnapshot> GetRoutine();

        private:
        std::vector<ControllerSnapshot> snapshots;

    };
}