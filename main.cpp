#include <iostream>
#include <vector>
#include <fstream>

#include <dlib/clustering.h>
#include <dlib/rand.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>

using namespace std;
using namespace dlib;

typedef matrix<double, 2, 1> sample_type;
typedef radial_basis_kernel<sample_type> kernel_type;

bool get_data( std::istream& istr, sample_type& st )
{
    std::string v1;
    if( !std::getline( istr, v1, ';' ) )
        return false;
    st( 0 ) = std::stold( v1 );

    std::string v2;
    if( !std::getline( istr, v2 ) )
        return false;
    st( 1 ) = std::stold( v2 );

    return true;
}


int main( int ac, char* av[] )
{
    int ret = 0;
    try
    {
        std::istream& istr = std::cin;
        if( ac != 2 )
            throw std::runtime_error( "need tone args!" );

        int count_centers = std::atol( av[1] );
        if( count_centers <= 0 )
            throw std::runtime_error( "count_centers need positive not zero number!" );

        kcentroid<kernel_type> kc( kernel_type( 0.05 ), 0.01, 15 );

        kkmeans<kernel_type> test( kc );

        std::vector<sample_type> samples;
        std::vector<sample_type> initial_centers;

        sample_type st;
        while( get_data( istr, st ) )
        {
            samples.emplace_back( st );
        }

        test.set_number_of_centers( count_centers );
        pick_initial_centers( count_centers, initial_centers, samples, test.get_kernel() );
        test.train( samples, initial_centers );

        for( auto& s : samples )
        {
            cout << s( 0 ) << ';' << s( 1 ) << ";cluster" << test( s ) + 1 << '\n';
        }
    }
    catch( const std::exception& err )
    {
        cerr << err.what() << '\n';
        ret = 1;
    }

    return ret;
}


