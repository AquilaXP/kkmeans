#pragma once

#include <map>
#include <vector>

#include <dlib/geometry/vector.h>


// возращает пару с минимальными координатами и максимальными
std::pair<dlib::dpoint, dlib::dpoint> max_min_coordxy( const std::vector<dlib::matrix<double, 2, 1>>& points )
{
    dlib::dpoint min_xy;
    dlib::dpoint max_xy;
    auto res_x =
        std::minmax_element( points.begin(), points.end(),
            []( const auto& p, const auto& res )
    { return p( 0 ) < res( 0 ); } );
    min_xy( 0 ) = ( *( res_x.first ) )( 0 );
    max_xy( 0 ) = ( *( res_x.second ) )( 0 );

    auto res_y =
        std::minmax_element( points.begin(), points.end(),
            []( const auto& p, const auto& res )
    { return p( 1 ) < res( 1 ); } );
    min_xy( 1 ) = ( *( res_y.first ) )( 1 );
    max_xy( 1 ) = ( *( res_y.second ) )( 1 );

    return std::make_pair( min_xy, max_xy );
}

struct param_shift_and_scale
{
    dlib::dpoint shift = { 0.0, 0.0 };
    double scale = { 0.0 };
};

param_shift_and_scale calculate( const std::vector<dlib::matrix<double, 2, 1>>& points, double max_dist )
{
    auto minmax_xy = max_min_coordxy( points );
    param_shift_and_scale param;

    double dist_x = minmax_xy.second( 0 ) - minmax_xy.first( 0 );
    double dist_y = minmax_xy.second( 1 ) - minmax_xy.first( 1 );

    double dist = ( std::max )( dist_x, dist_y );
    param.scale = max_dist / dist;

    param.shift = -dlib::dpoint( minmax_xy.first ) * param.scale;

    return param;
}