#include <iostream>
#include <vector>
#include <fstream>

#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>
#include <dlib/image_saver/image_saver.h>

#include "optimal_visualize_size.h"

using namespace dlib;

using matrixd_2_1 = matrix<double, 2, 1>;

std::vector< std::pair<matrixd_2_1, uint32_t> > read_data( const std::string& path )
{
    std::ifstream f( path, std::ios::binary );
    if( !f )
        throw std::runtime_error( "not open file:" + path );

    std::vector< std::pair<matrix<double, 2, 1>, uint32_t> > data;
    while( !f.eof() )
    {
        matrixd_2_1 m;

        std::string v;
        if( !std::getline( f, v, ';' ) )
            break;
        m( 0 ) = std::stod( v );

        if( !std::getline( f, v, ';' ) )
            break;
        m( 1 ) = std::stod( v );

        if( !std::getline( f, v ) )
            break;

        std::string number = v.substr( sizeof( "cluster" ) - 1 );
        data.emplace_back( std::make_pair( m, std::stod( number ) ) );
    }
    return data;
}

std::vector<matrixd_2_1> get( const std::vector< std::pair<matrixd_2_1, uint32_t> >& src )
{
    std::vector<matrixd_2_1> res( src.size() );
    std::transform( src.begin(), src.end(), res.begin(), []( const auto& v )
    { return v.first; } );

    return res;
}

uint32_t get_count_claster( const std::vector< std::pair<matrixd_2_1, uint32_t> >& src )
{
    auto res = std::max_element( src.begin(), src.end(), 
        []( const auto& v, const auto& r ){ return v.second < r.second; } );

    return res->second;
}

std::vector<rgb_pixel> generate_color_by_cluster( uint32_t count_cluster )
{
    std::vector<rgb_pixel> colors;
    for( uint32_t i = 0; i < count_cluster; ++i )
    {
        colors.emplace_back( rgb_pixel( std::rand() % 255, std::rand() % 255, std::rand() % 255 ) );
    }

    return colors;
}

int main( int ac, char* av[] )
{
    try
    {
        if( ac < 2 )
            throw std::runtime_error( "incorect count arguments:input_data output_file_image [xy_size]" );

        std::string input = av[1];
        std::string output = av[2];
        int size = 800;
        if( ac > 3 )
            size = std::stoll( av[3] );

        auto data = read_data( input );
        auto count_clusters = get_count_claster( data );

        array2d<rgb_pixel> img( size, size - 2 );
        image_window win;
        win.set_title( "win1" );
        assign_all_pixels( img, 0 );
        auto param = calculate( get(data), size );
        auto colors = generate_color_by_cluster( count_clusters );
        for( int i = 0; i < data.size(); ++i )
        {
            auto& v = data[i].first;
            auto num_cluser = data[i].second;

            point p( param.shift - 1 );
            p += v * param.scale;

            draw_line( img, p, p, colors[num_cluser-1] );
        }

        save_bmp( img, output );
    }
    catch( const std::exception& err )
    {
        std::cerr << err.what() << '\n';
        return 1;
    }

    return 0;
}