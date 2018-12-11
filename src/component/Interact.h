#ifndef INTERACT_H_
#define INTERACT_H_

#include "Component.h"

struct Interact : public IComponent<Interact> {

	Interact(){}

	Interact(const float &minX, const float &minY, const float &minZ,
			  const float &maxX, const float &maxY, const float &maxZ)
			  : minExtents(glm::vec3(minX, minY, minZ)),
			   	maxExtents(glm::vec3(maxX, maxY, maxZ))
	{};

	Interact(const glm::vec3 &maxExtents, const glm::vec3 &minExtents)
			  : minExtents(minExtents),
				maxExtents(maxExtents)
	{};

    Interact(std::ifstream &stream)
               : minExtents(glm::vec3(0.0f)),
 			   	 maxExtents(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Explode Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false);
        do {
            std::string buffer;
            std::string var;
            std::string value;
            stream >> std::ws;
            if(std::getline(stream, buffer)) {
                std::istringstream ss(buffer);
				if(!firstAcc && buffer == "{")
                    firstAcc = true;
                else if (firstAcc && buffer == "}")
                    lastAcc = true;
                else if(std::getline(ss, var, '=')) {
					if (var == "minExtents") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            minExtents = glm::vec3(v1, v2, v3);
                        }
                    }
					else if (var == "maxExtents") {
						if(std::getline(ss, value, '=')) {
							float v1, v2, v3;
							sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
							maxExtents = glm::vec3(v1, v2, v3);
						}
					}
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

	void initCorners(const glm::vec3 &min, const glm::vec3 &max) {
	    corners[0] = min;
	    corners[1] = glm::vec3(min.x, min.y, max.z);
	    corners[2] = glm::vec3(min.x, max.y, min.z);
	    corners[3] = glm::vec3(max.x, min.y, min.z);
	    corners[4] = glm::vec3(min.x, max.y, max.z);
	    corners[5] = glm::vec3(max.x, min.y, max.z);
	    corners[6] = glm::vec3(max.x, max.y, min.z);
	    corners[7] = max;
	}

	glm::vec3 halfExtents;
	glm::vec3 minExtents, maxExtents;
	glm::vec3 corners[8];

};

#endif
