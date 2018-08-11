// C++ Standard Libraries
#include <cmath>
#include <iostream>
#include "data_types.h"

//#include "haversine.cpp"
/**
 * Vincenty Distance
*/
double Vincenty_Distance( const double& latitude_01, const double& longitude_01,
                          const double& latitude_02, const double& longitude_02,
                          const double& a,
                          const double& b )
{
    // Flattening
    const double f = (a-b)/a;

    // tan U1
    const double tan_U1 = (1-f) * std::tan(latitude_01);
    const double tan_U2 = (1-f) * std::tan(latitude_02);

    // Longitudinal Distance
    const double cos_U1 = 1 / std::sqrt(1 + tan_U1 * tan_U1);
    const double cos_U2 = 1 / std::sqrt(1 + tan_U2 * tan_U2);
    const double sin_U1 = tan_U1 * cos_U1;
    const double sin_U2 = tan_U2 * cos_U2;

    // Iterate until complete
    const double L = longitude_02 - longitude_01;
    double lambda = L;
    double diff, sigma;
    double cos_alpha_sq, cos_2sigma_m;
    double cos_sigma, sin_sigma;

    while( true ){

        // 
        double sin_lambda = std::sin( lambda );
        double cos_lambda = std::cos( lambda );

        double c1 = (cos_U2 * sin_lambda)*(cos_U2 * sin_lambda);
        double c2 = (cos_U1 * sin_U2);
        double c3 = (sin_U1 * cos_U2 * cos_lambda);


        //  sin sigma
        sin_sigma = std::sqrt( c1 + ( c2 - c3 )*( c2 - c3 ) );

        // cos sigma
        cos_sigma = sin_U1 * sin_U2 + cos_U1 * cos_U2 * cos_lambda;

        // sigma
        sigma = std::atan2( sin_sigma, cos_sigma );

        // sin alpha
        double sin_alpha = (cos_U1 * cos_U2 * sin_lambda)/(sin_sigma);

        // cos^2 alpha
        cos_alpha_sq = 1 - (sin_alpha*sin_alpha);

        // cos^2 2sigmam
        cos_2sigma_m = cos_sigma - (2 * sin_U1 * sin_U2)/(cos_alpha_sq);

        // C
        double C = (f/16.0) * cos_alpha_sq * (4 + f * (4 - 3 * cos_alpha_sq));

        // Update Lambda
        diff = lambda;
        lambda = L + (1-C) * f * sin_alpha * (sigma + C * sin_sigma * ( cos_2sigma_m + C * cos_sigma * (-1 + 2 * cos_2sigma_m*cos_2sigma_m)));
        diff = lambda - diff;
        if( std::fabs(diff) < 0.00001 ){ break; }
    }

    // U2
    double u_sq = cos_alpha_sq  * (a*a - b*b)/(b*b);

    // Compute A, B
    double A = 1 + (u_sq/16384) * (4096 + u_sq * (-768 + u_sq * (320 - 175 * u_sq)));

    double B = (u_sq / 1024) * (256 + u_sq * (-128 + u_sq * (-128 + u_sq * (74 - 47 * u_sq))));

    // Sigma
    double cos_2sigma_m_sq = cos_2sigma_m * cos_2sigma_m;
    double delta_sigma = B * sin_sigma * ( cos_2sigma_m + (B/4.0) * (cos_sigma * (-1 * 2 * cos_2sigma_m_sq ) - (B/6.0) * cos_2sigma_m * (-3 + 4 * sin_sigma*sin_sigma) * (-3 + 4 * cos_2sigma_m_sq)));

    // Distance
    double s = b * A * (sigma - delta_sigma);
    return s;
}

/**
 * @brief Main Function
 */
double vincenty_distance(double latitude_01, double longitude_01, double latitude_02, double longitude_02)
{

    // Set our coordinates
    latitude_01  = latitude_01 * M_PI / 180.0;
    longitude_01 = longitude_01 * M_PI / 180.0;

    latitude_02 =  latitude_02 * M_PI / 180.0;
    longitude_02 = longitude_02 * M_PI / 180.0;

    // Set the datum components
    const double a = 6378137.0;
    const double b = 6356752.314245;

    // Vincenty Distance
    double distance = Vincenty_Distance( latitude_01, longitude_01,
                                         latitude_02, longitude_02,
                                         a, b);

    // Distance
    //std::cout << std::fixed << "Vincety distance: " << distance << std::endl;
	//std::cout << "Haversine distance: " << haversine_distance(latitude_01, longitude_01, latitude_02, longitude_02) << std::endl;
    // Exit
    return distance;
}

double vincenty_distance(std::pair<double, double> point1, std::pair<double, double> point2)
{

	double latitude_01 = point1.first;
	double longitude_01 = point1.second;
	double latitude_02 = point2.first;
	double longitude_02 = point2.second;
	
    // Set our coordinates
    latitude_01  = latitude_01 * M_PI / 180.0;
    longitude_01 = longitude_01 * M_PI / 180.0;

    latitude_02 =  latitude_02 * M_PI / 180.0;
    longitude_02 = longitude_02 * M_PI / 180.0;

    // Set the datum components
    const double a = 6378137.0;
    const double b = 6356752.314245;

    // Vincenty Distance
    double distance = Vincenty_Distance( latitude_01, longitude_01,
                                         latitude_02, longitude_02,
                                         a, b);

    return distance;
}

