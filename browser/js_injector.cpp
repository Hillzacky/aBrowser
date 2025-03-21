#include "js_injector.h"
#include <sstream>
#include <random>

JSInjector::JSInjector(const Settings &settings) : settings_(settings) {}

void JSInjector::inject(CefRefPtr<CefFrame> frame) {
  if (settings_.isCanvasSpoofEnabled()) {
    injectCanvasSpoof(frame);
  }
  if (settings_.isWebGlSpoofEnabled()) {
    injectWebGlSpoof(frame);
  }
  injectNavigatorSpoof(frame);
  injectTimezoneSpoof(frame);
  injectGeolocationSpoof(frame);
  injectMediaDevicesSpoof(frame);
  injectScreenSpoof(frame);
  injectBatterySpoof(frame);
  injectFontsSpoof(frame);
  injectPluginsSpoof(frame);
  // ... injeksi lainnya
}

void JSInjector::injectCanvasSpoof(CefRefPtr<CefFrame> frame) {
  static const char* canvasSpoofCode = R"(
    (function() {
      const toBlob = HTMLCanvasElement.prototype.toBlob;
      const toDataURL = HTMLCanvasElement.prototype.toDataURL;
      const getImageData = CanvasRenderingContext2D.prototype.getImageData;
      HTMLCanvasElement.prototype.toBlob = function() {
        arguments[0] = 'image/png';
        if (this.width > 0 && this.height > 0) {
          const imageData = this.getContext('2d').getImageData(0, 0, this.width, this.height);
          const pixelData = imageData.data;
          for (let i = 0; i < pixelData.length; i += 4) {
            pixelData[i] = Math.floor(Math.random() * 255);
            pixelData[i + 1] = Math.floor(Math.random() * 255);
            pixelData[i + 2] = Math.floor(Math.random() * 255);
          }
          this.getContext('2d').putImageData(imageData, 0, 0);
        }
        return toBlob.apply(this, arguments);
      };
      HTMLCanvasElement.prototype.toDataURL = function() {
        arguments[0] = 'image/png';
        if (this.width > 0 && this.height > 0) {
          const imageData = this.getContext('2d').getImageData(0, 0, this.width, this.height);
          const pixelData = imageData.data;
          for (let i = 0; i < pixelData.length; i += 4) {
            pixelData[i] = Math.floor(Math.random() * 255);
            pixelData[i + 1] = Math.floor(Math.random() * 255);
            pixelData[i + 2] = Math.floor(Math.random() * 255);
          }
          this.getContext('2d').putImageData(imageData, 0, 0);
        }
        return toDataURL.apply(this, arguments);
      };
      CanvasRenderingContext2D.prototype.getImageData = function() {
        if (arguments[2] > 0 && arguments[3] > 0) {
          const imageData = getImageData.apply(this, arguments);
          const pixelData = imageData.data;
          for (let i = 0; i < pixelData.length; i += 4) {
            pixelData[i] = Math.floor(Math.random() * 255);
            pixelData[i + 1] = Math.floor(Math.random() * 255);
            pixelData[i + 2] = Math.floor(Math.random() * 255);
          }
          return imageData;
        } else {
          return getImageData.apply(this, arguments);
        }
      };
    })();
  )";
  frame->ExecuteJavaScript(canvasSpoofCode, "", 0);
}

void JSInjector::injectWebGlSpoof(CefRefPtr<CefFrame> frame) {
  static const char* webGlSpoofCode = R"(
    (function() {
      const getParameter = WebGLRenderingContext.prototype.getParameter;
      WebGLRenderingContext.prototype.getParameter = function(parameter) {
        if (parameter === 37445) { // UNMASKED_VENDOR_WEBGL
          return 'Intel Inc.';
        } else if (parameter === 37446) { // UNMASKED_RENDERER_WEBGL
          return 'Intel Iris OpenGL Engine';
        }
        return getParameter(parameter);
      };
    })();
  )";
  frame->ExecuteJavaScript(webGlSpoofCode, "", 0);
}

void JSInjector::injectNavigatorSpoof(CefRefPtr<CefFrame> frame) {
  std::stringstream ss;
  ss << "(function() {"
     << "  Object.defineProperty(navigator, 'userAgent', {"
     << "    get: function() { return '" << settings_.getUserAgent() << "'; }"
     << "  });"
     << "  Object.defineProperty(navigator, 'platform', {"
     << "    get: function() { return 'Win32'; }"
     << "  });"
     << "})();";
  frame->ExecuteJavaScript(ss.str(), "", 0);
}

