#include <riscv/sim.h>

// Copied from spike main.
// TODO: This should really be provided in libriscv
static std::vector<std::pair<reg_t, mem_t*>> make_mems(const std::vector<mem_cfg_t> &layout)
{
  std::vector<std::pair<reg_t, mem_t*>> mems;
  mems.reserve(layout.size());
  for (const auto &cfg : layout) {
    mems.push_back(std::make_pair(cfg.base, new mem_t(cfg.size)));
  }
  return mems;
}

int main()
{
  std::vector<mem_cfg_t> mem_cfg { mem_cfg_t(0x80000000, 0x10000000) };
  std::vector<int> hartids = {0};
  cfg_t cfg(std::make_pair(0, 0),
            nullptr,
            "rv64gcv",
            "MSU",
            "vlen:128,elen:64",
            false,
            endianness_little,
            false,
            16,
            mem_cfg,
            hartids,
            false,
	    default_dm_config);
  std::vector<std::pair<reg_t, abstract_device_t*>> plugin_devices;
  std::vector<std::string> htif_args {"pk", "hello"};
  std::vector<std::pair<reg_t, mem_t*>> mems = make_mems(cfg.mem_layout());
  sim_t sim(&cfg, false,
            mems,
            plugin_devices,
            htif_args,
            default_dm_config,
            nullptr,
            true,
            nullptr,
            false,
            nullptr);
  sim.run();
}
