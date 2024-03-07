#include  <gtest/gtest.h>
#include "cpp/law/GpuLaw.h"

TEST(GpuLawTest, GpuLaw) {
    auto gpuLaw = GpuLaw();
    Particle** p = NULL;
    int particleCount = 0;
    gpuLaw.run(p, particleCount);
    EXPECT_EQ("GpuLaw", gpuLaw.getClassName());
}