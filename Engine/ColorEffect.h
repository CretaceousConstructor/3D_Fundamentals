#pragma once

#include "Point4.h"
#include "Vec3.h"
#include "Triangle.h"
class ColorEffect {
public:
	ColorEffect() = default;
	class Ps {
	public:
		Ps() = default;
		template<typename T>
		Color operator()(const T& in) const {
			return Color(in.color);
		}
	};
	class Vs {
	public:
		Vs() = default;
		template <typename T>
		T operator()(const T& in) const {
			return in;
		}
		class vIn {
		public:
			vIn() = default;
			/*vIn(Pointf4 a);
			vIn(const vIn& rhs);
			vIn operator+(const vIn& rhs) const;
			vIn& operator+= (const vIn& rhs);
			vIn  operator-(const vIn& rhs)const;
			vIn& operator-=(const vIn& rhs);
			vIn  operator* (const float rhs) const;
			vIn& operator*= (const float rhs);
			vIn& operator= (const vIn& rhs);
			*/
			

			vIn(Pointf4 a)
				:p(a)
			{
			}
			vIn(const vIn& rhs)
				: p(rhs.p)
			{
			}

			vIn operator+(const vIn& rhs) const
			{
				return vIn(*this) += rhs;
			}

			vIn& operator+=(const vIn& rhs)
			{
				p += rhs.p;
				return *this;
			}

			vIn operator-(const vIn& rhs) const
			{
				return vIn(*this) -= rhs;
			}

			vIn& operator-=(const vIn& rhs)
			{
				p -= rhs.p;
				return *this;
			}

			vIn operator*(const float rhs) const
			{
				return vIn(*this) *= rhs;
			}

			vIn& operator*=(const float rhs)
			{
				p *= rhs;
				return *this;
			}

			vIn& operator=(const vIn& rhs)
			{
				p = rhs.p;
				return *this;
			}
			Pointf4 p;

		};
		typedef vIn vOut;
	};
	class Gs {
	public:
		typedef Vs::vOut vIn;
		Gs() = default;
		class vOut {
		public:
			vOut() = default;
			/*vOut(Pointf4 a, Vec3 c);
			vOut(const vOut& rhs);
			vOut operator+(const vOut& rhs) const;
			vOut& operator+= (const vOut& rhs);
			vOut  operator-(const vOut& rhs)const;
			vOut& operator-=(const vOut& rhs);
			vOut  operator* (const float rhs) const;
			vOut& operator*= (const float rhs);
			vOut& operator= (const vOut& rhs);*/

			Pointf4 p;
			Vec3 color;
			 vOut(Pointf4 a, Vec3 c)
				:p(a),
				color(c)
			{
			}
			 vOut(const vOut& rhs)
				: p(rhs.p),
				color(rhs.color)
			{
			}
			vOut  operator+(const vOut& rhs) const
			{
				return vOut(*this) += rhs;
			}

			vOut&  operator+=(const vOut& rhs)
			{
				p += rhs.p;
				color += rhs.color;

				return *this;
			}
			vOut vOut ::operator-(const vOut& rhs) const
			{
				return vOut(*this) -= rhs;
			}

			vOut&  operator-=(const vOut& rhs)
			{
				p -= rhs.p;
				color -= rhs.color;
				return *this;
			}


			vOut  operator*(const float rhs) const
			{
				return vOut(*this) *= rhs;
			}

			vOut&  operator*=(const float rhs)
			{
				p *= rhs;

				color *= rhs;
				return *this;
			}

			vOut&  operator=(const vOut& rhs)
			{
				p = rhs.p;
				color = rhs.color;
				return *this;
			}



		};

		template <typename T>
		_Triangle<vOut> operator()(const T& v0, const T& v1, const T& v2, const int triangle_index) const {

			return
			{
				vOut{v0.p,toVec3(triangle_colors[triangle_index / 2])},
				vOut{v1.p,toVec3(triangle_colors[triangle_index / 2])},
				vOut{v2.p,toVec3(triangle_colors[triangle_index / 2])}
			};
		}


		void BindColors(std::vector<Color> colorList) {
			triangle_colors = colorList;
		}
	private:
		std::vector<Color> triangle_colors;
	};

};