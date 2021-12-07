#include <sst_config.h>

#include <memory>
#include <sst/core/component.h>
#include <sst/core/interfaces/stdMem.h>

namespace SST {
namespace Bell {
using namespace Interfaces;

class Bell : public Component {
public:
  SST_ELI_REGISTER_COMPONENT(Bell, "bell", "Bell",
                             SST_ELI_ELEMENT_VERSION(1, 0, 0),
                             "Example MMIO device for ringing a bell",
                             COMPONENT_CATEGORY_MEMORY)

  SST_ELI_DOCUMENT_PARAMS()
  SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS({"iface",
                                       "Interface into memory subsystem",
                                       "SST::Interfaces::StandardMem"})

  class setBell : public StandardMem::RequestHandler {
  public:
    setBell(Output *out) : StandardMem::RequestHandler(out) {}

    void handle(Interfaces::StandardMem::Write *write) override {
      if (write->data.front() > 0) {
        out->output("Christmas\a are ringing!");
        out->flush();
      }
    }
  };

  Bell(ComponentId_t id, Params &params)
      : Component(id), out_("", 0, 0, Output::STDOUT),
        handler_(this, &Bell::handleEvent), handlers_(&out_) {

    auto *tc = getTimeConverter("1GHz");
    iface_ = loadUserSubComponent<SST::Interfaces::StandardMem>(
        "iface", ComponentInfo::SHARE_NONE, tc, &handler_);
    auto vanadisMagicValue = 0xFFFFFFF0;
    iface_->setMemoryMappedAddressRegion(vanadisMagicValue, 1);

    registerAsPrimaryComponent();
    primaryComponentDoNotEndSim();

  }

  void init(unsigned int phase) override { iface_->init(phase); }
  void setup() override { iface_->setup(); }

private:
  void handleEvent(StandardMem::Request *req) {
    req->handle(&handlers_);
    primaryComponentOKToEndSim();
    delete req;
  }

  Output out_;
  StandardMem *iface_;
  StandardMem::Handler<Bell> handler_;
  setBell handlers_;
};
} // namespace Bell
} // namespace SST