void JSInjector::injectTimezoneSpoof(CefRefPtr<CefFrame> frame) {
    static const char* timezoneSpoofCode = R"(
    (function() {
      Date = function(date) {
        if (arguments.length === 0) {
          return new Date(Date.UTC(2023, 0, 1, 0, 0, 0)); // Spoof ke UTC
        } else {
          return new Date(date);
        }
      };
      Date.prototype = new Date();
      Date.now = function() { return new Date().getTime(); };
      Date.UTC = function() { return Date.prototype.getTime.apply(new Date(Date.prototype.getTime()), arguments); };
      Date.parse = function(dateString) { return Date.prototype.getTime.apply(new Date(Date.prototype.getTime()), [dateString]); };
    })();
  )";
    frame->ExecuteJavaScript(timezoneSpoofCode, "", 0);
}

void JSInjector::injectGeolocationSpoof(CefRefPtr<CefFrame> frame) {
    static const char* geolocationSpoofCode = R"(
    (function() {
      const originalGeolocation = navigator.geolocation;
      navigator.geolocation = {
        getCurrentPosition: function(success, error, options) {
          const position = {
            coords: {
              latitude: 0, // Spoof latitude
              longitude: 0, // Spoof longitude
              accuracy: 100,
              altitude: null,
              altitudeAccuracy: null,
              heading: null,
              speed: null
            },
            timestamp: Date.now()
          };
          success(position);
        },
        watchPosition: function(success, error, options) {
          return navigator.geolocation.getCurrentPosition(success, error, options);
        },
        clearWatch: function() {}
      };
    })();
  )";
    frame->ExecuteJavaScript(geolocationSpoofCode, "", 0);
}

void JSInjector::injectMediaDevicesSpoof(CefRefPtr<CefFrame> frame) {
    static const char* mediaDevicesSpoofCode = R"(
    (function() {
      const originalEnumerateDevices = navigator.mediaDevices.enumerateDevices;
      navigator.mediaDevices.enumerateDevices = function() {
        return new Promise(resolve => {
          resolve([
            {
              deviceId: 'fake_audio_input',
              kind: 'audioinput',
              label: 'Fake Audio Input',
              groupId: 'fake_group'
            },
            {
              deviceId: 'fake_audio_output',
              kind: 'audiooutput',
              label: 'Fake Audio Output',
              groupId: 'fake_group'
            },
            {
              deviceId: 'fake_video_input',
              kind: 'videoinput',
              label: 'Fake Video Input',
              groupId: 'fake_group'
            }
          ]);
        });
      };
    })();
  )";
    frame->ExecuteJavaScript(mediaDevicesSpoofCode, "", 0);
}

void JSInjector::injectScreenSpoof(CefRefPtr<CefFrame> frame) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(800, 2000); // Rentang acak untuk lebar dan tinggi layar

    int width = dis(gen


void JSInjector::injectFontsSpoof(CefRefPtr<CefFrame> frame) {
  static const char* fontsSpoofCode = R"(
    (function() {
      const originalQuery = document.fonts.query;
      document.fonts.query = function() {
        return new Promise(resolve => {
          resolve([
            { family: 'Arial', style: 'normal', weight: '400', stretch: 'normal', unicodeRange: 'U+0000-00FF' },
            { family: 'Times New Roman', style: 'normal', weight: '400', stretch: 'normal', unicodeRange: 'U+0000-00FF' },
            { family: 'Courier New', style: 'normal', weight: '400', stretch: 'normal', unicodeRange: 'U+0000-00FF' }
          ]);
        });
      };
    })();
  )";
  frame->ExecuteJavaScript(fontsSpoofCode, "", 0);
}

void JSInjector::injectPluginsSpoof(CefRefPtr<CefFrame> frame) {
  static const char* pluginsSpoofCode = R"(
    (function() {
      const originalPlugins = navigator.plugins;
      navigator.plugins = {
        length: 3,
        0: { name: 'Chrome PDF Plugin', filename: 'internal-pdf-viewer', description: 'Portable Document Format' },
        1: { name: 'Chrome PDF Viewer', filename: 'mhjfbmdgcfjbbpaeojofohoefgiehjai', description: '' },
        2: { name: 'Native Client', filename: 'internal-nacl-plugin', description: '' },
        namedItem: function(name) {
          return this[name];
        },
        refresh: function() {}
      };
    })();
  )";
  frame->ExecuteJavaScript(pluginsSpoofCode, "", 0);
}
