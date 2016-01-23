#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"
#include "blueprint.hpp"

/* --- BLUEPRINT PARSER --- */

class blueprint_parser
{
public:
	/* Typedefs */
	// Used for the path from an particular value from the basenode
	typedef std::vector<std::string> yaml_path;

	// Constructor
	blueprint_parser(std::string path);
	// Destructor
	~blueprint_parser();

	// Returns a new instance of an eve::blueprint using the typeID to find the bp.
	void get_bp_by_id(int id, eve::blueprint& bp);

private:
	
	YAML::Node basenode;
};

blueprint_parser::blueprint_parser(std::string path)
{
	std::cout << "Loading blueprints into memory..." << std::endl;
	basenode = YAML::LoadFile(path);
	if(basenode)
	{
		std::cout << "Blueprints successfully loaded into memory!" << std::endl;
	}
	else
	{
		std::cerr << "Error loading blueprints into memory!" << std::endl;
	}
}

blueprint_parser::~blueprint_parser()
{
	// Empty
}

void blueprint_parser::get_bp_by_id(int id, eve::blueprint& bp)
{
	// Get reference to the data struct were gonna fill
	auto& data = bp.get_data();

	// Get the basenode of the blueprint
	auto yaml_bp = basenode[std::to_string(id)];

	// Parsing ACTIVITIES
	if(auto yaml_act = yaml_bp["activities"])
	{
		// Fill in copy values
		if(auto yaml_copy = yaml_act["copying"])
		{
			// Fill in copy-materials
			if(auto yaml_mat = yaml_copy["materials"])
			{
				for(auto tuple : yaml_mat)
				{
					if(tuple && tuple["quantity"] && tuple["typeID"])
					{
						data.activities.copying.materials.emplace_back(
							tuple["quantity"].as<int>(),
							tuple["typeID"].as<int>());
					}
				}
			}
			// Fill in copy-skills
			if(auto yaml_skill = yaml_copy["skills"])
			{
				for(auto tuple : yaml_skill)
				{
					if(tuple && tuple["level"] && tuple["typeID"])
					{
						data.activities.copying.skills.emplace_back(
							tuple["level"].as<int>(), 
							tuple["typeID"].as<int>());
					}
				}	
			}
			// Fill in copy-time
			if(auto yaml_time = yaml_copy["time"])
			{
				data.activities.copying.time = yaml_time.as<int>();
			}
		}
		// Fill in Manufacturing values
		if(auto yaml_manu = yaml_act["manufacturing"])
		{
			//Fill in manu-materials
			if(auto yaml_mat = yaml_manu["materials"])
			{
				for(auto tuple : yaml_mat)
				{
					if(tuple && tuple["quantity"] && tuple["typeID"])
					{
						data.activities.manufacturing.materials.emplace_back(
							tuple["quantity"].as<int>(),
							tuple["typeID"].as<int>());
					}
				}
			}
			// Fill in Manufacturing products
			if(auto yaml_prod = yaml_manu["products"])
			{
				for(auto tuple : yaml_prod)
				{
					if(tuple && tuple["quantity"] && tuple["typeID"])
					{
						data.activities.manufacturing.products.emplace_back(
							tuple["quantity"].as<int>(),
							tuple["typeID"].as<int>());
					}
				}
			}
			//Fill in Manufacturing skills
			if(auto yaml_skill = yaml_manu["skills"])
			{
				for(auto tuple : yaml_skill)
				{
					if(tuple && tuple["level"] && tuple["typeID"])
					{
						data.activities.manufacturing.skills.emplace_back(
							tuple["level"].as<int>(), 
							tuple["typeID"].as<int>());
					}
				}
			}
			// Fill in Manufacturing time
			if(auto yaml_time = yaml_manu["time"])
			{
				data.activities.manufacturing.time = yaml_time.as<int>();
			}

			// TODO: RESEARCH, prod limit
			
		}
	}
}

/*
template <typename T>
T blueprint_parser::parse_as<T>(YAML::Node node, std::vector<std::string> path)
{
	for(const auto& next : path)
	{
		node = node[next];
	}
	if(node)
	{
		return node.as<T>();
	}
}
*/

/* --- ITEM PARSER --- */

class item_parser
{
public:
	item_parser(std::string path);
	~item_parser();

	int get_blueprint_id(std::string name);
	void get_bp_by_name(std::string name, eve::blueprint& bp);
	
private:
	const std::string language{"en"};

	YAML::Node basenode;
};

item_parser::item_parser(std::string path)
{
	std::cout << "Loading items into memory..." << std::endl;
	basenode = YAML::LoadFile(path);
	if(basenode)
	{
		std::cout << "Items successfully loaded into memory!" << std::endl;
	}
	else
	{
		std::cerr << "Error loading items into memory!" << std::endl;
	}
}

item_parser::~item_parser()
{
	// Empty
}

int item_parser::get_blueprint_id(std::string name)
{
	for(auto it = basenode.begin(); it != basenode.end(); ++it)
	{
		if(it->second["name"][language] && it->second["name"][language].as<std::string>() == name)
		{
			return it->first.as<int>();
		}
	}
	return -1;
}

void item_parser::get_bp_by_name(std::string name, eve::blueprint& bp)
{
	int id = get_blueprint_id(name);
	auto& data = bp.get_data();
	data.id = id;
	if(auto bp_base = basenode[id])
	{
		if(bp_base["basePrice"]) data.base_price = bp_base["basePrice"].as<double>();
		if(bp_base["graphicID"]) data.gfx_id = bp_base["graphicID"].as<int>();
		if(bp_base["groupID"]) data.group_id = bp_base["groupID"].as<int>();
		if(bp_base["marketGroupID"]) data.market_group_id = bp_base["marketGroupID"].as<int>();
		if(bp_base["name"][language]) data.name = bp_base["name"][language].as<std::string>();
		if(bp_base["portionSize"]) data.portion_size = bp_base["portionSize"].as<int>();
		if(bp_base["published"]) data.published = bp_base["published"].as<bool>();
		if(bp_base["volume"]) data.volume = bp_base["volume"].as<double>();
	}
	else
	{
		std::cerr << 
			"Error: Parsing \"typeIDs.yaml\". Function: get_bp_by_name. Name=\"" << 
			name << "\"" << 
			std::endl;
	}
}

/* --- YAML Parser --- */
class yaml_parser
{
public:
	eve::blueprint get_bp_by_id(int id);
	eve::blueprint get_bp_by_name(std::string name);

private:
	item_parser m_ip{"data/typeIDs.yaml"};
	blueprint_parser m_bp{"data/blueprints.yaml"};
};

eve::blueprint yaml_parser::get_bp_by_id(int id)
{
	return eve::blueprint{};
}

eve::blueprint yaml_parser::get_bp_by_name(std::string name)
{
	eve::blueprint bp{};
	m_ip.get_bp_by_name(name, bp);
	m_bp.get_bp_by_id(bp.get_data().id, bp);
	return bp;
}



/* --- MAIN --- */

int main()
{
	yaml_parser parser;

	// Do the search by name
	std::string bp_to_search{"Stabber Blueprint"};
	auto stabber_bp = parser.get_bp_by_name(bp_to_search);
	std::cout << stabber_bp << std::endl;

	return 0;
}