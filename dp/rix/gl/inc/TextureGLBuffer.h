// Copyright NVIDIA Corporation 2011
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#pragma once

#include "TextureGL.h"

namespace dp
{
  namespace rix
  {
    namespace gl
    {

      /*! \brief Class for OpenGL texture buffers.
       */
      class TextureGLBuffer : public TextureGL
      {
      public:
        static dp::rix::core::TextureHandle create( const dp::rix::core::TextureDescription &textureDescription );

        // setData overload to store buffer info in this class
        virtual bool setData( const dp::rix::core::TextureData& textureData );

        // sampler state overloads to not set sampler state
        virtual void applySamplerState( SamplerStateGLHandle samplerState );
        virtual void applyDefaultSamplerState();
        virtual void setDefaultSamplerState( SamplerStateGLHandle samplerState );

      public:
        static GLsizei getMaximumSize();

      protected:
        TextureGLBuffer( const dp::rix::core::TextureDescription &textureDescription );

        virtual void upload( unsigned int mipMapLevel, unsigned int layer, const void* ptr );

      protected:
        BufferGLHandle m_textureBuffer;
      };

    } // namespace gl
  } // namespace rix
} // namespace dp