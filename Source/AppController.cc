#include "AppController.h"
#include "MuTimer.h"

namespace mural {

  AppController::~AppController() {
    screenRenderingContext->finish();
  }

  void AppController::init(int width, int height) {
    this->width = width;
    this->height = height;

    theScheduler.scheduleMessage([] {
      printf("timer\n");
    }, 1000, false);
  }

  void AppController::update() {
    if (isPaused) return;

    // Update timers
    theScheduler.update();
  }

  void AppController::draw() {
    if (isPaused) return;

    // Redraw the canvas
    if (hasScreenCanvas) {
      setCurrentRenderingContext(screenRenderingContext);
      screenRenderingContext->present();
    }
  }

  void AppController::setCurrentRenderingContext(MuCanvasContext *renderingContext) {
    if (renderingContext != currentRenderingContext) {
      currentRenderingContext->flushBuffers();

      renderingContext->prepare();
      currentRenderingContext = renderingContext;
    }
  }

}