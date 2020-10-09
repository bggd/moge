#ifndef MOGE_SRC_APP_MAIN_LOOP_HPP_INCLUDED
#define MOGE_SRC_APP_MAIN_LOOP_HPP_INCLUDED

namespace moge {
namespace app {

class MainLoopBase {
public:
  virtual void onUpdate() = 0;
};

} // namespace app
} // namespace moge

#endif // MOGE_SRC_APP_MAIN_LOOP_HPP_INCLUDED
