#pragma once

#include <reanimated/CSS/config/CSSKeyframesConfig.h>
#include <reanimated/CSS/config/common.h>
#include <reanimated/CSS/easing/EasingFunctions.h>

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace reanimated {

enum class AnimationDirection { Normal, Reverse, Alternate, AlternateReverse };
enum class AnimationFillMode { None, Forwards, Backwards, Both };
enum class AnimationPlayState { Running, Paused };

struct CSSAnimationSettings {
  double duration;
  EasingFunction easingFunction;
  double delay;
  double iterationCount;
  AnimationDirection direction;
  AnimationFillMode fillMode;
  AnimationPlayState playState;
};

struct CSSAnimationConfig {
  std::string animationName;
  CSSAnimationSettings settings;
};

struct PartialCSSAnimationSettings {
  std::optional<double> duration;
  std::optional<EasingFunction> easingFunction;
  std::optional<double> delay;
  std::optional<double> iterationCount;
  std::optional<AnimationDirection> direction;
  std::optional<AnimationFillMode> fillMode;
  std::optional<AnimationPlayState> playState;
};

double getIterationCount(jsi::Runtime &rt, const jsi::Object &settings);

AnimationDirection getDirection(jsi::Runtime &rt, const jsi::Object &settings);

AnimationFillMode getFillMode(jsi::Runtime &rt, const jsi::Object &settings);

AnimationPlayState getPlayState(jsi::Runtime &rt, const jsi::Object &settings);

CSSAnimationSettings parseCSSAnimationSettings(
    jsi::Runtime &rt,
    const jsi::Value &settings);

CSSAnimationConfig parseCSSAnimationConfig(
    jsi::Runtime &rt,
    const jsi::Value &config);

PartialCSSAnimationSettings parsePartialCSSAnimationSettings(
    jsi::Runtime &rt,
    const jsi::Value &partialSettings);

} // namespace reanimated