double vincenty_distance(road my_road)
{

	std::pair<double, double> point1 = my_road.first;
	std::pair<double, double> point2 = my_road.second;

	double latitude_01 = point1.first;
	double longitude_01 = point1.second;
	double latitude_02 = point2.first;
	double longitude_02 = point2.second;
	
    // Set our coordinates
    latitude_01  = latitude_01 * M_PI / 180.0;
    longitude_01 = longitude_01 * M_PI / 180.0;

    latitude_02 =  latitude_02 * M_PI / 180.0;
    longitude_02 = longitude_02 * M_PI / 180.0;

    // Set the datum components
    const double a = 6378137.0;
    const double b = 6356752.314245;

    // Vincenty Distance
    double distance = Vincenty_Distance( latitude_01, longitude_01,
                                         latitude_02, longitude_02,
                                         a, b);

    return distance;
}

/*
*   \brief Ellipsoid Inverse Flattening constant
*
*   298.2572235636654651
*   \remarks WGS84 Ellipsoid constant
*/
const double kInverseFlattening = 298.2572235636654651;

/*
*   \brief Ellipsoid Flattening constant
*
*   Approximately 0.00335281
*   \remarks WGS84 Ellipsoid constant
*/
const double kFlattening = 1.0 / kInverseFlattening;

 /*
*   \brief Ellipsoid Semi Major Axis
*
*   6378137.0
*   \remarks WGS84 Ellipsoid constant
*/
const double kSemiMajorAxis = 6378137.0;

/*
*   \brief Ellipsoid Semi Minor Axis
*
*   Approximately 6356752.314245
*   \remarks WGS84 Ellipsoid constant
*/
const double kSemiMinorAxis = kSemiMajorAxis * (1 - kFlattening);

#define M_2PI M_PI * 2.0

/*
*   \brief Epsilon
*   \returns double epsilon of 0.5e-15.
*   \note Order 8260.54A Appendix 2, 3.3 Tolerances, states
*   "Empirical studies have shown that eps = 0.5e-13 and
*   tol = 1.0-e9 work well."
*
*   When implementing the TerpsTest validation application
*   eps must be set to 0.5e-15 for all tests to pass. If
*   set as stated in section 3.3 of 8260.54A then the
*   Tangent Fixed Radius Arc and Locus Tan Fixed Radius Arc
*   fails validation.
*
*/
const double kEps = 0.5e-15;

std::pair<double, double> vincenty_location(std::pair<double, double> &pt, double brng, double dist)
{
    double s = dist;
    double alpha1 = brng;
    double sinAlpha1 = sin(alpha1);
    double cosAlpha1 = cos(alpha1);

    double tanU1 = (1.0 - kFlattening) * tan(pt.first);
    double cosU1 = 1.0 / sqrt((1.0 + tanU1 * tanU1));
    double sinU1 = tanU1 * cosU1;
    double sigma1 = atan2(tanU1, cosAlpha1);
    double sinAlpha = cosU1 * sinAlpha1;
    double cosSqAlpha = 1.0 - sinAlpha * sinAlpha;
    double uSq = cosSqAlpha * (kSemiMajorAxis * kSemiMajorAxis - kSemiMinorAxis * kSemiMinorAxis) /
                 (kSemiMinorAxis * kSemiMinorAxis);
    double A = 1.0 + uSq / 16384.0 * (4096.0 + uSq * (-768.0 + uSq * (320.0 - 175.0 * uSq)));
    double B = uSq / 1024.0 * (256.0 + uSq * (-128.0 + uSq * (74.0 - 47.0 * uSq)));

    double sigma = s / (kSemiMinorAxis * A);
    double sigmaP = M_2PI;
    double sinSigma = sin(sigma);
    double cosSigma = cos(sigma);
    double cos2SigmaM = cos(2.0 * sigma1 + sigma);
    int iterLimit = 0;
    while (fabs(sigma - sigmaP) > kEps && ++iterLimit < 100)
    {
        cos2SigmaM = cos(2.0 * sigma1 + sigma);
        sinSigma = sin(sigma);
        cosSigma = cos(sigma);
        double cos2SigmaSq = cos2SigmaM * cos2SigmaM;
        double deltaSigma = B * sinSigma * (cos2SigmaM + B * 0.25 * (cosSigma * (-1.0 + 2.0 * cos2SigmaSq) -
                                                                     B / 6.0 * cos2SigmaM *
                                                                     (-3.0 + 4.0 * sinSigma * sinSigma) *
                                                                     (-3.0 + 4.0 * cos2SigmaSq)));

        sigmaP = sigma;
        sigma = s / (kSemiMinorAxis * A) + deltaSigma;
    }

    double tmp = sinU1 * sinSigma - cosU1 * cosSigma * cosAlpha1;
    double lat2 = atan2(sinU1 * cosSigma + cosU1 * sinSigma * cosAlpha1,
                        (1.0 - kFlattening) * sqrt(sinAlpha * sinAlpha + tmp * tmp));
    double lambda = atan2(sinSigma * sinAlpha1, cosU1 * cosSigma - sinU1 * sinSigma * cosAlpha1);
    double C = kFlattening / 16.0 * cosSqAlpha * (4.0 + kFlattening * (4.0 - 3.0 * cosSqAlpha));
    double L = lambda - (1.0 - C) * kFlattening * sinAlpha *
                        (sigma +
                         C * sinSigma * (cos2SigmaM + C * cosSigma * (-1.0 + 2.0 * cos2SigmaM * cos2SigmaM)));

    return std::make_pair(lat2, pt.second + L);
}

/*std::pair<double, double> vincenty_location_2(std::pair<double, double> &pt, double brng, double dist)
{
	
}*/
