// Copyright NVIDIA Corporation 2002-2005
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
/** \file */

#include <dp/sg/algorithm/Config.h>
#include <dp/sg/algorithm/ModelViewTraverser.h>
#include <dp/sg/core/Primitive.h>
#include <dp/sg/core/Path.h>
#include <dp/sg/core/Buffer.h>
#include "dp/util/SmartPtr.h"

namespace dp
{
  namespace sg
  {
    namespace algorithm
    {

      //! Intersection class.
      /** This class is used to store intersection results generated by the RayIntersectTraverser. 
        * It should only be used with classes derived from RayIntersectTraveser because some 
        * information like the distance makes sense only when knowing the ray data. 
        * \note Needs a valid ViewState, which in turns holds a valid camera. Call setViewState prior to apply().*/
      class Intersection
      {
        public:
          //! Default constructor.
          Intersection(void);

          //! Constructor.
          /** This contructor creates an intersection object from the given data. */
          DP_SG_ALGORITHM_API Intersection( dp::sg::core::Path * pPath                         //!< Path to the intersected drawable.
                               , const dp::sg::core::PrimitiveSharedPtr & pPrimitive  //!< Intersected drawable.
                               , const dp::math::Vec3f & isp                  //!< Intersection point on the drawable.
                               , float dist                                 //!< Distance from the ray origin to the drawable.
                               , unsigned int primitiveIndex                //!< Index of the intersected primitive in the Primitive.
                               , const std::vector<unsigned int> & vertexIndices //!< Indices of the vertices of the intersected primitive.
                               );

          //! Copy constructor.
          /** Creates a new Intersection object from the given one. */
          DP_SG_ALGORITHM_API Intersection( const Intersection & rhs    //!< Intersection object to copy from.
                               );

          //! Default destructor.
          DP_SG_ALGORITHM_API virtual ~Intersection(void);

          //! Assignment operator.
          DP_SG_ALGORITHM_API Intersection & operator = (const Intersection & rhs);

          //! Get the Path to the intersected drawable.
          /** \return Path to the drawable. */
          DP_SG_ALGORITHM_API dp::util::SmartPtr<dp::sg::core::Path> const & getPath() const;

          //! Get the intersected primitive
          /** \return Intersected primitive. */
          DP_SG_ALGORITHM_API const dp::sg::core::PrimitiveSharedPtr & getPrimitive() const;

          //! Get the intersection point on the intersected drawable.
          /** \return Intersection Point. */
          DP_SG_ALGORITHM_API const dp::math::Vec3f & getIsp() const;

          //! Get the distance from the ray origin to the intersection point.
          /** \return Distance from ray origin to intersection point. */
          DP_SG_ALGORITHM_API float getDist() const;

          /*! \brief Get the index of the intersected primitive. 
           *  \return An index to the intersected primitive.
           *  \remarks This function returns the index of the intersected primitive.
           *  e.g. the i-th strip in a TriangleStrip or the i-th triangle in Triangles.
           *  With this index you have the abilitiy to access the primitive and modify it. */
          DP_SG_ALGORITHM_API unsigned int getPrimitiveIndex() const;

          /*! \brief Get the indices if the intersected face, line or point.
           *  \return Indices to the vertex data of the intersected line, face or point.
           *  \remarks The vertices that are returned can be used to access the vertices of the 
           *  intersected object. 
           *  The size of this vector determines the primitive category. E.g. If the size of this vector 
           *  is 3 then the intersected face is a triangle. (4 is a Quad, 2 is a line, 1 a point...)
           *  \code
           *  // How to access the vertices and normals of the intersected triangle in a triangle strip
           *  const Vec3f * vertices = intersection->getPrimitive()->getVertexAttributeSet()->getVertices();
           *  const Vec3f * normals = intersection->getPrimitive()->getVertexAttributeSet()->getNormals();
           *  const std::vector<unsigned int> & vertIndices = intersection->getVertexIndices(); 
           *
           *  const Vec3f & v0 = vertices[vertIndices[0]];
           *  const Vec3f & v1 = vertices[vertIndices[1]];
           *  const Vec3f & v2 = vertices[vertIndices[2]];
           * 
           *  const Vec3f & n0 = normals[vertIndices[0]];
           *  const Vec3f & n1 = normals[vertIndices[1]];
           *  const Vec3f & n2 = normals[vertIndices[2]];
           *  \endcode
           */
          DP_SG_ALGORITHM_API const std::vector<unsigned int> & getVertexIndices() const;

