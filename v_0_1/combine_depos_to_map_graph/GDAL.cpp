#include <bits/stdc++.h>

#include "ogrsf_frmts.h"

#include "gdal_priv.h"
#include "cpl_conv.h"
#include "gdal.h"
#include "cpl_string.h"
#include <ogr_geometry.h>

//using namespace gml;

int main(){

	/*
	GDALAllRegister();
	
	GDALDataset *poDS;
	poDS = (GDALDataset*) GDALOpenEx("estonia-latest.osm.pbf", GDAL_OF_VECTOR, NULL, NULL, NULL);
	if( poDS == NULL )
	{
		printf( "Open failed.\n" );
		exit( 1 );
	}
	*/
	
	/*
	SpatialReference defaultGeoSys = new SpatialReference(""); 
    defaultGeoSys.SetWellKnownGeogCS("EPSG:4326"); 

    //define a circle using point and buffer         
    string pointlineString = "POINT (" + longitude + " " + latitude + ")"; 
    Geometry center = OGR.Ogr.CreateGeometryFromWkt(ref pointlineString, defaultGeoSys); 
    Geometry bufferDefn = center.Buffer(radiusInMiles, 10000); 
    Geometry bufferDefnPolygon = bufferDefn.GetGeometryRef(0); 

    Geometry actualCircle = Ogr.ForceToPolygon(bufferDefnPolygon);
    */    
    
    double latitude = 59.422727501;
    double longitude = 24.750652313;
    
    char* pszWKT;
    std::string pointlineString = (char*) "POINT (" + std::to_string(longitude) + " " + std::to_string(latitude) + ")";
	pszWKT = (char*) pointlineString.c_str();
	
	OGRGeometry *centerOfCircle;
	OGRGeometryFactory::createFromWkt( &pszWKT, NULL, &centerOfCircle );
	//= ogr.CreateGeometryFromWkt(ref pointlineString, GeoSys);
	/*
	OGRGeometry bufferDefination = centerOfCircle.Buffer(radiusInMiles, 100);
	OGRGeometry bufferDefnPolygonRef = bufferDefination.GetGeometryRef(0);
	OGRGeometry realCircle = Ogr.ForceToPolygon(bufferDefnPolygonRef);
	*/
	std::cout << centerOfCircle->getGeometryType() << "\n";
    
	return 0;
}
