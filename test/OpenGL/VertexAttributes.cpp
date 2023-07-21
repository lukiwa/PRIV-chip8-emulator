#include "gtest/gtest.h"
#include "VertexAttributes.h"
#include "Window.h"




TEST(VertexAttributesTests, GlTypeSizeIsSameAsPodSizes )
{
    ASSERT_EQ(VertexAttributes::GlTypeToSize(GL_FLOAT), sizeof(float));
    ASSERT_EQ(VertexAttributes::GlTypeToSize(GL_INT), sizeof(int));
    ASSERT_EQ(VertexAttributes::GlTypeToSize(GL_UNSIGNED_INT), sizeof(unsigned int));
    //not recognized, will invoke warning
    EXPECT_EQ(VertexAttributes::GlTypeToSize(GL_R), 0);
}

TEST(VertexAttributesTests, SingleAttributeOffsetShouldBeTypeSize)
{
    VertexAttributes attributes;
    const int count = 1;
    const GLenum type = GL_FLOAT;

    attributes.AddAttribute(count, type);
    attributes.Bind();
    ASSERT_EQ(attributes.GetLastOffset(), VertexAttributes::GlTypeToSize(type));
}

TEST(VertexAttributesTests, AttributeOffsetSizeShouldBeNumberOfAttributesTimesAttributesTimesSizeOfType)
{
    VertexAttributes attributes;
    const int count = 2;
    const int attributeNumber = 3;
    const GLenum type = GL_FLOAT;


    for (int attribute = 0; attribute < attributeNumber; ++attribute) {
        attributes.AddAttribute(count, type);
    }


    attributes.Bind();
    ASSERT_EQ(attributes.GetLastOffset(), count * attributeNumber * VertexAttributes::GlTypeToSize(type));
}

TEST(VertexAttributesTests, StrideIsSizeOfVertex)
{
    VertexAttributes attributes;
    const int count = 2;
    const int attributeNumber = 2;
    const GLenum type = GL_FLOAT;


    for (int attribute = 0; attribute < attributeNumber; ++attribute) {
        attributes.AddAttribute(count, type);
    }


    attributes.Bind();
    ASSERT_EQ(attributes.GetStride(), count * attributeNumber * VertexAttributes::GlTypeToSize(type));
}


