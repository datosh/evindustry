#pragma once

#include <vector>

namespace eve
{
	struct material_s
	{
		material_s(int quantity, int type_id) :
			quantity(quantity), type_id(type_id) { };

		int quantity;
		int type_id;
	};

	struct product_s
	{
		product_s(int quantity, int type_id) :
			probability(1), quantity(quantity), type_id(type_id) { };
		product_s(double probability, int quantity, int type_id) :
			probability(probability), quantity(quantity), type_id(type_id) { };

		double probability;
		int quantity;
		int type_id;
	};

	struct skill_s
	{
		skill_s(int level, int type_id) :
			level(level), type_id(type_id) { };

		int level;
		int type_id;
	};

	struct copying_s
	{
		std::vector<material_s> materials;
		std::vector<skill_s> skills;
		int time;
	};

	struct invention_s
	{
		std::vector<material_s> materials;
		std::vector<product_s> products;
		std::vector<skill_s> skills;
		int time;
	};

	struct manufacturing_s
	{
		std::vector<material_s> materials;
		std::vector<product_s> products;
		std::vector<skill_s> skills;
		int time;
	};

	struct research_material_s
	{
		std::vector<material_s> materials;
		std::vector<skill_s> skills;
		int time;
	};

	struct research_time_s
	{
		std::vector<material_s> materials;
		std::vector<skill_s> skills;
		int time;
	};

	struct activities_s
	{
		struct copying_s copying;
		struct invention_s invention;
		struct manufacturing_s manufacturing;
		struct research_material_s research_material;
		struct research_time_s research_time;
	};

	struct blueprint_s
	{
		// This comes from blueprints.yaml
		struct activities_s activities;
		int production_limit;

		// This comes from typeIDs.yaml
		int id;
		double base_price;
		int gfx_id;
		int group_id;
		int market_group_id;
		std::string name;
		int portion_size;
		bool published;
		double volume;
	};
}