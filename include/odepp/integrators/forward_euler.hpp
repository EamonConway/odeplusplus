#ifndef ODEPP_INTEGRATORS_FE_HPP
#define ODEPP_INTEGRATORS_FE_HPP
#include "odepp/types.hpp"
#include <utility>
namespace odepp {
namespace integrator {
struct forward_euler_fn {
public:
  template <class State, class Fn, class... FnArgs>
  [[nodiscard("State must be used")]] State
  operator()(Fn &&f, const RealType dt, RealType &t, const State &y0,
             FnArgs &&...args) const {
    auto y = y0;
    auto fn = f(t, y, std::forward<FnArgs>(args)...);

    if constexpr (std::is_floating_point_v<State>) {
      y += dt * fn;
    } else {
      for (std::size_t i = 0; i < fn.size(); ++i) {
        y.at(i) += dt * fn[i];
      }
    }
    t += dt;
    return y;
  }
};

inline constexpr forward_euler_fn forward_euler{};
} // namespace integrator
} // namespace odepp
#endif
