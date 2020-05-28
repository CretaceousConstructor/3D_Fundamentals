#pragma once
#include "Point4.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Triangle.h"


class PointLightEffect {
public:
	PointLightEffect() = default;

	class Vs {
	public:
		Vs() = default;
		class vOut;
		template <typename T>
		vOut operator()(const T& in) const {


			Vec3 n{ in.normal.x,in.normal.y,in.normal.z };

			Vec3 direction = Vec3{ in.p.x,in.p.y,in.p.z } - lightPosition;

			float dis = direction.Len();

			direction /= dis;




			float attenuation = 1.f / (quadradic_attenuation * dis * dis  + linear_attenuation * dis + constant_attenuation);
			float costheta = std::max(((-n.GetNormalized())) * direction, 0.f);



			Vec3 c = Vec3::GetHadamard(surfaceColor, ((lightColor * attenuation * costheta + abientLight)).Saturate() * 255.f);

			return { in.p,c };
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

			vOut(Pointf4 a, Vec3 b)
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
				p = rhs.p;
				c = rhs.c;
				return *this;
			}

			vOut operator+(const vOut& rhs) const
			{
				return vOut(*this) += rhs;
			}

			vOut& operator+=(const vOut& rhs)
			{
				p += rhs.p;
				c += rhs.c;

				return *this;
			}

			vOut operator-(const vOut& rhs) const
			{
				return vOut(*this) -= rhs;
			}

			vOut& operator-=(const vOut& rhs)
			{
				p -= rhs.p;
				c -= rhs.c;

				return *this;
			}

			vOut operator*(const float rhs) const
			{
				return vOut(*this) *= rhs;
			}

			vOut& operator*=(const float rhs)
			{
				p *= rhs;
				c *= rhs;

				return *this;
			}


			Pointf4 p;
			Vec3 c;
		};


		Vec3 lightPosition = { 0.f,0.f,-3.f };
		Vec3 originLightPosition = { 0.f,0.f,-3.f };
		const Vec3 lightColor = { 1.f,1.f,1.f };
		const Vec3 surfaceColor = { 1.f,1.f,1.f };
		const Vec3 abientLight = { 0.2f,0.2f,0.2f };

		float linear_attenuation = 0.5f;
		float quadradic_attenuation = 0.619f;
		float constant_attenuation = 0.2;




	};
	class Gs {
	public:

		typedef Vs::vOut vIn;
		typedef Vs::vOut vOut;
		Gs() = default;

		template <typename T>
		_Triangle<vOut> operator()(const T& v0, const T& v1, const T& v2, const int triangle_index) const {
			return{ v0,v1,v2 };
		}


		//	void BindColors(std::vector<Color> colorList) {
		//		triangle_colors = colorList;
		//	}
		//private:
		//	std::vector<Color> triangle_colors;
	};
	class Ps {
	public:
		Ps() = default;
		template<typename T>
		Color operator()(const T& in) const {
			return (Color)in.c;
		}
	};

};