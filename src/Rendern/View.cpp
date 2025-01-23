#include "View.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

View::View(std::shared_ptr<Data> data)
    : ZuRenderndesMenu(hauptmenu),
      Daten(data),
      Auswahl(data) {
      try {
            log = spdlog::basic_logger_mt("RenderingLogger",
                                          "progam-logs/view-log.txt");
            spdlog::set_level(spdlog::level::debug);
      } catch (const spdlog::spdlog_ex& ex) {
            std::cout << "Log init failed: " << ex.what() << std::endl;
            return;
      }
}

View::~View() {
      SPDLOG_LOGGER_DEBUG(log, "Something!");
}