        protected:
          //! Clone the whole object.
          /** Use this, for example, for the copy constructor. */
          void clone( const Intersection & rhs    //!< Object to clone.
                             ); 
      
          dp::sg::core::PrimitiveSharedPtr      m_pPrimitive;      //!< Intersected primitive.
          dp::util::SmartPtr<dp::sg::core::Path>  m_pPath;          //!< Path to the intersected primitive.
          dp::math::Vec3f               m_isp;            //!< Intersection point on the intersected primitive.
          float                         m_dist;           //!< Distance from the ray origin to the intersection point.
          unsigned int                  m_primitiveIndex; //!< Index of the intersected primitive in the Primitive.
          std::vector<unsigned int>     m_vertexIndices;  //!< Indices of the vertices of the intersected primitive.

      };

      inline Intersection::~Intersection() 
      {
      }

      inline Intersection::Intersection()
      : m_pPrimitive(NULL)
      , m_pPath(NULL)
      , m_isp(dp::math::Vec3f())
      , m_dist(0.0f)
      , m_primitiveIndex (0xffffffff)
      {
      }

       inline Intersection::Intersection ( dp::sg::core::Path * pPath
                                         , const dp::sg::core::PrimitiveSharedPtr & pPrimitive
                                         , const dp::math::Vec3f & isp
                                         , float dist
                                         , unsigned int primitiveIndex
                                         , const std::vector<unsigned int> & vertexIndices)

      {
        DP_ASSERT(pPrimitive);
        DP_ASSERT(pPath);

        m_isp       = isp; 
        m_dist      = dist;
        m_pPrimitive = pPrimitive;
        m_pPath     = pPath;
        m_primitiveIndex = primitiveIndex;
        m_vertexIndices = vertexIndices;
      }

      inline Intersection::Intersection (const Intersection & rhs)
      {
        clone(rhs);
      }

      inline Intersection & Intersection::operator = (const Intersection & rhs) 
      {
        clone(rhs);
        return (*this);
      }

      inline void Intersection::clone(const Intersection & rhs)
      {
        m_isp       = rhs.m_isp; 
        m_dist      = rhs.m_dist; 
        m_pPrimitive = rhs.m_pPrimitive; 
        m_pPath     = rhs.m_pPath; 
        m_primitiveIndex = rhs.m_primitiveIndex;
        m_vertexIndices = rhs.m_vertexIndices;
      }

      inline const dp::math::Vec3f & Intersection::getIsp() const
      {
        return m_isp;
      }

      inline float Intersection::getDist() const
      {
        return m_dist;
      }

      inline const dp::sg::core::PrimitiveSharedPtr & Intersection::getPrimitive() const
      {
        return m_pPrimitive;
      }

      inline dp::util::SmartPtr<dp::sg::core::Path> const & Intersection::getPath() const
      {
        return m_pPath;
      }

      inline unsigned int Intersection::getPrimitiveIndex() const
      {
        return m_primitiveIndex;
      }
  
      inline const std::vector<unsigned int> & Intersection::getVertexIndices() const
      {
        return m_vertexIndices;
      }

      //! RayIntersectTraverser
      /** A \a RayIntersectTraverser is a specialized traverser that calculates 
        * the intersections of a given ray that passes through the scene.
        * It does \b NOT consider face culling modes.
        * \note If you add new geometry objects classes to SceniX you must also derive from this class and 
        *  add an operator for this object to handle the intersection calculation.
        * \note If you create a special kind of transformation node you also have to 
        *  take care of the transformation stack in this class. 
        * \note Needs a valid ViewState. Call setViewState prior to apply().*/
      class RayIntersectTraverser : public SharedModelViewTraverser
      {
        public:
          //! Default constructor.
          DP_SG_ALGORITHM_API RayIntersectTraverser(void);

          //! Release all resources.
          /** By releasing all resources we can use this traverser for the 
            * next intersection calculation. */
          DP_SG_ALGORITHM_API void release();

          //! Set the ray for the intersection test.
          /** Sets a world-space ray along which to pick. The ray is defined as a world space 
            * \a origin point and \a direction vector. The direction vector must be normalized. */
          DP_SG_ALGORITHM_API void setRay( const dp::math::Vec3f &origin      //!< World space origin
                              , const dp::math::Vec3f &dir         //!< Direction of the ray - must be normalized!
                              );

