#include "application.hpp"

#include "networkmanager.hpp"

int main(int argc, char **argv) {
#if 0
  try {
    network::networkmanager manager;

    network::networkrequest request;
    request.url = "http://ifconfig.me/";
    request.method = "GET";
    request.callback = [](const std::string &response, long status_code) {
      if (status_code == 200) {
        std::cout << "Public IP: " << response << std::endl;
      } else {
        std::cerr << "Failed to fetch IP. Status code: " << status_code << std::endl;
      }
    };

    manager.send(request);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
#endif

  framework::application app(argc, std::move(argv));

  return app.run();
}
