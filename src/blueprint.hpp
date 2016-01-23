#pragma once

#include <iostream> // operator<<
#include <vector>

#include "parsing_structs.hpp"
#include "item.hpp"

namespace eve
{
	class blueprint
	{
	public:
		typedef struct blueprint_s data_t;

		data_t& get_data() { return data; }

		friend std::ostream &operator<<(std::ostream &output, const blueprint &bp)
		{
			output <<
				bp.data.name << " " << std::endl <<
				"type_id=" << bp.data.id << std::endl <<
				"manu_time=" << bp.data.activities.manufacturing.time << std::endl <<
				"copy_time=" << bp.data.activities.copying.time << std::endl <<
				"research_material_time=" << bp.data.activities.research_material.time << std::endl <<
				"research_time_eff_time=" << bp.data.activities.research_time.time << std::endl <<
				"base_price=" << bp.data.base_price << std::endl <<
				"volume=" << bp.data.volume <<
				std::endl;

			return output;
		}

	private:
		data_t data;
	};
}