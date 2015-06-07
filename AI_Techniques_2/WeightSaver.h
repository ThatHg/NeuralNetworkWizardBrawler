#ifndef WEIGHT_SAVER_H
#define WEIGHT_SAVER_H

#include <vector>

class WeightSaver
{
public:
	WeightSaver();
	~WeightSaver();
	WeightSaver(const WeightSaver& weightS);
	WeightSaver& operator=(const WeightSaver& weightS);

	bool Load();
	bool Save(const std::vector<double>& weights);
	const std::vector<double>& GetWeights() const;
private:
	std::vector<double> m_weights;
};

#endif