          //! Enable/disable camera plane clipping. 
          /** Enabling camera plane clipping forces the traverser to calculate only 
            * intersections that lie in between the camera's clip planes.
              \note
              if the RayIntersectTraverser is applied before the scene is rendered
              and the camera has been changed since the latest rendering,
              then this mode may yield incorrect results because the clip
              planes wouldn't have gotten a chance to re-adapt to the new camera
              settings*/
          DP_SG_ALGORITHM_API void setCamClipping( bool b    //!< true = enable clipping 
                                      );

          //! Get the nearest intersection.
          /** \returns The nearest intersection regarding the rays origin. */
          DP_SG_ALGORITHM_API const Intersection & getNearest( void ) const;
      
          //! Get intersections.
          /** \returns All intersections along the ray. */
          DP_SG_ALGORITHM_API const Intersection * getIntersections( void ) const;
      
          //! Get number of intersections.
          /** \returns The number of intersections along the ray. */
          DP_SG_ALGORITHM_API unsigned int getNumberOfIntersections( void ) const;

          //! Set the viewport size for intersection calculations with lines and points
          /** \note Both width and height have to be positive. */
          DP_SG_ALGORITHM_API void setViewportSize( unsigned int width, unsigned int height );

      
        protected:
          //! Default destructor.
          DP_SG_ALGORITHM_API virtual ~RayIntersectTraverser(void);

          //! Apply the traverser to the scene.
          /** Start the intersection calculation of the given 
            * ray with the scene objects. */
          DP_SG_ALGORITHM_API virtual void  doApply( const dp::sg::core::NodeSharedPtr & root );

          // Nodes in the tree:
          DP_SG_ALGORITHM_API virtual void handleGeoNode( const dp::sg::core::GeoNode *gnode );

          // Groups in the tree:
          DP_SG_ALGORITHM_API virtual void handleBillboard( const dp::sg::core::Billboard * p);
          DP_SG_ALGORITHM_API virtual void handleGroup( const dp::sg::core::Group * group);
          DP_SG_ALGORITHM_API virtual void handleLOD( const dp::sg::core::LOD * lod);
          DP_SG_ALGORITHM_API virtual void handleSwitch( const dp::sg::core::Switch * swtch);
          DP_SG_ALGORITHM_API virtual void handleTransform( const dp::sg::core::Transform * p);

