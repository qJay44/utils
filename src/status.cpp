#include "../include/utils/status.hpp"

#include "../include/utils/utils.hpp"
#include "../include/utils/clrp.hpp"

static const std::string statusPositive = clrp::format("Done"  , clrp::ATTRIBUTE::BOLD, clrp::FG::GREEN);
static const std::string statusNegative = clrp::format("Failed", clrp::ATTRIBUTE::BOLD, clrp::FG::RED);

static std::string title;
static std::string what;
static bool started;

void status::start(const std::string& titleArg, const std::string& whatArg) {
  if (started)
    error("An other status is already running ({}: {})", title, what);

  title = titleArg;
  what = whatArg;

  started = true;
  printf("%s [%s]...\r", title.c_str(), what.c_str());
}

void status::update(const std::string& whatArg, const bool& rightAlignment, const size_t width) {
  if (!started)
    error("No status to update");

  std::string msg;
  what = whatArg;

  if (rightAlignment)
    msg = std::format("{} {:>{}}...", title, what, width);
  else
    msg = std::format("{} {:<{}}...", title, what, width);

  printf("%s\r", msg.c_str());
}

void status::end(bool success) {
  if (!started)
    error("No status to end");

  printf("                                                                 \r");

  const char* const endStatus = success ? statusPositive.c_str() : statusNegative.c_str();
  printf("%s [%s] %s\n", title.c_str(), what.c_str(), endStatus);

  started = false;
}

