#pragma once
#include "Point4.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Triangle.h"
#include "Mat4.h"

class PerPixelEffect {
public:
	PerPixelEffect() = default;

	class Vs {
	public:
		Vs() = default;

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

			vOut(Pointf4 a, Vec4 b,Pointf4 c)
				:p(a),
				normal(b),
				worldSpace(c)
			{
			}
			vOut(const vOut& rhs)
				: p(rhs.p),
				normal(rhs.normal),
				worldSpace(rhs.worldSpace)
			{
			}

			vOut operator+(const vOut& rhs) const
			{
				return vOut(*this) += rhs;
			}

			vOut& operator+=(const vOut& rhs)
			{
				p += rhs.p;
				normal += rhs.normal;
				worldSpace += rhs.worldSpace;
				return *this;
			}

			vOut operator-(const vOut& rhs) const
			{
				return vOut(*this) -= rhs;
			}

			vOut& operator-=(const vOut& rhs)
			{
				p -= rhs.p;
				normal -= rhs.normal;
				worldSpace -= rhs.worldSpace;
				return *this;
			}

			vOut operator*(const float rhs) const
			{
				return vOut(*this) *= rhs;
			}

			vOut& operator*=(const float rhs)
			{
				p *= rhs;
				normal *= rhs;
				worldSpace *= rhs;
				return *this;
			}

			vOut& operator=(const vOut& rhs)
			{
				p = rhs.p;
				normal = rhs.normal;
				worldSpace = rhs.worldSpace;
				return *this;
			}

			Pointf4 p;
			Vec4 normal;
			Pointf4 worldSpace;
		};


		template <typename T>
		vOut operator()( const T& in) const {

			Pointf4 p = in.p;
			Vec4 n = in.normal;

			//n.Normalize();

			return vOut{p,n,p};
		}


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

	};
	class Ps {
	public:
		Ps() = default;
		template<typename T>
		Color operator()(const T& in) const {

			Vec3 n{ in.normal.x,in.normal.y,in.normal.z };

			n.Normalize();
			Vec3 direction = Vec3{ in.worldSpace.x,in.worldSpace.y,in.worldSpace.z } -lightPosition;
			float dis = direction.Len();
			direction /= dis;
			float attenuation = 1.f / (quadradic_attenuation * dis * dis + linear_attenuation * dis + constant_attenuation);

			float costheta = std::max(((n)) * direction, 0.f);

			Vec3 Rhat = n * (n * direction) * 2.f  - direction;



			Vec3 world{ in.worldSpace.x,in.worldSpace.y,in.worldSpace.z };
			//*2.f


			float nonSence = ((Rhat.GetNormalized()) * (world.GetNormalized()));

			auto s = lightColor * specular_intensity * std::pow(std::max(0.f, nonSence), specular_power);

			auto d = lightColor * attenuation * costheta;

			
			


			Vec3 c = Vec3::GetHadamard(surfaceColor, ( d + s  + abientLight).Saturate() * 255.f);

			//char buffer[100];
			//sprintf_s(buffer, "attenuation times costheta %f\n", attenuation*costheta);

			//OutputDebugStringA(buffer);
	
			return (Color)c;
		}


		static constexpr float specular_intensity = 4.5f;
		static constexpr float specular_power = 6.f;
		Vec3 lightPosition = { 0.f,0.f,-3.f };
		Vec3 originLightPosition = { 0.f,0.f,-3.f };
		const Vec3 lightColor = { 1.f,1.f,1.f };
		const Vec3 surfaceColor = { 0.1f,1.f,1.f };
		const Vec3 abientLight = { 0.3f,0.3f,0.3f };
		float linear_attenuation = 1.5f;
		float quadradic_attenuation = 2.619f;
		float constant_attenuation = 0.5;
	};

};