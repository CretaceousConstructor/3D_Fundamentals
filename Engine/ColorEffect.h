#pragma once

#include "Point4.h"
#include "Vec3.h"
#include "Triangle.h"
class ColorEffect {
public:
	ColorEffect() = default;

	class Vs {
	public:
		Vs() = default;
		class vOut;
		template <typename T>
		vOut operator()(const T& in) const {

		
			Vec3 n{ in.normal.x,in.normal.y,in.normal.z };
			float costheta = ((-n.GetNormalized())) * (lightDirection.GetNormalized());


			Vec3 c = Vec3::GetHadamard(surfaceColor, ((lightColor * costheta + abientLight)).Saturate() * 255.f);
			return { in.p,(Color)c };
		}

		class vIn {
		public:
			vIn() = default;

			vIn(Pointf4 a, Vec4 b)
				:p(a),
				normal(b)
			{
			}
			vIn(const vIn& rhs)
				: p(rhs.p),
				normal(rhs.normal)
			{
			}

			vIn operator+(const vIn& rhs) const
			{
				return vIn(*this) += rhs;
			}

			vIn& operator+=(const vIn& rhs)
			{
				p += rhs.p;
				normal += rhs.normal;
				return *this;
			}

			vIn operator-(const vIn& rhs) const
			{
				return vIn(*this) -= rhs;
			}

			vIn& operator-=(const vIn& rhs)
			{
				p -= rhs.p;
				normal -= rhs.normal;
				return *this;
			}

			vIn operator*(const float rhs) const
			{
				return vIn(*this) *= rhs;
			}

			vIn& operator*=(const float rhs)
			{
				p *= rhs;
				normal *= rhs;
				return *this;
			}

			vIn& operator=(const vIn& rhs)
			{
				p = rhs.p;
				normal = rhs.normal;
				return *this;
			}

			Pointf4 p;
			Vec4 normal;
		};

		class vOut {
		public:
			vOut() = default;

			vOut(Pointf4 a, Color b)
				:p(a),
				c(b)
			{
			}
			vOut(const vOut& rhs)
				: p(rhs.p),
				c(rhs.c)
			{
			}

			vOut& operator=(const vOut& rhs)
			{
				c = rhs.c;
				p = rhs.p;
				return *this;
			}

			vOut operator+(const vOut& rhs) const
			{
				return vOut(*this) += rhs;
			}

			vOut& operator+=(const vOut& rhs)
			{
				p += rhs.p;

				return *this;
			}

			vOut operator-(const vOut& rhs) const
			{
				return vOut(*this) -= rhs;
			}

			vOut& operator-=(const vOut& rhs)
			{
				p -= rhs.p;

				return *this;
			}

			vOut operator*(const float rhs) const
			{
				return vOut(*this) *= rhs;
			}

			vOut& operator*=(const float rhs)
			{
				p *= rhs;

				return *this;
			}


			Pointf4 p;
			Color c;
		};


		Vec3 lightDirection = { 0.f,0.f,-1.f };
		const Vec3 originLightDirection = { 0.f,0.f,-1.f };
		const Vec3 lightColor = { 0.1f,0.2f,0.8f };
		const Vec3 surfaceColor = { 1.f,1.f,1.f };
		const Vec3 abientLight = { 0.2f,0.2f,0.2f };


	};
	class Gs {
	public:

		typedef Vs::vOut vIn;
		typedef Vs::vOut vOut;
		Gs() = default;
		/*class vOut {
		public:
			vOut() = default;

			Pointf4 p;
			Pointf4 normal;
			Vec3 color;
			vOut(Pointf4 a, Vec3 c, Pointf4 n)
				:p(a),
				color(c),
				normal(n)
			{
			}
			vOut(const vOut& rhs)
				: p(rhs.p),
				color(rhs.color),
				normal(rhs.normal)
			{
			}
			vOut  operator+(const vOut& rhs) const
			{
				return vOut(*this) += rhs;
			}

			vOut& operator+=(const vOut& rhs)
			{
				p += rhs.p;
				color += rhs.color;
				normal += rhs.normal;

				return *this;
			}
			vOut vOut ::operator-(const vOut& rhs) const
			{
				return vOut(*this) -= rhs;
			}

			vOut& operator-=(const vOut& rhs)
			{
				p -= rhs.p;
				color -= rhs.color;
				normal -= rhs.normal;
				return *this;
			}


			vOut  operator*(const float rhs) const
			{
				return vOut(*this) *= rhs;
			}

			vOut& operator*=(const float rhs)
			{
				p *= rhs;
				color *= rhs;
				normal *= rhs;
				return *this;
			}

			vOut& operator=(const vOut& rhs)
			{
				p = rhs.p;
				color = rhs.color;
				normal = rhs.normal;
				return *this;
			}



		};*/


		template <typename T>
		_Triangle<vOut> operator()(const T& v0, const T& v1, const T& v2, const int triangle_index) const {
			return{ v0,v1,v2 };
		}


		void BindColors(std::vector<Color> colorList) {
			triangle_colors = colorList;
		}
	private:
		std::vector<Color> triangle_colors;
	};
	class Ps {
	public:
		Ps() = default;
		template<typename T>
		Color operator()(const T& in) const {
			return in.c;
		}
	};
};
