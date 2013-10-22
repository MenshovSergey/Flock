
class point_3d
{
    public:
		double x;
		double y;
		double z;
		point_3d()
		{
			x = 0;
			y = 0;
			z = 0;
		}
		point_3d(double new_x, double new_y, double new_z)
		{
			x = new_x;
			y = new_y;
			z = new_z;
		}
		point_3d operator+(point_3d& const second) const
		{
			point_3d res(x + second.x, y + second.y, z + second.z);
			return res;
		}
		point_3d operator-(point_3d& const second) const
		{
			point_3d res(x - second.x, y - second.y, z - second.z);
			return res;
		}
		point_3d operator*(double second) const
		{
			point_3d res(x * second, y * second, z * second);
			return res;
		}
		point_3d operator/(double second) const
		{
			point_3d res(x / second, y / second, z / second);
			return res;
		}

		point_3d operator+=(point_3d& const second)
		{
			x += second.x;
			y += second.y;
			z += second.z;
			return this*;
		}
		point_3d operator-=(point_3d& const second)
		{
			x -= second.x;
			y -= second.y;
			z -= second.z;
			return this*;
		}
		point_3d operator*=(double second)
		{
			x *= second.x;
			y *= second.y;
			z *= second.z;
			return this*;
		}
		point_3d operator/=(double second)
		{
			x /= second.x;
			y /= second.y;
			z /= second.z;
			return this*;
		}
}