#pragma once
#include <vector>
#include "autoRecordLib/ControllerSnapshot.h"

namespace autoRecordLib{
    class AutonomousRecorder{
        public:
        AutonomousRecorder();

        void RecordSnapshot(ControllerSnapshot snapshot);
        void ClearSnapshots();

        private:
        std::vector<ControllerSnapshot> snapshots;

    };
}