#include "MuCanvasContext2DScreen.h"
#include "AppController.h"

namespace mural {

  MuTexture *MuCanvasContext2DScreen::getTexture() {
    // This context may not be the current one, but it has to be in order for
    // glReadPixels to succeed.
    MuCanvasContext *previousContext = app.currentRenderingContext;
    app.currentRenderingContext = this;

    float w = width * backingStoreRatio;
    float h = height * backingStoreRatio;

    MuTexture *texture = getImageDataScaled(1, upsideDown, 0, 0, w, h)->getTexture();
    texture->contentScale = backingStoreRatio;

    app.currentRenderingContext = previousContext;
    return texture;
  }

  void MuCanvasContext2DScreen::present() {
    flushBuffers();

    if (!needsPresenting) { return; }

    // TODO: MSAA for screen present
    if (msaaEnabled) {
        //Bind the MSAA and View frameBuffers and resolve
        // glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, msaaFrameBuffer);
        // glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, viewFrameBuffer);
        // glResolveMultisampleFramebufferAPPLE();

        // glBindRenderbuffer(GL_RENDERBUFFER, viewRenderBuffer);
        // [glContext presentRenderbuffer:GL_RENDERBUFFER];
        // glBindFramebuffer(GL_FRAMEBUFFER, msaaFrameBuffer);
    }
    else {
        // glContext->presentRenderbuffer(GL_RENDERBUFFER);
    }
    needsPresenting = false;
  }

}