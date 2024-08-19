#pragma once
#include <vector>
#include <iostream>
#include <Eigen\Eigen>
#include <OpenMesh/Core/Geometry/VectorT.hh>

typedef Eigen::Vector3d Point3;
typedef Eigen::Vector4d Point4;

class BezierCurve
{
public:
	BezierCurve();  
	BezierCurve(int deg, double tmin, double tmax, std::vector<double>w, std::vector<Point3> controlpoints);
	BezierCurve(int deg, double tmin, double tmax, std::vector<Point3> controlpoints);
	~BezierCurve();

	void SetDegree(const int deg) { degree = deg; }
	void SetParameterSpan(const double min, const double max) { t_min = min; t_max = max; }
	void SetRational(const bool is_rational) { isRational = is_rational; }
	void SetWeights(const std::vector<double> w) { weights.clear(); weights = w; isRational = true; }
	void SetControlPoints(const std::vector<Point3> & points) { ctrlpoints.clear(); ctrlpoints = points; }

	const int GetDegree(void) const { return degree; }
	const void GetParameterSpan(double &min, double &max) const {  min = t_min; max = t_max; }
	const bool GetRational(void) const { return isRational; }
	const std::vector<double> GetWeights(void) const { return weights; }
	const std::vector<Point3> GetControlPoints(void) const { return ctrlpoints; }

	Point3 operator()(const double t) const { return DeCasteljau(t); }

	template<typename T>
	T DeCasteljau(const std::vector<T> &controlpoints, const double t)const
	{
		if (t < t_min || t > t_max) return T();
		double t_ = (t - t_min) / (t_max - t_min);

		std::vector<T> d(controlpoints);
		for (int j = 1; j <= degree; j++)
		{
			for (int i = 0; i <= degree - j; i++)
			{
				d[i] = (1 - t_) * d[i] + t_ * d[i + 1];
			}
		}
		return d[0];
	}

	template<typename T>
	T Derivative(const std::vector<T> &controlpoints, const double t, const int k) const
	{
		// k: kth derivative
		if (t < t_min || t > t_max) return T();
		std::vector<T> d(controlpoints);
		if (k > degree) return T();

		for (int j = 1; j <= k; j++)
		{
			for (int i = 0; i <= degree - j; i++)
			{
				d[i] = (degree - j + 1) / (t_max - t_min) * (d[i + 1] - d[i]);
			}
		}
		std::vector<T> dev_ctrlpts(d.begin(), d.end() - k);

		BezierCurve dev_Curve;
		dev_Curve.SetDegree(degree - k);
		dev_Curve.SetParameterSpan(t_min, t_max);

		return dev_Curve.DeCasteljau(dev_ctrlpts, t);
	}


	Point3 DeCasteljau(const double t)const;
	Point3 Derivative(const double t) const;
	Point3 Derivative2(const double t) const;

	void Split(double t, BezierCurve &left_c, BezierCurve &right_c);
	
	/******************************************/
	bool SaveControlPoints(const std::string & filename) const;
	bool LoadControlPoints(const std::string & filename);
	//计算曲线的弧长,detel_x是积分的步长
	double Calculated_arc_length(double detel_x) {
		double result = 0.0;
		double x = t_min;
		Point3 C_t;
		while (x < t_max) {
			C_t = Derivative(x);
			x += detel_x;
			result += C_t.norm() * detel_x;
		}
		x -= detel_x;
		result -= Derivative(x).norm() * (x+detel_x-t_max);
		return result;
	}
private:
	int degree;
	double t_min;
	double t_max;	
	bool isRational;
	std::vector<double> weights;
	std::vector<Point3> ctrlpoints;
};
