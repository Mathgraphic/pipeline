// Copyright (c) 2002-2016, NVIDIA CORPORATION. All rights reserved.
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


#include <dp/sg/algorithm/OptimizeTraverser.h>

using namespace dp::sg::core;

namespace dp
{
  namespace sg
  {
    namespace algorithm
    {

      DEFINE_STATIC_PROPERTY( OptimizeTraverser, IgnoreNames );

      BEGIN_REFLECTION_INFO( OptimizeTraverser )
        DERIVE_STATIC_PROPERTIES( OptimizeTraverser, ExclusiveTraverser );
        INIT_STATIC_PROPERTY_RW( OptimizeTraverser, IgnoreNames, bool, Semantic::VALUE, value, value );
      END_REFLECTION_INFO

      OptimizeTraverser::OptimizeTraverser( void )
      : m_ignoreNames(true)
      {
      }

      OptimizeTraverser::~OptimizeTraverser( void )
      {
      }

      void OptimizeTraverser::doApply( const NodeSharedPtr & root )
      {
        ExclusiveTraverser::doApply( root );
      }

      bool OptimizeTraverser::optimizationAllowed( ObjectSharedPtr const& obj )
      {
        DP_ASSERT( obj != NULL );

        return( !obj->getHints( Object::DP_SG_HINT_DYNAMIC ) );
      }

    } // namespace algorithm
  } // namespace sg
} // namespace dp
