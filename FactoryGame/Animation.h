#pragma once
#include "SFML\Graphics.hpp"
#include <functional>
#include <list>
#include <memory>

class Anim
{
public:
	enum Type
	{
		Linear,
		EndStep,
		StartStep,
		FastStart,
		SlowStart
	};

	static std::list<std::shared_ptr<Anim>> ANIMATIONS;

	Anim(double finishTime,Type type) :finishTime(finishTime), timePased(0),type(type) {}
	~Anim() {};

	virtual void step(double delta) = 0;

	double getTimePassed() { return timePased; }
	double getProcess() { return timePased / finishTime; }
	bool isDone() { return itIsDone; }

protected:
	double timePased;
	double finishTime;
	Type type;

	bool itIsDone = false;
};


template <typename T>
class Animation : public Anim
{
public:


	Animation(std::function<void(T)> settingFunction, T from, T to, double finishIn, Anim::Type type)
		:Anim(finishIn,type)
		, settingFunction(settingFunction)
		, fromValue(from)
		, toValue(to)
	{
		step(0);
	}

	~Animation() {}

	virtual void step(double delta);

private:

	std::function<void(T)> settingFunction;
	T fromValue;
	T toValue;

};

template<typename T, typename O>
sf::Vector2<T> operator*(const sf::Vector2<T> &left, const O &right)
{
	return left * (T)right;
}

template<typename T>
void Animation<T>::step(double delta)
{
	if (isDone())
		return;

	timePased += delta;

	double process = getProcess();

	if (process >= 1)
	{
		itIsDone = true;
		settingFunction(toValue);
		return;
	}
	
		T newValue;

		switch (type)
		{
		default:
		case Anim::Type::Linear:
			newValue = ((toValue - fromValue)*process) + fromValue;
			break;

		case Anim::Type::EndStep:
			newValue = fromValue;
			break;

		case Anim::Type::StartStep:
			newValue = toValue;
			break;
		case Anim::Type::FastStart:
			newValue = ((toValue - fromValue)* (-(process*process) + (2 * process))) + fromValue;
			break;
		case Anim::Type::SlowStart:
			newValue = ((toValue - fromValue)* (process*process)) + fromValue;
			break;
		}
	
	settingFunction(newValue);

}

