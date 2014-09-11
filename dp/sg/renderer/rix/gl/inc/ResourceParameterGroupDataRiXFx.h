// Copyright NVIDIA Corporation 2012
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

#include <dp/sg/renderer/rix/gl/Config.h>
#include <dp/sg/renderer/rix/gl/inc/ResourceManager.h>
#include <dp/sg/renderer/rix/gl/inc/ResourceSampler.h>
#include <dp/sg/core/EffectData.h>
#include <dp/rix/fx/Manager.h>

#include <vector>

namespace dp
{
  namespace sg
  {
    namespace renderer
    {
      namespace rix
      {
        namespace gl
        {
          class ResourceParameterGroupDataRiXFx;
          typedef dp::util::SmartPtr<ResourceParameterGroupDataRiXFx> SmartResourceParameterGroupDataRiXFx;
          typedef ResourceParameterGroupDataRiXFx* WeakResourceParameterGroupDataRiXFx;


          class ResourceParameterGroupDataRiXFx : public ResourceManager::Resource
          {
          public:
            /** \brief Fetch resource for the given object/resourceManager. If no resource exists it'll be created **/
            static SmartResourceParameterGroupDataRiXFx get( const dp::sg::core::ParameterGroupDataSharedPtr& parameterGroupData, const dp::rix::fx::SmartManager& rixFx, const SmartResourceManager& resourceManager );
            virtual ~ResourceParameterGroupDataRiXFx();

            virtual const dp::sg::core::HandledObjectSharedPtr& getHandledObject() const;
            virtual void update();
            virtual bool update( const dp::util::Event& event );

            dp::rix::fx::GroupDataSharedHandle getGroupData() const { return m_groupData; }

          protected:
            ResourceParameterGroupDataRiXFx( const dp::sg::core::ParameterGroupDataSharedPtr& parameterGroupData, const dp::rix::fx::SmartManager& rixFx, const SmartResourceManager& resourceManager );
      
            dp::sg::core::ParameterGroupDataSharedPtr m_parameterGroupData;
            dp::rix::fx::GroupDataSharedHandle         m_groupData;
            dp::rix::fx::SmartManager                 m_rixFx;

            // keep referenced resources alive
            std::vector<SmartResourceSampler> m_resourceSamplers;
          };

        } // namespace gl
      } // namespace rix
    } // namespace renderer
  } // namespace sg
} // namespace dp
