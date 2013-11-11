#pragma once

class point_3d
{
    public:
		double x;
		double y;
		double z;

		point_3d();
		point_3d(double const new_x, double const new_y, double const new_z);
        point_3d(const point_3d& rhv);
		point_3d operator+(const point_3d& second) const;
		point_3d operator-(const point_3d& second) const;
		point_3d operator*(double const second) const;
		point_3d operator/(double const second) const;
		point_3d& operator+=(const point_3d& second);
		point_3d& operator-=(const point_3d& second);
		point_3d& operator*=(double const second);
		point_3d& operator/=(double const second);
};


double abs(point_3d a);