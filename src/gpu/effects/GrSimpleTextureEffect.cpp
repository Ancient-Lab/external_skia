/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * This file was autogenerated from GrSimpleTextureEffect.fp; do not modify.
 */
#include "GrSimpleTextureEffect.h"
#if SK_SUPPORT_GPU
#include "glsl/GrGLSLColorSpaceXformHelper.h"
#include "glsl/GrGLSLFragmentProcessor.h"
#include "glsl/GrGLSLFragmentShaderBuilder.h"
#include "glsl/GrGLSLProgramBuilder.h"
#include "SkSLCPP.h"
#include "SkSLUtil.h"
class GrGLSLSimpleTextureEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLSimpleTextureEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrSimpleTextureEffect& _outer = args.fFp.cast<GrSimpleTextureEffect>();
        (void) _outer;
        fColorSpaceHelper.emitCode(args.fUniformHandler, _outer.colorXform().get());
        SkSL::String sk_TransformedCoords2D_0 = fragBuilder->ensureCoords2D(args.fTransformedCoords[0]);
        fragBuilder->codeAppendf("vec4 _tmp0;\n%s = %s * (_tmp0 = texture(%s, %s).%s , %s != mat4(1.0) ? vec4(clamp((%s * vec4(_tmp0.xyz, 1.0)).xyz, 0.0, _tmp0.w), _tmp0.w) : _tmp0);\n", args.fOutputColor, args.fInputColor ? args.fInputColor : "vec4(1)", fragBuilder->getProgramBuilder()->samplerVariable(args.fTexSamplers[0]).c_str(), sk_TransformedCoords2D_0.c_str(), fragBuilder->getProgramBuilder()->samplerSwizzle(args.fTexSamplers[0]).c_str(), fColorSpaceHelper.isValid() ? args.fUniformHandler->getUniformCStr(fColorSpaceHelper.gamutXformUniform()) : "mat4(1.0)", fColorSpaceHelper.isValid() ? args.fUniformHandler->getUniformCStr(fColorSpaceHelper.gamutXformUniform()) : "mat4(1.0)");
    }
private:
    void onSetData(const GrGLSLProgramDataManager& pdman, const GrFragmentProcessor& _proc) override {
        const GrSimpleTextureEffect& _outer = _proc.cast<GrSimpleTextureEffect>();
        {
        if (fColorSpaceHelper.isValid()) {
            fColorSpaceHelper.setData(pdman, _outer.colorXform().get());
        }
        }
    }
    UniformHandle fImageVar;
    GrGLSLColorSpaceXformHelper fColorSpaceHelper;
};
GrGLSLFragmentProcessor* GrSimpleTextureEffect::onCreateGLSLInstance() const {
    return new GrGLSLSimpleTextureEffect();
}
void GrSimpleTextureEffect::onGetGLSLProcessorKey(const GrShaderCaps& caps, GrProcessorKeyBuilder* b) const {
    b->add32(GrColorSpaceXform::XformKey(fColorXform.get()));
}
bool GrSimpleTextureEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrSimpleTextureEffect& that = other.cast<GrSimpleTextureEffect>();
    (void) that;
    if (fImage != that.fImage) return false;
    if (fColorXform != that.fColorXform) return false;
    if (fMatrix != that.fMatrix) return false;
    return true;
}
GR_DEFINE_FRAGMENT_PROCESSOR_TEST(GrSimpleTextureEffect);
#if GR_TEST_UTILS
sk_sp<GrFragmentProcessor> GrSimpleTextureEffect::TestCreate(GrProcessorTestData* testData) {

    int texIdx = testData->fRandom->nextBool() ? GrProcessorUnitTest::kSkiaPMTextureIdx
                                               : GrProcessorUnitTest::kAlphaTextureIdx;
    static const SkShader::TileMode kTileModes[] = {
        SkShader::kClamp_TileMode,
        SkShader::kRepeat_TileMode,
        SkShader::kMirror_TileMode,
    };
    SkShader::TileMode tileModes[] = {
        kTileModes[testData->fRandom->nextULessThan(SK_ARRAY_COUNT(kTileModes))],
        kTileModes[testData->fRandom->nextULessThan(SK_ARRAY_COUNT(kTileModes))],
    };
    GrSamplerParams params(tileModes, testData->fRandom->nextBool()
                                                               ? GrSamplerParams::kBilerp_FilterMode
                                                               : GrSamplerParams::kNone_FilterMode);

    const SkMatrix& matrix = GrTest::TestMatrix(testData->fRandom);
    sk_sp<GrColorSpaceXform> colorSpaceXform = GrTest::TestColorXform(testData->fRandom);
    return GrSimpleTextureEffect::Make(testData->textureProxy(texIdx), std::move(colorSpaceXform),
                                       matrix);
}
#endif
#endif
