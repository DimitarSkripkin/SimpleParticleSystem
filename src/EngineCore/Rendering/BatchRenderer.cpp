#include "BatchRenderer.h"

BatchRenderer::BatchRenderer() {}

void BatchRenderer::Draw(BatchRecorder & batchRecorder, SpriteMaterial & spriteMaterial) {
    // bind shader here?
    for (auto & ptr : batchRecorder.subBatches) {
        auto drawBatch = ptr.second;
        if (!drawBatch->vao.IsStarted()) {
            continue;
        }

        spriteMaterial.UpdateTexture(drawBatch->texture);
        if (drawBatch->texture == nullptr) {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        drawBatch->vao.Bind();

        glDrawArrays(GL_TRIANGLES, 0, static_cast<uint32_t>(drawBatch->vertices.size()));

        drawBatch->vao.Unbind();
    }
}
