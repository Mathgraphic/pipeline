// Copyright NVIDIA Corporation 2002-2010
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
/** @file */

#include <memory>

#if defined(_WIN32)
# include <basetsd.h>
#endif
#if defined(LINUX)
# include <stdint.h>
typedef uintptr_t UINT_PTR;   //!< Linux specific type definition for UINT_PTR, as it's known from MSVC.
#endif

#include <dp/util/Allocator.h>
#include <dp/util/DPAssert.h>
#include <dp/util/SmartPtr.h>

namespace dp
{
  namespace sg
  {
    namespace core
    {

      /*! \brief Typedefs for objects
         The following typedefs should be defined for an object.
         Handle
         SharedPtr
         WeakPtr
         Lock
      **/
      template <typename ObjectType> struct ObjectTraits {};

      template <typename T>
      class SharedPtr : public std::shared_ptr<T>
      {
        public:
          SharedPtr();
          SharedPtr( std::shared_ptr<T> const& sp );

          // implicit upcast (Derived -> Base)
          template <typename U> SharedPtr( std::shared_ptr<U> const& sp );

          // explicit downcast (Base -> Derived), two flavours
          template <typename U> SharedPtr<U> dynamicCast() const;
          template <typename U> SharedPtr<U> staticCast() const;

          // explicit in-place cast
          template <typename U> SharedPtr<U> const& inplaceCast() const;

          template <typename U> bool isPtrTo() const;

          // convenience handling on clone
          SharedPtr<T> clone() const;

          typename ObjectTraits<T>::WeakPtr getWeakPtr() const;

          template <typename U> bool operator==( U const* rhs ) const;

        private:
          T * get() const;    // hide std::shared_ptr<T>::get(), use getWeakPtr(), instead

        public:
          static SharedPtr<T> const null;
      };

      template <typename T>
      inline SharedPtr<T>::SharedPtr()
      {}

      template <typename T>
      inline SharedPtr<T>::SharedPtr( std::shared_ptr<T> const& sp )
        : std::shared_ptr<T>( sp )
      {}

      template <typename T>
      template <typename U>
      inline SharedPtr<T>::SharedPtr( std::shared_ptr<U> const& sp )
        : std::shared_ptr<T>( std::static_pointer_cast<T>( sp ) )
      {
        DP_STATIC_ASSERT(( boost::is_base_of<T,U>::value ));
      }

      template <typename T>
      template <typename U>
      inline SharedPtr<U> SharedPtr<T>::dynamicCast() const
      {
        DP_STATIC_ASSERT(( boost::is_base_of<T,U>::value ));
        return( std::dynamic_pointer_cast<U>( *this ) );
      }

      template <typename T>
      template <typename U>
      inline SharedPtr<U> SharedPtr<T>::staticCast() const
      {
        DP_STATIC_ASSERT(( boost::is_base_of<T,U>::value ));
        DP_ASSERT( dynamic_cast<U*>( std::shared_ptr<T>::get() ) );
        return( std::static_pointer_cast<U>( *this ) );
      }

      template <typename T>
      template <typename U>
      inline SharedPtr<U> const& SharedPtr<T>::inplaceCast() const
      {
        DP_STATIC_ASSERT(( boost::is_base_of<T,U>::value || boost::is_base_of<U,T>::value ));
        return( *reinterpret_cast<SharedPtr<U> const*>(this) );
      }

      template <typename T>
      template <typename U>
      inline bool SharedPtr<T>::isPtrTo() const
      {
        return( dynamic_cast<U*>( std::shared_ptr<T>::get() ) != nullptr );
      }

      template <typename T>
      inline SharedPtr<T> SharedPtr<T>::clone() const
      {
        return( (*this)->clone().staticCast<T>() );
      }

      template <typename T>
      inline typename ObjectTraits<T>::WeakPtr SharedPtr<T>::getWeakPtr() const
      {
        return( std::shared_ptr<T>::get() );
      }

      template <typename T>
      template <typename U>
      inline bool SharedPtr<T>::operator==( U const* rhs ) const
      {
        return( std::shared_ptr<T>::get() == rhs );
      }

      template<typename T> const SharedPtr<T> SharedPtr<T>::null( nullptr );

      /*! \brief Functor class to clone an object
       *  \remark This Functor can be used, for example, to clone all objects of a STL container, using the
       *  STL algorithm transform. */
      struct CloneObject
      {
        /*! \brief The function call operator of this functor.
         *  \param src A reference to the SharedHandle to clone.
         *  \return A clone of the parameter \a src. */
        template<typename T>
        SharedPtr<T> operator()( SharedPtr<T> const& src )
        {
          return( src.clone() );
        }
      };

      /*! \brief Special casting operator for const WeakPtr.
       *  \param rhs The const WeakPtr to cast.
       *  \return \a rhs casted from type \c const \c UWeakPtr to type \c const \c WeakPtr<T>.
       *  \remark A weakPtr_cast can be used to do a downcast a WeakPtr. In debug builds, it is checked whether
       *  that downcast is allowed. */
      template<typename T, typename UWeakPtr>
      inline const typename ObjectTraits<T>::WeakPtr & weakPtr_cast( const UWeakPtr & rhs )
      {
        DP_ASSERT( !rhs || dynamic_cast<typename ObjectTraits<T>::WeakPtr>(rhs) );
        return( *reinterpret_cast<const typename ObjectTraits<T>::WeakPtr *>(&rhs) );
      }

      /*! \brief Special casting operator for WeakPtr.
       *  \param rhs The WeakPtr to cast.
       *  \return \a rhs casted from type \c UWeakPtr to type \c WeakPtr<T>.
       *  \remark A weakPtr_cast can be used to do a downcast a WeakPtr. In debug builds, it is checked whether
       *  that downcast is allowed. */
      template<typename T, typename UWeakPtr>
      inline typename ObjectTraits<T>::WeakPtr & weakPtr_cast( UWeakPtr & rhs )
      {
        DP_ASSERT( !rhs || dynamic_cast<typename ObjectTraits<T>::WeakPtr>(rhs) );
        return( *reinterpret_cast<typename ObjectTraits<T>::WeakPtr *>(&rhs) );
      }

      template<typename T, typename U>
      inline typename ObjectTraits<T>::WeakPtr const & weakPtr_cast( U const* p )
      {
        DP_ASSERT( !p || dynamic_cast<T const*>(p) );
        return( *reinterpret_cast<typename ObjectTraits<T>::WeakPtr *>(p) );
      }

      template<typename T, typename U>
      inline typename ObjectTraits<T>::WeakPtr getWeakPtr( U const* p )
      {
        DP_STATIC_ASSERT(( boost::is_base_of<T,U>::value ));
        return( typename ObjectTraits<T>::WeakPtr(p) );
      }

    }//namespace core
  }//namespace sg
}//namespace dp
