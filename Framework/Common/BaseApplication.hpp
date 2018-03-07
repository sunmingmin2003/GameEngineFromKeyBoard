#pragma once
#include "GfxConfiguration.h"
#include "IApplication.hpp"

namespace My {
class BaseApplication : implements IApplication {
public:
  BaseApplication(GfxConfiguration &cfg);
  virtual int Initialize();
  virtual void Finalize();
  virtual void Tick();
  virtual bool IsQuit();

protected:
  // Flag if need quit the main loop of the application
  static bool m_bQuit;
  GfxConfiguration m_Config;

private:
  // hide the default construct to enforce a configuration
  BaseApplication(){};
};
} // namespace My