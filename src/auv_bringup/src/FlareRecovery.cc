// Dynamic SAUVC flare with a floor pivot and simulation-time recovery.
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <gz/common/Console.hh>
#include <gz/plugin/Register.hh>
#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>
#include <gz/sim/Util.hh>
#include <gz/sim/components/ContactSensorData.hh>
#include <gz/sim/components/Collision.hh>
#include <gz/sim/components/Name.hh>
#include <gz/sim/components/ParentEntity.hh>
#include <gz/sim/components/Pose.hh>
#include <gz/sim/components/JointPositionReset.hh>
#include <gz/sim/components/JointVelocityReset.hh>
#include <sdf/Element.hh>
#include "FlareRecoveryState.hh"

namespace sauvc {
class FlareRecovery final : public gz::sim::System,
    public gz::sim::ISystemConfigure, public gz::sim::ISystemPreUpdate,
    public gz::sim::ISystemReset {
 public:
  void Configure(const gz::sim::Entity &_entity,
      const std::shared_ptr<const sdf::Element> &_sdf,
      gz::sim::EntityComponentManager &_ecm, gz::sim::EventManager &) override {
    model=gz::sim::Model(_entity);
    link=gz::sim::Link(model.LinkByName(_ecm,"link"));
    if (link.Entity()==gz::sim::kNullEntity) {
      gzerr << "SAUVC recovery: missing flare link\n"; return;
    }
    initial=gz::sim::worldPose(_entity,_ecm);
    pivot=model.JointByName(_ecm,"floor_pivot");
    if (_sdf->HasElement("robot_name")) robotName=_sdf->Get<std::string>("robot_name");
    if (_sdf->HasElement("reset_seconds")) state.duration=_sdf->Get<double>("reset_seconds");
    if (_sdf->HasElement("tip_torque")) tipTorque=_sdf->Get<double>("tip_torque");
    valid=std::isfinite(state.duration) && state.duration>0 && std::isfinite(tipTorque) && tipTorque>=0;
    state.Reset();
    if (valid) gzmsg << "SAUVC flare recovery active: " << model.Name(_ecm)
      << ", reset=" << state.duration << " s sim time\n";
  }
  void Reset(const gz::sim::UpdateInfo &, gz::sim::EntityComponentManager &_ecm) override {
    state.Reset();
    if(valid) Restore(_ecm);
  }
  void PreUpdate(const gz::sim::UpdateInfo &_info,
      gz::sim::EntityComponentManager &_ecm) override {
    if (!valid || _info.paused) return;
    // Harmonic Contact system stores ContactSensorData on COLLISION entities,
    // not on sensor entities. Match Collision to avoid visuals with the same name.
    for (std::size_t i=0;i<collisions.size();++i)
      if(collisions[i]==gz::sim::kNullEntity)
        collisions[i]=_ecm.EntityByComponents(gz::sim::components::Collision(),
          gz::sim::components::Name(i==0 ? "body" : "golf_ball_tip"),
          gz::sim::components::ParentEntity(link.Entity()));
    if(robot==gz::sim::kNullEntity || !_ecm.HasEntity(robot))
      robot=_ecm.EntityByComponents(gz::sim::components::Name(robotName));
    bool contact=false;
    for (auto sensor:collisions) {
      if (sensor==gz::sim::kNullEntity) continue;
      if (const auto *data=_ecm.Component<gz::sim::components::ContactSensorData>(sensor)) {
        for(const auto &c:data->Data().contact()) {
          if (IsRobot(c.collision1().id(),_ecm) || IsRobot(c.collision2().id(),_ecm)) {
            contact=true; break;
          }
        }
      }
    }
    const double now=std::chrono::duration<double>(_info.simTime).count();
    const auto step=state.Step(now,contact);
    if (step.hit) {
      gz::math::Vector3d away(1,0,0);
      if(robot!=gz::sim::kNullEntity) {
        away=initial.Pos()-gz::sim::worldPose(robot,_ecm).Pos(); away.Z(0);
        if(away.Length()<1e-6) away=gz::math::Vector3d(1,0,0);
        away.Normalize();
      }
      torque=gz::math::Vector3d(0,0,1).Cross(away)*tipTorque;
      kickUntil=now+0.12;
      gzmsg << "SAUVC " << model.Name(_ecm) << " hit by " << robotName << "; falling\n";
    }
    if (!step.free) {
      Restore(_ecm);
      if(step.restore) gzmsg << "SAUVC " << model.Name(_ecm) << " restored after " << state.duration << " s\n";
    } else if (now<kickUntil) {
      // Small finite-duration torque guarantees a visible tip after a real contact.
      link.AddWorldWrench(_ecm,gz::math::Vector3d::Zero,torque);
    }
  }
 private:
  bool IsRobot(gz::sim::Entity e,const gz::sim::EntityComponentManager &ecm) const {
    for(int i=0;i<16 && e!=gz::sim::kNullEntity;++i) {
      if(e==robot && robot!=gz::sim::kNullEntity) return true;
      const auto *p=ecm.Component<gz::sim::components::ParentEntity>(e);
      if(!p) break;
      e=p->Data();
    }
    return false;
  }
  void Restore(gz::sim::EntityComponentManager &ecm) {
    model.SetWorldPoseCmd(ecm,initial);
    if (pivot!=gz::sim::kNullEntity) {
      ecm.SetComponentData<gz::sim::components::JointPositionReset>(pivot,std::vector<double>{0,0,0});
      ecm.SetComponentData<gz::sim::components::JointVelocityReset>(pivot,std::vector<double>{0,0,0});
    }
    link.SetLinearVelocity(ecm,gz::math::Vector3d::Zero);
    link.SetAngularVelocity(ecm,gz::math::Vector3d::Zero);
  }
  gz::sim::Model model{gz::sim::kNullEntity};
  gz::sim::Link link{gz::sim::kNullEntity};
  std::array<gz::sim::Entity,2> collisions{gz::sim::kNullEntity,gz::sim::kNullEntity};
  gz::sim::Entity robot{gz::sim::kNullEntity}, pivot{gz::sim::kNullEntity};
  gz::math::Pose3d initial;
  gz::math::Vector3d torque{0,0,0};
  std::string robotName{"ORCA_V3"};
  RecoveryState state;
  double kickUntil{0}, tipTorque{0.15};
  bool valid{false};
};
}
GZ_ADD_PLUGIN(sauvc::FlareRecovery,gz::sim::System,
  gz::sim::ISystemConfigure,gz::sim::ISystemPreUpdate,gz::sim::ISystemReset)
GZ_ADD_PLUGIN_ALIAS(sauvc::FlareRecovery,"sauvc::FlareRecovery")
