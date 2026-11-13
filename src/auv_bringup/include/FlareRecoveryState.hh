#ifndef SAUVC_FLARE_RECOVERY_STATE_HH
#define SAUVC_FLARE_RECOVERY_STATE_HH
#include <cmath>
namespace sauvc {
struct RecoveryStep { bool hit{false}; bool restore{false}; bool free{false}; };
class RecoveryState {
 public:
  double duration{2.0}, clearDuration{0.25};
  void Reset() { falling=false; armed=false; clearSince=-1; last=-1; hitTime=0; }
  RecoveryStep Step(double now, bool contact) {
    RecoveryStep out;
    if (last>=0 && now<last) { Reset(); out.restore=true; }
    last=now;
    if (falling) {
      if (now-hitTime+1e-9>=duration) {
        falling=false; armed=false; clearSince=-1; out.restore=true;
      } else out.free=true;
      return out;
    }
    if (!armed) {
      if (contact) clearSince=-1;
      else if (clearSince<0) clearSince=now;
      else if (now-clearSince+1e-9>=clearDuration) armed=true;
    }
    if (armed && contact) {
      falling=true; armed=false; hitTime=now;
      out.hit=true; out.free=true;
    }
    return out;
  }
 private:
  bool falling{false}, armed{false};
  double hitTime{0}, clearSince{-1}, last{-1};
};
}
#endif
