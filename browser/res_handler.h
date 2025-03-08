#ifndef RES_HANDLER_H
#define RES_HANDLER_H

#include <include/cef_app.h>
#include <include/cef_resource_handler.h>

class ResHandler : public CefResourceHandler {
public:
  ResHandler(const std::string &mimeType, const std::string &data);
  ~ResHandler();

  bool Open(CefRefPtr<CefRequest> request, bool &handle_request,
            CefRefPtr<CefCallback> callback) override;
  bool Skip(int64 bytes_to_skip, int64 &bytes_skipped,
            CefRefPtr<CefResourceHandler::Callback> callback) override;
  bool Read(void *data_out, int bytes_to_read, int &bytes_read,
            CefRefPtr<CefResourceHandler::Callback> callback) override;
  void Cancel() override;
  void GetResponseHeaders(CefRefPtr<CefResponse> response, int64 &response_length,
                           CefString &redirectUrl) override;

private:
  std::string mimeType_;
  std::string data_;
  int offset_;
};

#endif
