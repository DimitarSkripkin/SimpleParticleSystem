#pragma once

#include "BatchRecorder.h"
#include "Material.h"

class BatchRenderer {
public:
    BatchRenderer();

    void Draw(BatchRecorder & batchRecorder, SpriteMaterial & spriteMaterial);

private:
};
