#pragma once

class point_3d
{
    public:
		double x;
		double y;
		double z;

		point_3d();
		point_3d(double new_x, double new_y, double new_z);
        point_3d(point_3d& rhv);
		point_3d operator+(point_3d& const second) const;
		point_3d operator-(point_3d& const second) const;
		point_3d operator*(double second) const;
		point_3d operator/(double second) const;
		point_3d& operator+=(point_3d& const second);
		point_3d& operator-=(point_3d& const second);
		point_3d& operator*=(double second);
		point_3d& operator/=(double second);
};


double abs(point_3d a);