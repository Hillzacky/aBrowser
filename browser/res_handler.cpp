#include "res_handler.h"

ResHandler::ResHandler(const std::string &mimeType, const std::string &data)
    : mimeType_(mimeType), data_(data), offset_(0) {}

ResHandler::~ResHandler() {}

bool ResHandler::Open(CefRefPtr<CefRequest> request, bool &handle_request,
                      CefRefPtr<CefCallback> callback) {
  handle_request = true;
  return true;
}

bool ResHandler::Skip(int64 bytes_to_skip, int64 &bytes_skipped,
                      CefRefPtr<CefResourceHandler::Callback> callback) {
  int64 available = data_.length() - offset_;
  bytes_skipped = std::min(bytes_to_skip, available);
  offset_ += bytes_skipped;
  return true;
}

bool ResHandler::Read(void *data_out, int bytes_to_read, int &bytes_read,
                      CefRefPtr<CefResourceHandler::Callback> callback) {
  int64 available = data_.length() - offset_;
  bytes_read = std::min(bytes_to_read, static_cast<int>(available));
  if (bytes_read > 0) {
    memcpy(data_out, data_.c_str() + offset_, bytes_read);
    offset_ += bytes_read;
    return true;
  }
  return false;
}

void ResHandler::Cancel() {}

void ResHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
                                     int64 &response_length,
                                     CefString &redirectUrl) {
  response->SetMimeType(mimeType_);
  response_length = data_.length();
}
