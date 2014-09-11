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

#include <dp/rix/gl/RiXGL.h>
#include "Vector.h"

#include "VertexAttributesGL.h"
#include "IndicesGL.h"
#include "GeometryDescriptionGL.h"

#include "dp/util/Observer.h"
  
namespace dp
{
  namespace rix
  {
    namespace gl
    {

      class GeometryGL : public dp::rix::core::Geometry, public dp::util::Subject, public dp::util::Observer
      {
      public:
        ~GeometryGL();

        void upload();

        virtual void onNotify( const dp::util::Event &event, dp::util::Payload *payload );
        virtual void onDestroyed( const dp::util::Subject& subject, dp::util::Payload* payload );

        void setVertexAttributes( VertexAttributesGLSharedHandle const & vertexAttributes );
        VertexAttributesGLSharedHandle const & getVertexAttributes() const { return m_vertexAttributes; }

        void setIndices( IndicesGLSharedHandle const & indices );
        IndicesGLSharedHandle const & getIndices() const { return m_indices; }

        void setGeometryDescription( GeometryDescriptionGLSharedHandle const & geometryDescription );
        GeometryDescriptionGLSharedHandle const & getGeometryDescription() const { return m_geometryDescription; }

        /****************/
        /* VBO Storage **/
        /****************/
        Vec4f m_boundingBoxLower;
        Vec4f m_boundingBoxExtends;

      protected:
        GeometryDescriptionGLSharedHandle   m_geometryDescription;
        VertexAttributesGLSharedHandle      m_vertexAttributes;
        IndicesGLSharedHandle               m_indices;
      };
    } // namespace gl
  } // namespace rix
} // namespace dp
