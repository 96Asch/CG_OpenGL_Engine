#include "GLUtil.h"

#include "Global.h"

namespace GLUtil {

    void enableDepthTesting(const bool &enable) {
        static bool isDepthTesting = false;
        if(enable && !isDepthTesting) {
            isDepthTesting = true;
            glEnable(GL_DEPTH_TEST);
        }
        else if(!enable && isDepthTesting) {
            isDepthTesting = false;
            glDisable(GL_DEPTH_TEST);
        }
    }

    void cullBackFaces(const bool &enable) {
        static bool isCulledBackface = false;
        if(enable && !isCulledBackface) {
            isCulledBackface = true;
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
        else if(!enable && isCulledBackface) {
            isCulledBackface = false;
            glDisable(GL_CULL_FACE);
        }
    }

    void enableDepthMask(const bool &enable) {
        static bool isDepthMasking = false;
        if (enable && !isDepthMasking) {
            glDepthMask(true);
            isDepthMasking = true;
        }
        else if (!enable && isDepthMasking) {
            glDepthMask(false);
            isDepthMasking = false;
        }
    }

}