          // Other operators:
          DP_SG_ALGORITHM_API virtual void handlePrimitive( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handlePoints( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void checkAPoint( const dp::sg::core::Primitive * p, const dp::math::Vec3f & v, unsigned int );
          DP_SG_ALGORITHM_API virtual void handleLines( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleLineStrip( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleLineLoop( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleTriangles( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleTriangleStrip( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleTriangleFan( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleQuads( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handleQuadStrip( const dp::sg::core::Primitive * p );
          DP_SG_ALGORITHM_API virtual void handlePatches( const dp::sg::core::Primitive * p );

          /*! \brief Store the active clip planes of \a p for later usage.
           *  \param p A pointer to the constant Group to get the active clip planes from.
           *  \return The result of ModelViewTraverser::preTraverseGroup().
           *  \sa postTraverseGroup */
          DP_SG_ALGORITHM_API virtual bool preTraverseGroup( const dp::sg::core::Group *p );

          /*! \brief Restore the set of active clip planes to the set before entering \a p.
           *  \param p A pointer to the constant Group just traversed.
           *  \remarks The clip planes stored in preTraverseGroup are removed.
           *  \sa preTraverseGroup */
          DP_SG_ALGORITHM_API virtual void postTraverseGroup( const dp::sg::core::Group *p );

          //! Handles actions to take between transform stack adjustment and traversal.
          /** Adjusts the ray origin and direction and the camera direction in model space.
            * \return result of the base class (ModelViewTraverser). */
          DP_SG_ALGORITHM_API virtual bool preTraverseTransform( const dp::math::Trafo *p    //!< Trafo of node to traverse next 
                                                    );

          //! Handles stuff to do between traversal and transform stack adjustment.
          /** Readjusts the ray origin and direction and the camera direction in model space. */
          DP_SG_ALGORITHM_API virtual void postTraverseTransform( const dp::math::Trafo *p   //!< Trafo of node that was traversed immediately before this call. 
                                                     );

          /*! \brief Test a point against all active clip planes
           *  \param p A reference to a constant point to test against the clip planes.
           *  \return \c true if p is on the visible side of all active clip planes, otherwise \c false. */
          DP_SG_ALGORITHM_API bool checkClipPlanes( const dp::math::Vec3f & p );

          /*! \brief Test a sphere against all active clip planes
           *  \param p A reference to a constant sphere to test agains the clip planes.
           *  \return \c true if p is at least partially on the visible side of all active clip planes,
           *  otherwise \c false. */
          DP_SG_ALGORITHM_API bool checkClipPlanes( const dp::math::Sphere3f & p );

          //! %Intersection type (bounding sphere).
          /** These are the possible types of intersections between the ray 
            * and the boundingsphere of an object in the scene. These types 
            * are used for the preintersection calculation with the objects 
            * bounding sphere. Regarding the intersection type we can skip 
            * objects. */
          enum ISType { _NONE = 0       //!< No intersection
                      , _BSTANGENT      //!< Tangential intersection
                      , _BSNEAR         //!< Intersection with the front part of the bounding sphere
                      , _BSFAR          //!< Intersection with the back part of the bounding sphere
                      , _BSNEARFAR      //!< Intersection with the front and back part of the bounding sphere 
                      };

          //! Check the current ray for intersection with a \c Sphere3f.
          /** \return true, if the ray intersects \a sphere, otherwise false. */
          DP_SG_ALGORITHM_API bool checkIntersection( const dp::math::Sphere3f &sphere );

          //! Get the intersection point in model coordinates.
          /** \returns the point of intersection in model coordinates */
          DP_SG_ALGORITHM_API dp::math::Vec3f getModelIntersection( float dist  //!< Input: modelspace distance between the ray origin and the point of intersection
                                                     );     

          //! Get the intersection point in world coordinates.
          /** \returns the point of intersection in world coordinates */
          DP_SG_ALGORITHM_API dp::math::Vec3f getWorldIntersection( const dp::math::Vec3f& misp  //!< Input: the point of intersection, in model coordinates
                                                     );

          //!Check if the intersection point is within the camera's clips planes.
          /** \return true: intersection is within the camera's clip planes, false: intersection is outside of the camera's clip planes */
          DP_SG_ALGORITHM_API bool isClipped( const dp::math::Vec3f& isp   //!< Input: The point of intersection, in world coordinates
                                 , const dp::math::Vec3f& misp  //!< Input: The point of intersection, in model coordinates
                                 );

          //! Intersect with a box.
          /** This methods tells if it intersects a box or not.
            * It also calculates the intersection point between a box and a ray and the distance of
            * the intersection from the origin of the ray.
            * \returns true: intersection in front of the ray origin, false: no such intersection */
          DP_SG_ALGORITHM_API bool intersectBox( const dp::math::Vec3f &p0   //!< lower left front point of box
                                    , const dp::math::Vec3f &p1   //!< upper right back point of box
                                    , dp::math::Vec3f &isp        //!< Result: intesection point (world space)
                                    , float &dist               //!< Result: distance form camera to intersection
                                    );

          //! Intersect with line.
          /** This method tells if it intersects the line or not. 
            * It also calculates the intersection point between line and ray and the distance 
            * of the intersection from the origin of the ray.
            * \returns true: intersection in front of the ray origin, false: no such intersection */
          DP_SG_ALGORITHM_API bool intersectLine( const dp::math::Vec3f & v0  //!< First vertex of the line
                                     , const dp::math::Vec3f & v1  //!< Second vertex of the line
                                     , float width                 //!< line width
                                     , dp::math::Vec3f & isp       //!< Result: intersection point (world space)
                                     , float & dist              //!< Result: distance from camera to intersection
                                     );    

          //! Intersect with point.
          /** This method tells if it intersects the point or not. 
            * It also calculates the intersection point between point and ray and the distance 
            * of the intersection from the origin of the ray.
            * \returns true: intersection in front of the ray origin, false: no such intersection */
          DP_SG_ALGORITHM_API bool intersectPoint( const dp::math::Vec3f & v0  //!< vertex of the point
                                      , float size                  //!< point size
                                      , dp::math::Vec3f & isp       //!< Result: intersection point (world space)
                                      , float & dist              //!< Result: distance from camera to intersection
                                      );    

          //! Intersect with triangle.
          /** This method tells if it intersects the triangle or not. 
            * It also calculates the intersection point between triangle and ray and the distance 
            * of the intersection from the origin of the ray.
            * \returns true: intersection in front of the ray origin, false: no such intersection */
          DP_SG_ALGORITHM_API bool intersectTriangle( const dp::math::Vec3f & v0  //!< First vertex of the triangle
                                         , const dp::math::Vec3f & v1  //!< Second vertex of the triangle
                                         , const dp::math::Vec3f & v2  //!< Third vertex of the triangle
                                         , dp::math::Vec3f & isp       //!< Result: intersection point (world space)
                                         , float & dist              //!< Result: distance from camera to intersection
                                         );    

          //! Store the intersection point \a isp.
          /** If the point isn't clipped, it is stored to the intersection list.  */
          DP_SG_ALGORITHM_API void storeIntersection( const dp::sg::core::Primitive *p       //!< Primitive that holds the intersection
                                         , const dp::math::Vec3f &isp      //!< Intersection point
                                         , float dist                    //!< Distance from camera to intersection
                                         , unsigned int primitiveIndex   //!< Index of the intersected primitive
                                         , const std::vector<unsigned int> & vertexIndices //!< Indices of the vertices of the intersected primitive
                                         );

    #if !defined(NDEBUG)
          /** Dump intersection map - for Debug*/
          DP_SG_ALGORITHM_API void dumpIntersectionList();
    #endif

        private:
          void checkLine( const dp::sg::core::Primitive * p, const dp::sg::core::Buffer::ConstIterator<dp::math::Vec3f>::Type &vertices
                        , unsigned int i0, unsigned int i1, unsigned int pi );
          void checkQuad( const dp::sg::core::Primitive * p, const dp::sg::core::Buffer::ConstIterator<dp::math::Vec3f>::Type &vertices
                        , unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3, unsigned int pi );
          void checkTriangle( const dp::sg::core::Primitive * p, const dp::sg::core::Buffer::ConstIterator<dp::math::Vec3f>::Type &vertices
                            , unsigned int i0, unsigned int i1, unsigned int i2, unsigned int pi );
          bool equal( const dp::math::Vec3f & v0, const dp::math::Vec3f & v1, float width ) const;

          bool continueTraversal(unsigned int hints, const dp::math::Sphere3f& bs);
       
          static const dp::math::Vec3f _RAY_ORIGIN_DEFAULT;    //!< Default value: (0.f, 0.f,  0.f)
          static const dp::math::Vec3f _RAY_DIRECTION_DEFAULT; //!< Default value: (0.f, 0.f, -1.f)

          bool                          m_camClipping;      //!< true: use camera far/near clipping planes

          std::stack<std::vector<dp::sg::core::ClipPlaneSharedPtr> > m_clipPlanes;   //!< vector of active clip planes
          dp::util::SmartPtr<dp::sg::core::Path>  m_curPath;          //!< Current path.
          std::vector<Intersection>     m_intersectionList; //!< Intersection list containing all intersections.
          std::stack<dp::math::Vec3f>   m_msRayOrigin;      //!< stack of Origin point of the ray in model space
          std::stack<dp::math::Vec3f>   m_msRayDir;         //!< stack of Direction of the ray in model space
          std::stack<dp::math::Vec3f>   m_msCamDir;         //!< stack of camera direction in model space
          unsigned int                  m_nearestIntIdx;    //!< Index of the nearest z intersection.
          dp::math::Vec3f               m_rayOrigin;        //!< Origin point of the ray - default (0,0,0)
          dp::math::Vec3f               m_rayDir;           //!< Direction of the ray - default (0,0,-1)
          std::stack<float>             m_scaleFactors;
          unsigned int                  m_viewportHeight;
          unsigned int                  m_viewportWidth;
          float                         m_currentLineWidth;
          float                         m_currentPointSize;
          std::vector<unsigned int>     m_currentHints;
      };

      inline void RayIntersectTraverser::setCamClipping(bool flag)
      {
        m_camClipping = flag;
      }

      inline unsigned int RayIntersectTraverser::getNumberOfIntersections() const
      {
        return( dp::util::checked_cast<unsigned int>(m_intersectionList.size()) );
      }

      inline const Intersection & RayIntersectTraverser::getNearest() const
      {
        DP_ASSERT(!m_intersectionList.empty());
        return m_intersectionList[m_nearestIntIdx];
      }
   
      inline const Intersection * RayIntersectTraverser::getIntersections() const
      {
        DP_ASSERT(!m_intersectionList.empty());
        return &m_intersectionList[0];
      }

    } // namespace algorithm
  } // namespace sp
} // namespace dp
