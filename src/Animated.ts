import { maybeBuild } from './createAnimatedComponent';
import { LayoutAnimationFunction, LayoutAnimationType } from './reanimated2';
import { shouldBeUseWeb } from './reanimated2/PlatformChecker';
import {
  configureLayoutAnimations as configureLayoutAnimations$,
  enableLayoutAnimations,
} from './reanimated2/core';

export {
  addWhitelistedNativeProps,
  addWhitelistedUIProps,
} from './ConfigHelper';
export {
  default as createAnimatedComponent,
  maybeBuild,
} from './createAnimatedComponent';

export type { SharedValue } from './reanimated2/commonTypes';
export { ReanimatedFlatList as FlatList } from './reanimated2/component/FlatList';
export { AnimatedImage as Image } from './reanimated2/component/Image';
export { AnimatedScrollView as ScrollView } from './reanimated2/component/ScrollView';
export { AnimatedText as Text } from './reanimated2/component/Text';
export { AnimatedView as View } from './reanimated2/component/View';
export type { AnimateStyle } from './reanimated2/helperTypes';

export function configureLayoutAnimations(
  viewTag: number,
  type: LayoutAnimationType,
  config: LayoutAnimationFunction | Keyframe,
  sharedTransitionTag = ''
): void {
  if (!shouldBeUseWeb()) {
    enableLayoutAnimations(true, false);
  }

  configureLayoutAnimations$(
    viewTag,
    type,
    maybeBuild(config),
    sharedTransitionTag
  );
}
