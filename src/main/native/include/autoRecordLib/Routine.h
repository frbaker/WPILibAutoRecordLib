#include <autoRecordLib/ControllerSnapshot.h>
#include <vector>
namespace autoRecordLib{
struct Routine{
    std::vector<ControllerSnapshot> snapshots;
};
}