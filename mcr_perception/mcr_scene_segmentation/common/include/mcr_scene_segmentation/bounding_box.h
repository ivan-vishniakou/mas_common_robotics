/*
 * Copyright 2016 Bonn-Rhein-Sieg University
 *
 * Author: Sergey Alexandrov
 *
 */
#ifndef MCR_SCENE_SEGMENTATION_BOUNDING_BOX_H
#define MCR_SCENE_SEGMENTATION_BOUNDING_BOX_H

#include <vector>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <mcr_scene_segmentation/aliases.h>

class BoundingBox
{
public:
    typedef Eigen::Vector3f Point;
    typedef std::vector<Point, Eigen::aligned_allocator<Point> > Points;

    inline const Point& getCenter() const
    {
        return center_;
    }

    inline const Points& getVertices() const
    {
        return vertices_;
    }

    inline Eigen::Vector3f getDimensions() const
    {
        return dimensions_;
    }

    inline float getVolume() const
    {
        return dimensions_[0] * dimensions_[1] * dimensions_[2];
    }

    /** Create a bounding box around the cloud, restricting it to be parallel to
      * the plane defined by the normal. */
    static BoundingBox create(const typename PointCloud::ConstPtr& cloud,
                              const Eigen::Vector3f& normal);

    /** Create a bounding box around the point vector, restricting it to be
      * parallel to the plane defined by the normal. */
    static BoundingBox create(const typename PointCloud::VectorType& points,
                              const Eigen::Vector3f& normal);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
    Point center_;
    Points vertices_;
    Eigen::Vector3f dimensions_;
};

#endif  // MCR_SCENE_SEGMENTATION_BOUNDING_BOX_H
