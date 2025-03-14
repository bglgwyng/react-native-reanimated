#pragma once
#include <reanimated/CSS/config/PropertyInterpolatorsConfig.h>
#include <reanimated/CSS/registry/StaticPropsRegistry.h>
#include <reanimated/Fabric/ShadowTreeCloner.h>
#include <reanimated/Fabric/updates/UpdatesRegistry.h>

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace reanimated {

class UpdatesRegistryManager {
 public:
  UpdatesRegistryManager();

#ifdef ANDROID
  explicit UpdatesRegistryManager(
      const std::shared_ptr<StaticPropsRegistry> &staticPropsRegistry);
#endif

  std::lock_guard<std::mutex> createLock() const;

  // TODO - ensure that other sublibraries can easily hook into this registry
  // manager (e.g. add priority to registries)
  void addRegistry(const std::shared_ptr<UpdatesRegistry> &registry);

  void pauseReanimatedCommits();
  bool shouldReanimatedSkipCommit();
  void unpauseReanimatedCommits();

  void pleaseCommitAfterPause();
  bool shouldCommitAfterPause();
  void cancelCommitAfterPause();
  void removeBatch(const std::vector<Tag> &tags);
  PropsMap collectProps();

#ifdef ANDROID
  bool hasPropsToRevert();
  void collectPropsToRevertBySurface(
      std::unordered_map<SurfaceId, PropsMap> &propsMapBySurface);
  void clearPropsToRevert(SurfaceId surfaceId);
#endif

 private:
  mutable std::mutex mutex_;
  std::atomic<bool> isPaused_;
  std::atomic<bool> shouldCommitAfterPause_;
  std::vector<std::shared_ptr<UpdatesRegistry>> registries_;

#ifdef ANDROID
  PropsToRevertMap propsToRevertMap_;
  const std::shared_ptr<StaticPropsRegistry> staticPropsRegistry_;

  static void addToPropsMap(
      PropsMap &propsMap,
      const ShadowNode::Shared &shadowNode,
      const folly::dynamic &props);
#endif
};

} // namespace reanimated
