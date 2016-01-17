#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

class Blueprint
{
public:
	Blueprint(int copy_time, int manufacturing_time);
	~Blueprint();

	std::string to_string();

	friend std::ostream &operator<<(std::ostream &output, const Blueprint &bp)
	{
		output << 
			"Copy Time = " << bp.copy_time << std::endl <<
			"Manufacturing Time = " << bp.manufacturing_time << std::endl;

		return output;
	}

private:
	int copy_time;
	int manufacturing_time;
};

Blueprint::Blueprint(int copy_time, int manufacturing_time) : 
	copy_time(copy_time), 
	manufacturing_time(manufacturing_time)
{
	// Empty
}

Blueprint::~Blueprint()
{
	// Empty
}

std::string Blueprint::to_string()
{
	return std::to_string(copy_time) + std::to_string(manufacturing_time);
}

class BlueprintParser
{
public:
	BlueprintParser(std::string path);
	~BlueprintParser();

	Blueprint create_bp_by_id(int id);

private:

	YAML::Node basenode;
};

BlueprintParser::BlueprintParser(std::string path)
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

BlueprintParser::~BlueprintParser()
{
	// Empty
}

Blueprint BlueprintParser::create_bp_by_id(int id)
{
	auto yaml_bp = basenode[std::to_string(id)];
	int copy_time = yaml_bp["activities"]["copying"]["time"].as<int>();
	int manufacturing_time = yaml_bp["activities"]["manufacturing"]["time"].as<int>();
	return Blueprint(copy_time, manufacturing_time);
}

class ItemParser
{
public:
	ItemParser(std::string path);
	~ItemParser();

	int get_blueprint_id(std::string name);
	
private:
	const std::string language{"en"};

	YAML::Node basenode;
};

ItemParser::ItemParser(std::string path)
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

ItemParser::~ItemParser()
{
	// Empty
}

int ItemParser::get_blueprint_id(std::string name)
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

int main()
{
	ItemParser ip{"data/typeIDs.yaml"};
	BlueprintParser bp{"data/blueprints.yaml"};

	int id = ip.get_blueprint_id("Stabber Blueprint");

	std::cout << "Stabber is: " << id << std::endl;

	Blueprint stabber_bp = bp.create_bp_by_id(id);

	std::cout << stabber_bp << std::endl;

	return 0;
}