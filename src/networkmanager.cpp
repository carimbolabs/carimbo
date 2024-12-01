#include "networkmanager.hpp"

#ifdef EMSCRIPTEN
#include <emscripten/fetch.h>
#else
#include <curl/curl.h>
#endif

#include <fmt/format.h>

using namespace network;

networkmanager::networkmanager() {
#ifndef EMSCRIPTEN
  const auto result = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (result != CURLE_OK) {
    throw std::runtime_error(fmt::format("Failed to initialize CURL: {}", curl_easy_strerror(result)));
  }
#endif
}

networkmanager::~networkmanager() {
#ifndef EMSCRIPTEN
  curl_global_cleanup();
#endif
}

void networkmanager::send(const networkrequest &request) {
#ifdef EMSCRIPTEN
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);

  strncpy(attr.requestMethod, request.method.c_str(), sizeof(attr.requestMethod) - 1);
  attr.requestMethod[sizeof(attr.requestMethod) - 1] = '\0';

  auto user_request = std::make_unique<networkrequest>(request);
  attr.userData = user_request.release();

  attr.onsuccess = [](emscripten_fetch_t *fetch) {
    std::unique_ptr<networkrequest> request(static_cast<networkrequest *>(fetch->userData));
    request->callback(std::string(fetch->data, fetch->numBytes), fetch->status);
    emscripten_fetch_close(fetch);
  };

  attr.onerror = [](emscripten_fetch_t *fetch) {
    std::unique_ptr<networkrequest> request(static_cast<networkrequest *>(fetch->userData));
    request->callback("", fetch->status);
    emscripten_fetch_close(fetch);
  };

  if (!request.body.empty()) {
    attr.requestData = request.body.c_str();
    attr.requestDataSize = request.body.size();
  }

  if (!request.headers.empty()) {
    std::vector<std::string> header_strings;
    std::vector<const char *> header_pointers;

    for (const auto &[key, value] : request.headers) {
      header_strings.emplace_back(key + ": " + value);
    }

    for (const auto &header : header_strings) {
      header_pointers.push_back(header.c_str());
    }

    header_pointers.push_back(nullptr);

    attr.requestHeaders = header_pointers.data();
  }

  emscripten_fetch(&attr, request.url.c_str());
#else
  auto curl = std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>(curl_easy_init(), &curl_easy_cleanup);

  curl_easy_setopt(curl.get(), CURLOPT_URL, request.url.c_str());
  curl_easy_setopt(curl.get(), CURLOPT_CUSTOMREQUEST, request.method.c_str());

  auto headers = std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)>(nullptr, &curl_slist_free_all);
  for (const auto &[key, value] : request.headers) {
    const auto header = key + ": " + value;
    headers.reset(curl_slist_append(headers.release(), header.c_str()));
  }
  if (headers) {
    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers.get());
  }

  if (!request.body.empty()) {
    curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, request.body.c_str());
  }

  auto data = std::string{};
  curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, [](void *ptr, size_t size, size_t nmemb, void *userdata) {
    const auto real_size = size * nmemb;
    auto *response = static_cast<std::string *>(userdata);
    response->append(static_cast<char *>(ptr), real_size);
    return real_size;
  });
  curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &data);

  const auto result = curl_easy_perform(curl.get());
  if (result != CURLE_OK) {
    throw std::runtime_error(fmt::format("CURL request failed: {}", curl_easy_strerror(result)));
  }

  long code = 0;
  curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &code);
  request.callback(data, code);
#endif
}
